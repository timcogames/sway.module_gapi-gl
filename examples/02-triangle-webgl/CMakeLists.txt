#---------------------------------------------------------------------------------
# CMake version
#---------------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.25.0 FATAL_ERROR)

#---------------------------------------------------------------------------------
# Project directories
#---------------------------------------------------------------------------------

set(MODULE_TRIANGLE_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(MODULE_TRIANGLE_LIST_DIR "${CMAKE_CURRENT_LIST_DIR}")
set(MODULE_TRIANGLE_CMAKE_DIR "${MODULE_TRIANGLE_ROOT_DIR}/../../submodules/sway.module_core/cmake_modules")
set(MODULE_TRIANGLE_LIB_DIR "${MODULE_TRIANGLE_ROOT_DIR}/lib")
set(MODULE_TRIANGLE_BIN_DIR "${CMAKE_SOURCE_DIR}/bin")

#---------------------------------------------------------------------------------
# Include CMake modules
#---------------------------------------------------------------------------------

include("${MODULE_TRIANGLE_CMAKE_DIR}/options.cmake")
include("${MODULE_TRIANGLE_CMAKE_DIR}/set_output_dir.cmake")
include("${MODULE_TRIANGLE_CMAKE_DIR}/project_metadata.cmake")
include("${MODULE_TRIANGLE_CMAKE_DIR}/enable_cxx17.cmake")
include("${MODULE_TRIANGLE_CMAKE_DIR}/add_submodule.cmake")
include("${MODULE_TRIANGLE_CMAKE_DIR}/modules/compiler/clang/create_library.cmake")
include("${MODULE_TRIANGLE_CMAKE_DIR}/modules/compiler/emscripten/setup.cmake")
include("${MODULE_TRIANGLE_CMAKE_DIR}/modules/compiler/emscripten/create_bitcode.cmake")
include("${MODULE_TRIANGLE_CMAKE_DIR}/modules/compiler/emscripten/create_library.cmake")
include("${MODULE_TRIANGLE_CMAKE_DIR}/modules/compiler/emscripten/gen_target_name.cmake")
include("${MODULE_TRIANGLE_CMAKE_DIR}/modules/compiler/emscripten/set_optimization.cmake")
include("${MODULE_TRIANGLE_CMAKE_DIR}/modules/compiler/emscripten/set_environment.cmake")
include("${MODULE_TRIANGLE_CMAKE_DIR}/modules/compiler/emscripten/set_compilation.cmake")
include("${MODULE_TRIANGLE_CMAKE_DIR}/modules/compiler/emscripten/set_modularize.cmake")

#---------------------------------------------------------------------------------
# [EMSCRIPTEN]: Setup
#---------------------------------------------------------------------------------

if(GLOB_EMSCRIPTEN_PLATFORM)
  emscripten_setup()
endif()

#---------------------------------------------------------------------------------
# Project
#---------------------------------------------------------------------------------

project_metadata("triangle" 0.2.6)
project(${MODULE_TRIANGLE_PROJ_NAME} VERSION ${MODULE_TRIANGLE_VERSION} LANGUAGES CXX)

if (GLOB_EMSCRIPTEN_PLATFORM)
  set(CMAKE_CXX_COMPILER "${GLOB_EMSCRIPTEN_ROOT_DIR}/emcc")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} \
    -s MODULARIZE=1 \
    -s EXPORT_NAME=Module \
    -s EXPORT_ES6=1 \
    -s FULL_ES3=1 \
    -s LLD_REPORT_UNDEFINED=1 \
    -s EXPORTED_FUNCTIONS=\"[_main]\"")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-return-type -Wno-int-to-pointer-cast -Wno-unknown-pragmas -Wno-unicode-whitespace \
    -Wno-unused-local-typedef -Wno-invalid-noreturn -Wno-unused-parameter -Wno-unused-variable -Wno-unused-command-line-argument -Wno-gnu-zero-variadic-macro-arguments")
endif()

#---------------------------------------------------------------------------------
# Executable output path
#---------------------------------------------------------------------------------

set_output_dir(${MODULE_TRIANGLE_BIN_DIR})

#---------------------------------------------------------------------------------
# Find libraries
#---------------------------------------------------------------------------------

find_library(GLUT_glut_LIBRARY GLUT DOC "GLUT library for OSX")
find_package(OpenGL REQUIRED)
if(OPENGL_FOUND)
  include_directories(${OPENGL_INCLUDE_DIRS})
  link_directories(${OPENGL_LIBRARY_DIRS})
  add_definitions(${OPENGL_DEFINITIONS})
endif()

set(MODULE_TRIANGLE_DIR ${CMAKE_CURRENT_LIST_DIR})

# include_directories("/usr/include/aarch64-linux-gnu")
# include_directories("/opt/.emsdk/upstream/emscripten/cache/sysroot/include")

# Получаем пути ко всем хедерам и исходникам библиотеки
file(GLOB_RECURSE MODULE_TRIANGLE_HEADERS "${MODULE_TRIANGLE_DIR}/*.hpp")
file(GLOB_RECURSE MODULE_TRIANGLE_SOURCES "${MODULE_TRIANGLE_DIR}/*.cpp")

add_executable(${MODULE_TRIANGLE_TARGET} ${MODULE_TRIANGLE_SOURCES})
set_target_properties(${MODULE_TRIANGLE_TARGET} PROPERTIES OUTPUT_NAME ${MODULE_TRIANGLE_PROJ_NAME})

enable_cxx17(${MODULE_TRIANGLE_TARGET})
target_link_libraries(${MODULE_TRIANGLE_TARGET} GL GLESv2 ${GLUT_LIBRARY} ${OPENGL_LIBRARY} module_gapi_gl module_core_iface)
