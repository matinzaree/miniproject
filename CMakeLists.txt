cmake_minimum_required(VERSION 3.21)
project(prj)

set(CMAKE_CXX_STANDARD 23)

add_executable(prj main.cpp product.h customer.h money.h)
