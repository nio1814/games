macro(copy_images target images)
	set(target "${target}-images")
	add_custom_target(${target} ALL DEPENDS ${images})
	foreach(IMAGE ${images})
		add_custom_command(
			TARGET ${target}
			COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/${IMAGE} ${CMAKE_CURRENT_BINARY_DIR}
		)
	endforeach(IMAGE)
endmacro(copy_images)

add_subdirectory(goomba)
add_subdirectory(mmx)
add_subdirectory(mario1little)
