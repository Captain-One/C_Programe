cmake_minimum_required(VERSION 3.10)

project(PDCP)

include_directories(./)

aux_source_directory(. PDCPSRCS)
add_library(PDCP SHARED ${PDCPSRCS})
#target_link_libraries(LISTS)
