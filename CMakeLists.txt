#---------------------------------------------------------------------------------
# CMake version
#---------------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.14.3 FATAL_ERROR)

#---------------------------------------------------------------------------------
# Project directories
#---------------------------------------------------------------------------------

set(MODULE_GAPI_GL_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(MODULE_GAPI_GL_LIST_DIR "${CMAKE_CURRENT_LIST_DIR}")
set(MODULE_GAPI_GL_CMAKE_DIR "${MODULE_GAPI_GL_ROOT_DIR}/submodules/sway.module_core/cmake_modules")
set(MODULE_GAPI_GL_LIB_DIR "${MODULE_GAPI_GL_ROOT_DIR}/lib")
set(MODULE_GAPI_GL_BIN_DIR "${CMAKE_SOURCE_DIR}/bin")

#---------------------------------------------------------------------------------
# Include CMake modules
#---------------------------------------------------------------------------------

include("${MODULE_GAPI_GL_CMAKE_DIR}/options.cmake")
include("${MODULE_GAPI_GL_CMAKE_DIR}/set_output_dir.cmake")
include("${MODULE_GAPI_GL_CMAKE_DIR}/project_metadata.cmake")
include("${MODULE_GAPI_GL_CMAKE_DIR}/enable_cxx17.cmake")
include("${MODULE_GAPI_GL_CMAKE_DIR}/add_submodule.cmake")
include("${MODULE_GAPI_GL_CMAKE_DIR}/modules/compiler/clang/create_library.cmake")
include("${MODULE_GAPI_GL_CMAKE_DIR}/modules/compiler/emscripten/setup.cmake")
include("${MODULE_GAPI_GL_CMAKE_DIR}/modules/compiler/emscripten/create_bitcode.cmake")
include("${MODULE_GAPI_GL_CMAKE_DIR}/modules/compiler/emscripten/create_library.cmake")
include("${MODULE_GAPI_GL_CMAKE_DIR}/modules/compiler/emscripten/gen_target_name.cmake")
include("${MODULE_GAPI_GL_CMAKE_DIR}/modules/compiler/emscripten/set_optimization.cmake")
include("${MODULE_GAPI_GL_CMAKE_DIR}/modules/compiler/emscripten/set_environment.cmake")
include("${MODULE_GAPI_GL_CMAKE_DIR}/modules/compiler/emscripten/set_compilation.cmake")
include("${MODULE_GAPI_GL_CMAKE_DIR}/modules/compiler/emscripten/set_modularize.cmake")

#---------------------------------------------------------------------------------
# Project options
#---------------------------------------------------------------------------------

option(MODULE_GAPI_GL_SHARED_LIB "Build shared library (.so)" OFF)
option(MODULE_GAPI_GL_ENVIRONMENT "Environment variable" OFF)
option(MODULE_GAPI_GL_COMPILATION "Compilation variable" OFF)
option(MODULE_GAPI_GL_MT "Enable multithreading" OFF)
option(MODULE_GAPI_GL_ENABLE_TESTS "Enable test builds" OFF)
option(MODULE_GAPI_GL_ENABLE_COVERAGE "Enable coverage builds" OFF)
option(MODULE_GAPI_GL_ENABLE_EXAMPLES "Enable example builds" OFF)
option(MODULE_USE_AS_STUB "Enable test builds" OFF)

#---------------------------------------------------------------------------------
# [EMSCRIPTEN]: Setup
#---------------------------------------------------------------------------------

if(GLOB_EMSCRIPTEN_PLATFORM)
  emscripten_setup()
endif()

#---------------------------------------------------------------------------------
# Project
#---------------------------------------------------------------------------------

project_metadata("gapi_gl" 0.2.6)
project(${MODULE_GAPI_GL_PROJ_NAME} VERSION ${MODULE_GAPI_GL_VERSION} LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=default -fPIE")

#---------------------------------------------------------------------------------
# Submodules
#---------------------------------------------------------------------------------

add_submodule("module_core" submodules/sway.module_core)

# if(MODULE_GAPI_GL_SHARED_LIB AND NOT GLOB_EMSCRIPTEN_PLATFORM)
#   set(CMAKE_CXX_COMPILER "g++")
#   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Werror -pedantic")
#   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-variable -Wno-unused-parameter -Wno-return-stack-address -Wno-return-type -Wno-int-to-pointer-cast -Wno-variadic-macros -Wno-null-pointer-arithmetic")
# endif()

if (CMAKE_BUILD_TYPE MATCHES Debug)
  # Для выявления ошибок связанных с памятью
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
endif()

# if(MODULE_GAPI_GL_ENABLE_TESTS OR MODULE_USE_AS_STUB)
#   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_STUB")
# endif()

message("[${MODULE_GAPI_GL_PROJ_NAME}]: ${MODULE_GAPI_GL_VERSION}
         compiler | ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}
       build type | ${CMAKE_BUILD_TYPE}
       shared lib | ${MODULE_GAPI_GL_SHARED_LIB}
         cxxflags | ${CMAKE_CXX_FLAGS} ${EXTRA_FLAGS}
 build type flags | ${BUILD_TYPE_CXX_FLAGS}
        build dir | ${CMAKE_BINARY_DIR}
   install prefix | ${CMAKE_INSTALL_PREFIX}

   emscripten dir | ${GLOB_EMSCRIPTEN_ROOT_DIR}
        boost dir | ${GLOB_BOOST_ROOT_DIR}
        gtest dir | ${GLOB_GTEST_ROOT_DIR}

             stub | ${MODULE_USE_AS_STUB}
       emscripten | ${GLOB_EMSCRIPTEN_PLATFORM}
         coverage | ${MODULE_GAPI_GL_ENABLE_COVERAGE}
            tests | ${MODULE_GAPI_GL_ENABLE_TESTS}
         examples | ${MODULE_GAPI_GL_ENABLE_EXAMPLES}
")

#---------------------------------------------------------------------------------
# Executable output path
#---------------------------------------------------------------------------------

set_output_dir(${MODULE_GAPI_GL_BIN_DIR})

#---------------------------------------------------------------------------------
# Include project headers
#---------------------------------------------------------------------------------

include_directories("${MODULE_GAPI_GL_LIST_DIR}/lib/cxx/include")
include_directories("${MODULE_GAPI_GL_LIST_DIR}/submodules/sway.module_core/lib/cxx/include")
include_directories("${MODULE_GAPI_GL_LIST_DIR}/submodules/sway.module_math/lib/cxx/include")
include_directories("${MODULE_GAPI_GL_LIST_DIR}/submodules/sway.module_gapi/include")
include_directories("${MODULE_GAPI_GL_LIST_DIR}/submodules/sway.module_platform-glx11/lib/cxx/include")

# Получаем пути ко всем хедерам и исходникам библиотеки
file(GLOB_RECURSE MODULE_GAPI_GL_HEADERS "${MODULE_GAPI_GL_LIST_DIR}/lib/cxx/include/*.*")
file(GLOB_RECURSE MODULE_GAPI_GL_SOURCES "${MODULE_GAPI_GL_LIST_DIR}/lib/cxx/src/*.*")

find_package(OpenGL REQUIRED)
find_library(GLUT_glut_LIBRARY GLUT DOC "GLUT library for OSX")

#---------------------------------------------------------------------------------
# Create interfaces
#---------------------------------------------------------------------------------

set(MODULE_CORE_TARGET_IFACE "module_core_iface")

set(TARGET_OBJECT_LIST)
list(APPEND TARGET_OBJECT_LIST $<TARGET_OBJECTS:module_core>)

create_iface(${MODULE_CORE_TARGET_IFACE} ${TARGET_OBJECT_LIST})

#---------------------------------------------------------------------------------
# [EMSCRIPTEN] Bitcode
#---------------------------------------------------------------------------------

if(GLOB_EMSCRIPTEN_PLATFORM)
  create_bitcode(${MODULE_GAPI_GL_TARGET} "${MODULE_GAPI_GL_ROOT_DIR}/lib/cxx/src/*.*")
else()
  create_library(${MODULE_GAPI_GL_TARGET} "${MODULE_GAPI_GL_ROOT_DIR}/lib/cxx/src/*.*")
endif()

enable_cxx17(${MODULE_GAPI_GL_TARGET})

if(GLOB_EMSCRIPTEN_PLATFORM)
  create_emscripten_library(${MODULE_GAPI_GL_TARGET} ${MODULE_GAPI_GL_ENVIRONMENT} ${MODULE_GAPI_GL_COMPILATION} OUTPUT_TARGET_NAME_LIST)

  # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Oz --profiling-funcs")

  foreach(target IN LISTS OUTPUT_TARGET_NAME_LIST)
    target_link_options(${target} PUBLIC 
      "SHELL:-s STRICT=1"
      "SHELL:-s MODULARIZE=1"
      "SHELL:-s FULL_ES3=1"
      "SHELL:-s SUPPORT_LONGJMP=0"
      "SHELL:-s EXPORT_NAME=\"create_gapi_gl_module\""
      "SHELL:-s EXPORTED_FUNCTIONS=@${MODULE_GAPI_GL_LIB_DIR}/exports.json"
      "SHELL:-s EXPORTED_RUNTIME_METHODS=@${MODULE_GAPI_GL_LIB_DIR}/runtime-exports.json")

    if(MODULE_GAPI_GL_SHARED_LIB)
      target_link_options(${target} PUBLIC 
        "SHELL:-shared"
        "SHELL:-dynamiclib"
        "SHELL:-s SIDE_MODULE=1")
    endif()

    if(MODULE_GAPI_GL_MT)
      target_link_options(${target} PUBLIC 
        "SHELL:-Wl,--shared-memory,--no-check-features"
        "SHELL:-s USE_PTHREADS=1"
        "SHELL:-s PTHREAD_POOL_SIZE=8"
        "SHELL:-s IMPORTED_MEMORY=1")
    endif()
    printf_link_options(${target})
  endforeach()
else()
  # create_library(${MODULE_CORE_TARGET} "${MODULE_CORE_ROOT_DIR}/lib/cxx/src/*.*")
endif()

# if(MODULE_GAPI_GL_SHARED_LIB)
#   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -fexceptions -fvisibility=hidden")

#   # Добавляем в проект цель для сборки динамической библиотеки
#   add_library(${MODULE_GAPI_GL_TARGET} SHARED ${MODULE_GAPI_GL_SOURCES})
#   set_target_properties(${MODULE_GAPI_GL_TARGET} PROPERTIES OUTPUT_NAME ${MODULE_GAPI_GL_PROJ_NAME})
#   set_target_properties(${MODULE_GAPI_GL_TARGET} PROPERTIES PREFIX "")
#   if(GLOB_EMSCRIPTEN_PLATFORM)
#     set_target_properties(${MODULE_GAPI_GL_TARGET} PROPERTIES SUFFIX ".wasm")
#   else()
#     set_target_properties(${MODULE_GAPI_GL_TARGET} PROPERTIES SUFFIX ".dylib.${MODULE_GAPI_GL_VERSION}")
#     # set_target_properties(${MODULE_GAPI_GL_TARGET} PROPERTIES SUFFIX ".so.${MODULE_GAPI_GL_VERSION}")
#   endif()
#   target_compile_definitions(${MODULE_GAPI_GL_TARGET} PRIVATE -DBUILD_DLLAPI_LIBMODULE)
# else()
#   # Добавляем в проект цель для сборки статической библиотеки
#   add_library(${MODULE_GAPI_GL_TARGET} STATIC ${MODULE_GAPI_GL_SOURCES})
#   set_target_properties(${MODULE_GAPI_GL_TARGET} PROPERTIES OUTPUT_NAME ${MODULE_GAPI_GL_PROJ_NAME})
#   set_target_properties(${MODULE_GAPI_GL_TARGET} PROPERTIES PREFIX "")
#   set_target_properties(${MODULE_GAPI_GL_TARGET} PROPERTIES SUFFIX ".a.${MODULE_GAPI_GL_VERSION}")
# endif()

# enable_cxx17(${MODULE_GAPI_GL_TARGET})
# target_link_libraries(${MODULE_GAPI_GL_TARGET} module_core GL GLESv2 ${GLUT_LIBRARY} ${OPENGL_LIBRARY})

#---------------------------------------------------------------------------------
# Examples
#---------------------------------------------------------------------------------

if(MODULE_GAPI_GL_ENABLE_EXAMPLES AND NOT GLOB_EMSCRIPTEN_PLATFORM)
  message(STATUS "Examples have been enabled")

  add_submodule("libmodule_platform_glx11" submodules/sway.module_platform-glx11)
  add_subdirectory(examples/01-triangle)
  add_subdirectory(examples/02-ibo)
  add_subdirectory(examples/03-texture)
endif()

if(MODULE_GAPI_GL_ENABLE_EXAMPLES AND GLOB_EMSCRIPTEN_PLATFORM)
  message(STATUS "Examples have been enabled")

  add_subdirectory(examples/01-triangle-webgl)
endif()

#---------------------------------------------------------------------------------
# Tests
#---------------------------------------------------------------------------------

if(MODULE_GAPI_GL_ENABLE_TESTS)
  if(MODULE_GAPI_GL_SHARED_LIB)
    message(STATUS "[${MODULE_GAPI_GL_PROJ_NAME}]: Tests are only allowed with a static lib")
  else()
    message(STATUS "[${MODULE_GAPI_GL_PROJ_NAME}]: Tests have been enabled")
    add_subdirectory(lib/cxx/tests/google)
  endif()
endif()
