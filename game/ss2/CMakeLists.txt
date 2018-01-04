cmake_minimum_required(VERSION 3.6)

project(ss2)

if(${QT_VERSION} EQUAL 5)
	find_package(Qt5OpenGL REQUIRED)
else()
	find_package(Qt4 COMPONENTS REQUIRED QtOpenGL)
	include(${QT_USE_FILE})
	add_definitions(${QT_DEFINITIONS})
endif()
find_package(OpenGL REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SS2_SOURCE
	main.cpp
	mainwindow.cpp
	levelwindow.cpp
	level.cpp
	object.cpp
	glwidget.cpp
	vectornd.cpp
	vector3d.cpp
	vector2d.cpp
	mass.cpp
#	${CMAKE_CURRENT_SOURCE_DIR}/../lib/src/light.cpp
	camera.cpp
#	${CMAKE_CURRENT_SOURCE_DIR}/../lib/src/mouse.cpp
#	${CMAKE_CURRENT_SOURCE_DIR}/../lib/src/keys.cpp
	qtgl.cpp
	sprite.cpp
	tga.cpp
	textureloader.cpp
)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall")

add_executable(${PROJECT_NAME} ${SS2_SOURCE} ss2.qrc)
if(${QT_VERSION} EQUAL 5)
	qt5_use_modules(${PROJECT_NAME} OpenGL)
endif()
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${QT_LIBRARIES})

#file(GLOB_RECURSE IMAGES "img/*.*")
#message(STATUS "${IMAGES}")

add_subdirectory(img/characters/goomba)
