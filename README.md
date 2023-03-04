# telloc
Cross-platform C library for connecting to the DJI Tello with video support

This was created for the Roadrunner Dynamics Club.

## What?
This library supports Windows, MacOS and Linux developers who might want to make cool apps to control their fancy flying robot.

## Why?
Mostly because existing tello libraries are overly complicated, abandoned, and/or do not work.

This library implements a clean, cross-platform interface for:
* Sending commands and receiving responses
* Receiving video data as RBG images
* Receiving state data as a string

## How?
### Building the library
To build this library, you simply need to install ffmpeg libraries (avformat, avcodec, avutil, swscale).

Windows:

    choco install ffmpeg-shared


MacOS:

    brew install ffmpeg


Debian/Ubuntu:

    sudo apt install libavformat-dev libavcodec-dev libavutil-dev libswscale-dev

Then you should be able to build telloc with CMake.

```
mkdir build
cd build
cmake ..
make
```

telloc also comes with a testing program for Windows / Unix-based systems that will attempt to connect to the drone and display information if successful.
And Python3 bindings.

```
mkdir build
cd build
cmake .. -DBUILD_TESTING=True -DBUILD_PYTHON=True
make
```

### Using the python library :snake:
1. Build The library with python bindings

```
mkdir build
cd build
cmake .. -DBUILD_PYTHON=True
make
```

2. Copy libtellopy.so into the tellopy folder
```
cd ..
cp build/libtellopy.so tellopy
```

3. Install the python library
```
cd ..
pip install -e tellopy
```

### Using the library
telloc has a simple interface defined in `telloc.h`.
You can read `main.c` for example usage.

telloc spawns three threads when you call `telloc_connect(...)`:
* the state thread - reads state strings and saves them into a buffer.
* the video thread - reads and decodes video data into an RGB image buffer.
* the keepalive thread - sends a keepalive query to the drone once per second.

To attempt a connection and spawn threads, you can run

    tello_connection *connection = telloc_connect();

When you want to send data to a successful connection, you do:

    char *command="streamon";
    char *response=malloc(TELLOC_STATE_SIZE);
    int ret_command = telloc_send_command(connection, command, strlen(command), response, TELLOC_STATE_SIZE)
    printf("Response was %s\n", response);


To read the most recent video frame, you can do the following:

    unsigned char *image = malloc(TELLOC_VIDEO_SIZE);
    unsigned int image_bytes;
    unsigned int image_width;
    unsigned int image_height;
    int ret_video = telloc_read_image(connection, image, TELLOC_VIDEO_SIZE, &image_bytes, &image_width, &image_height);
    if (ret_video==0)
        printf("Image: %d bytes; %d x %d\n", image_bytes, image_width, image_height);

To read the most recent state string, you can do the following:

    char *state = malloc(TELLOC_STATE_SIZE);
    int ret_state = telloc_read_state(connection, state, TELLOC_STATE_SIZE);
    if (ret_state==0)
        printf("State: %s\n", state);


## TODO
- [ ] Use static libraries for ffmepg, build static telloc
- [ ] Save binaries somewhere accessible


# Release Notes
* 2023-02-18: Improved interface by using opaque struct pointer instead of void*; untested on windows.


## License

This is licenced under the Unlicence, so basically, do whatever you want but please don't sue me.

see LICENSE.
