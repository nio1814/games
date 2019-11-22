set(PROJECT marble)

find_package(Qt5Widgets)
find_package(Qt5OpenGL REQUIRED)
find_package(OpenGL REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../lib/src)

set(SRC
	main.cpp
	mainwindow.cpp
	glwidget.cpp
)

set(CMAKE_AUTOMOC ON)

add_executable(${PROJECT} ${SRC})

qt5_use_modules(${PROJECT} Widgets OpenGL)

target_link_libraries(${PROJECT} gamelib ${OPENGL_LIBRARIES} ${QT_LIBRARIES})
