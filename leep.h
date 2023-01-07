#ifndef LEEP_H_
#define LEEP_H_
// definations / function definations:-

typedef int Errno;

#define return_defer(value) do { result = (value); goto defer; } while (0)

#endif // LEEP_H_
#ifdef LEEP_IMPLEMENTATION
// function implementations:-

class Leep
{
public:
  void fill(uint32_t *pixels, size_t width, size_t height, uint32_t color) {
    for (size_t i = 0; i < width*height; ++i) {
      pixels[i] = color;
    }
  }

  void fill_rect(uint32_t *pixels, size_t pixels_width, size_t pixels_height,
		 int x0, int y0, size_t w, size_t h,
		 uint32_t color)
  {
    for (int dy = 0; dy < (int) h; ++dy) {
      int y = y0 + dy;
      if (0 <= y && y < (int) pixels_height) {
	for (int dx = 0; dx < (int) w; ++dx) {
	  int x = x0 + dx;
	  if (0 <= x && x < (int) pixels_width) {
	    pixels[y*pixels_width + x] = color;
	  }
	}
      }
    }
  }
  
  Errno save_to_ppm_file(uint32_t *pixels, size_t width, size_t height, const char *file_path) {
    int result = 0;
    FILE *f = NULL;
    {
      f = fopen(file_path, "wb");
      if (f == NULL) return_defer(errno);

      fprintf(f, "P6\n%zu %zu 255\n", width, height);
      if (ferror(f)) return_defer(errno);

      for (size_t i = 0; i < width*height; ++i) {
	uint32_t pixel = pixels[i];
	uint8_t bytes[3] = {
			    (pixel>>(8*0))&0xFF,
			    (pixel>>(8*1))&0xFF,
			    (pixel>>(8*2))&0xFF
	};
	fwrite(bytes, sizeof(bytes), 1, f);
	if (ferror(f)) return_defer(errno);
      }
    }
  defer:
    if (f) fclose(f);
    return result;
  }
  
};

#endif // LEEP_IMPLEMENTATION
