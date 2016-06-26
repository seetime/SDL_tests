# this one is important
SET(CMAKE_SYSTEM_NAME Linux)
#this one not so much
SET(CMAKE_SYSTEM_VERSION 1)

# specify the cross compiler
SET(CMAKE_C_COMPILER   	arm-linux-gnueabihf-gcc)
SET(CMAKE_CXX_COMPILER 	arm-linux-gnueabihf-g++)
#SET(CMAKE_C_COMPILER   arm-linux-gnueabi-gcc)
#SET(CMAKE_CXX_COMPILER arm-linux-gnueabi-g++)



# where is the target environment 
SET(CMAKE_FIND_ROOT_PATH  /export/bananapi/ubuntu-mate-15.04-desktop-armhf-banana-pro/rootfs/ )
set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} 
	${CMAKE_FIND_ROOT_PATH}usr/lib/arm-linux-gnueabihf/
	${CMAKE_FIND_ROOT_PATH}lib/arm-linux-gnueabihf/
)

# search for programs in the build host directories
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# for libraries and headers in the target directories
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
