cmake_minimum_required(VERSION 3.10)

project(RRC)

include_directories(./)

add_subdirectory(MESSAGE)

aux_source_directory(./ RRCSRCS)

set(rrcs ${RRCSRCS})

#message("${RRCSRCS}")

if(rrcs)
	add_library(RRC SHARED ${RRCSRCS})
	target_link_libraries(RRC RRC-MESSAGE)
endif()
