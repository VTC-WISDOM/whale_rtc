cmake_minimum_required(VERSION 3.13)

set(target "whale_rtc_module")
project(${target} C CXX ASM)

add_subdirectory(submodules/rp2x_pcf8523)

add_library(${target} INTERFACE)

target_sources(${target} INTERFACE
	src/whale_rtc.c
)

target_include_directories(${target} INTERFACE
	..
)

target_link_libraries(${target} INTERFACE
	hardware_i2c
	hardware_gpio
)

target_link_libraries(${target} INTERFACE
	rp2x_pcf8523_lib
)

target_compile_definitions(${target} INTERFACE
	# PCF8523 pin definitions 
	W_RTC_I2C=i2c0
	W_RTC_SDA=4
	W_RTC_SCL=5
	W_RTC_MFP1=2
)

