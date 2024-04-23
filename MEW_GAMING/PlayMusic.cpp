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

TTF_Font* Graphics::loadFont(const char* path, int size)
{
    TTF_Font* gFont = TTF_OpenFont(path, size);
    if (gFont == nullptr)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load font %s", TTF_GetError());
    }
    return gFont;
}


void* Graphics::renderText(SDL_Renderer* renderer,std::string  text, TTF_Font* font, SDL_Color textColor,int x, int y)
{
    SDL_Surface* textSurface =
        TTF_RenderText_Solid(font, text.c_str(), textColor);
    if (textSurface == nullptr) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
            SDL_LOG_PRIORITY_ERROR,
            "Render text surface %s", TTF_GetError());
        return nullptr;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (texture == nullptr) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
            SDL_LOG_PRIORITY_ERROR,
            "Create texture from text %s", SDL_GetError());
    }
    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
    SDL_Rect dstRect = { x, y, texW, texH };
    SDL_RenderCopy(renderer, texture, NULL, &dstRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(texture);


}


void Graphics::closeMusic()
{
    Mix_Quit();
}