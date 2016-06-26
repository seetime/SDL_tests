#
# Find the native Ogg/Theora includes and libraries
#
# This module defines
# OGGTHEORA_INCLUDE_DIR, where to find ogg/ogg.h and theora/theora.h
# OGGTHEORA_LIBRARIES, the libraries to link against to use Ogg/Theora.
# OGGTHEORA_FOUND, If false, do not try to use Ogg/Theora.

FIND_PATH(OGGTHEORA_ogg_INCLUDE_DIR ogg/ogg.h)

FIND_PATH(OGGTHEORA_theora_INCLUDE_DIR theora/theora.h)

FIND_LIBRARY(OGGTHEORA_ogg_LIBRARY ogg)

FIND_LIBRARY(OGGTHEORA_theoraenc_LIBRARY theoraenc)

FIND_LIBRARY(OGGTHEORA_theoradec_LIBRARY theoradec)

SET(OGGTHEORA_INCLUDE_DIRS
  ${OGGTHEORA_ogg_INCLUDE_DIR}
  ${OGGTHEORA_theora_INCLUDE_DIR}
  )
#HACK multiple directories
SET(OGGTHEORA_INCLUDE_DIR ${OGGTHEORA_INCLUDE_DIRS})

SET(OGGTHEORA_LIBRARIES
  ${OGGTHEORA_ogg_LIBRARY}
  ${OGGTHEORA_theoraenc_LIBRARY}
  ${OGGTHEORA_theoradec_LIBRARY}
  )
#HACK multiple libraries
SET(OGGTHEORA_LIBRARY ${OGGTHEORA_LIBRARIES})

GET_FILENAME_COMPONENT(_CURRENT_DIR  "${CMAKE_CURRENT_LIST_FILE}" PATH)

TRY_RUN(
  OGGTHEORA_NO_444_SUBSAMPLING _OGGTHEORA_COMPILE_SUCCESS
  "${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/TestOggTheoraSubsampling"
  "${_CURRENT_DIR}/TestOggTheoraSubsampling.c"
  CMAKE_FLAGS
  "-DINCLUDE_DIRECTORIES:STRING=${OGGTHEORA_INCLUDE_DIRS}"
  "-DLINK_LIBRARIES:STRING=${OGGTHEORA_LIBRARIES}"
  )

IF(NOT _OGGTHEORA_COMPILE_SUCCESS)
  MESSAGE(SEND_ERROR "Failed to compile ${_CURRENT_DIR}/TestOggTheoraSubsampling.c")
ENDIF(NOT _OGGTHEORA_COMPILE_SUCCESS)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(OGGTHEORA
  "Could NOT find the ogg and theora libraries"
  OGGTHEORA_ogg_LIBRARY
  OGGTHEORA_theoraenc_LIBRARY
  OGGTHEORA_theoradec_LIBRARY
  OGGTHEORA_ogg_INCLUDE_DIR
  OGGTHEORA_theora_INCLUDE_DIR
  )

MARK_AS_ADVANCED(OGGTHEORA_ogg_INCLUDE_DIR OGGTHEORA_theora_INCLUDE_DIR
  OGGTHEORA_ogg_LIBRARY OGGTHEORA_theoraenc_LIBRARY
  OGGTHEORA_theoradec_LIBRARY
  )

