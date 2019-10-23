cmake_minimum_required(VERSION 3.10)

project(simulate)

include_directories(./ ../LAYER2/MAC ../LAYER2/RLC ../LAYER2/PDCP ../LAYER2/RLC/AM ../LAYER2/RLC/UM ../LAYER2/RLC/TM)

aux_source_directory(. SIMSRCS)

add_executable(simulate ${SIMSRCS})

target_link_libraries(simulate UTIL MAC RLC PDCP)
