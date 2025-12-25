#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>
#include <ctype.h>
#include <stdio.h>

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

void skipline(FILE *fp){
    int ch;
    while ((ch=fgetc(fp)) != '\n' && ch!=EOF);
}

int skip_header(FILE *fp){
    int ch;
    skipline(fp);       // skip header

    while((ch=fgetc(fp))!=EOF){
        // Skip comments
        if(isspace(ch)) continue;
        // If is a comment skip the line
        if(ch=='#'){
            skipline(fp);
        } else {
            ungetc(ch, fp);
            return 0;
        }
    }
    return 1;
}

int color_rescale(const int im_range, const int sdl_range,
                   int *red, int *green, int *blue){
    if(*red>im_range || *green>im_range || *blue>im_range){
        printf("Pixel color of the maximum value range");
        return 1;
    }

    *red   = (*red   * sdl_range) / im_range;
    *green = (*green * sdl_range) / im_range;
    *blue  = (*blue  * sdl_range) / im_range;

    return 0;
}

int main(int argc, char *argv[]){
    
    /* ---------------------------- ppm file open --------------------------- */

    // Check input consistency
    if(argc!=2){
        printf("Wrong program execution, use the following syntaxt:  "
               "`./image_viewer image.ppm`\n");
        return 1;
    }
    printf("Image name: `%s`\n", argv[1]);

    // Init ppm file reading
    FILE* fp = fopen(argv[1], "r");
    skip_header(fp);

    // Get image format information
    int width, height, pixels;
    fscanf(fp,"%d %d",&width, &height);
    pixels = width*height;
    int color_range;
    fscanf(fp, "%d", &color_range);
    printf("Image dimention %d x %d\nBits per color channel: %d\n",
           width, height, color_range);
    printf("\nPress enter to continue...");
    while (getchar()!='\n');

    /* ------------------------ import ppm file in SDL ---------------------- */
    SDL_Init(SDL_INIT_VIDEO);   // init SDL

    SDL_FRect pixel;            // init pixel as a rectagle
    pixel.w = 1;
    pixel.h = 1;

    // init windows and renderer
    SDL_CreateWindowAndRenderer(argv[1], width, height,
                                SDL_WINDOW_RESIZABLE, &window, &renderer);

    // init SDL texture to store the image
    SDL_Texture *image = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBX8888,
                                           SDL_TEXTUREACCESS_TARGET,
                                           width, height);
    SDL_SetRenderTarget(renderer, image);

    // fill image texture
    int red, green, blue;
    for(int j=0; j<pixels; j++){
        fscanf(fp, "%d %d %d", &red, &green, &blue);
        printf("Pixel %6d - Color %3d %3d %3d\n", 
               j, red, green, blue);
        pixel.x = j%width;
        pixel.y = (int)(j/width);
        if(color_rescale(color_range, 255, &red, &green, &blue)) return 1;
        SDL_SetRenderDrawColor(renderer, red, green, blue, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &pixel);
    }
    SDL_SetRenderTarget(renderer, NULL);
    fclose(fp);

    /* --------------------------- display the image ------------------------ */
    bool running = true;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) running = false;
        }
        SDL_RenderClear(renderer);
        SDL_RenderTexture(renderer, image, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
