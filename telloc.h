// Include file specifying the interface for the telloc library.
//
#ifndef TELLOC_TELLOC_H
#define TELLOC_TELLOC_H

#define TELLOC_RESPONSE_TIMEOUT 150
#define TELLOC_ADDRESS "192.168.10.1"
#define TELLOC_COMMAND_PORT 8889
#define TELLOC_STATE_PORT 8890
#define TELLOC_VIDEO_PORT 11111
#define TELLOC_STATE_SIZE 1024
#define TELLOC_VIDEO_SIZE (960 * 720 * 3 * 2)

// function to connect to the Tello drone using the default address 192.168.10.1
int telloc_connect(void** connection_ptr_addr);

// function to connect to the Tello drone using a specified interface
int telloc_connect_interface(void** connection_ptr_addr, char* interface_address);

// function to send a command to the Tello drone and receive a response
// the response pointer can be NULL, resulting in no response being saved.
int telloc_send_command(void* connection_ptr, char* command, unsigned int length, char* response, unsigned int response_length);

// function to receive the most recent state of the Tello drone
int telloc_read_state(void* connection_ptr, char* state_buffer, unsigned int state_buffer_length);

// function to receive an RGB format video frame from the Tello drone
int telloc_read_image(void* connection_ptr, unsigned char* image, unsigned int image_buffer_size, unsigned int* image_bytes, unsigned int* image_width, unsigned int* image_height);

// function to disconnect from the Tello drone
int telloc_disconnect(void** connection_ptr_addr);

#endif //TELLOC_TELLOC_H
