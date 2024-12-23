#### Конфигурируем проект для сборки

```console
cmake --preset default -B build

# deprecated
cmake -D CMAKE_BUILD_TYPE=Release \
      -D GLOB_EMSCRIPTEN_ROOT_DIR=/Users/<USER_NAME>/Documents/Third-party/emsdk/upstream/emscripten \
      -D GLOB_EMSCRIPTEN_PLATFORM=ON \
      -D GLOB_GTEST_ROOT_DIR= \
      -D GLOB_GMOCK_ROOT_DIR= \
      -D GLOB_GTEST_LIB_DIR= \
      -D GLOB_GMOCK_LIB_DIR= \
      -D MODULE_CORE_LIB_TYPE=object \
      -D MODULE_CORE_ENVIRONMENT=node \
      -D MODULE_CORE_COMPILATION=async \
      -D MODULE_PLTF_LIB_TYPE=object \
      -D MODULE_PLTF_ENVIRONMENT=node \
      -D MODULE_PLTF_COMPILATION=async \
      -D MODULE_GAPI_GL_ENVIRONMENT=node \
      -D MODULE_GAPI_GL_COMPILATION=async \
      -D MODULE_GAPI_GL_LIB_TYPE=shared \
      -D MODULE_GAPI_GL_MT=ON \
      -D MODULE_GAPI_GL_ENABLE_TESTS=OFF \
      -D MODULE_GAPI_GL_ENABLE_COVERAGE=OFF \
      -D MODULE_GAPI_GL_ENABLE_EXAMPLES=ON \
      ../
```

#### Собираем проект

```console
cmake --build build --preset Debug

# deprecated
cmake --build ./
```

#### Запускаем сервер

```console
python3 ./server.py
```

#### Запускаем приложение в браузере

```console
http://localhost:7800
```
