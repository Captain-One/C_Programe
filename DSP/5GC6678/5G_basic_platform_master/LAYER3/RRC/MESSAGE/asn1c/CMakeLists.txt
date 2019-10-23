cmake_minimum_required(VERSION 3.10)

project(asn1c-rrc)

include_directories(./)

aux_source_directory(./ asn1csrcs)

add_library(asn1c-rrc SHARED ${asn1csrcs})
