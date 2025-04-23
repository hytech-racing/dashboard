# Copyright (c) HyTech Racing
# SPDX-License-Identifier: Apache-2.0

board_runner_args(jlink "--device=STM32H723HE" "--speed=4000") #allows flashing and debugging with jlink
board_runner_args(pyocd "--target=stm32h723ve" "--frequency=4000000") #allows flashing and debugging with pyocd

set(OPENOCD_STM32_TARGET "stm32h7x") #TODO: Check
board_runner_args(openocd "--use-elf") #allows for flashing through openocd
board_runner_args(openocd "--cmd-pre-init=source [find target/stm32h7x.cfg]")

include(${ZEPHYR_BASE}/boards/common/nrfjprog.board.cmake)
include(${ZEPHYR_BASE}/boards/common/jlink.board.cmake) #support for jlink runner
include(${ZEPHYR_BASE}/boards/common/pyocd.board.cmake) #support for pyocd runner
include(${ZEPHYR_BASE}/boards/common/openocd.board.cmake) #support for openocd runner


#Template to add more runners alter
#include(${CMAKE_CURRENT_LIST_DIR}/../../common/example_runner.board.cmake) 