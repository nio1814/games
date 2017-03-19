set(PROJECT sidescroller)

find_package(Qt5OpenGL REQUIRED)
find_package(OpenGL REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/src)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../lib/src)

set(SRC
	main.cpp
	mainwindow.cpp
	levelwindow.cpp
	src/game.cpp
	src/objects.cpp
	src/level.cpp
	src/playerkeys.cpp
	src/animation.cpp
	src/screen.cpp
	src/movement.cpp
	src/functions.cpp
#	src/sound.cpp
)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_executable(${PROJECT} ${SRC} ssgame.qrc)

qt5_use_modules(${PROJECT} OpenGL)

target_link_libraries(${PROJECT} gamelib ${OPENGL_LIBRARIES})
