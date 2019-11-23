set(PROJECT sidescroller)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/src)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../lib/src)

set(SRC
	main.cpp
	mainwindow.cpp
	levelwindow.cpp
  glwidget.cpp
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

add_executable(${PROJECT} ${SRC} ssgame.qrc)

qt5_use_modules(${PROJECT} OpenGL)

target_link_libraries(${PROJECT} gamelib ${OPENGL_LIBRARIES} ${QT_LIBRARIES})
