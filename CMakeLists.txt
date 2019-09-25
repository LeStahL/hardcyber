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

# Find the right python interpreter version
find_package(Python3 REQUIRED COMPONENTS Interpreter)
find_package(OpenGL REQUIRED COMPONENTS OpenGL)

set(COMMON_HEADERS config_types.h config.h glext.h engine/platform.h engine/renderer.h engine/shader.h engine/loader.h engine/orchestrator.h)
set(SFX_SHADER sfx.frag)
set(STRINGS_FILE font/strings.txt)
set(FRAGMENT_SHADER_FILES ocean.frag logo210.frag graffiti.frag starsky.frag text.frag post.frag deadline.frag)

set(FRAGMENT_SHADERS "")
foreach(shader ${FRAGMENT_SHADER_FILES})
    list(APPEND FRAGMENT_SHADERS "gfx/${shader}")
endforeach(shader)


#################################
# Demo executable
#################################

set(DEMO_HEADERS common.h draw.h scenes.h pal_linux.h pal_win32.h sequence.h)

set(SFX_HEADER sfx.h)
add_custom_target(minification
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/minification/
    COMMAND "${Python3_EXECUTABLE}" shader-compressor.py -o "${PROJECT_SOURCE_DIR}/${SFX_HEADER}" "${PROJECT_SOURCE_DIR}/${SFX_SHADER}" --no-minification
    SOURCES minification/shader-compressor.py ${SFX_SHADER}
    BYPRODUCTS ${SFX_HEADER}
)

set(SHADER_HEADER shaders.gen.h)
set(SHADER_FILES gfx/load.frag)
set(SHADER_SYMBOLS_PATH gfx/symbols/)
add_custom_target(minification2
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/
    COMMAND "${Python3_EXECUTABLE}" minification/symbolize.py ${SHADER_FILES} -s ${SHADER_SYMBOLS_PATH} -o ${SHADER_HEADER}
    SOURCES minification/symbolize.py minification/Rule.py minification/Token.py minification/GLSLLexer130.py minification/Compressor.py ${SHADER_FILES}
    BYPRODUCTS ${SHADER_HEADER}
)

set(FONT_HEADER font/font.h)
add_custom_target(texture_packing
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/font/
    COMMAND "${Python3_EXECUTABLE}" pack.py
    SOURCES font/pack.py ${STRINGS_FILE}
    BYPRODUCTS ${FONT_HEADER}
)

set(SYMBOLS_HEADER gfx/symbols.h)
add_custom_target(symbolization
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/gfx/
    COMMAND "${Python3_EXECUTABLE}" symbolize.py ${FRAGMENT_SHADER_FILES} -o symbols.h
    SOURCES gfx/symbolize.py minification/Rule.py minification/Token.py minification/GLSLLexer130.py minification/Compressor.py ${FRAGMENT_SHADERS}
    BYPRODUCTS ${SYMBOLS_HEADER}
)

add_executable(hardcyber
    ls.c
    ${COMMON_HEADERS}
    ${DEMO_HEADERS}
    ${SFX_SHADER}
    ${STRINGS_FILE}
    ${FRAGMENT_SHADERS}
    ${SHADER_FILES}
)
add_dependencies(hardcyber minification)
add_dependencies(hardcyber minification2)
add_dependencies(hardcyber texture_packing)
add_dependencies(hardcyber symbolization)

target_include_directories(hardcyber SYSTEM PRIVATE "${OPENGL_INCLUDE_DIR}")

target_link_libraries(hardcyber OpenGL::GL)

if(MSVC)
    set_target_properties(hardcyber PROPERTIES LINK_FLAGS "/ENTRY:demo /SUBSYSTEM:Windows /OPT:REF /OPT:ICF=10 /VERBOSE /NODEFAULTLIB")
    target_compile_options(hardcyber PRIVATE /Gy /O1 /fp:fast /GR- /GS- /MT )

    if (MSVC_VERSION GREATER_EQUAL 1910) # VS2017
        target_link_libraries(hardcyber Winmm.lib User32.lib ucrt.lib msvcrt.lib vcruntime.lib ucrt.lib Vfw32.lib)
    else()
        # for debug output: User32.lib ucrt.lib msvcrt.lib
        target_link_libraries(hardcyber User32.lib Winmm.lib ucrt.lib msvcrt.lib)
    endif()

    message("CMAKE_SIZEOF_VOID_P: ${CMAKE_SIZEOF_VOID_P}")
    if (${CMAKE_SIZEOF_VOID_P} EQUAL 32)
        find_program(KKRUNCHY_K7 kkrunchy_k7.exe HINTS "${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}")
        add_custom_command(TARGET hardcyber COMMAND "${KKRUNCHY_K7}" --best "$<TARGET_FILE:hardcyber>" --out "$<TARGET_FILE_DIR:hardcyber>/hardcyberc.exe" POST_BUILD)
    endif()
else()
    find_package(SDL2 REQUIRED)
    target_include_directories(hardcyber SYSTEM PRIVATE ${SDL2_INCLUDE_DIRS})
    target_link_libraries(hardcyber ${SDL2_LIBRARIES})
endif()
