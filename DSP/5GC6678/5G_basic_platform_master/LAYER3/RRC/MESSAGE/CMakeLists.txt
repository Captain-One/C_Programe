cmake_minimum_required(VERSION 3.10)

project(MESSAGE)

include_directories(./)

#add_subdirectory(asn1c)

aux_source_directory(./ asn1csrcs)

aux_source_directory(./asn1c asn1csrcs)

add_library(RRC-MESSAGE SHARED ${asn1csrcs})
