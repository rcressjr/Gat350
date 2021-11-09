#pragma once
#include <string>
#include "ColorBuffer.h"

using color_t = SDL_Color;

class Image {
public:
	Image() = default;
	Image(const std::string& filename, uint8_t alpha = 255);

	bool Load(const std::string& filename, uint8_t alpha = 255);
	void Flip();
	friend class Framebuffer;

public:
	ColorBuffer colorBuffer;
};