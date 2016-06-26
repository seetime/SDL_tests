cmake_minimum_required(VERSION 2.6)

SET( PRJ_NAME CamStreamingSuite)
PROJECT( ${PRJ_NAME} )

# The version number
set(${PRJ_NAME}_VERSION 0.5) 

set(EXTERN_PATH ${PROJECT_SOURCE_DIR}/external)

# On Visual 2005 and above, this module can set the debug working directory
cmake_policy(SET CMP0026 OLD)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmakemodule")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmakemodule/rpavlik-cmake-modules-fe2273")
#list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmakemodule/rpavlik-cmake-modules-1c73e35")
include(FLSHelpers)
include(CreateLaunchers)
include(MSVCMultipleProcessCompile) # /MP

option(USE_CROSSCOMPILE "Enabel cross compile option tio build this package in a Virtual machine" NO)
option(USE_ARMHF_TOOLCHAIN "Use armhf tool chain" NO)
option(USE_PTHREAD "Use pthread library working with ffmpeg" ON)
option(USE_OGGTHEORA "Use the native Ogg/Theora working with ffmpeg" OFF)


#if("${CMAKE_CXX_COMPILER}" MATCHES "arm")
#	set(USE_CROSSCOMPILE 	YES)
#endif()

if("${CMAKE_CXX_COMPILER}" MATCHES "gnueabihf")
	set(USE_ARMHF_TOOLCHAIN 	YES)
	set(ARMHF_LIB_PATH_SUFFIX 	arm-linux-gnueabihf)
endif()

# Compile external dependencies
add_subdirectory (external)



set(PREBUILT_ROOT_DIR "${EXTERN_PATH}/prebuilt/")
set(PREBUILT_LIB_DIR "${EXTERN_PATH}/prebuilt/lib/")

if( CMAKE_SIZEOF_VOID_P EQUAL 8 )
	#MESSAGE ("-- Host system is 64 bits  CMAKE_SIZEOF_VOID_P=${CMAKE_SIZEOF_VOID_P} --")
	
	if(MSVC)
		set ( MACHINETAG	x64)
		set (CMAKE_PREFIX_PATH 
			"C:\\Qt52\\5.2.0\\msvc2012_64_opengl"
			"c:\\Program Files\\Microsoft SDKs\\Windows\\v7.1\\Lib\\"
			)
		set (QTDIR "C:/Qt52/5.2.0/msvc2012_64_opengl")
		set (FFMPEG_PATH ${PREBUILT_ROOT_DIR}/ffmpeg-20160610-git-0a9e781-win64-dev/)
	elseif (CMAKE_SYSTEM_NAME MATCHES "(L|l?)inux")
		EXEC_PROGRAM( ${CMAKE_C_COMPILER}
  			ARGS -dumpmachine
  			OUTPUT_VARIABLE MACHINETAG
		)
	endif(MSVC)
else( CMAKE_SIZEOF_VOID_P EQUAL 8 )
	#MESSAGE ("-- Host system is 32 bits  CMAKE_SIZEOF_VOID_P=${CMAKE_SIZEOF_VOID_P} --")
	
	if(MSVC)
		set ( MACHINETAG	x86)
		set (CMAKE_PREFIX_PATH 
			"C:\\Qt52\\5.2.0\\msvc2012"
			"c:\\Program Files\\Microsoft SDKs\\Windows\\v7.1\\Lib\\"
			)
		set (QTDIR "C:/Qt52/5.2.0/msvc2012")
		set (FFMPEG_PATH ${PREBUILT_ROOT_DIR}/ffmpeg-20160610-git-0a9e781-win32-dev/)
		#set (FFMPEG_PATH ${EXTERN_PATH}/ffmpeg/Windows7/)
	elseif (CMAKE_SYSTEM_NAME MATCHES "(L|l?)inux")
		EXEC_PROGRAM( ${CMAKE_C_COMPILER}
  			ARGS -dumpmachine
  			OUTPUT_VARIABLE MACHINETAG
		)
		#set ( MACHINETAG	$ENV{OSTYPE})
		#set ( MACHINETAG	linux)
		MESSAGE ("-- MACHINETAG : $ENV{OSTYPE} ${MACHINETAG}") 
	endif(MSVC)
endif( CMAKE_SIZEOF_VOID_P EQUAL 8 )


if(MSVC)
	set(PREBUILT_LIB_DIR ${PREBUILT_LIB_DIR}${MACHINETAG}/) 
	list(APPEND CMAKE_SYSTEM_PROGRAM_PATH ${EXTERN_PATH}/prebuilt/include) 

	# Instruct CMake where to find cmake related stuffs
	SET( BINDIR binvc-${MACHINETAG})
elseif( CMAKE_SYSTEM_NAME MATCHES "(L|l?)inux" )
	SET( BINDIR bin-${MACHINETAG})
	set (FFMPEG_PATH "$ENV{HOME}/ffmpeg_build/")
endif(MSVC)



set(PROJECT_OUTPUT_DIR ${PROJECT_SOURCE_DIR}/../${BINDIR})
set (RUN_ENV "PATH=${PROJECT_OUTPUT_DIR}") 
MESSAGE ("-- PROJECT_OUTPUT_DIR: ${PROJECT_OUTPUT_DIR}")

file(MAKE_DIRECTORY ${PROJECT_OUTPUT_DIR})


#=============================================================
# Required environment
#=============================================================
if(MSVC)
	# Set some environment variable
	set(ENV{PREBUILT_ROOT_DIR} "${PREBUILT_ROOT_DIR}")
	set(ENV{PREBUILT_LIB_DIR} "${PREBUILT_LIB_DIR}")


	# pthread for windows
	set(PTHREAD_DIR ${PREBUILT_ROOT_DIR}/pthreads-w32-2-9-1)
	set(ENV{PTHREAD_DIR} "${PTHREAD_DIR}")

	# FFMpeg for windows
	set(ENV{FFMPEG_DIR} "${FFMPEG_PATH}")
	set(FFMPEG_RUNTIME_DIR ${FFMPEG_PATH}/lib)

	# To resolve the prebuilt SDL_ttf linkage
	set(ENV{SDLDIR} "${PREBUILT_ROOT_DIR}")
	set(ENV{SDL2IMAGEDIR} "${PREBUILT_ROOT_DIR}/SDL2_image-2.0.1/")
	set(ENV{SDL2TTFDIR} "${PREBUILT_ROOT_DIR}/SDL2_ttf-2.0.14/")
	
	# For windows compatible libraries
	include_directories(${PROJECT_SOURCE_DIR}/wincompat)

	MESSAGE ("-- After PREBUILT_LIB_DIR: $ENV{PREBUILT_LIB_DIR}")
elseif( CMAKE_SYSTEM_NAME MATCHES "(L|l?)inux" )
	set(ENV{FFMPEG_DIR} "${FFMPEG_PATH}")
endif()

MESSAGE ("@${PRJ_NAME} -- CMAKE_FIND_ROOT_PATH : ${CMAKE_FIND_ROOT_PATH}") 

MESSAGE ("@${PRJ_NAME} -- USE_CROSSCOMPILE : ${USE_CROSSCOMPILE}")
MESSAGE ("@${PRJ_NAME} -- CMAKE_LIBRARY_PATH  : ${CMAKE_LIBRARY_PATH}") 
MESSAGE ("@${PRJ_NAME} -- USE_ARMHF_TOOLCHAIN  : ${USE_ARMHF_TOOLCHAIN}") 

find_package(Freetype)
find_package(SDL)
find_package(SDL_image)
find_package(SDL_ttf)
#find_package(SDL_net)


#find_package(FFMpeg REQUIRED)
find_package(FFMPEG REQUIRED)

MESSAGE ("@${PRJ_NAME} -- THREADS_PTHREADS_INCLUDE_DIR : ${THREADS_PTHREADS_INCLUDE_DIR}") 
MESSAGE ("@${PRJ_NAME} -- CMAKE_THREAD_LIBS_INIT : ${CMAKE_THREAD_LIBS_INIT}") 
MESSAGE ("@${PRJ_NAME} -- FFMPEG_FOUND : ${FFMPEG_FOUND}") 
MESSAGE ("@${PRJ_NAME} -- FFMPEG_INCLUDE_DIR : ${FFMPEG_INCLUDE_DIR}") 
MESSAGE ("@${PRJ_NAME} -- FFMPEG_LIBRARIES : ${FFMPEG_LIBRARIES}") 

#==========================================================
# Setting for FFMpeg dependant libraries

set( FFMPEG_DEPENDANT_LIBS "") 

if( CMAKE_SYSTEM_NAME MATCHES "(L|l?)inux" )

	set( FFMPEG_DEPENDANT_LIBS ${FFMPEG_DEPENDANT_LIBS} m va) 

elseif (MSVC)

if(NOT FREETYPE_FOUND) 
	set(FREETYPE_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/external/include) 
#	SET(FREETYPE_LIBRARY ${PROJECT_SOURCE_DIR}/external/prebuilt/lib/freetype235.lib ) 
	SET(FREETYPE_LIBRARY ${PROJECT_SOURCE_DIR}/external/prebuilt/lib/libfreetype-6.lib ) 
	message ( " Manual setting: FREETYPE_LIBRARY => ${FREETYPE_LIBRARY} ")
endif()

endif ( CMAKE_SYSTEM_NAME MATCHES "(L|l?)inux" )


if (USE_PTHREAD)
	#set(THREADS_PREFER_PTHREAD_FLAG ON)
	#find_package(Threads REQUIRED)
	#set(FFMPEG_DEPENDANT_LIBS ${FFMPEG_DEPENDANT_LIBS} Threads::Threads)

	if(MSVC)
		set(THREADS_USE_PTHREADS_WIN32 true)
	endif(MSVC)

	find_package(Threads REQUIRED)
	
	#if(THREADS_HAVE_PTHREAD_ARG)
  	#	target_compile_options(PUBLIC ${TARGET} "-pthread")
	#endif()

	if(CMAKE_THREAD_LIBS_INIT)
		set(FFMPEG_DEPENDANT_LIBS ${FFMPEG_DEPENDANT_LIBS} "${CMAKE_THREAD_LIBS_INIT}")
	endif()
endif(USE_PTHREAD)

# mp3lame
find_package(Mp3Lame)
if ( MP3LAME_FOUND )
	set(FFMPEG_DEPENDANT_LIBS ${FFMPEG_DEPENDANT_LIBS} "${MP3LAME_LIBRARIES}")
endif ()

# OGG & Theora
#find_package(OGGTHEORA)
#if ( OGGTHEORA_FOUND )
#	set(FFMPEG_DEPENDANT_LIBS ${FFMPEG_DEPENDANT_LIBS} "${OGGTHEORA_LIBRARIES}")
#endif ()

set(PLATFORM_LIBRARIES )
if(MSVC)
	list(APPEND PLATFORM_LIBRARIES ws2_32 winmm) 
endif (MSVC)


# includes
SET( ${PRJ_NAME}Includes
)

set( LIVE_LIBRARIES
		BasicUsageEnvironment
		groupsock
		liveMedia
		UsageEnvironment
) 

set( SDL2_LIBRARIES
		SDL2
		SDL2main
) 

SET( SDL2_INCLUDE_DIR
		${EXTERN_PATH}/SDL2-2.0.4/include/
)

SET( LOG4CPP_INCLUDE_DIR
		${EXTERN_PATH}/log4cpp/include/
)

SET( RAPPIDJSON_INCLUDE_DIR
		${EXTERN_PATH}/rapidjson/
)

set( SDL_RELATED_LIBRARIES
	${FREETYPE_LIBRARY}
	${SDL_LIBRARY}
	${SDL_IMAGE_LIBRARIES}
	${SDL_TTF_LIBRARIES}
) 



MESSAGE ("@${PRJ_NAME} -- FFMPEG_DEPENDANT_LIBS : ${FFMPEG_DEPENDANT_LIBS}") 
MESSAGE ("@${PRJ_NAME} -- FFMPEG_theora_LIBRARY : ${FFMPEG_theora_LIBRARY}") 
MESSAGE ("@${PRJ_NAME} -- FFMPEG_z_LIBRARY : ${FFMPEG_z_LIBRARY}") 
MESSAGE ("@${PRJ_NAME} -- SDL_INCLUDE_DIR : ${SDL_INCLUDE_DIR}") 
MESSAGE ("@${PRJ_NAME} -- SDL_RELATED_LIBRARIES : ${SDL_RELATED_LIBRARIES}") 



ADD_SUBDIRECTORY( colortest )
ADD_SUBDIRECTORY( testSDL )
ADD_SUBDIRECTORY( testSDL_opengl )
