# Проверяем версию CMake
cmake_minimum_required(VERSION 3.14.3 FATAL_ERROR)

include("${CMAKE_CURRENT_SOURCE_DIR}/submodules/sway.module_core/cmakehelpers/custom_enable_cxx17.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/submodules/sway.module_core/cmakehelpers/custom_add_subdirectory.cmake")

# Мета-информация о проекте
set(META_GAPI_GL_PRJNAME "module_gapi_gl")
set(META_GAPI_GL_LIBNAME "lib${META_GAPI_GL_PRJNAME}")
set(META_GAPI_GL_VERSION_MAJOR 0)
set(META_GAPI_GL_VERSION_MINOR 16)
set(META_GAPI_GL_VERSION_PATCH 34)
set(META_GAPI_GL_VERSION ${META_GAPI_GL_VERSION_MAJOR}.${META_GAPI_GL_VERSION_MINOR}.${META_GAPI_GL_VERSION_PATCH})

# Опции сборки
option(MODULE_GAPI_GL_SHARED_LIB "Build shared library (.so)" OFF)
option(MODULE_GAPI_GL_ENABLE_COVERAGE "Enable coverage builds" OFF)
option(MODULE_GAPI_GL_ENABLE_TESTS "Enable test builds" OFF)
option(MODULE_GAPI_GL_ENABLE_EXAMPLES "Enable example builds" OFF)
option(MODULE_USE_AS_STUB "Enable test builds" OFF)
option(MODULE_USE_EMSCRIPTEN "Using emscripten compiler" OFF)
option(CUSTOM_EMSCRIPTEN_ROOT_DIR "Emscripten root directory" OFF)
option(CUSTOM_BOOST_ROOT_DIR "Boost root directory" OFF)
option(CUSTOM_GTEST_ROOT_DIR "GTest root directory" OFF)

if (NOT DEFINED CMAKE_TOOLCHAIN_FILE AND MODULE_USE_EMSCRIPTEN)
  set(CMAKE_TOOLCHAIN_FILE "${CUSTOM_EMSCRIPTEN_ROOT_DIR}/cmake/Modules/Platform/Emscripten.cmake")
  include(${CMAKE_TOOLCHAIN_FILE})
endif ()

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build" FORCE)
endif ()

project(${META_GAPI_GL_PRJNAME} VERSION ${META_GAPI_GL_VERSION} LANGUAGES CXX)

# Подмодули
custom_add_subdirectory("libmodule_core" submodules/sway.module_core)

if (MODULE_USE_EMSCRIPTEN)
  set(CMAKE_CXX_COMPILER "${CUSTOM_EMSCRIPTEN_ROOT_DIR}/em++")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --bind -Os")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_EMSCRIPTEN -s FULL_ES3=1")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-unknown-pragmas -Wno-unicode-whitespace \
      -Wno-unused-local-typedef -Wno-invalid-noreturn -Wno-unused-command-line-argument")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s WASM=1 -s MODULARIZE=1")
endif ()

if (MODULE_GAPI_GL_ENABLE_TESTS OR MODULE_USE_AS_STUB)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_STUB")
endif ()

message("[${META_GAPI_GL_PRJNAME}]: ${META_GAPI_GL_VERSION}
         compiler | ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}
       build type | ${CMAKE_BUILD_TYPE}
       shared lib | ${MODULE_CORE_SHARED_LIB}
         cxxflags | ${CMAKE_CXX_FLAGS} ${EXTRA_FLAGS}
 build type flags | ${BUILD_TYPE_CXX_FLAGS}
        build dir | ${CMAKE_BINARY_DIR}
   install prefix | ${CMAKE_INSTALL_PREFIX}

   emscripten dir | ${CUSTOM_EMSCRIPTEN_ROOT_DIR}
        boost dir | ${CUSTOM_BOOST_ROOT_DIR}
        gtest dir | ${CUSTOM_GTEST_ROOT_DIR}

             stub | ${MODULE_USE_AS_STUB}
       emscripten | ${MODULE_USE_EMSCRIPTEN}
         coverage | ${MODULE_GAPI_GL_ENABLE_COVERAGE}
            tests | ${MODULE_GAPI_GL_ENABLE_TESTS}
         examples | ${MODULE_GAPI_GL_ENABLE_EXAMPLES}
")

# Определяем каталог вывода по умолчанию
if (CMAKE_BUILD_TYPE MATCHES Debug)
  set(LIBRARY_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/bin/dbg")
  set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/bin/dbg")
else ()
  set(LIBRARY_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/bin")
  set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/bin")
endif ()

set(GLUT_INCLUDE_DIRS "/opt/X11/include")
set(GLUT_LIBRARY_DIRS "/opt/X11/lib")
set(MODULE_GAPI_GL_DIR ${CMAKE_CURRENT_LIST_DIR})

# Добавляем пути для поиска хедеров
include_directories("${GLUT_INCLUDE_DIRS}")
include_directories("${MODULE_GAPI_GL_DIR}/lib/include")
include_directories("${MODULE_GAPI_GL_DIR}/submodules/sway.module_core/lib/include")
include_directories("${MODULE_GAPI_GL_DIR}/submodules/sway.module_math/lib/include")
include_directories("${MODULE_GAPI_GL_DIR}/submodules/sway.module_gapi/include")

include_directories("${MODULE_GAPI_GL_DIR}/submodules/sway.module_platform-glx11/include")

# Получаем пути ко всем хедерам и исходникам библиотеки
file(GLOB_RECURSE MODULE_GAPI_GL_HEADERS "${MODULE_GAPI_GL_DIR}/lib/include/*.*")
file(GLOB_RECURSE MODULE_GAPI_GL_SOURCES "${MODULE_GAPI_GL_DIR}/lib/src/*.*")

find_package(OpenGL REQUIRED)
find_library(GLUT_glut_LIBRARY GLUT DOC "GLUT library for OSX")

link_directories("${GLUT_LIBRARY_DIRS}")

if (MODULE_GAPI_GL_SHARED_LIB)
  set(CMAKE_CXX_COMPILER "g++")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Werror -pedantic")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-parameter -Wno-return-type -Wno-int-to-pointer-cast -Wno-variadic-macros -Wno-null-pointer-arithmetic")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=default -fPIE")

  # Добавляем в проект цель для сборки динамической библиотеки
  add_library(${META_GAPI_GL_LIBNAME} SHARED ${MODULE_GAPI_GL_SOURCES})
  set_target_properties(${META_GAPI_GL_LIBNAME} PROPERTIES OUTPUT_NAME ${META_GAPI_GL_PRJNAME})
  set_target_properties(${META_GAPI_GL_LIBNAME} PROPERTIES PREFIX "")
  set_target_properties(${META_GAPI_GL_LIBNAME} PROPERTIES SUFFIX ".dylib.${META_GAPI_GL_VERSION}")
  # set_target_properties(${META_GAPI_GL_LIBNAME} PROPERTIES SUFFIX ".so.${META_GAPI_GL_VERSION}")
  target_compile_definitions(${META_GAPI_GL_LIBNAME} PRIVATE -DBUILD_DLLAPI_LIBMODULE)
else ()
  # Добавляем в проект цель для сборки статической библиотеки
  add_library(${META_GAPI_GL_LIBNAME} STATIC ${MODULE_GAPI_GL_SOURCES})
  set_target_properties(${META_GAPI_GL_LIBNAME} PROPERTIES OUTPUT_NAME ${META_GAPI_GL_PRJNAME})
  set_target_properties(${META_GAPI_GL_LIBNAME} PROPERTIES PREFIX "")
  set_target_properties(${META_GAPI_GL_LIBNAME} PROPERTIES SUFFIX ".a.${META_GAPI_GL_VERSION}")
endif ()

custom_enable_cxx17(${META_GAPI_GL_LIBNAME})
target_link_libraries(${META_GAPI_GL_LIBNAME} libmodule_core GL GLESv2 ${GLUT_LIBRARY} ${OPENGL_LIBRARY})

# Добавляем построение примеров
if (MODULE_GAPI_GL_ENABLE_EXAMPLES AND NOT MODULE_USE_EMSCRIPTEN)
  message(STATUS "Examples have been enabled")

  custom_add_subdirectory("libmodule_platform_glx11" submodules/sway.module_platform-glx11)
  add_subdirectory(examples/01-triangle)
  add_subdirectory(examples/02-ibo)
endif ()

if (MODULE_GAPI_GL_ENABLE_EXAMPLES AND MODULE_USE_EMSCRIPTEN)
  message(STATUS "Examples have been enabled")

  add_subdirectory(examples/01-triangle-webgl)
endif ()

# Добавляем построение тестов
if (MODULE_GAPI_GL_ENABLE_TESTS)
  if (MODULE_GAPI_GL_SHARED_LIB)
    message(STATUS "[${META_GAPI_GL_PRJNAME}]: Tests are only allowed with a static lib")
  else ()
    message(STATUS "[${META_GAPI_GL_PRJNAME}]: Tests have been enabled")
    add_subdirectory(lib/tests/google)
  endif ()
endif ()
