cmake_minimum_required(VERSION 3.10)

project(TM)

include_directories(./)

aux_source_directory(. TMSRCS)
add_library(TM SHARED ${TMSRCS})
