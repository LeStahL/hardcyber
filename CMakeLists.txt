# Hardcyber - PC-64k-Intro by Team210 at Deadline 2k19
# Copyright (C) 2019 Alexander Kraus <nr4@z10.info>
# Copyright (C) 2019 DaDummy <c.anselm@paindevs.com>
# 
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 3.12)

project(hardcyber)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CTRL_ALT_TEST_MINIFIER OFF)

# Find the right python interpreter version
find_package(Python3 REQUIRED COMPONENTS Interpreter)
find_package(OpenGL REQUIRED COMPONENTS OpenGL)

if(MSVC AND ${CTRL_ALT_TEST_MINIFIER})
    find_program(MINIFIER shader_minifier.exe HINTS ${PROJECT_BINARY_DIR})
    add_custom_target(minification
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    )
else()
    add_custom_target(minification
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/minification/
        COMMAND "${Python3_EXECUTABLE}" shader-compressor.py  -o "${PROJECT_SOURCE_DIR}/sfx.h" "${PROJECT_SOURCE_DIR}/sfx.frag" --no-minification
        COMMAND "${Python3_EXECUTABLE}" shader-compressor.py -o "${PROJECT_SOURCE_DIR}/gfx/load.h" "${PROJECT_SOURCE_DIR}/gfx/load.frag" --no-minification
    )
endif()

add_custom_target(texture_packing
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/font/
    COMMAND "${Python3_EXECUTABLE}" pack.py
)

add_custom_target(symbolization
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/gfx/
    COMMAND "${Python3_EXECUTABLE}" symbolize.py logo210.frag graffiti.frag starsky.frag text.frag post.frag -o symbols.h
)

if(MSVC)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:demo /SUBSYSTEM:Windows  /OPT:REF  /OPT:ICF=10 /VERBOSE /NODEFAULTLIB ")
endif()

add_executable(hardcyber ls.c )
add_dependencies(hardcyber minification)
add_dependencies(hardcyber texture_packing)
add_dependencies(hardcyber symbolization)

target_include_directories(hardcyber SYSTEM PRIVATE "${OPENGL_INCLUDE_DIR}")

target_link_libraries(hardcyber OpenGL::GL)

if(MSVC)
    target_compile_options(hardcyber PRIVATE /Gy /O1 /fp:fast /GR- /GS- /MT )

    if (MSVC_VERSION GREATER_EQUAL 1910) # VS2017
        target_link_libraries(hardcyber Winmm.lib User32.lib ucrt.lib msvcrt.lib vcruntime.lib ucrt.lib Vfw32.lib)
    else()
        # for debug output: User32.lib ucrt.lib msvcrt.lib
        target_link_libraries(hardcyber User32.lib Winmm.lib ucrt.lib msvcrt.lib)
    endif()

    find_program(KKRUNCHY_K7 kkrunchy_k7.exe HINTS "${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}")
    add_custom_command(TARGET hardcyber COMMAND "${KKRUNCHY_K7}" --best "$<TARGET_FILE:hardcyber>" --out "$<TARGET_FILE_DIR:hardcyber>/hardcyberc.exe" POST_BUILD)
else()
    find_package(SDL2 REQUIRED)
    target_include_directories(hardcyber SYSTEM PRIVATE ${SDL2_INCLUDE_DIRS})
    target_link_libraries(hardcyber ${SDL2_LIBRARIES})
endif()
