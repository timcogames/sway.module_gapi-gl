ARG TARGET_PLATFORM=

#_________________________________________________________________________________
#                                                                      Build stage

FROM --platform=$TARGET_PLATFORM emscripten/emsdk:latest AS base

#_________________________________________________________________________________
#                                                                             Info

LABEL Victor Timoshin <victor-timoshin@hotmail.com>

#_________________________________________________________________________________
#                                                                             Args

# ARG TARGET_PLATFORM_OS=<not used>
# ARG TARGET_PLATFORM_ARCH=<not used>

ARG GTEST_ROOT_DIR=/usr/src/gtest
ARG GMOCK_ROOT_DIR=/usr
ARG GTEST_LIB_DIR=/tmp/lib
ARG GMOCK_LIB_DIR=/tmp/lib
ARG ENABLED_TESTS=
ARG ENABLED_COVERAGE=
ARG ENABLED_EXAMPLES=

#_________________________________________________________________________________
#                                                                       Copy files

COPY /lib /module_gapi_gl_workspace/lib
COPY /submodules /module_gapi_gl_workspace/submodules
COPY /cmake_modules /module_gapi_gl_workspace/cmake_modules
COPY /examples /module_gapi_gl_workspace/examples
COPY /CMakeLists.txt /module_gapi_gl_workspace
COPY /index.html /module_gapi_gl_workspace

RUN mkdir /module_gapi_gl_workspace/lcov_report

#_________________________________________________________________________________
#                                                          Build development image

FROM base as module_gapi_gl-debug
WORKDIR /module_gapi_gl_workspace/build

RUN cmake -D CMAKE_BUILD_TYPE=Debug \
          -D GLOB_EMSCRIPTEN_ROOT_DIR=/emsdk/upstream/emscripten \
          -D GLOB_EMSCRIPTEN_PLATFORM=ON \
          -D MODULE_CORE_ENVIRONMENT=web,node \
          -D MODULE_CORE_COMPILATION=async \
          -D GLOB_GTEST_ROOT_DIR=$GTEST_ROOT_DIR \
          -D GLOB_GMOCK_ROOT_DIR=$GMOCK_ROOT_DIR \
          -D GLOB_GTEST_LIB_DIR=$GTEST_LIB_DIR \
          -D GLOB_GMOCK_LIB_DIR=$GMOCK_LIB_DIR \
          -D MODULE_GAPI_GL_ENABLE_TESTS=$ENABLED_TESTS \
          -D MODULE_GAPI_GL_ENABLE_COVERAGE=$ENABLED_COVERAGE \
          -D MODULE_GAPI_GL_ENABLE_EXAMPLES=$ENABLED_EXAMPLES

RUN cmake --build .

WORKDIR /module_gapi_gl_workspace

ENTRYPOINT ["tail"]
CMD ["-f", "/dev/null"]

#_________________________________________________________________________________
#                                                           Build production image

FROM base as module_gapi_gl-release
WORKDIR /module_gapi_gl_workspace/build

RUN cmake -D CMAKE_BUILD_TYPE=Release \
          -D GLOB_EMSCRIPTEN_ROOT_DIR=/emsdk/upstream/emscripten \
          -D GLOB_EMSCRIPTEN_PLATFORM=ON \
          -D MODULE_CORE_ENVIRONMENT=web,node \
          -D MODULE_CORE_COMPILATION=async \
          -D GLOB_GTEST_ROOT_DIR=$GTEST_ROOT_DIR \
          -D GLOB_GMOCK_ROOT_DIR=$GMOCK_ROOT_DIR \
          -D GLOB_GTEST_LIB_DIR=$GTEST_LIB_DIR \
          -D GLOB_GMOCK_LIB_DIR=$GMOCK_LIB_DIR \
          -D MODULE_GAPI_GL_ENABLE_TESTS=$ENABLED_TESTS \
          -D MODULE_GAPI_GL_ENABLE_COVERAGE=$ENABLED_COVERAGE \
          -D MODULE_GAPI_GL_ENABLE_EXAMPLES=$ENABLED_EXAMPLES ../

RUN cmake --build ./

WORKDIR /module_gapi_gl_workspace

ENTRYPOINT ["tail"]
CMD ["-f", "/dev/null"]