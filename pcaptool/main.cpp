#include <byte-order-convert.hpp>

struct MAC_PDU_FrameHeader
{
    uint16_t    PH_MARK;
    uint16_t    LEN;

    uint8_t     SLOTID : 4;
    uint8_t     BD_TYPE : 4;

    uint8_t		DST_RFBN : 4;
    uint8_t     DST_BD_TYPE : 3;
    uint8_t     IS_SINGLE_SUBPACKET : 1;

    uint8_t     PCI_8 : 1;
    uint8_t     RFB_DIR : 1;
    uint8_t     REV1 : 2;
    uint8_t     RFBN : 4;

    uint8_t     PCI_7_0;
};

#include <vector>
#include <array>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <chrono>

typedef std::vector<uint8_t> frame_load_t;
void sub_frame_handle(MAC_PDU_FrameHeader &frame_header, frame_load_t &frame_load);
void create_pcap_file(const char *name);
void close_pcap_file();
void add_packet(uint32_t sec, uint32_t usec, uint8_t *tags, uint16_t tags_len, uint8_t *load, uint16_t length);
int main(int argc, char **argv) {
    using namespace std;
    MAC_PDU_FrameHeader frame_header;
    frame_load_t        frame_load;
    uint16_t            frame_length;
    ifstream fin;
    try {
        fin.exceptions(ios::badbit | ios::eofbit | ios::failbit);
        fin.open(argv[1], ios::binary);
        create_pcap_file(argv[2]);
        while (true) {
            fin.read((char *)&frame_header, sizeof(frame_header));
            boc::ntoh((const uint8_t *)&frame_header.LEN, frame_length);
            frame_load.resize(frame_length - sizeof(frame_header));
            fin.read((char *)frame_load.data(), frame_load.size());
            sub_frame_handle(frame_header, frame_load);
        }
    }
    catch (exception & e) {
    }
    return 0;
}

void sub_frame_handle(MAC_PDU_FrameHeader &frame_header, frame_load_t &frame_load) {
    using namespace std;
    uint16_t length, type, load_length;
    uint8_t *sub_frame = frame_load.data();
    uint8_t *sub_load;
    uint32_t sub_time_sec = 0, sub_time_usec = 0;
    boc::ntoh(sub_frame, length);
#if 1   // 文档中描述的
    boc::ntoh(sub_frame + 2, type);
    uint16_t time_mark = type >> 15, lv1t = (type >> 12) & 0x3, lv2tphy = (type >> 8) & 0xf, lv2ttran = (type >> 4) & 0xf, lv2tlogic = type & 0xf;
#else   // 错误的组包方式照成的                                
    type = *(uint16_t *)(sub_frame + 2);
    uint16_t time_mark = type >> 15;
    uint16_t tmp = type;
    boc::ntoh((uint8_t *)&tmp, type);
    uint16_t lv1t = (type >> 12) & 0x3, lv2tphy = (type >> 8) & 0xf, lv2ttran = (type >> 4) & 0xf, lv2tlogic = type & 0xf;
#endif
    type = type & 0x7fff;
    static size_t index = 0;
    index++;
    if (time_mark) {
        boc::ntoh(sub_frame + 4, sub_time_sec);
        boc::ntoh(sub_frame + 8, sub_time_usec);
        sub_load = sub_frame + 12;
        load_length = frame_load.size() - 12;
    }
    else {
        auto now = std::chrono::system_clock::now().time_since_epoch();
        sub_time_sec = now.count() / 1000000000;
        sub_time_usec = now.count() / 1000 % 1000000;
        sub_load = sub_frame + 4;
        load_length = frame_load.size() - 4;
    }
    if (load_length == 0)
    {
        return;
    }
    uint8_t tags[64];
    tags[0] = 1;                        // radiotype   1:FDD 2:TDD
    tags[1] = 1 - frame_header.RFB_DIR; // direction
    uint8_t *curr = tags + 2;
    size_t   tags_len = 2;
    uint8_t  rntitype = 0xFF;
    uint16_t fn = 0;
    uint16_t rnti = 0;
    uint16_t ueid = 0;
    switch (type) {
    case 0x0111: {rntitype = 0; }break;//BCCH
    case 0x0522:break;//PCCH
    case 0x0853:break;//CCCH UL
    case 0x0533:break;//CCCH DL
    case 0x0854:break;//DCCH DL
    case 0x0534:break;//DCCH DL
    case 0x0855:break;//DTCH UL
    case 0x0535:break;//DTCH DL
    case 0x0966:break;//MCCH
    case 0x0967:break;//MTCH
    case 0x0640: {boc::ntoh(sub_load, fn); boc::ntoh(sub_load + 2, rnti); ueid = rnti; rntitype = 2; sub_load += 4; load_length -= 4;  }break;//RACH
    case 0x0300:break;//PHICH
    case 0x0200:break;//PCFICH
    case 0x0400:break;//PDCCH
    case 0x0700:break;//PUCCH
    case 0x0530: {boc::ntoh(sub_load, fn); boc::ntoh(sub_load + 2, rnti); ueid = rnti; if (rnti == 0xFFFF)rntitype = 4; else rntitype = 3; sub_load += 4; load_length -= 4; }break;//DL-SCH
    case 0x0850: {boc::ntoh(sub_load, fn); boc::ntoh(sub_load + 2, rnti); ueid = rnti; rntitype = 3; sub_load += 4; load_length -= 4; }break;//UL-SCH
    default:break;
    }
    if (rntitype == 0xFF)
    {
        return;
    }
    *curr++ = rntitype;             // rnti type        
#define SET_TAG_X08(t,x) {*curr++ = t; *curr++ = x;}
#define SET_TAG_X16(t,x) {*curr++ = t; curr = boc::hton(curr, x);}
    SET_TAG_X16(2, rnti);                   // rnti
    SET_TAG_X16(3, ueid);                   // ueid      
    fn = ((fn & 0x3FF) << 4) | ((fn >> 10) & 0xF);
    SET_TAG_X16(4, fn);                     // fn
    SET_TAG_X08(5, 0);                      // predefine data
    SET_TAG_X08(7, 1);                      // crc stat
#undef SET_TAG_X16
#undef SET_TAG_X08
    *curr++ = 1;                            // load
    tags_len = curr - tags;
    add_packet(sub_time_sec, sub_time_usec, tags, tags_len, sub_load, load_length);
}

#include <pcap/pcap.h>

std::ofstream pcap_f;

void create_pcap_file(const char *name) {
    pcap_f.open(name, std::ios::binary);
    pcap_file_header pf = {};
    pf.linktype = DLT_USER0;
    pf.magic = 0xa1b2c3d4;
    pf.sigfigs = 0;
    pf.snaplen = 0xffff;
    _get_timezone((long *)&pf.thiszone);
    pf.version_major = 2;
    pf.version_minor = 4;
    pcap_f.write((char *)&pf, sizeof(pf));
}

struct mpcap_pkthdr {
    struct mts {
        uint32_t tv_sec;
        uint32_t tv_usec;
    }ts;
    uint32_t caplen;
    uint32_t len;
};

void add_packet(uint32_t sec, uint32_t usec, uint8_t *tags, uint16_t tags_len, uint8_t *load, uint16_t length) {
    if (pcap_f) {
        mpcap_pkthdr pkthdr;
        pkthdr.caplen = tags_len + length;
        pkthdr.len = tags_len + length;
        pkthdr.ts.tv_sec = sec;
        pkthdr.ts.tv_usec = usec;
        pcap_f.write((char *)&pkthdr, sizeof(pkthdr));
        pcap_f.write((char *)tags, tags_len);
        pcap_f.write((char *)load, length);
    }
}
void close_pcap_file() {
    pcap_f.close();
}
