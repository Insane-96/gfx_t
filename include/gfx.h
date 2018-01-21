#ifdef _WIN32
    #include <SDL.h>
#else
    #include <SDL2/SDL.h>
#endif

typedef struct gfx_context{
    SDL_Window *window;
    SDL_Renderer *renderer;
    unsigned int width;
    unsigned int height;
    float delta_time;
    float aspect_ratio;
    unsigned long long last;
} gfx_context_t;

typedef struct gfx_color
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} gfx_color_t;

gfx_context_t *gfx_new(const char *, unsigned int, unsigned int);
void gfx_destroy(draw_context_t *);
void gfx_blit(draw_context_t *);
void gfx_clear(draw_context_t *, draw_color_t);
void gfx_put_pixel(draw_context_t *, int, int, draw_color_t);
gfx_color_t gfx_get_color_zero();