#ifndef __SENDECODE_4_L2_H
#define __SENDECODE_4_L2_H

#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>	/* for atoi(3) */
#include <unistd.h>	/* for getopt(3) */
#include <string.h>	/* for strerror(3) */
#include <sysexits.h>	/* for EX_* exit codes */
#include <errno.h>	/* for errno */
#include <string.h>


#include "asn_application.h"
#include "asn_internal.h"	/* for ASN__DEFAULT_STACK_MAX */

#include "BCCH-BCH-Message.h"
#include "BCCH-BCH-MessageType.h"

#include "BCCH-DL-SCH-Message.h"
#include "BCCH-DL-SCH-MessageType.h"

#include "DL-CCCH-Message.h"
#include "DL-CCCH-MessageType.h"

#include "UL-CCCH-Message.h"
#include "UL-CCCH-MessageType.h"

#include "DL-DCCH-Message.h"
#include "DL-DCCH-MessageType.h"

#include "UL-DCCH-Message.h"
#include "UL-DCCH-MessageType.h"

#include "MCCH-Message.h"
#include "MCCH-MessageType.h"

#include "PCCH-Message.h"
#include "PCCH-MessageType.h"

#include "rrc_sdecode4L2.h"   


typedef struct RRC_Encode_Result{
	unsigned char *data;
	size_t size;
}RRC_Encode_Result_t;

int CYDD_EXPORT RRC_sencode(RRC_Sdecode_Result_4_L2 *input, void *output, size_t *size);


#endif



