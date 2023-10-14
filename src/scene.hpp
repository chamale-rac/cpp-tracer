#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <SDL2/SDL.h>
#include "./image.hpp"

namespace RT
{
    class Scene
    {
    public:
        // Constructor and destructor
        Scene();
        ~Scene();

        // Perform the rendering
        bool Render(Image &outputImage);
    };
};

#endif
