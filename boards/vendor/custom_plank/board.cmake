# Copyright (c) HyTech
# SPDX-License-Identifier: Apache-2.0

board_runner_args(jlink "--device=nrf52" "--speed=4000") #TODO: Change to be right
board_runner_args(pyocd "--target=nrf52840" "--frequency=4000000") #TODO: Change to be right
board_runner_args(example "--param=foo") #TODOL Change to be right

set(OPENOCD_STM32_TARGET "stm32h7x") #TODO: Check

include(${ZEPHYR_BASE}/boards/common/nrfjprog.board.cmake)
include(${ZEPHYR_BASE}/boards/common/jlink.board.cmake)
include(${ZEPHYR_BASE}/boards/common/pyocd.board.cmake)
include(${ZEPHYR_BASE}/boards/common/openocd-nrf5.board.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/../../common/example_runner.board.cmake)

# From Nucleo Board, see if we need
# # keep first
# board_runner_args(stm32cubeprogrammer "--port=swd" "--reset-mode=hw")
# board_runner_args(jlink "--device=STM32H723ZG" "--speed=4000")
# board_runner_args(openocd --target-handle=_CHIPNAME.cpu0)

# # keep first
# include(${ZEPHYR_BASE}/boards/common/stm32cubeprogrammer.board.cmake)
# include(${ZEPHYR_BASE}/boards/common/openocd.board.cmake)
# include(${ZEPHYR_BASE}/boards/common/jlink.board.cmake)
