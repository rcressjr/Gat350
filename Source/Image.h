#pragma once
#include <string>
#include "ColorBuffer.h"
#include "SDL.h"

using color_t = SDL_Color;

class Image {
public:
	bool Load(const std::string& filename, uint8_t alpha = 255);
	void Flip();
	friend class Framebuffer;

public:
	ColorBuffer colorBuffer;
};