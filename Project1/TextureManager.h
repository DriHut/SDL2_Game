#pragma once

#include <SDL_image.h>
#include <SDL_ttf.h>

class TextureManager {

public:
	static SDL_Texture* loadTexture(const char* file_name);
	static SDL_Surface* loadSurface(const char* file_name);

	static SDL_Surface* cropSpriteSheet(SDL_Surface* sprite_sheet, int x, int y, int width, int height);
	static SDL_Texture* cropSpriteSheetToTexture(SDL_Surface* sprite_sheet, int x, int y, int width, int height);

	static SDL_Texture* GetTextTexture(const char* text, TTF_Font* font, SDL_Color color);
};