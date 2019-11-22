find_package(Qt5Widgets)
set(CMAKE_AUTOMOC TRUE)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_subdirectory(lib/src)
add_subdirectory(marble)
add_subdirectory(rubik)
add_subdirectory(ssgame)

