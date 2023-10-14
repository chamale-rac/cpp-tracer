#include "app.h"

// Our constructor (default)
App::App()
{
    isRunning = true;
    pWindow = NULL;
    pRenderer = NULL;
}

// Initialization, set up the window and renderer.
bool App::OnInit()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return false;
    }

    // Initialize the window
    pWindow = SDL_CreateWindow("CPP Tracer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);

    // Checking if the window was created successfully.
    if (pWindow != NULL)
    {
        pRenderer = SDL_CreateRenderer(pWindow, -1, 0);

        // Initialize the image
        m_image.Init(1280, 720, pRenderer);
    }
    else
    {
        return false;
    }
    return true;
}

// Main loop, this is where the magic happens xd
int App::OnExecute()
{
    SDL_Event event;

    if (OnInit() == false)
    {
        return -1;
    }

    while (isRunning)
    {
        // Handle events
        while (SDL_PollEvent(&event) != 0)
        {
            OnEvent(&event);
        }
        OnLoop();
        OnRender();
    }

    return 0;
}

// Real handling of events
void App::OnEvent(SDL_Event *event)
{
    if (event->type == SDL_QUIT)
    {
        isRunning = false;
    }
}

void App::OnLoop()
{
}

void App::OnRender()
{
    // Colorize the window.
    SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
    SDL_RenderClear(pRenderer);

    // Render the scene.
    m_scene.Render(m_image);

    // Display the image.
    m_image.Display();

    // Show the results
    SDL_RenderPresent(pRenderer);
}

void App::OnExit()
{
    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);
    pWindow = NULL;
    SDL_Quit();
}
