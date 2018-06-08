
#include "rrc.h"

int RRC_encode(RRC_Sdecode_Result_4_L2 *pinpdu, RRC_Encode_Result_t *result)
{
  uint8_t *enbuf = result->data;
  int rv;
  size_t esize = 0;
  
  rv = RRC_sencode(pinpdu,enbuf,&esize);
  if(rv != 0)
  {
    printf("RRC Encode err!!!\n");
    return -1;
  }  
  result->size = esize;  
  return 0;
}






