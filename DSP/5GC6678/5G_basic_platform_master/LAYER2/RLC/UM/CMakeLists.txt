cmake_minimum_required(VERSION 3.10)

project(UM)

include_directories(./)

aux_source_directory(. UMSRCS)
add_library(UM SHARED ${UMSRCS})
