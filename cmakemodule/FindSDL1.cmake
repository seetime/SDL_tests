# Locate the SDL2_image library. This CMake module is a modified version
# of the original FindSDL_image.cmake file
# ###########################################################################
# Locate SDL_image library
# This module defines
# SDL2IMAGE_LIBRARY, the name of the library to link against
# SDLIMAGE_FOUND, if false, do not try to link to SDL
# SDL2IMAGE_INCLUDE_DIR, where to find SDL/SDL.h
#
# $SDLDIR is an environment variable that would
# correspond to the ./configure --prefix=$SDLDIR
# used in building SDL.
#
# Created by Eric Wing. This was influenced by the FindSDL.cmake 
# module, but with modifications to recognize OS X frameworks and 
# additional Unix paths (FreeBSD, etc).

#=============================================================================
# Copyright 2005-2009 Kitware, Inc.
#
# Distributed under the OSI-approved BSD License (the "License");
# see accompanying file Copyright.txt for details.
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#=============================================================================
# (To distributed this file outside of CMake, substitute the full
#  License text for the above reference.)

FIND_PATH(SDL_INCLUDE_DIR SDL.h
  HINTS
  $ENV{SDLDIR}
  PATH_SUFFIXES include
  PATHS
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local/include/SDL
  /usr/include/SDL
  /sw/include/SDL # Fink
  /opt/local/include/SDL # DarwinPorts
  /opt/csw/include/SDL # Blastwave
  /opt/include/SDL
)

if (MSVC)
  if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(VC_LIB_PATH_SUFFIX lib/x64)
  else()
    set(VC_LIB_PATH_SUFFIX lib/x86)
  endif()
endif ()

FIND_LIBRARY(SDL_LIBRARY 
  NAMES SDL
  HINTS
  $ENV{SDLDIR}
  PATH_SUFFIXES lib64 lib ${VC_LIB_PATH_SUFFIX} ${ARMHF_LIB_PATH_SUFFIX}
  PATHS
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local
  /usr/
  /sw
  /opt/local
  /opt/csw
  /opt
)

SET(SDL_FOUND "NO")
IF(SDL_LIBRARY AND SDL_INCLUDE_DIR)
  SET(SDL_FOUND "YES")
ENDIF(SDL_LIBRARY AND SDL_INCLUDE_DIR)
 