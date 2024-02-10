#---------------------------------------------------------------------------------
# CMake version
#---------------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.25.0 FATAL_ERROR)

#---------------------------------------------------------------------------------
# Project directories
#---------------------------------------------------------------------------------

set(MODULE_GAPI_GL_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(MODULE_GAPI_GL_LIST_DIR "${CMAKE_CURRENT_LIST_DIR}")
set(MODULE_GAPI_GL_CMAKE_DIR "${MODULE_GAPI_GL_ROOT_DIR}/submodules/sway.module_core/cmake_modules")
set(MODULE_GAPI_GL_LIB_DIR "${MODULE_GAPI_GL_ROOT_DIR}/lib")
set(MODULE_GAPI_GL_BIN_DIR "${CMAKE_SOURCE_DIR}/bin")

set(X11_INC_DIRS "/opt/X11/include")
set(X11_LIB_DIRS "/opt/X11/lib")

#---------------------------------------------------------------------------------
# Include CMake modules
#---------------------------------------------------------------------------------

include("${MODULE_GAPI_GL_CMAKE_DIR}/options.cmake")
include("${MODULE_GAPI_GL_CMAKE_DIR}/set_output_dir.cmake")
include("${MODULE_GAPI_GL_CMAKE_DIR}/project_metadata.cmake")
include("${MODULE_GAPI_GL_CMAKE_DIR}/enable_cxx17.cmake")
include("${MODULE_GAPI_GL_CMAKE_DIR}/add_submodule.cmake")
include("${MODULE_GAPI_GL_CMAKE_DIR}/modules/create_object_library.cmake")
include("${MODULE_GAPI_GL_CMAKE_DIR}/modules/create_interface.cmake")
include("${MODULE_GAPI_GL_CMAKE_DIR}/modules/compiler/clang/create_library.cmake")
include("${MODULE_GAPI_GL_CMAKE_DIR}/modules/compiler/emscripten/setup.cmake")
include("${MODULE_GAPI_GL_CMAKE_DIR}/modules/compiler/emscripten/create_library.cmake")
include("${MODULE_GAPI_GL_CMAKE_DIR}/modules/compiler/emscripten/gen_target_name.cmake")
include("${MODULE_GAPI_GL_CMAKE_DIR}/modules/compiler/emscripten/set_optimization.cmake")
include("${MODULE_GAPI_GL_CMAKE_DIR}/modules/compiler/emscripten/set_environment.cmake")
include("${MODULE_GAPI_GL_CMAKE_DIR}/modules/compiler/emscripten/set_compilation.cmake")
include("${MODULE_GAPI_GL_CMAKE_DIR}/modules/compiler/emscripten/set_modularize.cmake")

#---------------------------------------------------------------------------------
# Project options
#---------------------------------------------------------------------------------

option(MODULE_GAPI_GL_LIB_TYPE "Build type library" OFF)
option(MODULE_GAPI_GL_ENVIRONMENT "Environment variable" OFF)
option(MODULE_GAPI_GL_COMPILATION "Compilation variable" OFF)
option(MODULE_GAPI_GL_MT "Enable multithreading" OFF)
option(MODULE_GAPI_GL_ALL_EXPORT "" OFF)
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
add_submodule("module_platform_glx11" submodules/sway.module_platform-glx11)

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
         lib type | ${MODULE_CORE_LIB_TYPE}
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

include_directories("${X11_INC_DIRS}")
include_directories("${MODULE_GAPI_GL_LIST_DIR}/lib/cxx/include")
include_directories("${MODULE_GAPI_GL_LIST_DIR}/submodules/sway.module_core/lib/cxx/include")
include_directories("${MODULE_GAPI_GL_LIST_DIR}/submodules/sway.module_math/lib/cxx/include")
include_directories("${MODULE_GAPI_GL_LIST_DIR}/submodules/sway.module_gapi/api/cxx/include")
include_directories("${MODULE_GAPI_GL_LIST_DIR}/submodules/sway.module_platform-glx11/lib/cxx/include")

# Получаем пути ко всем хедерам и исходникам библиотеки
file(GLOB_RECURSE MODULE_GAPI_GL_HEADERS "${MODULE_GAPI_GL_LIST_DIR}/lib/cxx/include/*.*")
file(GLOB_RECURSE MODULE_GAPI_GL_SOURCES "${MODULE_GAPI_GL_LIST_DIR}/lib/cxx/src/*.*")

link_directories("${X11_LIB_DIRS}")
find_package(OpenGL REQUIRED)
if(OPENGL_FOUND)
  # include_directories(${OPENGL_INCLUDE_DIRS})
  # link_directories(${OPENGL_LIBRARY_DIRS})
  # add_definitions(${OPENGL_DEFINITIONS})
  message("OPENGL_INCLUDE_DIRS: ${OPENGL_INCLUDE_DIRS}")
  message("OPENGL_LIBRARY_DIRS: ${OPENGL_LIBRARY_DIRS}")
  message("OPENGL_DEFINITIONS: ${OPENGL_DEFINITIONS}")
endif()
find_library(GLUT_glut_LIBRARY GLUT DOC "GLUT library for OSX")

#---------------------------------------------------------------------------------
# Build object library
#---------------------------------------------------------------------------------

if(NOT TARGET ${MODULE_GAPI_GL_OBJ_TARGET})
  set(MODULE_GAPI_GL_LIB_SOURCES "${MODULE_GAPI_GL_ROOT_DIR}/lib/cxx/src/*.*")
  set(MODULE_GAPI_GL_ENABLE_FILE_EXPORT TRUE)

  create_object_library(${MODULE_GAPI_GL_OBJ_TARGET} ${MODULE_GAPI_GL_LIB_SOURCES} ${MODULE_GAPI_GL_ENABLE_FILE_EXPORT})
  enable_cxx17(${MODULE_GAPI_GL_OBJ_TARGET})
endif()

#---------------------------------------------------------------------------------
# Create interfaces
#---------------------------------------------------------------------------------

set(MODULE_GAPI_GL_DEPENDENCY_LIST "module_gapi_gl_dependences")
if(NOT TARGET module_gapi_gl_dependences)
  set(TARGET_OBJECT_LIST)

  set(MODULE_CORE_OBJ_TARGET "module_core_obj")
  if(TARGET ${MODULE_CORE_OBJ_TARGET})
    list(APPEND TARGET_OBJECT_LIST $<TARGET_OBJECTS:${MODULE_CORE_OBJ_TARGET}>)
  endif()

  # TODO: Модуль не создает объект
  # set(MODULE_PLTF_OBJ_TARGET "module_pltf_obj")
  # if(TARGET ${MODULE_PLTF_OBJ_TARGET})
  #   list(APPEND TARGET_OBJECT_LIST $<TARGET_OBJECTS:${MODULE_PLTF_OBJ_TARGET}>)
  # endif()

  if(TARGET ${MODULE_GAPI_GL_OBJ_TARGET})
    list(APPEND TARGET_OBJECT_LIST $<TARGET_OBJECTS:${MODULE_GAPI_GL_OBJ_TARGET}>)
  endif()

  create_interface(${MODULE_GAPI_GL_DEPENDENCY_LIST} ${TARGET_OBJECT_LIST})
endif()

#---------------------------------------------------------------------------------
# [EMSCRIPTEN] 
#---------------------------------------------------------------------------------

if(NOT MODULE_GAPI_GL_LIB_TYPE STREQUAL "object")
  if(GLOB_EMSCRIPTEN_PLATFORM)
    create_emscripten_library(${MODULE_GAPI_GL_LIB_TARGET} ${MODULE_GAPI_GL_ENVIRONMENT} ${MODULE_GAPI_GL_COMPILATION} OUTPUT_TARGET_NAME_LIST)

    # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --profiling-funcs")

    foreach(target IN LISTS OUTPUT_TARGET_NAME_LIST)
      target_link_options(${target} PUBLIC 
        "SHELL:-s MODULARIZE=1"
        "SHELL:-s FULL_ES3=1"
        "SHELL:-s SUPPORT_LONGJMP=0"
        "SHELL:-s EXPORT_NAME=\"create_gapi_gl_module\""
        "SHELL:-s EXPORTED_RUNTIME_METHODS=@${MODULE_GAPI_GL_LIB_DIR}/runtime-exports.json")

      # target_link_options(${target} PUBLIC 
      #   "SHELL:-s STRICT=1")
      # OR
      target_link_options(${target} PUBLIC "SHELL:-s BINARYEN_ASYNC_COMPILATION=1")

      if(MODULE_GAPI_GL_ALL_EXPORT)
        target_link_options(${target} PUBLIC "SHELL:-s LINKABLE=1") # Полный экспорт
      else()
        target_link_options(${target} PUBLIC "SHELL:-s EXPORTED_FUNCTIONS=@${MODULE_GAPI_GL_LIB_DIR}/exports.json") # Частичный экспорт
      endif()

      if(MODULE_GAPI_GL_LIB_TYPE STREQUAL "shared")
        target_link_options(${target} PUBLIC 
          "SHELL:-shared"
          "SHELL:-dynamiclib")

        if(MODULE_GAPI_GL_ALL_EXPORT)
          target_link_options(${target} PUBLIC "SHELL:-s SIDE_MODULE=2")
        else()
          target_link_options(${target} PUBLIC "SHELL:-s SIDE_MODULE=1")
        endif()
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
endif()

#---------------------------------------------------------------------------------
# Examples
#---------------------------------------------------------------------------------

if(MODULE_GAPI_GL_ENABLE_EXAMPLES AND NOT GLOB_EMSCRIPTEN_PLATFORM)
  message(STATUS "Examples have been enabled")

  add_subdirectory(examples/02-triangle)
  add_subdirectory(examples/03-ibo)
  add_subdirectory(examples/04-texture)
endif()

if(MODULE_GAPI_GL_ENABLE_EXAMPLES AND GLOB_EMSCRIPTEN_PLATFORM)
  message(STATUS "Examples have been enabled")

  # add_subdirectory(examples/01-dyn-webgl)
  # add_subdirectory(examples/02-triangle-webgl)
  add_subdirectory(examples/04-texture)
endif()

#---------------------------------------------------------------------------------
# Tests
#---------------------------------------------------------------------------------

if(MODULE_GAPI_GL_ENABLE_TESTS)
  if(${MODULE_GAPI_GL_SHARED_LIB} MATCHES "static")
    message(STATUS "[${MODULE_GAPI_GL_PROJ_NAME}]: Tests have been enabled")
    add_subdirectory(lib/cxx/tests/google)
  else()
    message(STATUS "[${MODULE_GAPI_GL_PROJ_NAME}]: Tests are only allowed with a static lib")
  endif()
endif()
