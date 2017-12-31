set(PROJECT sidescroller)

if(${QT_VERSION} EQUAL 5)
	find_package(Qt5OpenGL REQUIRED)
else()
	find_package(Qt4 COMPONENTS REQUIRED QtOpenGL)
	include(${QT_USE_FILE})
	add_definitions(${QT_DEFINITIONS})
endif()
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

if(${QT_VERSION}==5)
	qt5_use_modules(${PROJECT} OpenGL)
else()
endif()

target_link_libraries(${PROJECT} gamelib ${OPENGL_LIBRARIES} ${QT_LIBRARIES})
