
#ifndef _RTXCONTEXT_H_
#define _RTXCONTEXT_H_

#define OSRTENCBUFSIZ 16*1024    /* dynamic encode buffer extent size     */

/**
 * @addtogroup rtxCtxt
 * @{
 */
/* run-time error info structures */

#define OSRTERRSTKSIZ	8	/* error stack size			*/
#define OSRTMAXERRPRM	5	/* maximum error parameters		*/

/**
 * @struct OSRTErrLocn rtContext.h
 * Run-time error location structure
 *
 * This structure is a container structure that holds information on 
 * the location within a C source file where a run-time error occured.
 */
typedef struct {
   const OSUTF8CHAR* module;
   OSINT32	lineno;
} OSRTErrLocn;

/**
 * @struct OSRTErrInfo rtContext.h
 * Run-time error information structure
 *
 * This structure is a container structure that holds information on 
 * run-time errors.  The stack variable holds the trace stack information 
 * that shows where the error occurred in the source code.  The parms 
 * variable holds error parameters that are substituted into the message 
 * that is returned to the user.
 */
typedef struct {
   OSRTErrLocn  stack[OSRTERRSTKSIZ];
   OSINT16      status;
   OSUINT8      stkx;
   OSUINT8      parmcnt;
   OSUTF8CHAR*  parms[OSRTMAXERRPRM];
   OSUTF8CHAR*  elemName;
} OSRTErrInfo;

typedef struct {
   OSRTDList list;              /* list of errors */
   OSRTErrInfo reserved;        /* error info elem, used if nomem to alloc */
   OSRTDListNode reservedNode;  /* node placeholder for errInfo elem       */
} OSRTErrInfoList;

/**
 * @struct OSRTBuffer rtContext.h
 * Run-time message buffer structure
 *
 * This structure holds encoded message data.  For an encode operation, 
 * it is where the message being built is stored.  For decode, it 
 * holds a copy of the message that is being decoded.  
 */
typedef struct {
   OSOCTET*     data;           /* pointer to start of data buffer      */
   size_t       byteIndex;      /* byte index                           */
   size_t       size;           /* current buffer size                  */
   OSINT16      bitOffset;      /* current bit offset (8 - 1)           */
   OSBOOL       dynamic;        /* is buffer dynamic?                   */
   OSBOOL       aligned;        /* is buffer byte aligned?              */
} OSRTBuffer;

typedef OSUINT32 OSRTFLAGS;

/**
 * @struct OSRTBufSave rtContext.h
 * Structure to save the current message buffer state
 *
 * This structure is used to save the current state of the buffer.
 */
typedef struct {
   size_t      byteIndex;      /* byte index                           */
   OSINT16     bitOffset;      /* current bit offset (8 - 1)           */
   OSRTFLAGS   flags;          /* flag bits                            */
} OSRTBufSave;

/* OSRTCTXT flag mask values : bits 32 - 16 are for common flags, bits  */
/* 15 - 0 are reserved for application specific flags                   */

#define OSDIAG          0x80000000  /* diagnostic tracing enabled       */
#define OSTRACE         0x40000000  /* tracing enabled                  */
#define OSDISSTRM       0x20000000  /* disable stream encode/decode     */
#define OSSAVEBUF       0x10000000  /* do not free dynamic encode buffer */

/* Flag mask constant values */

#define ASN1DYNCTXT     0x8000  /* set if context is dynamic            */
#define ASN1INDEFLEN    0x4000  /* set if message is indefinite length  */
#define ASN1TRACE       0x2000  /* enable PER bit tracing               */
#define ASN1LASTEOC     0x1000  /* indicates last parsed item was EOC   */
#define ASN1FASTCOPY    0x0800  /* turns on the "fast copy" mode        */
#define ASN1CONSTAG     0x0400  /* form of last parsed tag              */
#define ASN1CANXER      0x0200  /* canonical XER                        */
#define ASN1OPENTYPE    0x0080  /* item is an open type field           */

/**
 * @struct OSRTCTXT rtContext.h
 * Run-time context structure
 *
 * This structure is a container structure that holds all working 
 * variables involved in encoding or decoding a message.
 */
typedef struct OSCTXT {          /* run-time context block               */
   void*         pMemHeap;       /* internal message memory heap         */
   OSRTBuffer    buffer;         /* data buffer                          */
   OSRTBufSave   savedInfo;      /* saved buffer info                    */
    Asn1SizeCnst *pSizeConstraint;
   //    OSRTErrInfoList errInfo;      /* run-time error info                  */
//    OSUINT32      initCode;       /* code double word to indicate init    */
   OSRTFLAGS     flags;          /* flag bits                            */
   OSOCTET       level;          /* nesting level                        */
//  OSOCTET       state;          /* encode/decode process state          */
//  OSOCTET       spare[2];       /* word boundary padding                */
//  struct OSRTSTREAM* pStream;   /* Stream                               */
//  struct OSRTPrintStream *pPrintStrm; /* Print Stream                   */
//  OSRTDList elemNameStack;      /* element name stack                   */
//  const OSOCTET* key;           /* pointer to run-time key data         */
//  size_t        keylen;         /* run-time key length                  */
//  OSVoidPtr	 pXMLInfo;       /* XML specific info                    */
//  OSVoidPtr	 pASN1Info;      /* ASN.1 specific info                  */
   OSVoidPtr     pUserData;      /* User defined data                    */
} OSCTXT;



/* Macros */
#if (!defined(BREW_MODULE) && !defined(FLAT_BREW))
#define OSCRTLMEMSET    memset
#define OSCRTLMEMCMP    memcmp
#define OSCRTLMEMCPY    memcpy
#define OSCRTLSTRCPY    strcpy
#define OSCRTLSTRNCPY   strncpy
#define OSCRTLSTRCAT    strcat
#define OSCRTLSTRNCAT   strncat
#define OSCRTLSTRCMP    strcmp
#define OSCRTLSTRNCMP   strncmp
#define OSCRTLSTRLEN    strlen
#define OSCRTLMALLOC    malloc
#define OSCRTLREALLOC   realloc
#define OSCRTLFREE      free
#else
#define OSCRTLMEMSET    MEMSET
#define OSCRTLMEMCMP    MEMCMP
#define OSCRTLMEMCPY    MEMCPY
#define OSCRTLSTRCPY    STRCPY
#define OSCRTLSTRNCPY   STRNCPY
#define OSCRTLSTRCAT    STRCAT
#define OSCRTLSTRNCAT   STRNCAT
#define OSCRTLSTRCMP    STRCMP
#define OSCRTLSTRNCMP   STRNCMP
#define OSCRTLSTRLEN    STRLEN
#define OSCRTLMALLOC    MALLOC
#define OSCRTLREALLOC   REALLOC
#define OSCRTLFREE      FREE
#endif

#define OSRTMAX(a,b)        (((a)>(b))?(a):(b))
#define OSRTMIN(a,b)        (((a)<(b))?(a):(b))

#define OSRTBUFCUR(pctxt)   (pctxt)->buffer.data[(pctxt)->buffer.byteIndex]
#define OSRTBUFPTR(pctxt)   &(pctxt)->buffer.data[(pctxt)->buffer.byteIndex]
#define OSRTBUFFER(pctxt)   (pctxt)->buffer.data
#define OSRTBUFSIZE(pctxt)  (pctxt)->buffer.size
#define ASN1BUF_INDEFLEN(cp)    (((cp)->flags&ASN1INDEFLEN)!=0)

#define OSRTPUTCHAR(pctxt,ch) \
(pctxt)->buffer.data[(pctxt)->buffer.byteIndex++]=(OSOCTET)ch;

#define OSRTPUTCHARREV(pctxt,ch) \
(pctxt)->buffer.data[--(pctxt)->buffer.byteIndex]=(OSOCTET)ch;

#define OSRTZTERM(pctxt) \
(pctxt)->buffer.data[(pctxt)->buffer.byteIndex]=(OSOCTET)0;



#define OSRTCHKBUFUTF8LEN(pctxt,lower,upper,stat) \
do { size_t nchars = OSRTGETBUFUTF8LEN (pctxt); \
stat = (nchars >= lower && nchars <= upper) ? 0 : RTERR_CONSVIO; } while(0)

#define HEXCHARTONIBBLE(ch,b) do { \
if (ch >= '0' && ch <= '9') b = (unsigned char)(ch - '0'); \
else if (ch >= 'a' && ch <= 'f') b = (unsigned char)((ch - 'a') + 10); \
else if (ch >= 'A' && ch <= 'F') b = (unsigned char)((ch - 'A') + 10); \
else b = 0xFF; } while(0)

#define NIBBLETOHEXCHAR(b,ch) do { \
if (b >= 0 && b <= 9) ch = (char)(b + '0'); \
else if (b >= 0x0a && b <= 0x0f) ch = (char)((b - 10)+ 'a'); \
else ch = '?'; } while(0)

#define NIBBLETOUCHEXCHAR(b,ch) do { \
if (b >= 0 && b <= 9) ch = (char)(b + '0'); \
else if (b >= 0x0a && b <= 0x0f) ch = (char)((b - 10)+ 'A'); \
else ch = '?'; } while(0)

#define OSRTSAFECONSTCAST(towhere,ptr) ((towhere)((size_t)ptr))

#define OS_WHITESPACE_COLLAPSE 0
#define OS_WHITESPACE_PRESERVE 1
#define OS_WHITESPACE_REPLACE  2

#define OS_ISNULLPTR(ptr) (((const void*)0) == ptr)

#define OSRTISSTREAM(pctxt) \
((pctxt)->pStream != 0 && !((pctxt)->flags & OSDISSTRM))

#define OSRTBUFSAVE(pctxt) { \
(pctxt)->savedInfo.byteIndex = (pctxt)->buffer.byteIndex; \
(pctxt)->savedInfo.flags = (pctxt)->flags; }

#define OSRTBUFRESTORE(pctxt) { \
(pctxt)->buffer.byteIndex = (pctxt)->savedInfo.byteIndex; \
(pctxt)->flags = (pctxt)->savedInfo.flags; }

#define rtxMemAlloc rtxHeapAlloc
#define rtxMemAllocType(pctxt,ctype) (ctype*)rtxHeapAlloc(pctxt,sizeof(ctype))
#define rtxMemAllocTypeZ(pctxt,ctype) (ctype*)rtxHeapAlloc(pctxt,sizeof(ctype))
#define OSCRTLMEMSET memset

#define rtxDListAllocNodeAndData(pctxt, ctype, pnode, pdata1){\
*pdata1=(ctype*)rtxHeapAlloc(pctxt,sizeof(ctype)); \
*pnode=(OSRTDListNode *)rtxHeapAlloc(pctxt,sizeof(OSRTDListNode)); \
*pnode->data=*pdata1; }


#endif
