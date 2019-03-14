#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_TTF
#include "SDL_include.h"

int main (int argc, char** argv) {

    /* Inicializa todas as bibliotecas */
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);
    Mix_Init(MIX_INIT_FLAC | MIX_INIT_MP3 | MIX_INIT_OGG);
    TTF_Init();

    /* Fecha todas */
    TTF_Quit();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}
