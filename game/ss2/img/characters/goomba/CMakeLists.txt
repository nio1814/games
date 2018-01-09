set(IMAGES
	goomba1.tga
	goomba2.tga
)

#add_custom_target(goomba ALL DEPENDS ${IMAGES})
#foreach(IMAGE ${IMAGES})
#	add_custom_command(
#		TARGET goomba
#		COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/${IMAGE} ${CMAKE_CURRENT_BINARY_DIR}
#	)
#endforeach(IMAGE)

copy_images(goomba "${IMAGES}")
