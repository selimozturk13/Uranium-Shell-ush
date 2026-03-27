 # Copyright (C) 2026 Selim Öztürk
 #
 # This program is free software; you can redistribute it and/or modify
 # it under the terms of the GNU General Public License as published by
 # the Free Software Foundation, either version 3 of the License, or
 # (at your option) any later version.
 #
 # This program is distributed in the hope that it will be useful,
 # but WITHOUT ANY WARRANTY; without even the implied warranty of
 # MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 # GNU General Public License for more details.
 #
 # You should have received a copy of the GNU General Public License
 # along with this program. If not, see <https://www.gnu.org/licenses/>.
 

cmake_minimum_required(VERSION 3.10)

# Project Name
project(ush C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Add the include directory so "ush.h" can be found
include_directories(include)

if(APPLE)
    include_directories(/usr/local/include /opt/homebrew/include)
    link_directories(/usr/local/lib /opt/homebrew/lib)
endif()

find_library(READLINE_LIBRARY NAMES readline edit)

# Gather all source files from the src directory
file(GLOB SOURCES "src/*.c")

# Define the executable
add_executable(ush ${SOURCES})

if(READLINE_LIBRARY)
    target_link_libraries(ush PRIVATE ${READLINE_LIBRARY})
else()
    message(FATAL_ERROR "Readline library not found!")
endif()

# Common compiler warnings to help with debugging
target_compile_options(ush PRIVATE -Wall -Wextra -g)