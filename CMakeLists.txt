cmake_minimum_required(VERSION 3.1)
project(telloc C)

set(CMAKE_C_STANDARD 11)

# check if we are on Windows (should work with MinGW and Visual Studio)
if (WIN32)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
    set(BUILD_SHARED_LIBS TRUE)
    # choco install ffmpeg-shared
    include_directories("C:\\Program Files\\FFmpeg\\include")
    link_directories("C:\\Program Files\\FFmpeg\\lib")

    add_library(telloc SHARED telloc_windows.c video.c)
    target_link_libraries(telloc ws2_32 avformat avcodec avutil swscale)

else() # Unix-based systems (MacOS or Linux)
    # sudo apt install pkg-config libavformat-dev libavcodec-dev libavutil-dev
    # brew install ffmpeg
    # or whatever you use
    find_path(AVCODEC_INCLUDE_DIR libavcodec/avcodec.h)
    find_library(avcodec_LIBRARIES avcodec)

    find_path(AVFORMAT_INCLUDE_DIR libavformat/avformat.h)
    find_library(avformat_LIBRARIES avformat)

    find_path(AVUTIL_INCLUDE_DIR libavutil/avutil.h)
    find_library(avutil_LIBRARIESS avutil)

    find_path(SWSCALE_INCLUDE_DIR libswscale/swscale.h)
    find_library(swscale_LIBRARIES swscale)

    include_directories(${AVCODEC_INCLUDE_DIR})
    include_directories(${AVFORMAT_INCLUDE_DIR})
    include_directories(${AVUTIL_INCLUDE_DIR})
    include_directories(${SWSCALE_INCLUDE_DIR})

    add_library(telloc SHARED telloc_unix.c video.c)
    target_link_libraries(telloc ${avformat_LIBRARIES} ${avcodec_LIBRARIES} ${avutil_LIBRARIESS} ${swscale_LIBRARIES})
endif()

# if you want to build the test program
if(BUILD_TESTING)
    # main.c is just a test program. It prints state and video data on Unix
    #  and opens a window to display the video on Windows.
    add_executable(main main.c)
    target_link_libraries(main telloc)
endif()
