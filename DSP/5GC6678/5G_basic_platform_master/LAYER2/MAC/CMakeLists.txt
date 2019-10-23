cmake_minimum_required(VERSION 3.10)

project(MAC)

include_directories(./)

aux_source_directory(. MACSRCS)
add_library(MAC SHARED ${MACSRCS})
