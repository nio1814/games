set(PROJECT racing)

find_package(Qt5Widgets)
find_package(Qt5OpenGL REQUIRED)
find_package(OpenGL REQUIRED)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../lib/src)

set(SOURCE
  main.cpp
  mainwindow.cpp
  glwidget.cpp
  level.cpp
  meshobject.cpp
)

add_executable(${PROJECT} ${SOURCE} racing.qrc)
qt5_use_modules(${PROJECT} Widgets OpenGL)
target_link_libraries(${PROJECT} gamelib ${OPENGL_LIBRARIES})
