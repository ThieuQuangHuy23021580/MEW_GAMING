#include"PlayMusic.h"

Mix_Music* Graphics::loadMusic(const char* path)
{
    Mix_Music* gMusic = Mix_LoadMUS(path);
    if (gMusic == nullptr) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
            SDL_LOG_PRIORITY_ERROR,
            "Could not load music! SDL_mixer Error: %s", Mix_GetError());
    }
    return gMusic;

}
void Graphics::play(Mix_Music* gMusic)
{
    if (gMusic == nullptr) return;

    if (Mix_PlayingMusic() == 0) {
        Mix_PlayMusic(gMusic, -1);
    }
    else if (Mix_PausedMusic() == 1) {
        Mix_ResumeMusic();
    }
}

//CLICK SOUND:
Mix_Chunk* Graphics::loadSound(const char* path) {
    Mix_Chunk* gChunk = Mix_LoadWAV(path);
    if (gChunk == nullptr) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
            SDL_LOG_PRIORITY_ERROR,
            "Could not load CLICK sound! SDL_mixer Error: %s", Mix_GetError());
    }
    return gChunk;
}
void Graphics::playSound(Mix_Chunk* gChunk) {
    if (gChunk != nullptr) {
        Mix_PlayChannel(-1, gChunk, 0);
    }
}



void Graphics::closeMusic()
{
    Mix_Quit();
}