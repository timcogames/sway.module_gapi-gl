# Мета-информация о проекте
set(META_PRJNAME_EXAMPLES "module_gapi_examples_texture")
set(META_LIBNAME_EXAMPLES "lib${META_PRJNAME_EXAMPLES}")

project(${META_PRJNAME_EXAMPLES} CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ldl")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(X11_INC_DIRS "/opt/X11/include")
set(X11_LIB_DIRS "/opt/X11/lib")

# Получаем пути ко всем исходникам с тестами
file(GLOB MODULE_GAPI_SOURCE_EXAMPLES "${PROJECT_SOURCE_DIR}/*.cpp")

include_directories("${MODULE_GAPI_GL_DIR}/submodules/sway.module_platform-glx11/lib/cxx/include")

add_executable(${META_LIBNAME_EXAMPLES} ${MODULE_GAPI_SOURCE_EXAMPLES})

target_link_libraries(${META_LIBNAME_EXAMPLES} X11 GLU module_pltf module_gapi_gl_obj module_core_obj)
