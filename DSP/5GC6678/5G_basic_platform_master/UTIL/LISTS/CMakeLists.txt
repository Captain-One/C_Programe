cmake_minimum_required(VERSION 3.10)

project(LIST)

include_directories(./)

aux_source_directory(. LISTSRCS)
add_library(LIST SHARED ${LISTSRCS})
#target_link_libraries(LISTS)
