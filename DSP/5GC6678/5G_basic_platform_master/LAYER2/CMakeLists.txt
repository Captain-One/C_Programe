cmake_minimum_required(VERSION 3.10)

project(LAYER2)

include_directories(./ ./MAC ./RLC ./PDCP ./RLC/AM ./RLC/UM ./RLC/TM)

add_subdirectory(MAC)
add_subdirectory(RLC)
add_subdirectory(PDCP)

#add_library(LAYER2 SHARED MAC RLC PDCP)

#target_link_libraries(layer2 MAC RLC PDCP)
