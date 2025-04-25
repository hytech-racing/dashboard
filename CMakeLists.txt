#-------------------------------------------------------------------------------
# Zephyr Example Application
#
# Copyright (c) 2021 Nordic Semiconductor ASA
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.13.1)

#set(BOARD_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

project(dashboard)
    

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
target_sources(app PRIVATE src/main.c)
target_include_directories(app PRIVATE include)