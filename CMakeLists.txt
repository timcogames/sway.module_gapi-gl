# Проверяем версию CMake
cmake_minimum_required(VERSION 3.10.2 FATAL_ERROR)

# Мета-информация о проекте
set(META_PROJECT_NAME module_gapi_gl)
set(META_LIB_NAME lib${META_PROJECT_NAME})
set(META_VERSION_MAJOR 0)
set(META_VERSION_MINOR 6)
set(META_VERSION_PATCH 16)
set(META_VERSION ${META_VERSION_MAJOR}.${META_VERSION_MINOR}.${META_VERSION_PATCH})

# Опции сборки
option(BUILD_SHARED "Build shared library" OFF)
option(ENABLE_COVERAGE "Enable coverage builds" OFF)
option(ENABLE_TESTS "Enable test builds" OFF)
option(ENABLE_EXAMPLES "Enable example builds" OFF)

project(${META_PROJECT_NAME} C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(ENABLE_COVERAGE)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g ")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ftest-coverage")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
endif()

# Определяем каталог вывода по умолчанию
if(CMAKE_BUILD_TYPE MATCHES Debug)
	set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/dbg)
	set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/dbg)
else()
	set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
	set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
endif()

set(MODULE_GAPI_DIR ${CMAKE_CURRENT_LIST_DIR})

# Добавляем пути для поиска хедеров
include_directories(${MODULE_GAPI_DIR}/include)
include_directories(${MODULE_GAPI_DIR}/modules/sway.module_core/include)
include_directories(${MODULE_GAPI_DIR}/modules/sway.module_math/include)

# Получаем пути ко всем хедерам и исходникам библиотеки
file(GLOB_RECURSE MODULE_GAPI_HEADERS ${MODULE_GAPI_DIR}/include/*.*)
file(GLOB_RECURSE MODULE_GAPI_SOURCE ${MODULE_GAPI_DIR}/src/*.*)

find_package(OpenGL REQUIRED)
find_package(X11 REQUIRED)

set(Boost_USE_STATIC_LIBS ON)
set(BOOST_COMPONENTS system filesystem thread)
find_package(Boost 1.58 REQUIRED COMPONENTS ${BOOST_COMPONENTS})
if(NOT Boost_FOUND)
	message(FATAL_ERROR "Fatal error: Boost (version >= 1.58) required.")
else()
	message(STATUS "Boost includes: ${Boost_INCLUDE_DIRS}")
	message(STATUS "Boost libs: ${Boost_LIBRARIES}")

	include_directories(${Boost_INCLUDE_DIRS})
endif()

if(BUILD_SHARED)
	# Добавляем в проект цель для сборки динамической библиотеки
	add_library(${META_LIB_NAME} SHARED ${MODULE_GAPI_SOURCE})
	set_target_properties(${META_LIB_NAME} PROPERTIES OUTPUT_NAME ${META_PROJECT_NAME})
	set_target_properties(${META_LIB_NAME} PROPERTIES PREFIX "")
	set_target_properties(${META_LIB_NAME} PROPERTIES SUFFIX ".so.${META_VERSION}")
else()
	# Добавляем в проект цель для сборки статической библиотеки
	add_library(${META_LIB_NAME} STATIC ${MODULE_GAPI_SOURCE})
	set_target_properties(${META_LIB_NAME} PROPERTIES OUTPUT_NAME ${META_PROJECT_NAME})
	set_target_properties(${META_LIB_NAME} PROPERTIES PREFIX "")
	set_target_properties(${META_LIB_NAME} PROPERTIES SUFFIX ".a.${META_VERSION}")
endif()

target_link_libraries(${META_LIB_NAME} GL X11 ${Boost_LIBRARIES})

if(ENABLE_EXAMPLES OR ENABLE_TESTS)
	if(NOT TARGET libmodule_core)
		add_subdirectory(modules/sway.module_core)
	endif()
endif()

# Добавляем построение примеров
if(ENABLE_EXAMPLES)
	message(STATUS "Examples have been enabled")

	# Добавляем пути для поиска хедеров
	include_directories(${CMAKE_SOURCE_DIR}/modules/sway.module_platform-glx11/include)
	
	add_subdirectory(modules/sway.module_platform-glx11)
	add_subdirectory(examples)
endif()

# Добавляем построение тестов
if(ENABLE_TESTS)
	message(STATUS "Tests have been enabled")
	
	add_subdirectory(tests)
endif()

