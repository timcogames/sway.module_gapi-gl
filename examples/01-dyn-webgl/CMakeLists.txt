#---------------------------------------------------------------------------------
# CMake version
#---------------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.25.0 FATAL_ERROR)

#---------------------------------------------------------------------------------
# Project directories
#---------------------------------------------------------------------------------

set(MODULE_GAPI_GL_EX_01_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(MODULE_GAPI_GL_EX_01_LIST_DIR "${CMAKE_CURRENT_LIST_DIR}")
set(MODULE_GAPI_GL_EX_01_CMAKE_DIR "${MODULE_GAPI_GL_EX_01_ROOT_DIR}/../../submodules/sway.module_core/cmake_modules")
set(MODULE_GAPI_GL_EX_01_LIB_DIR "${MODULE_GAPI_GL_EX_01_ROOT_DIR}/lib")
set(MODULE_GAPI_GL_EX_01_BIN_DIR "${CMAKE_SOURCE_DIR}/bin")

#---------------------------------------------------------------------------------
# Include CMake modules
#---------------------------------------------------------------------------------

include("${MODULE_GAPI_GL_EX_01_CMAKE_DIR}/options.cmake")
include("${MODULE_GAPI_GL_EX_01_CMAKE_DIR}/set_output_dir.cmake")
include("${MODULE_GAPI_GL_EX_01_CMAKE_DIR}/project_metadata.cmake")
include("${MODULE_GAPI_GL_EX_01_CMAKE_DIR}/enable_cxx17.cmake")
include("${MODULE_GAPI_GL_EX_01_CMAKE_DIR}/add_submodule.cmake")
include("${MODULE_GAPI_GL_EX_01_CMAKE_DIR}/modules/compiler/clang/create_library.cmake")
include("${MODULE_GAPI_GL_EX_01_CMAKE_DIR}/modules/compiler/emscripten/setup.cmake")
include("${MODULE_GAPI_GL_EX_01_CMAKE_DIR}/modules/compiler/emscripten/create_bitcode.cmake")
include("${MODULE_GAPI_GL_EX_01_CMAKE_DIR}/modules/compiler/emscripten/create_library.cmake")
include("${MODULE_GAPI_GL_EX_01_CMAKE_DIR}/modules/compiler/emscripten/gen_target_name.cmake")
include("${MODULE_GAPI_GL_EX_01_CMAKE_DIR}/modules/compiler/emscripten/set_optimization.cmake")
include("${MODULE_GAPI_GL_EX_01_CMAKE_DIR}/modules/compiler/emscripten/set_environment.cmake")
include("${MODULE_GAPI_GL_EX_01_CMAKE_DIR}/modules/compiler/emscripten/set_compilation.cmake")
include("${MODULE_GAPI_GL_EX_01_CMAKE_DIR}/modules/compiler/emscripten/set_modularize.cmake")

#---------------------------------------------------------------------------------
# [EMSCRIPTEN]: Setup
#---------------------------------------------------------------------------------

if(GLOB_EMSCRIPTEN_PLATFORM)
  emscripten_setup()
endif()

#---------------------------------------------------------------------------------
# Project
#---------------------------------------------------------------------------------

project_metadata("gapi_gl_ex_01" 0.2.6)
project(${MODULE_GAPI_GL_EX_01_PROJ_NAME} VERSION ${MODULE_GAPI_GL_EX_01_VERSION} LANGUAGES CXX)

if (GLOB_EMSCRIPTEN_PLATFORM)
  set(CMAKE_CXX_COMPILER "${GLOB_EMSCRIPTEN_ROOT_DIR}/emcc")

  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
    -s EXPORT_ES6=1 \
    -s FULL_ES3=1")

  if(MODULE_GAPI_GL_ALL_EXPORT)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s MAIN_MODULE=2")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
      -s MAIN_MODULE=1 \
      -s EXPORTED_FUNCTIONS=[\"_main\"]")
  endif()

  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s NO_EXIT_RUNTIME=1")

  # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
  #   -s WASM_ASYNC_COMPILATION=1 \
  #   -s ENVIRONMENT=worker")

  # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s OFFSCREEN_FRAMEBUFFER=1")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s OFFSCREENCANVAS_SUPPORT=1")

  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_WEBGL2=1")

  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
    --preload-file ../../../@/wwwroot/dist/module_gapi_gl_wasm_async.wasm \
    -s FORCE_FILESYSTEM=1")

  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
    -Wl,--shared-memory,--no-check-features \
    -s USE_PTHREADS=1")
  # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s PROXY_TO_PTHREAD=1")

  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-return-type -Wno-int-to-pointer-cast -Wno-unknown-pragmas -Wno-unicode-whitespace \
    -Wno-unused-local-typedef -Wno-invalid-noreturn -Wno-unused-parameter -Wno-unused-variable -Wno-unused-command-line-argument -Wno-gnu-zero-variadic-macro-arguments")
endif()

#---------------------------------------------------------------------------------
# Executable output path
#---------------------------------------------------------------------------------

set_output_dir(${MODULE_GAPI_GL_EX_01_BIN_DIR})

#---------------------------------------------------------------------------------
# Find libraries
#---------------------------------------------------------------------------------

find_package(OpenGL REQUIRED)
if(OPENGL_FOUND)
  # include_directories(${OPENGL_INCLUDE_DIRS})
  # link_directories(${OPENGL_LIBRARY_DIRS})
  # add_definitions(${OPENGL_DEFINITIONS})
endif()
find_library(GLUT_glut_LIBRARY GLUT DOC "GLUT library for OSX")

set(MODULE_GAPI_GL_EX_01_DIR ${CMAKE_CURRENT_LIST_DIR})

# Получаем пути ко всем хедерам и исходникам библиотеки
file(GLOB_RECURSE MODULE_GAPI_GL_EX_01_HEADERS "${MODULE_GAPI_GL_EX_01_DIR}/*.hpp")
file(GLOB_RECURSE MODULE_GAPI_GL_EX_01_SOURCES "${MODULE_GAPI_GL_EX_01_DIR}/*.cpp")

add_executable(${MODULE_GAPI_GL_EX_01_TARGET} ${MODULE_GAPI_GL_EX_01_SOURCES})
set_target_properties(${MODULE_GAPI_GL_EX_01_TARGET} PROPERTIES OUTPUT_NAME ${MODULE_GAPI_GL_EX_01_PROJ_NAME})
set_target_properties(${MODULE_GAPI_GL_EX_01_TARGET} PROPERTIES LINK_FLAGS "--entry")

enable_cxx17(${MODULE_GAPI_GL_EX_01_TARGET})
target_link_libraries(${MODULE_GAPI_GL_EX_01_TARGET} -lGL GLESv2 ${GLUT_LIBRARY} ${OPENGL_LIBRARY} module_gapi_gl module_core_iface)
