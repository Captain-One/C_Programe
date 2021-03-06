#############################################################################
#                               uCOS XSDK BSP                               #
#                                                                           #
#        (c) Copyright 2014-2019; Silicon Laboratories Inc.,                #
#               400 W. Cesar Chavez, Austin, TX 78701                       #
#                                                                           #
#  All rights reserved. Protected by international copyright laws.          #
#                                                                           #
# Your use of this software is subject to your acceptance of the terms      #
# of a Silicon Labs Micrium software license, which can be obtained by      #
# contacting info@micrium.com. If you do not agree to the terms of this     #
# license, you may not use this software.                                   #
#                                                                           #
# Please help us continue to provide the Embedded community with the finest #
# software available. Your honesty is greatly appreciated.                  #
#                                                                           #
#   You can find our product's documentation at: doc.micrium.com            #
#                                                                           #
#         For more information visit us at: www.micrium.com                 #
#############################################################################


ARCH_LIBSOURCES:= psua53/ucos_impl.c \
                  psua53/ucos_int_impl.c \
                  psua53/asm_vector.S \
                  psua53/translation_table.S \
                  scugic/ucos_scugic.c \
                  ipi/ucos_int_ipi.c


ARCH_INCLUDEFILES:=psua53/ucos_int_impl.h \
                   psua53/ucos_impl.h \
                   scugic/ucos_scugic.h \
                   ipi/ucos_int_ipi.h
