#include <stdio.h>    // Input/Output functions
#include <stdlib.h>   // Memory & utility functions
#include <stdint.h>   // Fixed-width integer types
#include <SDL2/SDL.h> // Graphics & window handling

// Bitmap File Header (14 bytes)
#pragma pack(push, 1)
typedef struct
{
    uint16_t bfType;      // File type: should be 'BM'
    uint32_t bfSize;      // File size in bytes
    uint16_t bfReserved1; // Reserved, must be 0
    uint16_t bfReserved2; // Reserved, must be 0
    uint32_t bfOffBits;   // Offset to pixel data
} BITMAPFILEHEADER;
#pragma pack(pop)

// DIB Header (BITMAPINFOHEADER - 40 bytes)
#pragma pack(push, 1)
typedef struct
{
    uint32_t biSize;         // Header size (40 bytes)
    int32_t biWidth;         // Image width
    int32_t biHeight;        // Image height
    uint16_t biPlanes;       // Always 1
    uint16_t biBitCount;     // Bits per pixel
    uint32_t biCompression;  // Compression (0 = none)
    uint32_t biSizeImage;    // Image size (can be 0 if uncompressed)
    int32_t biXPelsPerMeter; // Horizontal resolution
    int32_t biYPelsPerMeter; // Vertical resolution
    uint32_t biClrUsed;      // Colors used
    uint32_t biClrImportant; // Important colors
} BITMAPINFOHEADER;
#pragma pack(pop)

// function declarations     
void align_image_data(unsigned char *data_BMP, unsigned char *data_aligned, int width, int height, int row_padded);
void zoom(unsigned char *data_aligned, int width, int height, SDL_Surface *surface, int zoom_factor);

// main function
int main(int argc, char *argv[])
{
    int zoom_factor = 1;
    if (argc != 2)
    {
        printf("Usage: %s <image.bmp>\n", argv[0]);
        return 1;
    }

    // Opening the Image File
    FILE *fp = fopen(argv[1], "rb");
    if (!fp)
    {
        perror("Error opening file");
        return 1;
    }

    BITMAPFILEHEADER fileHeader;
    BITMAPINFOHEADER infoHeader;

    // Reading the BitMapFileHeader and BitMapInfoHeader
    fread(&fileHeader, sizeof(BITMAPFILEHEADER), 1, fp);
    fread(&infoHeader, sizeof(BITMAPINFOHEADER), 1, fp);

    // Checking if the Image File is actually an BMP File
    if (fileHeader.bfType != 0x4D42)
    {
        printf("Not a valid BMP file!\n");
        fclose(fp);
        return 1;
    }

    // Checking if the Image is Uncompressed and 24-Bit BMP Image
    if (infoHeader.biBitCount != 24 || infoHeader.biCompression != 0)
    {
        printf("Only uncompressed 24-bit BMP supported!\n");
        fclose(fp);
        return 1;
    }

    // Width and Height of the Image
    // Row padded calculation
    int width = infoHeader.biWidth;
    int height = infoHeader.biHeight;
    int row_padded = (width * 3 + 3) & (~3);

    // Reading the Pixel Data form the Image File
    unsigned char *data_BMP = (unsigned char *)malloc(row_padded * height);
    unsigned char *data_aligned = (unsigned char *)malloc(width * height * 3);
    fseek(fp, fileHeader.bfOffBits, SEEK_SET);
    fread(data_BMP, row_padded, height, fp);
    fclose(fp);

    // Initializing the SDL Vidoe Subsystem
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("SDL Error: %s\n", SDL_GetError());
        free(data_BMP);
        free(data_aligned);
        return 1;
    }
    align_image_data(data_BMP, data_aligned, width, height, row_padded);

    // SDL Window and Surface Creation
    SDL_Window *window = SDL_CreateWindow("BMP Image Viewer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width * zoom_factor, height * zoom_factor, SDL_WINDOW_SHOWN);
    SDL_Surface *surface = SDL_GetWindowSurface(window);

    SDL_Keycode key;

    zoom(data_aligned, width, height, surface, zoom_factor);
    SDL_UpdateWindowSurface(window); // Update Window Surface

    // Event initialization to monitor user actions
    SDL_Event event;
    SDL_bool running = SDL_TRUE;

    // Main Loop
    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = SDL_FALSE;
            }
            else if (event.type == SDL_KEYDOWN)
            {
                SDL_Keycode key = event.key.keysym.sym;

                if (key == SDLK_PLUS || key == SDLK_EQUALS || key == SDLK_KP_PLUS)
                {
                    if (zoom_factor < 3)
                        zoom_factor++;
                }
                else if (key == SDLK_MINUS || key == SDLK_KP_MINUS)
                {
                    if (zoom_factor > 1)
                        zoom_factor--;
                }

                SDL_SetWindowSize(window, width * zoom_factor, height * zoom_factor);
                surface = SDL_GetWindowSurface(window);
                zoom(data_aligned, width, height, surface, zoom_factor);
                SDL_UpdateWindowSurface(window);
            }
        }
    }

    SDL_DestroyWindow(window); // Destroying SDL Window
    SDL_Quit();                // Close all SDL subsystems
    free(data_BMP);            // Free allocated memory
    free(data_aligned);        // Free allocated memory

    return 0;
}
