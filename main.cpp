#include <iostream>
#include <SDL2/sdl.h>
#include <SDL2/sdl_mixer.h>
#include <SDL2/sdl_image.h>

#undef main

int main()
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    SDL_Window* w = SDL_CreateWindow("SDL Sound Test"
            , SDL_WINDOWPOS_UNDEFINED
            , SDL_WINDOWPOS_UNDEFINED
            , 400
            , 400
            , SDL_WINDOW_SHOWN);
    SDL_Renderer* r =
        SDL_CreateRenderer(w, -1, SDL_RENDERER_ACCELERATED);
    SDL_Texture* t = IMG_LoadTexture(r, "./bg.png");
    SDL_RenderCopy(r, t, NULL, NULL);
    SDL_RenderPresent(r);
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096);
    Mix_Music* music = Mix_LoadMUS("music.wav");
    Mix_Chunk* effect1 = Mix_LoadWAV("e1.wav");
    Mix_Chunk* effect2 = Mix_LoadWAV("e2.wav");
    if (0 == music || 0 == effect1 || 0 == effect2) {
        std::cout << Mix_GetError() << std::endl;
        return -1;
    }
    SDL_Event e;
    bool quit = false;
    // Play Music
    Mix_PlayMusic(music, -1);
    // Event Loop
    while (!quit) {
        SDL_WaitEvent(&e);
        switch (e.type) {
            case SDL_KEYDOWN:
                switch (e.key.keysym.scancode) {
                    case SDL_SCANCODE_1:
                         Mix_PlayChannel( -1, effect1, 0 );
                        break;
                    case SDL_SCANCODE_2:
                         Mix_PlayChannel( -1, effect2, 0 );
                        break;
                    case SDL_SCANCODE_P:
                        if (Mix_PausedMusic()) {
                            Mix_ResumeMusic();
                        } else {
                            Mix_PauseMusic();
                        }
                    default:
                        break;
                }
                break;
            case SDL_QUIT:
                quit = true;
            default:
                break;
        }
    }

    Mix_FreeChunk(effect1);
    effect1 = 0;
    Mix_FreeChunk(effect2);
    effect2 = 0;
    Mix_FreeMusic(music);
    music = 0;
    SDL_DestroyWindow(w);
    w = 0;
    SDL_Quit();
    return 0;
}
