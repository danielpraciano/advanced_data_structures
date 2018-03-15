project(ADV_DS)
cmake_minimum_required(VERSION 3.7.2 FATAL_ERROR)

##== Module directories
set(CoreDir "${CMAKE_SOURCE_DIR}/core")
set(TestDir "${CMAKE_SOURCE_DIR}/test")

subdirs(
    "${CoreDir}"
    "${TestDir}"
)
