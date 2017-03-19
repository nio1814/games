set(PROJECT marble)

if(${QT_VERSION} EQUAL 5)
	find_package(Qt5Widgets)
	find_package(Qt5OpenGL REQUIRED)
else()
	find_package(Qt4 COMPONENTS REQUIRED QtOpenGL)
	include(${QT_USE_FILE})
	add_definitions(${QT_DEFINITIONS})

endif()
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

if(${QT_VERSION} EQUAL 5)
	qt5_use_modules(${PROJECT} Widgets OpenGL Core)
endif()

target_link_libraries(${PROJECT} gamelib ${OPENGL_LIBRARIES} ${QT_LIBRARIES})
