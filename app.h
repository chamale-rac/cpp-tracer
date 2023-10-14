#ifndef APP_H
#define APP_H

#include <SDL2/SDL.h>
#include "./src/image.hpp"
#include "./src/scene.hpp"

class App
{
public:
    App();
    int OnExecute();
    bool OnInit();
    void OnEvent(SDL_Event *event);
    void OnLoop();
    void OnRender();
    void OnExit();

private:
    // Image instance to store the image xd
    Image m_image;

    // Scene instance
    RT::Scene m_scene;

    // SDL2 stuff.
    bool isRunning;
    SDL_Window *pWindow;
    SDL_Renderer *pRenderer;
};

#endif
