#### Конфигурируем проект для сборки

```console
cmake -D CMAKE_BUILD_TYPE=Release \
      -D MODULE_GAPI_GL_ENABLE_EXAMPLES=ON \
      ../
```

#### Запускаем сборку

```console
cmake --build ./
```

#### Запускаем приложение

```console
./../bin/libmodule_gapi_examples_triangle
```
