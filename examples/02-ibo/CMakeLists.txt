# Мета-информация о проекте
set(META_PRJNAME_EXAMPLES "module_gapi_examples_ibo")
set(META_LIBNAME_EXAMPLES "lib${META_PRJNAME_EXAMPLES}")

project(${META_PRJNAME_EXAMPLES} CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ldl")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Получаем пути ко всем исходникам с тестами
file(GLOB MODULE_GAPI_SOURCE_EXAMPLES "${PROJECT_SOURCE_DIR}/*.cpp")

include_directories("${MODULE_GAPI_GL_DIR}/submodules/sway.module_platform-glx11/lib/include")

add_executable(${META_LIBNAME_EXAMPLES} ${MODULE_GAPI_SOURCE_EXAMPLES})

target_link_libraries(${META_LIBNAME_EXAMPLES} GLU libmodule_pltf libmodule_gapi_gl libmodule_core)
