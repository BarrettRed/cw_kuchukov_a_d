### **README.md**

# Chess Game

Шахматное приложение на C++ с графическим интерфейсом, поддерживающее основные правила шахмат, работу с таймерами и сохранение/загрузку игры.  

## **Особенности**
- Полная реализация правил шахмат.
- Графический интерфейс с использованием SFML.
- Возможность сохранения и загрузки игр в формате JSON.
- Таймеры для отслеживания времени каждого игрока.

---

## **Зависимости**

Для сборки приложения необходимо установить следующие библиотеки:
- [SFML](https://www.sfml-dev.org/) (версии 2.5 и выше)
- [nlohmann-json](https://github.com/nlohmann/json)
- [tinyfiledialogs](https://sourceforge.net/projects/tinyfiledialogs/)
- [doctest](https://github.com/doctest/doctest) (опционально, для тестов)

Все зависимости устанавливаются с помощью менеджера пакетов [vcpkg](https://vcpkg.io/).

---

## **Сборка проекта**

### **1. Установка vcpkg**
Если vcpkg ещё не установлен, выполните следующие шаги:
```bash
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.bat
```

### **2. Установка зависимостей**
Убедитесь, что используете триплет `x64-windows`. Для установки всех необходимых библиотек выполните:
```bash
vcpkg install sfml nlohmann-json tinyfiledialogs doctest --triplet x64-windows
```

### **3. Сборка проекта**
1. В корне репозитория выполните команды:
    ```bash
    cmake -B build -DCMAKE_TOOLCHAIN_FILE="<путь_до_вашей_папки_vcpkg>/scripts/buildsystems/vcpkg.cmake"
    cmake --build build --config Release
    cmake --install build --config Release
    ```

2. После сборки исполняемый файл будет находиться в папке `install/bin/`.

---

## **Запуск**
 
1. Перейдите в папку `install/bin`:
    ```bash
    cd install/bin
    ```
2. Запустите приложение:
    ```bash
    CHESS_GAME.exe
    ```

---

## **Документация**
Документация, сгенерированная с помощью Doxygen, доступна в папке `install/docs/html`. Для просмотра откройте файл `index.html` в браузере.  

---

## **Тестирование** (опционально)
Для запуска тестов выполните:
```bash
cd bin.rel/test
chess_test.exe
```

