#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <vector>
#include <SDL2/SDL.h>

class Image
{
public:
    // Constructor
    Image();

    // Destructor
    ~Image();

    // Initialize the image with the given dimensions and renderer.
    void Init(const int x_size, const int y_size, SDL_Renderer *rRenderer);

    // Set the color of the pixel at the given coordinates.
    void SetPixel(const int x, const int y, const double red, const double green, const double blue);

    // Display the image using the given renderer.
    void Display(SDL_Renderer *renderer);

private:
    // Convert the given RGB color values to a Uint32 color value.
    Uint32 ConvertColor(const double red, const double green, const double blue);

    // Initialize the texture used to display the image.
    void InitTexture();

private:
    // Arrays to store image data.
    std::vector<std::vector<double>> red_channel;
    std::vector<std::vector<double>> green_channel;
    std::vector<std::vector<double>> blue_channel;

    // Texture used to display the image.
    SDL_Texture *texture;

    // Dimensions of the image.
    int m_x_size;
    int m_y_size;

    // SDL stuff.
    SDL_Renderer *m_pRenderer;
    SDL_Texture *m_pTexture;
};

#endif