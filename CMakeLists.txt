project(games)

find_package(Qt5Widgets)
find_package(Qt5OpenGL REQUIRED)
find_package(OpenGL REQUIRED)

set(CMAKE_AUTOMOC TRUE)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

if(MSVC)
  add_compile_options(/W1 /WX)
else()
  add_compile_options(-Wall -Wextra -Werror -fsanitize=address)
endif()

add_subdirectory(lib/src)
add_subdirectory(marble)
add_subdirectory(rubik)
add_subdirectory(ssgame)
add_subdirectory(racing)
add_subdirectory(stick)
