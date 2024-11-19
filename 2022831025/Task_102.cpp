#include <bits/stdc++.h>
#include <SDL2/SDL.h>

#define Screen_Width 860
#define Screen_Height 520

int main(int argc, char **argv)
{
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL couldn't be initialized\n";
    }
    else
        std::cout << "Window is Ready\n";

    window = SDL_CreateWindow(
        "Introduction",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        Screen_Width,
        Screen_Height,
        SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    bool gameIsRunning = true;

    // Initial values
    int centerX = Screen_Width / 2;
    int centerY = Screen_Height / 2;
    int initialRadius = 15;
    int radius = initialRadius;
    int radiusChange = 1; 

    while (gameIsRunning)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                gameIsRunning = false;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 250, 0, 250);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        for (int x = centerX - radius; x <= centerX + radius; x++)
        {
            int height = static_cast<int>(sqrt(radius * radius - (x - centerX) * (x - centerX)));
            int startY = centerY - height;
            int endY = centerY + height;

            for (int y = startY; y <= endY; y++)
            {
                SDL_RenderDrawPoint(renderer, x, y);
            }
        }

        radius += radiusChange;

        if (centerX + radius >= Screen_Width || centerY + radius >= Screen_Height || centerX - radius <= 0 || centerY - radius <= 0)
        {
            radius = initialRadius;
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
