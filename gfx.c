#include "gfx.h"

gfx_context_t *gfx_new(const char *title, unsigned int width, unsigned int height)
{
    gfx_context_t *context = malloc(sizeof(gfx_context_t));
    if (!context)
        return NULL;

    SDL_Init(SDL_INIT_VIDEO); 

    context->window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);
    if(!context->window)
    {
        SDL_Quit();
        free(context);
        return NULL;
    }

    context->renderer = SDL_CreateRenderer(context->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(!context->renderer)
    {
        SDL_DestroyWindow(context->window);
        SDL_Quit();
        free(context);
        return NULL;
    }

    context->delta_time = 0;
    context->width = width;
    context->height = height;
    context->aspect_ratio = (float)width / (float)height;
    context->last = SDL_GetPerformanceCounter();

    return context;
}

void gfx_destroy(gfx_context_t *context)
{
    SDL_DestroyRenderer(context->renderer);
   
    SDL_DestroyWindow(context->window);

    SDL_Quit();

    free(context);
}

void gfx_blit(gfx_context_t *context)
{
    SDL_RenderPresent(context->renderer);
    unsigned long long now = SDL_GetPerformanceCounter();
    context->delta_time = (float)(now - context->last) / SDL_GetPerformanceFrequency();
    context->last = now;
}

void gfx_clear(gfx_context_t *context, gfx_color_t color)
{
    SDL_SetRenderDrawColor(context->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(context->renderer);
}

void gfx_put_pixel(gfx_context_t *context, int x, int y, gfx_color_t color)
{
    SDL_SetRenderDrawColor(context->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawPoint(context->renderer, x, y);
}

gfx_color_t gfx_get_color_zero(){
    gfx_color_t color;
    color.r = 0;
    color.g = 0;
    color.b = 0;
    color.a = 0;
    return color;
}