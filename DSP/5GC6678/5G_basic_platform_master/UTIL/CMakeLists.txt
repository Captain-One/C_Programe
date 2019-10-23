cmake_minimum_required(VERSION 3.10)

project(UTIL)

include_directories(./)

#add_subdirectory(hashtable)
#add_subdirectory(MEM)

aux_source_directory(./ UTILSRCS)
aux_source_directory(./hashtable UTILSRCS)
aux_source_directory(./LISTS UTILSRCS)
aux_source_directory(./MEM UTILSRCS)

add_library(UTIL SHARED ${UTILSRCS})

#target_link_libraries(UTIL hashtable MEM)
