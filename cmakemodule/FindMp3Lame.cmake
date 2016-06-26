# - Find Lame
# This module can be used to find Lame
# Once done this will define
#
# MP3LAME_FOUND        If false, don't try to use Lame
#
# MP3LAME_INCLUDE_DIRS The Lame include directory
# MP3LAME_LIBRARIES    Link these to use Lame

INCLUDE (CheckIncludeFiles)
INCLUDE (CheckLibraryExists)
SET(MP3LAME_FOUND FALSE)

set(MP3LAME_ROOT "$ENV{MP3LAME_ROOT}")

if(NOT MP3LAME_INCLUDE_DIRS)
    find_path(MP3LAME_INCLUDE_DIRS lame/lame.h
        HINTS 
        PATH_SUFFIXES include
        PATHS
            ${MP3LAME_ROOT}/include
            ~/Library/Frameworks
            /Library/Frameworks
            /usr/local/include
            /usr/include
            /sw/include
            /opt/local/include
            /mingw
        )
endif()

if(NOT MP3LAME_LIBRARIES)
    find_library(MP3LAME_LIBRARY_RELEASE
        NAMES mp3lame libmp3lame
        HINTS ${MP3LAME_ROOT}
        PATH_SUFFIXES lib lib64
        PATHS
            ${MP3LAME_ROOT}
            /usr/local
            /usr
            /sw
            /opt/local
            /opt/csw
            /opt
            /mingw
        )
    find_library(MP3LAME_LIBRARY_DEBUG
        NAMES mp3lamed libmp3lamed
        HINTS ${MP3LAME_ROOT}
        PATH_SUFFIXES lib lib64
        PATHS
            ${MP3LAME_ROOT}
            /usr/local
            /usr
            /sw
            /opt/local
            /opt/csw
            /opt
            /mingw
        )

    include(SelectLibraryConfigurations)
    select_library_configurations(MP3LAME)
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(MP3LAME DEFAULT_MSG MP3LAME_INCLUDE_DIRS MP3LAME_LIBRARIES)

mark_as_advanced(MP3LAME_INCLUDE_DIRS MP3LAME_LIBRARIES)
