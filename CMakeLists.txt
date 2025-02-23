# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================



cmake_minimum_required(VERSION 3.13)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(PICO_BOARD pico CACHE STRING "Board type")
include(pico_sdk_import.cmake)
project(Projeto_Final C CXX ASM)
pico_sdk_init()
add_executable(Projeto_Final     Projeto_Final.c inc/ssd1306.c)

# Generate PIO header
pico_generate_pio_header(Projeto_Final ${CMAKE_CURRENT_LIST_DIR}/ws2818b.pio)

pico_enable_stdio_usb(Projeto_Final 1)
pico_enable_stdio_uart(Projeto_Final 0)

# Add the standard include files to the build
target_include_directories(Projeto_Final PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(Projeto_Final 
        hardware_pio
        hardware_clocks
        pico_stdlib 
        hardware_adc
        hardware_i2c)

pico_add_extra_outputs(Projeto_Final)
