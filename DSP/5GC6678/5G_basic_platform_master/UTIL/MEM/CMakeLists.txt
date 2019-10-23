cmake_minimum_required(VERSION 3.10)

project(MEM)

include_directories(./)

aux_source_directory(. MEMSRCS)
add_library(MEM SHARED ${MEMSRCS})
#target_link_libraries(LISTS)
