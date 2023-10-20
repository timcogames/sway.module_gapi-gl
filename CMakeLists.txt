# Проверяем версию CMake
cmake_minimum_required(VERSION 3.14.3 FATAL_ERROR)

set(MODULE_GAPI_GL_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(MODULE_GAPI_GL_CMAKE_DIR ${MODULE_GAPI_GL_ROOT_DIR}/submodules/sway.module_core/cmakehelpers)
set(MODULE_GAPI_GL_LIB_DIR ${MODULE_GAPI_GL_ROOT_DIR}/lib)
set(MODULE_GAPI_GL_BIN_DIR ${CMAKE_SOURCE_DIR}/bin)

include("${MODULE_GAPI_GL_CMAKE_DIR}/options.cmake")
include("${MODULE_GAPI_GL_CMAKE_DIR}/set_output_dir.cmake")
include("${MODULE_GAPI_GL_CMAKE_DIR}/project_metadata.cmake")
include("${MODULE_GAPI_GL_CMAKE_DIR}/enable_cxx17.cmake")
include("${MODULE_GAPI_GL_CMAKE_DIR}/add_submodule.cmake")

# Мета-информация о проекте
set(META_GAPI_GL_PRJNAME "module_gapi_gl")
set(META_GAPI_GL_LIBNAME "lib${META_GAPI_GL_PRJNAME}")
set(META_GAPI_GL_VERSION_MAJOR 0)
set(META_GAPI_GL_VERSION_MINOR 16)
set(META_GAPI_GL_VERSION_PATCH 34)
set(META_GAPI_GL_VERSION ${META_GAPI_GL_VERSION_MAJOR}.${META_GAPI_GL_VERSION_MINOR}.${META_GAPI_GL_VERSION_PATCH})

# Опции сборки
option(MODULE_GAPI_GL_SHARED_LIB "Build shared library (.so)" OFF)
option(MODULE_GAPI_GL_MT "Enable multithreading" OFF)
option(MODULE_GAPI_GL_ENABLE_COVERAGE "Enable coverage builds" OFF)
option(MODULE_GAPI_GL_ENABLE_TESTS "Enable test builds" OFF)
option(MODULE_GAPI_GL_ENABLE_EXAMPLES "Enable example builds" OFF)
option(MODULE_USE_AS_STUB "Enable test builds" OFF)

if (NOT DEFINED CMAKE_TOOLCHAIN_FILE AND GLOB_EMSCRIPTEN_PLATFORM)
  set(CMAKE_TOOLCHAIN_FILE "${GLOB_EMSCRIPTEN_ROOT_DIR}/cmake/Modules/Platform/Emscripten.cmake")
  include(${CMAKE_TOOLCHAIN_FILE})
endif ()

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build" FORCE)
endif ()

project(${META_GAPI_GL_PRJNAME} VERSION ${META_GAPI_GL_VERSION} LANGUAGES CXX)

# Подмодули
add_submodule("core" submodules/sway.module_core)

if (GLOB_EMSCRIPTEN_PLATFORM)
  set_property(GLOBAL PROPERTY TARGET_SUPPORTS_SHARED_LIBS TRUE)
  set(CMAKE_CXX_COMPILER "${GLOB_EMSCRIPTEN_ROOT_DIR}/em++")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --no-entry")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Os -Wall -std=c++17 -shared -dynamiclib")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unknown-pragmas -Wno-unicode-whitespace \
      -Wno-unused-local-typedef -Wno-invalid-noreturn -Wno-unused-command-line-argument")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DEMSCRIPTEN_PLATFORM")

  # set(EMSCRIPTEN_THREADS -s USE_PTHREADS=1 
  #                        -s PTHREAD_POOL_SIZE=8 
  #                        -s IMPORTED_MEMORY=1 
  #                        -s ALLOW_BLOCKING_ON_MAIN_THREAD=1)

  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s WASM=1")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Oz --profiling-funcs")
  if (MODULE_GAPI_GL_SHARED_LIB)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s SIDE_MODULE=1")
  endif ()
  if (MODULE_GAPI_GL_MT)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,--shared-memory,--no-check-features")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_PTHREADS=1 -s PTHREAD_POOL_SIZE=8")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s IMPORTED_MEMORY=1")
  endif ()
  # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s MODULARIZE=1 -s EXPORT_NAME=\"pluginInitialize\"")
  # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s EXPORT_ALL=1")
  # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s EXPORTED_FUNCTIONS=[\"_pluginInitialize\"]") # Функция уже помечена EMSCRIPTEN_KEEPALIVE
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s FULL_ES3=1")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s SUPPORT_LONGJMP=0")
  # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s STANDALONE_WASM=1") # wasi_snapshot_preview1
  # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s PROXY_TO_WORKER=1")
  # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s PROXY_TO_PTHREAD=1")
  # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s BUILD_AS_WORKER=1")
  # set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s USE_PTHREADS=1")
  # set(CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS "${CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS} -s USE_PTHREADS=1")

  # set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -sWASM=1 -sSIDE_MODULE=1")
  # # set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -sMODULARIZE=1 -sBUILD_AS_SHARED_LIB=1 -sEXPORT_ALL=1 -sDISABLE_EXCEPTION_CATCHING=0 -sFORCE_FILESYSTEM=1 -sSINGLE_FILE=1 -sBINARYEN_ASYNC_COMPILATION=0")
  # set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -sMODULARIZE=1 -sEXPORT_NAME=\"createModule\" -sEXPORT_ALL=1")
  # set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -sFULL_ES3=1")
  # set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${EMSCRIPTEN_THREADS}")
  # set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -sSTRICT_JS=1 -sDYNAMIC_EXECUTION=0 -sNO_POLYFILL=1 -sUSE_CLOSURE_COMPILER=0 -sEXPORTED_RUNTIME_METHODS=FS,wasmMemory,allocateUTF8OnStack")

  # set(CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS "${CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS} -sWASM=1 -sSIDE_MODULE=1")
  # set(CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS "${CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS} -sMODULARIZE=1 -sEXPORT_NAME=\"createModule\" -sEXPORT_ALL=1")
  # set(CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS "${CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS} -sFULL_ES3=1")
  # set(CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS "${CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS} -sDISABLE_EXCEPTION_CATCHING=0 -sFORCE_FILESYSTEM=1 -sSINGLE_FILE=1 -sBINARYEN_ASYNC_COMPILATION=0")
  # set(CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS "${CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS} ${EMSCRIPTEN_THREADS} -sPROXY_TO_PTHREAD=1")
  # set(CMAKE_STRIP TRUE) 
endif ()

if (MODULE_GAPI_GL_SHARED_LIB AND NOT GLOB_EMSCRIPTEN_PLATFORM)
  set(CMAKE_CXX_COMPILER "g++")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Werror -pedantic")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-variable -Wno-unused-parameter -Wno-return-stack-address -Wno-return-type -Wno-int-to-pointer-cast -Wno-variadic-macros -Wno-null-pointer-arithmetic")
endif ()

# add_definitions(-sUSE_PTHREADS)
# add_compile_options("SHELL:-sUSE_PTHREADS=1 -sIMPORTED_MEMORY=1 -sPTHREAD_POOL_SIZE=8")
# add_link_options("SHELL:-sUSE_PTHREADS=1 -sIMPORTED_MEMORY=1 -sPTHREAD_POOL_SIZE=8")

if (MODULE_GAPI_GL_ENABLE_TESTS OR MODULE_USE_AS_STUB)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_STUB")
endif ()

message("[${META_GAPI_GL_PRJNAME}]: ${META_GAPI_GL_VERSION}
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
# include_directories("${GLOB_EMSCRIPTEN_ROOT_DIR}/system/include")
include_directories("${MODULE_GAPI_GL_DIR}/lib/include")
include_directories("${MODULE_GAPI_GL_DIR}/submodules/sway.module_core/lib/cpp/include")
include_directories("${MODULE_GAPI_GL_DIR}/submodules/sway.module_math/lib/cpp/include")
include_directories("${MODULE_GAPI_GL_DIR}/submodules/sway.module_gapi/include")
include_directories("${MODULE_GAPI_GL_DIR}/submodules/sway.module_platform-glx11/cpp/include")

# Получаем пути ко всем хедерам и исходникам библиотеки
file(GLOB_RECURSE MODULE_GAPI_GL_HEADERS "${MODULE_GAPI_GL_DIR}/lib/include/*.*")
file(GLOB_RECURSE MODULE_GAPI_GL_SOURCES "${MODULE_GAPI_GL_DIR}/lib/src/*.*")

find_package(OpenGL REQUIRED)
find_library(GLUT_glut_LIBRARY GLUT DOC "GLUT library for OSX")

link_directories("${GLUT_LIBRARY_DIRS}")

if (MODULE_GAPI_GL_SHARED_LIB)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -fexceptions -fvisibility=hidden")

  # Добавляем в проект цель для сборки динамической библиотеки
  add_library(${META_GAPI_GL_LIBNAME} SHARED ${MODULE_GAPI_GL_SOURCES})
  set_target_properties(${META_GAPI_GL_LIBNAME} PROPERTIES OUTPUT_NAME ${META_GAPI_GL_PRJNAME})
  set_target_properties(${META_GAPI_GL_LIBNAME} PROPERTIES PREFIX "")
  if (GLOB_EMSCRIPTEN_PLATFORM)
    set_target_properties(${META_GAPI_GL_LIBNAME} PROPERTIES SUFFIX ".wasm")
  else ()
    set_target_properties(${META_GAPI_GL_LIBNAME} PROPERTIES SUFFIX ".dylib.${META_GAPI_GL_VERSION}")
    # set_target_properties(${META_GAPI_GL_LIBNAME} PROPERTIES SUFFIX ".so.${META_GAPI_GL_VERSION}")
  endif ()
  target_compile_definitions(${META_GAPI_GL_LIBNAME} PRIVATE -DBUILD_DLLAPI_LIBMODULE)
else ()
  # Добавляем в проект цель для сборки статической библиотеки
  add_library(${META_GAPI_GL_LIBNAME} STATIC ${MODULE_GAPI_GL_SOURCES})
  set_target_properties(${META_GAPI_GL_LIBNAME} PROPERTIES OUTPUT_NAME ${META_GAPI_GL_PRJNAME})
  set_target_properties(${META_GAPI_GL_LIBNAME} PROPERTIES PREFIX "")
  set_target_properties(${META_GAPI_GL_LIBNAME} PROPERTIES SUFFIX ".a.${META_GAPI_GL_VERSION}")
endif ()

enable_cxx17(${META_GAPI_GL_LIBNAME})
target_link_libraries(${META_GAPI_GL_LIBNAME} module_core GL GLESv2 ${GLUT_LIBRARY} ${OPENGL_LIBRARY})

# Добавляем построение примеров
if (MODULE_GAPI_GL_ENABLE_EXAMPLES AND NOT GLOB_EMSCRIPTEN_PLATFORM)
  message(STATUS "Examples have been enabled")

  add_submodule("libmodule_platform_glx11" submodules/sway.module_platform-glx11)
  add_subdirectory(examples/01-triangle)
  add_subdirectory(examples/02-ibo)
  add_subdirectory(examples/03-texture)
endif ()

if (MODULE_GAPI_GL_ENABLE_EXAMPLES AND GLOB_EMSCRIPTEN_PLATFORM)
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
