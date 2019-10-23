cmake_minimum_required(VERSION 3.10)

project(RLC)

include_directories(./ ./AM ./UM ./TM)

add_subdirectory(AM)
add_subdirectory(UM)
add_subdirectory(TM)

aux_source_directory(. RLCSRCS)
add_library(RLC SHARED ${RLCSRCS})
target_link_libraries(RLC AM UM TM)
#target_link_libraries(RLC AM TM)
