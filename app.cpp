#include "app.h"

// Our constructor (default)
App::App()
{
    isRunning = true;
    pWindow = NULL;
    pRenderer = NULL;
}

bool App::OnInit()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return false;
    }

    // Initialize the window
    pWindow = SDL_CreateWindow("CPP Tracer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);

    if (pWindow != NULL)
    {
        pRenderer = SDL_CreateRenderer(pWindow, -1, 0);

        // Initialize the image
        m_image.Init(1280, 720, pRenderer);

        // Create color variations.
        for (int x = 0; x < 1280; ++x)
        {
            for (int y = 0; y < 720; ++y)
            {
                double red = (static_cast<double>(x) / 1280.0) * 255.0;
                double green = (static_cast<double>(y) / 720.0) * 255.0;
                m_image.SetPixel(x, y, red, green, 0.0);
            }
        }
    }
    else
    {
        return false;
    }
    return true;
}

int App::OnExecute()
{
    SDL_Event event;

    if (OnInit() == false)
    {
        return -1;
    }

    while (isRunning)
    {
        while (SDL_PollEvent(&event) != 0)
        {
            OnEvent(&event);
        }
        OnLoop();
        OnRender();
    }

    return 0;
}

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
    // Colorize
    SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
    SDL_RenderClear(pRenderer);

    // Display the image.
    m_image.Display(pRenderer);

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
