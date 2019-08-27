macro(find_qt)
	find_package(Qt5Widgets)
	if (Qt5Widgets_FOUND)
		set(QT_LIBRARIES Qt5::Widgets)
		set(QT_VERSION 5)
	else()
		find_package(Qt4 REQUIRED)
		include(${QT_USE_FILE})
		add_definitions(${QT_DEFINITIONS})
		set(QT_VERSION 4)
	endif()
	set(CMAKE_AUTOMOC TRUE)
	set(CMAKE_AUTOUIC ON)
	set(CMAKE_AUTORCC ON)
endmacro(find_qt)

find_qt()


add_subdirectory(lib/src)
add_subdirectory(marble)
add_subdirectory(rubik)
add_subdirectory(ssgame)

