cmake_minimum_required(VERSION 3.12)
project(Canvas)

# Установка версии языка C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Поиск и подключение пакета SFML
find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

# Добавление пути к заголовочным файлам SFML
include_directories(include ${SFML_INCLUDE_DIRS})

# Добавление пути к исходным файлам
file(GLOB_RECURSE SOURCES "src/*.cpp" "src/GEO/*.cpp" "src/GUI/*.cpp")

# Создание исполняемого файла
add_executable(Canvas ${SOURCES})

# Подключение библиотек SFML
target_link_libraries(Canvas sfml-system sfml-window sfml-graphics)
