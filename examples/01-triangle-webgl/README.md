#### Конфигурируем проект для сборки

```console
cmake -DCMAKE_BUILD_TYPE=Release \
      -DGLOB_EMSCRIPTEN_ROOT_DIR=/Users/apriori85/Documents/Third-party/emsdk/upstream/emscripten \
      -DGLOB_EMSCRIPTEN_PLATFORM=ON \
      -DMODULE_GAPI_GL_ENABLE_EXAMPLES=ON ../
```

#### Собираем проект

```console
cmake --build ./
```

#### Запускаем сервер

```console
python3 -m http.server 7800 --directory ./../bin
```

#### Запускаем приложение в браузере

```console
http://localhost:7800
```
