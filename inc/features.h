#include<SDL2/SDL.h>
#include<stdint.h>

// function Prototypes
void align_image_data(unsigned char *data_BMP, unsigned char *data_aligned, int width, int height, int row_padded);

void display(unsigned char *data_aligned, int width, int height, int win_height, int win_width, SDL_Surface *surface, int zoom_factor);
