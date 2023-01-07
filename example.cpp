#include <iostream>
#include <errno.h>
#include <stdint.h>
#include <string.h>

// TODO: class canvas that stores pixels and screen data
// TODO: define rounded color values
// TODO: move some function to leep.h file
// TODO: implement more save functions for other file types (idea: could use stb.h library)

#define LEEP_IMPLEMENTATION
#include "leep.h"

#define WIDTH 1000
#define HEIGHT 800

uint32_t pixels[WIDTH*HEIGHT];

int main(void) {

  const char file_path[] = "output.ppm";
  
  Leep leep;
  leep.fill(pixels, WIDTH, HEIGHT, 0xFF0000FF);

  int rw = 600;
  int rh = 300;
  
  leep.fill_rect(pixels, WIDTH, HEIGHT, WIDTH/2-rw/2, HEIGHT/2-rh/2, rw, rh, 0xFFFF2020);
  
  Errno err = leep.save_to_ppm_file(pixels, WIDTH, HEIGHT, file_path);
  
  if (err) {
    fprintf(stderr, "error while saving file %s: %s\n", file_path, strerror(errno));
    return -1;
  }
  
  return 0; 
}
