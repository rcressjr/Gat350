#include "Renderer.h"
#include "Framebuffer.h"
#include "Image.h"
#include "PostProcess.h"
#include <iostream>
#include <SDL.h>

int main(int, char**) {
	const int WIDTH = 800;
	const int HEIGHT = 600;

	std::unique_ptr<Renderer> renderer = std::make_unique<Renderer>();
	renderer->Initialize(WIDTH, HEIGHT);
	
	std::unique_ptr<Framebuffer> framebuffer = std::make_unique<Framebuffer>(renderer.get(), renderer->width, renderer->height);

	std::unique_ptr<Image> image = std::make_unique<Image>();
	image->Load("../resources/flower.bmp");
	image->Flip();
	
	//PostProcess::Invert(framebuffer->colorBuffer);

	std::unique_ptr<Image> image1 = std::make_unique<Image>(*image.get());
	PostProcess::BoxBlur(image1->colorBuffer);

	std::unique_ptr<Image> image2 = std::make_unique<Image>(*image.get());
	PostProcess::GaussianBlur(image2->colorBuffer);

	std::unique_ptr<Image> image3 = std::make_unique<Image>(*image.get());
	PostProcess::Sharpen(image3->colorBuffer);

	std::unique_ptr<Image> image4 = std::make_unique<Image>(*image.get());
	PostProcess::Monochrome(image4->colorBuffer);
	PostProcess::Edge(image4->colorBuffer, 0);

	bool quit = false;
	SDL_Event event;
	while (!quit) {

		SDL_PollEvent(&event);
		switch (event.type) {
		case SDL_QUIT:
			quit = true;
			break;
		}

		framebuffer->Clear(color_t{ 0, 0, 0, 0 });

        for (int i = 0; i < 100; i++) {
            framebuffer->DrawPoint(rand() % renderer->width, rand() % renderer->height, { 0, 255, 0, 255 });
        }

        for (int i = 0; i < 20; i++) {
            framebuffer->DrawRect(rand() % renderer->width, rand() % renderer->height, 20, 20, { 0, 0, 255, 0 });
        }

        for (int i = 0; i < 20; i++) {
            framebuffer->DrawLine(renderer->width >> 1, renderer->height >> 1, rand() % renderer->width, rand() % renderer->height, { 255, 255, 255, 0 });
        }

        framebuffer->DrawTriangle(rand() % renderer->width, rand() % renderer->height, rand() % renderer->width, rand() % renderer->height, rand() % renderer->width, rand() % renderer->height, {180, 255, 15, 255});

		framebuffer->DrawCircle(rand() % renderer->width, rand() % renderer->height, rand() % renderer->height, {255, 117, 0, 255});

        for (int i = 0; i < 10; i++) {
            framebuffer->DrawQuadraticCurve(rand() % renderer->width, rand() % renderer->height, rand() % renderer->width, rand() % renderer->height, rand() % renderer->width, rand() % renderer->height, 30, { 255, 255, 0, 255 });
        }

        for (int i = 0; i < 10; i++) {
            framebuffer->DrawCubicCurve(rand() % renderer->width, rand() % renderer->height, rand() % renderer->width, rand() % renderer->height, rand() % renderer->width, rand() % renderer->height, rand() % renderer->width, rand() % renderer->height, 30, { 255, 255, 255, 255 });
        }

		framebuffer->DrawImage(300, 50, image.get());

		framebuffer->DrawImage(0, 300, image1.get());

		framebuffer->DrawImage(200, 300, image2.get());
		
		framebuffer->DrawImage(400, 300, image3.get());
	
		framebuffer->DrawImage(600, 300, image4.get());

		framebuffer->Update();

		renderer->CopyBuffer(framebuffer.get());

		renderer->Present();
	}

	SDL_Quit();

	return 0;
}
