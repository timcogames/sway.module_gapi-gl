# Мета-информация о проекте
set(META_PROJECT_NAME_EXAMPLES module_gapi_examples)
set(META_LIB_NAME_EXAMPLES lib${META_PROJECT_NAME_EXAMPLES})

project(${META_PROJECT_NAME_EXAMPLES} C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

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

# Получаем пути ко всем исходникам с тестами
file(GLOB MODULE_GAPI_SOURCE_EXAMPLES ${PROJECT_SOURCE_DIR}/*.cpp)

add_executable(${META_LIB_NAME_EXAMPLES} ${MODULE_GAPI_SOURCE_EXAMPLES})

target_include_directories(${META_LIB_NAME_EXAMPLES} PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(${META_LIB_NAME_EXAMPLES} GLU libmodule_platform_glx11 libmodule_gapi_gl libmodule_core ${Boost_LIBRARIES})
