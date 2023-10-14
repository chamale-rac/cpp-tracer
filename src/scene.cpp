#include "./scene.hpp"

// The constructor
RT::Scene::Scene(){};
RT::Scene::~Scene(){};

bool RT::Scene::Render(Image &outputImage)
{
    // Get the actual dimension
    int xSize = outputImage.GetXSize();
    int ySize = outputImage.GetYSize();

    // Again, checking some color variations
    for (int x = 0; x < xSize; ++x)
    {
        for (int y = 0; y < ySize; y++)
        {
            double red = (static_cast<double>(x) / static_cast<double>(xSize)) * 255.0;
            double green = (static_cast<double>(y) / static_cast<double>(ySize)) * 255.0;

            outputImage.SetPixel(x, y, red, green, 0.0);
        }
    }
    return true;
};