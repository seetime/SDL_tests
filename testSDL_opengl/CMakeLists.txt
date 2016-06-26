cmake_minimum_required(VERSION 2.8)

# set project name from current directory
get_filename_component(TARGET ${CMAKE_CURRENT_SOURCE_DIR} NAME) 
project( ${TARGET} )

SET(${TARGET}_HEADERS

)

SET(${TARGET}_SOURCES 
	#testoverlay.c
	testgl.c
)

INCLUDE_DIRECTORIES(
    ${SDL_INCLUDE_DIR}
)

find_package(OpenGL)

if (OPENGL_FOUND)

	add_definitions(-DHAVE_OPENGL)

	INCLUDE_DIRECTORIES(
	    ${OPENGL_INCLUDE_DIR}
	)
	set(MORELIBS ${MORELIBS} ${OPENGL_LIBRARIES})
endif()

IF (UNIX)
set(MORELIBS ${MORELIBS} -lm)
ENDIF()

# set the path to the library folder
link_directories(
  ${CMAKE_LIBRARY_PATH}
)

if (CMAKE_FIND_ROOT_PATH)
	SET( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} --sysroot=${CMAKE_FIND_ROOT_PATH}" )
endif()

add_executable( ${TARGET} ${${TARGET}_SOURCES} ${${TARGET}_HEADERS} )
target_link_libraries( ${TARGET} ${ALL_LIBS} ${MORELIBS} ${SDL_RELATED_LIBRARIES})

if (MSVC)
    create_target_launcher(${TARGET} ARGS "testH264.mp4" WORKING_DIRECTORY "${PROJECT_OUTPUT_DIR}" ENVIRONMENT "${RUN_ENV}")
endif (MSVC)

	add_custom_command(
	   TARGET ${TARGET} POST_BUILD
	   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/${TARGET}${CMAKE_EXECUTABLE_SUFFIX}" "${PROJECT_OUTPUT_DIR}"
	   WORKING_DIRECTORY ${PROJECT_OUTPUT_DIR}
	  )

