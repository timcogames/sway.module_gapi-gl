# Мета-информация о проекте
set(META_GAPI_GL_PRJNAME_TESTS "module_gapi_tests")
set(META_GAPI_GL_LIBNAME_TESTS "lib${META_GAPI_GL_PRJNAME_TESTS}")

project(${META_GAPI_GL_PRJNAME_TESTS} CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)

set(GTest_ROOT "${GLOB_GTEST_ROOT_DIR}")
set(GMOCK_INCLUDE_DIR "${GTest_ROOT}/googlemock/include")
set(GTEST_INCLUDE_DIR "${GTest_ROOT}/googletest/include")
set(GTEST_LIBRARY_DIR "${GTest_ROOT}/build/lib")

set(GTEST_MAIN_LIBRARY "${GTEST_LIBRARY_DIR}/gtest_main.lib")

# find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

include_directories(${GTEST_INCLUDE_DIR} ${GMOCK_INCLUDE_DIR})

# Получаем пути ко всем исходникам с тестами
file(GLOB MODULE_GAPI_GL_SOURCE_TESTS ${PROJECT_SOURCE_DIR}/*.cpp)

add_executable(${META_GAPI_GL_LIBNAME_TESTS} ${MODULE_GAPI_GL_SOURCE_TESTS} "${GTest_ROOT}/googletest/src/gtest_main.cc")
target_link_libraries(${META_GAPI_GL_LIBNAME_TESTS} libmodule_gapi_gl libmodule_core ${GTEST_LIBRARY_DIR}/libgtest.a ${GTEST_LIBRARY_DIR}/libgmock.a ${CMAKE_DL_LIBS})

add_custom_command(TARGET ${META_GAPI_GL_LIBNAME_TESTS} POST_BUILD COMMAND ${META_GAPI_GL_LIBNAME_TESTS})
