cmake_minimum_required(VERSION 3.10)

project(hashtable)

include_directories(./)

aux_source_directory(. HASHSRCS)
add_library(hashtable SHARED ${HASHSRCS})
#target_link_libraries(LISTS)
