# Мета-информация о проекте
set(META_PRJNAME_EXAMPLES "module_gapi_examples_triangle")
set(META_LIBNAME_EXAMPLES "lib${META_PRJNAME_EXAMPLES}")

project(${META_PRJNAME_EXAMPLES} CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ldl")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Получаем пути ко всем исходникам с тестами
file(GLOB MODULE_GAPI_SOURCE_EXAMPLES "${PROJECT_SOURCE_DIR}/*.cpp")

add_executable(${META_LIBNAME_EXAMPLES} ${MODULE_GAPI_SOURCE_EXAMPLES})

target_include_directories(${META_LIBNAME_EXAMPLES} PRIVATE ${BOOST_INCLUDEDIR})
target_link_libraries(${META_LIBNAME_EXAMPLES} GLU libmodule_platform_glx11 libmodule_gapi_gl libmodule_core ${BOOST_LIBRARIES})
