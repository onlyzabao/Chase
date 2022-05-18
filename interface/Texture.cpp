#include "Texture.h"

Texture::Texture()
{

    p_texture = nullptr;
    size = {0, 0};
}

Texture::~Texture()
{
    free();
}

bool Texture::loadFromFile(SDL_Renderer *_p_renderer, const std::string &_path)
{
    free();

    SDL_Texture *p_newTexture = nullptr;

    SDL_Surface *p_loadedSurface = IMG_Load(_path.c_str());
    if (p_loadedSurface == nullptr)
    {
        std::cout << "Unable to load image " << _path << "! SDL_image Error: " << IMG_GetError() << std::endl;
        return false;
    }
    else
    {
        SDL_SetColorKey(p_loadedSurface, SDL_TRUE, SDL_MapRGB(p_loadedSurface->format, 255, 255, 255));

        p_newTexture = SDL_CreateTextureFromSurface(_p_renderer, p_loadedSurface);
        if (p_newTexture == nullptr)
        {
            std::cout << "Unable to create texture from " << _path << "! SDL Error: " << SDL_GetError() << std::endl;
            return false;
        }
        else
        {
            p_texture = p_newTexture;
            size.w = p_loadedSurface->w;
            size.h = p_loadedSurface->h;
        }
        SDL_FreeSurface(p_loadedSurface);
    }
    return true;
}

bool Texture::loadFromRenderedText(SDL_Renderer *_p_renderer, TTF_Font *_p_font, const std::string &_textureText, const SDL_Color &_textColor)
{
    free();

    SDL_Surface *p_textSurface = TTF_RenderText_Solid(_p_font, _textureText.c_str(), _textColor);
    if (p_textSurface != nullptr)
    {
        p_texture = SDL_CreateTextureFromSurface(_p_renderer, p_textSurface);
        if (p_texture == nullptr)
        {
            std::cout << "Unable to create texture from rendered text! SDL Error: " << SDL_GetError() << std::endl;
            return false;
        }
        else
        {
            size.w = p_textSurface->w;
            size.h = p_textSurface->h;
        }
        SDL_FreeSurface(p_textSurface);
    }
    else
    {
        std::cout << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << std::endl;
        return false;
    }
    return true;
}

void Texture::free()
{
    if (p_texture != nullptr)
    {
        SDL_DestroyTexture(p_texture);
        p_texture = nullptr;
        size = {0, 0};
    }
}

void Texture::setColor(const Uint8 &_red, const Uint8 &_green, const Uint8 &_blue) const
{
    SDL_SetTextureColorMod(p_texture, _red, _green, _blue);
}

void Texture::setBlendMode(const SDL_BlendMode &_blending) const
{
    SDL_SetTextureBlendMode(p_texture, _blending);
}

void Texture::setAlpha(const Uint8 &_alpha) const
{
    SDL_SetTextureAlphaMod(p_texture, _alpha);
}

void Texture::draw(SDL_Renderer *_p_renderer, const Coordinate &_position, double _angle, SDL_Rect *_p_clip) const
{
    SDL_Rect renderQuad = {_position.x, _position.y, size.w, size.h};
    if (_p_clip != nullptr)
    {
        renderQuad.w =_p_clip->w;
        renderQuad.h = _p_clip->h;
    }
    SDL_RenderCopyEx(_p_renderer, p_texture, _p_clip, &renderQuad, _angle, nullptr, SDL_FLIP_NONE);
}

Size Texture::getSize() const
{
    return size;
}