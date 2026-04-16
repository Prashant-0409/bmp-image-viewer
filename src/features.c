#include <SDL2/SDL.h>

// Functions Definition
void align_image_data(unsigned char *data_BMP, unsigned char *data_aligned, int width, int height, int row_padded)
{
    int i = 0;
    for (int y = height - 1; y >= 0; y--) // Looping in y-axis
    {
        for (int x = 0; x < width; x++) // Looping in x-axis
        {
            int index = y * row_padded + x * 3; // Index calculation

            data_aligned[i] = data_BMP[index];
            data_aligned[i + 1] = data_BMP[index + 1];
            data_aligned[i + 2] = data_BMP[index + 2];

            i = i + 3;
        }
    }
}

void zoom(unsigned char *data_aligned, int width, int height, SDL_Surface *surface, int zoom_factor)
{
    Uint32 color;
    SDL_Rect rect;

    for (int y = 0; y < height; y++) // Looping in y-axis
    {
        for (int x = 0; x < width; x++) // Looping in x-axis
        {
            int index = (y * width + x) * 3; // Index calculation

            unsigned char blue = data_aligned[index];
            unsigned char green = data_aligned[index + 1];
            unsigned char red = data_aligned[index + 2];

            color = SDL_MapRGB(surface->format, red, green, blue);

            rect.x = x * zoom_factor;
            rect.y = y * zoom_factor;
            rect.w = zoom_factor;
            rect.h = zoom_factor;

            SDL_FillRect(surface, &rect, color); // Displaying the Pixel on the Screen
        }
    }
}
