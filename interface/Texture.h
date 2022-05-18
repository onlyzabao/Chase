#pragma once
#include "../core/GameHeader.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class Texture
{
public:
    Texture();
    ~Texture();

    void free();

    Size getSize() const;
    
    bool loadFromFile(SDL_Renderer *_p_renderer, const std::string &_path);
    bool loadFromRenderedText(SDL_Renderer *_p_renderer, TTF_Font *_p_font, const std::string &_textureText, const SDL_Color &_textColor);
    void setColor(const Uint8 &_red, const Uint8 &_green, const Uint8 &_blue) const;
    void setBlendMode(const SDL_BlendMode &_blending) const;
    void setAlpha(const Uint8 &_alpha) const;
    void draw(SDL_Renderer *_p_renderer, const Coordinate &_position, double _angle = 0.0, SDL_Rect *_p_clip = nullptr) const;

private:
    SDL_Texture *p_texture;
    Size size;
};