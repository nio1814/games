project(gamelib)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SRC
  object/object.cpp
  object/objects.cpp
#  object/collection.cpp
#  object/spheres.cpp
  object/plane.cpp
#  object/planes.cpp
#  object/lines.cpp
  object/line.cpp
  object/sphere.cpp
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
	light.cpp
	glwidget.cpp
	tga.cpp
  model3d.cpp
  texture.cpp
  quaternion.cpp
)

set(CMAKE_AUTOMOC ON)

add_library(${PROJECT_NAME} ${SRC})

qt5_use_modules(${PROJECT_NAME} OpenGL)
