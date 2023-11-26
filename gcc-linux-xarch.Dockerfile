ARG TARGET_PLATFORM=

#_________________________________________________________________________________
#                                                                      Build stage

FROM --platform=$TARGET_PLATFORM gcc:10 AS base

#_________________________________________________________________________________
#                                                                             Info

LABEL Victor Timoshin <victor-timoshin@hotmail.com>

#_________________________________________________________________________________
#                                                                             Args

# ARG TARGET_PLATFORM_OS==<not used>
ARG TARGET_PLATFORM_ARCH=

ARG GTEST_ROOT_DIR=/usr/src/gtest
ARG GTEST_LIB_DIR=/tmp/lib
ARG ENABLED_TESTS=
ARG ENABLED_COVERAGE=

#_________________________________________________________________________________
#                                                                          Install

RUN apt-get update -y && apt-get install -y \
    cmake \
    lcov \
    libgtest-dev

RUN `([ $TARGET_PLATFORM_ARCH = arm64/v8 ] && ln -s /usr/lib/aarch64-linux-gnu /tmp/lib ) || \
     ([ $TARGET_PLATFORM_ARCH = arm64 ] && ln -s /usr/lib/aarch64-linux-gnu /tmp/lib ) || \
     ([ $TARGET_PLATFORM_ARCH = amd64 ] && ln -s /usr/lib/x86_64-linux-gnu /tmp/lib )`

#_________________________________________________________________________________
#                                              Copy project files to the workspace

COPY /lib /module_gapi_gl_workspace/lib
COPY /cmake_modules /module_gapi_gl_workspace/cmake_modules
COPY /CMakeLists.txt /module_gapi_gl_workspace
COPY /index.html /module_gapi_gl_workspace

RUN mkdir /module_gapi_gl_workspace/lcov_report

#_________________________________________________________________________________
#                                                          Build development image

FROM base as module_gapi_gl-debug

WORKDIR /module_gapi_gl_workspace/build

RUN cmake -DCMAKE_BUILD_TYPE=Debug \
          -DGLOB_GTEST_ROOT_DIR=$GTEST_ROOT_DIR \
          -DGLOB_GTEST_LIB_DIR=$GTEST_LIB_DIR \
          -DMODULE_GAPI_GL_ENABLE_TESTS=$ENABLED_TESTS \
          -DMODULE_GAPI_GL_ENABLE_COVERAGE=$ENABLED_COVERAGE ../

RUN cmake --build ./

WORKDIR /module_gapi_gl_workspace

ENTRYPOINT ["tail"]
CMD ["-f", "/dev/null"]

#_________________________________________________________________________________
#                                                           Build production image

FROM base as module_gapi_gl-release

WORKDIR /module_gapi_gl_workspace/build

RUN cmake -DCMAKE_BUILD_TYPE=Release \
          -DGLOB_GTEST_ROOT_DIR=$GTEST_ROOT_DIR \
          -DGLOB_GTEST_LIB_DIR=$GTEST_LIB_DIR \
          -DMODULE_GAPI_GL_ENABLE_TESTS=$ENABLED_TESTS \
          -DMODULE_GAPI_GL_ENABLE_COVERAGE=$ENABLED_COVERAGE ../

RUN cmake --build ./

WORKDIR /module_gapi_gl_workspace

ENTRYPOINT ["tail"]
CMD ["-f", "/dev/null"]
