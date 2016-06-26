# SDL(Simple DirectMedia Layer) Tutorials


This source shows how to use CMake to build the tutorial executables on various OS environments.

The executables can be buildable in various situation with help of CMake.

It is tested in the following environments

    - Linux native
    - Cross compile on ubuntu 14.04
    - Windows 7


In order to cross compile this package, you need to prepare your own root file system by copying the target root file system into your host system.
Check below steps.

1. clone this source

    ```
    cd ~
    git clone https://github.com/seetime/SDL_tests.git
    cd <source_dir>
    ```


2. prepare your custom root file system

    For example, assume it is located at /<your_rootfilesystem> 

3. Modify a toolchain script at  

    vim cmakemodule/Toolchain_bpi_arm.cmake

    or

    vim cmakemodule/Toolchain_bpi_armhf.cmake

    Find CMAKE_FIND_ROOT_PATH and modify it to point to your custom root file system location and save it.

4. Create the Makefiles by running

    ```
    cd ~/<source_dir>
    mkdir build_crosscompile
    cd build_crosscompile
    cmake .. -DCMAKE_TOOLCHAIN_FILE=../cmakemodule/Toolchain_bpi_armhf.cmake
    make
    ```

5. Find all executables in ~/bin-xxxxxx folder


In this way, I was able to run the binaries built out of crosscompiling on the target machine. If you share the source tree as nfs with 

the target machine and build it in both side of host machine and target machine, then you can see this.

