# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

#define cpp source path
set(SRC_DIR libmp3lame)

#set *.h source path
include_directories(libmp3lame)

#set cpp source path
aux_source_directory(libmp3lame SRC_LIST)

#set *.so files output path，please add this before add_library
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI})

#add cpp files into library
add_library(lamemp3
        SHARED
        lame_util.h
        lame_util.c
        ${SRC_LIST})


target_link_libraries( # Specifies the target library.
        lamemp3

        # Links the target library to the log library
        # included in the NDK.
        log)