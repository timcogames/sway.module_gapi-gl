#### Конфигурируем проект для Google тестов

```console
cmake -DGLOB_GTEST_ROOT_DIR=/Users/apriori85/Documents/Third-party/googletest \
      -DMODULE_GAPI_GL_ENABLE_TESTS=ON ../
```

#### Запускаем сборку

```console
cmake --build ./
```
