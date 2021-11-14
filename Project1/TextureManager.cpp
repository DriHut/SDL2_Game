#include "TextureManager.h"
#include "Reference.h"
#include <iostream>

SDL_Texture* TextureManager::loadTexture(const char* file_name)
{
	// Load texture map for texture
	SDL_Surface* tmp = IMG_Load(file_name);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tmp);

	if (texture) { // log if texture got loaded
		std::cout << "texture loaded: " << file_name << " !..." << std::endl;
	}
	else {
		std::cerr << "couldn't load texture: " << file_name << " !..." << std::endl;
	}

	SDL_FreeSurface(tmp); // unload the surface

	return texture;
}

SDL_Surface* TextureManager::loadSurface(const char* file_name)
{
	// Load texture map for texture
	SDL_Surface* tmp = IMG_Load(file_name);

	if (tmp) { // log if surface got loaded
		std::cout << "surface loaded: " << file_name << " !..." << std::endl;
	}
	else {
		std::cerr << "couldn't load surface: " << file_name << " !..." << std::endl;
	}

	return tmp;
}

SDL_Surface* TextureManager::cropSpriteSheet(SDL_Surface* sprite_sheet, int x, int y, int width, int height) {
	// create a copy
	SDL_Surface* surface = SDL_CreateRGBSurface(sprite_sheet->flags, width, height, sprite_sheet->format->BitsPerPixel, sprite_sheet->format->Rmask, sprite_sheet->format->Gmask, sprite_sheet->format->Bmask, sprite_sheet->format->Amask);

	// set the croping square
	SDL_Rect rect = { x, y, width, height };

	// crop
	SDL_BlitSurface(sprite_sheet, &rect, surface, 0);

	return surface;
}

SDL_Texture* TextureManager::cropSpriteSheetToTexture(SDL_Surface* sprite_sheet, int x, int y, int width, int height) {
	// call surface crop to prevent redundancy
	SDL_Surface* surface = TextureManager::cropSpriteSheet(sprite_sheet, x, y, width, height);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface); // unload the surface

	return texture;
}

SDL_Texture* TextureManager::GetTextTexture(const char* text, TTF_Font* font, SDL_Color color) {
	// use the library to create the surface
	SDL_Surface* text_surface = TTF_RenderText_Solid(font, text, color);
	//convert to texture
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, text_surface);

	// free the surface
	SDL_FreeSurface(text_surface);
	return texture;
}