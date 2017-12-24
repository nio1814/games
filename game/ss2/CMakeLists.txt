cmake_minimum_required(VERSION 3.6)

project(ss2)

if(${QT_VERSION}==5)
	find_package(Qt5OpenGL REQUIRED)
else()
	find_package(Qt4 COMPONENTS REQUIRED QtOpenGL)
	include(${QT_USE_FILE})
	add_definitions(${QT_DEFINITIONS})
endif()
find_package(OpenGL REQUIRED)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../lib/src)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SS2_SOURCE
	main.cpp
	mainwindow.cpp
	levelwindow.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../lib/src/glwidget.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../lib/src/vector3d.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../lib/src/light.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../lib/src/camera.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../lib/src/mouse.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../lib/src/keys.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../lib/src/qtgl.cpp
)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)

add_executable(${PROJECT_NAME} ${SS2_SOURCE})
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${QT_LIBRARIES})
