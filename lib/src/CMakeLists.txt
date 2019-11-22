set(CMAKE_INCLUDE_CURRENT_DIR ON)

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

qt5_use_modules(gamelib OpenGL)
