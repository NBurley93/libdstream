cmake_minimum_required(VERSION 3.15)
project(dstream)

add_library(dstream STATIC
    src/DataStream.cc
    src/DataStream.hh
)