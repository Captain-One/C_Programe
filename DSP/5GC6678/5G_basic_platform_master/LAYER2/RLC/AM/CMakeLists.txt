cmake_minimum_required(VERSION 3.10)

project(AM)

include_directories(./)

aux_source_directory(. AMSRCS)
add_library(AM SHARED ${AMSRCS})
#target_link_libraries(LISTS)
