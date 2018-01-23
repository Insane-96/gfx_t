#ifdef _WIN32
    #include <SDL.h>
#else
    #include <SDL2/SDL.h>
#endif

#include <iostream>

using namespace std;

namespace gfx{
    struct Context{
        SDL_Window *window;
        SDL_Renderer *renderer;
        unsigned int width;
        unsigned int height;
        float delta_time;
        float aspect_ratio;
        unsigned long long last;

        Context(const char *title, unsigned int width, unsigned int height)
        {
            SDL_Init(SDL_INIT_VIDEO); 

            this->window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);
            if(!this->window)
            {
                SDL_Quit();
                cout << "Could not create window";
                //Throw exception
            }

            this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if(!this->renderer)
            {
                SDL_DestroyWindow(this->window);
                SDL_Quit();
                cout << "Could not create renderer";
                //Throw exception
            }

            this->delta_time = 0;
            this->width = width;
            this->height = height;
            this->aspect_ratio = (float)width / (float)height;
            this->last = SDL_GetPerformanceCounter();
        }

        ~Context()
        {
            Destroy();
        }

        void Destroy()
        {
            SDL_DestroyRenderer(this->renderer);
            SDL_DestroyWindow(this->window);
            SDL_Quit();
        }

        void Blit()
        {
            SDL_RenderPresent(this->renderer);
            unsigned long long now = SDL_GetPerformanceCounter();
            this->delta_time = (float)(now - this->last) / SDL_GetPerformanceFrequency();
            this->last = now;
        }

        void Clear(Color color)
        {
            SDL_SetRenderDrawColor(this->renderer, color.r, color.g, color.b, color.a);
            SDL_RenderClear(this->renderer);
        }

        void PutPixel(int x, int y, Color color)
        {
            SDL_SetRenderDrawColor(this->renderer, color.r, color.g, color.b, color.a);
            SDL_RenderDrawPoint(this->renderer, x, y);
        }
    };

    struct Color{
        unsigned char r;
        unsigned char g;
        unsigned char b;
        unsigned char a;

        Color()
        {
            r = 0;
            g = 0;
            b = 0;
            a = 0;
        }

        Color(char r, char g, char b, char a)
        {
            this->r = r;
            this->g = g;
            this->b = b;
            this->a = a;
        }
    };
}