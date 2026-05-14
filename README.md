# BMP Image Viewer
A simple BMP image viewer written in C without using any external image libraries.

## Description
It is a very simple image viewer for 24-bit BMP image files. It does not use any external image libraries, relyes on SDL2 a cross platform multimedia library. It works by open a BMP image file in the read mode and then extracts header meta data and all the pixel data used to render the picture. It uses a simple rendering technique which renders the whole image pixel by pixel.

## Getting Started

### Dependencies  
This Project uses only SDL2 as an external library so the only dependency is the SDL2 libray itself.

### Installation  
To build and run this project in your machine you will need some tools :  
+ gcc (any C compiler),  
+ make (to automate the build process),  
+ SDL2 library (for rendering the picture)

Install GCC and Make on ubuntu using apt :  
```bash
sudo apt update
sudo apt install build-essentials 
```
Install SDL2 on ubuntu using apt :  
```bash
sudo apt install libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev
```
### Executing  
Clone the project :  
```bash
git clone https://github.com/Prashant-0409/bmp-image-viewer.git
cd bmp-image-viewer
```
### Project Structure
```text
bmp-image-viewer/
├── src/
│   ├── bmp_viewer.c
│   └── features.c
├── obj/
├── inc/
│   └── features.h
├── pictures/
│   ├── test_1.bmp
│   └── test_2.bmp
├── Makefile
└── README.md
```



