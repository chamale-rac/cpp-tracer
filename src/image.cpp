#include "image.hpp"

// Constructor (default)
Image::Image()
{
    m_x_size = 0;
    m_y_size = 0;
    m_pTexture = NULL;
}

// Destructor
Image::~Image()
{
    if (m_pTexture != NULL)
    {
        SDL_DestroyTexture(m_pTexture);
    }
}

// Initialize
void Image::Init(const int x_size, const int y_size, SDL_Renderer *rRenderer)
{
    // Resize the image arrays.
    red_channel.resize(x_size, std::vector<double>(y_size, 0.0));
    green_channel.resize(x_size, std::vector<double>(y_size, 0.0));
    blue_channel.resize(x_size, std::vector<double>(y_size, 0.0));

    // Store the dimensions.
    m_x_size = x_size;
    m_y_size = y_size;

    // Store the pointer to the renderer.
    m_pRenderer = rRenderer;

    // Initialize the texture.
    InitTexture();
}

void Image::SetPixel(const int x, const int y, const double red, const double green, const double blue)
{
    // Set the pixel color.
    red_channel.at(x).at(y) = red;
    green_channel.at(x).at(y) = green;
    blue_channel.at(x).at(y) = blue;
}

// Function to generate the display;
void Image::Display()
{
    // Alloc memory for the pixel buffer.
    Uint32 *temp_pixels = new Uint32[m_x_size * m_y_size];

    // Clear the pixel buffer.
    memset(temp_pixels, 0, m_x_size * m_y_size * sizeof(Uint32));

    for (int x = 0; x < m_x_size; ++x)
    {
        for (int y = 0; y < m_y_size; ++y)
        {
            temp_pixels[y * m_x_size + x] = ConvertColor(red_channel.at(x).at(y), green_channel.at(x).at(y), blue_channel.at(x).at(y));
        }
    }

    // Update the texture with the pixel buffer.
    SDL_UpdateTexture(m_pTexture, NULL, temp_pixels, m_x_size * sizeof(Uint32));

    // Delete the pixel buffer.
    delete[] temp_pixels;

    // Copy the texture to the renderer.
    SDL_Rect srcRect, bounds;
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = m_x_size;
    srcRect.h = m_y_size;
    bounds = srcRect;

    // &srcRect is the source rectangle, &bounds is the destination rectangle.
    SDL_RenderCopy(m_pRenderer, m_pTexture, &srcRect, &bounds);
}

int Image::GetXSize()
{
    return m_x_size;
};

int Image::GetYSize()
{
    return m_y_size;
};

// Function to init the texture.
void Image::InitTexture()
{
    // Initialise the texture.
    Uint32 rmask, gmask, bmask, amask;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#else // little endian, like x86
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#endif
    // Delete any previously created texture before we create a new one.
    if (m_pTexture != NULL)
        SDL_DestroyTexture(m_pTexture);

    // Create the texture that will store the image.
    SDL_Surface *tempSurface = SDL_CreateRGBSurface(0, m_x_size, m_y_size, 32, rmask, gmask, bmask, amask);
    m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, tempSurface);
    SDL_FreeSurface(tempSurface);
}

// Function to convert colours to Uint32.
Uint32 Image::ConvertColor(const double red, const double green, const double blue)
{
    // Convert the colors to unsigned integers.
    unsigned char r = static_cast<unsigned char>(red);
    unsigned char g = static_cast<unsigned char>(green);
    unsigned char b = static_cast<unsigned char>(blue);

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    Uint32 pixel_color = (r << 24) + (g << 16) + (b << 8) + 255;
#else
    Uint32 pixel_color = (255 << 24) + (r << 16) + (g << 8) + b;
#endif

    return pixel_color;
}
