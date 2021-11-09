#pragma once
#include <vector>
#include "Renderer.h"

struct ColorBuffer {
	~ColorBuffer() { delete[] data; }
	ColorBuffer() = default;
	ColorBuffer(const ColorBuffer & other) {
		width = other.width;
		height = other.height;
		if (other.data) {
			data = new uint8_t[width * height * sizeof(color_t)];
			memcpy(data, other.data, width * height * sizeof(color_t));
		}
	}
	inline void SetColor(int x, int y, const color_t& color) const;

	uint8_t* data{ nullptr };

	int width = 0;
	int height = 0;
	int pitch = 0;
};

inline void ColorBuffer::SetColor(int x, int y, const color_t& color) const {
	if (x < 0  || x >= width ||  y < 0 || y >= height) return;

	((color_t*)(data))[x + y * width] = color;
}
