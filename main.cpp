#include <bits/stdc++.h>
#include <SDL2/SDL.h>

#define Screen_Width 860
#define Screen_Height 520
#define Circle_Radius 30


int random(int min, int max) {
    return min + rand() % (max - min + 1);
}

int main(int argc, char **argv)
{
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL couldn't be initialized\n";
    }

    window = SDL_CreateWindow(
        "Introduction",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        Screen_Width,
        Screen_Height,
        SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    bool gameIsRunning = true;
    int circleX = 0;
    int moveSpeed = 3;

   
    int staticCircleX = 2 * Screen_Width / 3;
    int staticCircleY = Screen_Height * 9 / 10;

    while (gameIsRunning)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                gameIsRunning = false;
            }
            else if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_LEFT:
                    staticCircleX -= moveSpeed; 
                    break;
                case SDLK_RIGHT:
                    staticCircleX += moveSpeed; 
                     break;
                case SDLK_UP:
                    staticCircleY -= moveSpeed; 
                    break;
                case SDLK_DOWN:
                    staticCircleY += moveSpeed; 
                    break;
                default:
                    break;
                }
            }
        }

       
        SDL_SetRenderDrawColor(renderer, 0, 250, 0, 250);
        SDL_RenderClear(renderer);

              SDL_SetRenderDrawColor(renderer, 250, 250, 250, 255);
        int circleY = Screen_Height / 2;
        for (int x = circleX; x <= circleX + 2 * Circle_Radius; x++)
        {
            int height = static_cast<int>(sqrt(Circle_Radius * Circle_Radius - (x - (circleX + Circle_Radius)) * (x - (circleX + Circle_Radius))));
            int startY = circleY - height;
            int endY = circleY + height;
            for (int y = startY; y <= endY; y++)
            {
                SDL_RenderDrawPoint(renderer, x, y);
            }
        }

       
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        int radius2 = 23;
        for (int x2 = staticCircleX - radius2; x2 <= staticCircleX + radius2; x2++)
        {
            int height2 = static_cast<int>(sqrt(radius2 * radius2 - (x2 - staticCircleX) * (x2 - staticCircleX)));
            int startY2 = staticCircleY - height2;
            int endY2 = staticCircleY + height2;
            for (int y2 = startY2; y2 <= endY2; y2++)
            {
                SDL_RenderDrawPoint(renderer, x2, y2);
            }
        }

        SDL_RenderPresent(renderer);

       
        bool collision = false;
        for (int x = staticCircleX - radius2; x <= staticCircleX + radius2; x++)
        {
            for (int y = staticCircleY - radius2; y <= staticCircleY + radius2; y++)
            {
                if ((x - circleX) * (x - circleX) + (y - circleY) * (y - circleY) <= Circle_Radius * Circle_Radius)
                {
                    collision = true;
                    break;
                }
            }
            if (collision)
            {
                break;
            }
        }

       
        if (collision)
        {
            staticCircleX = random(radius2, Screen_Width - radius2);
            staticCircleY = random(radius2, Screen_Height - radius2);
        }

       
        circleX += moveSpeed;

       
        if (circleX >= Screen_Width)
        {
            circleX = -2 * Circle_Radius;
        }

        SDL_Delay(10);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}