set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_qt()

if(${QT_VERSION}==5)
	find_package(Qt5OpenGL)
else()
	find_package(Qt4 COMPONENTS REQUIRED QtOpenGL)
	include(${QT_USE_FILE})
	add_definitions(${QT_DEFINITIONS})
endif()

set(SRC
	object.cpp
	gameobject.cpp
	mouse.cpp
	vector3d.cpp
	camera.cpp
	keys.cpp
	mass.cpp
	datastructs.cpp
	menu.cpp
	level.cpp
	masking.cpp
	texturecode.cpp
	qtgl.cpp
	3ds.cpp
	3dsLoader.cpp
	sphere.cpp
	light.cpp
	glwidget.cpp
	tga.cpp
)

set(CMAKE_AUTOMOC ON)

add_library(gamelib ${SRC})

if(${QT_VERSION}==5)
	qt5_use_modules(gamelib OpenGL)
endif()
