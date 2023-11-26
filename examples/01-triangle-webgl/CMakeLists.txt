# Проверяем версию CMake
cmake_minimum_required(VERSION 3.14.3 FATAL_ERROR)

include("${CMAKE_CURRENT_SOURCE_DIR}/../../submodules/sway.module_core/cmakehelpers/enable_cxx17.cmake")

# Мета-информация о проекте
set(META_TRIANGLE_PRJNAME "module_triangle")
set(META_TRIANGLE_LIBNAME "lib${META_TRIANGLE_PRJNAME}")
set(META_TRIANGLE_VERSION_MAJOR 0)
set(META_TRIANGLE_VERSION_MINOR 1)
set(META_TRIANGLE_VERSION_PATCH 0)
set(META_TRIANGLE_VERSION ${META_TRIANGLE_VERSION_MAJOR}.${META_TRIANGLE_VERSION_MINOR}.${META_TRIANGLE_VERSION_PATCH})

# Опции сборки
option(GLOB_EMSCRIPTEN_ROOT_DIR "Emscripten root directory" OFF)
option(GLOB_BOOST_ROOT_DIR "Boost root directory" OFF)
option(GLOB_GTEST_ROOT_DIR "GTest root directory" OFF)

if (NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  set(CMAKE_TOOLCHAIN_FILE "${GLOB_EMSCRIPTEN_ROOT_DIR}/cmake/Modules/Platform/Emscripten.cmake")
  include(${CMAKE_TOOLCHAIN_FILE})
endif()

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build" FORCE)
endif()

project(${META_TRIANGLE_PRJNAME} VERSION ${META_TRIANGLE_VERSION} LANGUAGES CXX)

if (GLOB_EMSCRIPTEN_PLATFORM)
  set(CMAKE_CXX_COMPILER "${GLOB_EMSCRIPTEN_ROOT_DIR}/emcc")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s MODULARIZE=1 -s EXPORT_NAME=Module -s EXPORT_ES6=1 -s FULL_ES3=1 -s LLD_REPORT_UNDEFINED=1 -s EXPORTED_FUNCTIONS=\"[_main]\"")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-return-type -Wno-int-to-pointer-cast -Wno-unknown-pragmas -Wno-unicode-whitespace \
  -Wno-unused-local-typedef -Wno-invalid-noreturn -Wno-unused-parameter -Wno-unused-variable -Wno-unused-command-line-argument -Wno-gnu-zero-variadic-macro-arguments")
endif()

# Определяем каталог вывода по умолчанию
if (CMAKE_BUILD_TYPE MATCHES Debug)
  set(LIBRARY_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/bin/dbg")
  set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/bin/dbg")
else()
  set(LIBRARY_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/bin")
  set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/bin")
endif()

find_library(GLUT_glut_LIBRARY GLUT DOC "GLUT library for OSX")
find_package(OpenGL REQUIRED)
if(OPENGL_FOUND)
  include_directories(${OPENGL_INCLUDE_DIRS})
  link_directories(${OPENGL_LIBRARY_DIRS})
  add_definitions(${OPENGL_DEFINITIONS})
endif()

set(MODULE_TRIANGLE_DIR ${CMAKE_CURRENT_LIST_DIR})

# Получаем пути ко всем хедерам и исходникам библиотеки
file(GLOB_RECURSE MODULE_TRIANGLE_HEADERS "${MODULE_TRIANGLE_DIR}/*.hpp")
file(GLOB_RECURSE MODULE_TRIANGLE_SOURCES "${MODULE_TRIANGLE_DIR}/*.cpp")

add_executable(${META_TRIANGLE_LIBNAME} ${MODULE_TRIANGLE_SOURCES})
set_target_properties(${META_TRIANGLE_LIBNAME} PROPERTIES OUTPUT_NAME "index")
set_target_properties(${META_TRIANGLE_LIBNAME} PROPERTIES SUFFIX ".html")

enable_cxx17(${META_TRIANGLE_LIBNAME})
target_link_libraries(${META_TRIANGLE_LIBNAME} GL GLESv2 ${GLUT_LIBRARY} ${OPENGL_LIBRARY} module_gapi_gl module_core)
