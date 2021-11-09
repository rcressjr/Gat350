#include "Renderer.h"
#include "Framebuffer.h"
#include "Image.h"
#include "PostProcess.h"
#include "Tracer.h"
#include "Scene.h"
#include "Material.h"

#include <iostream>
#include <SDL.h>

int main(int, char**)
{
	const int WIDTH = 800;
	const int HEIGHT = 600;

	std::unique_ptr<Renderer> renderer = std::make_unique<Renderer>();
	renderer->Initialize(WIDTH, HEIGHT);

	std::unique_ptr<Framebuffer> framebuffer = std::make_unique<Framebuffer>(renderer.get(), renderer->width, renderer->height);

	// ray tracer
	std::unique_ptr<Tracer> tracer = std::make_unique<Tracer>();

	//samplers
	//std::shared_ptr<Image> image = std::make_shared<Image>("../resources/cat.bmp");
	/*std::shared_ptr<TextureSampler> texture1 = std::make_unique<TextureSampler>(std::make_unique<Image>("../resources/earth.bmp"));
	std::shared_ptr<TextureSampler> texture2 = std::make_unique<TextureSampler>(std::make_unique<Image>("../resources/metal.bmp"));

	std::shared_ptr<CheckerSampler> black_checker = std::make_unique<CheckerSampler>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 1, 1, 1 });
	std::shared_ptr<CheckerSampler> red_checker = std::make_unique<CheckerSampler>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 1, 0, 0 });*/

	std::vector<std::shared_ptr<Sampler>> samplers;

	samplers.push_back(std::make_unique<TextureSampler>(std::make_unique<Image>("../resources/earth.bmp")));
	samplers.push_back(std::make_unique<TextureSampler>(std::make_unique<Image>("../resources/metal.bmp")));
	samplers.push_back(std::make_unique<TextureSampler>(std::make_unique<Image>("../resources/planet.bmp")));
	samplers.push_back(std::make_unique<TextureSampler>(std::make_unique<Image>("../resources/wood.bmp")));
	samplers.push_back(std::make_unique<TextureSampler>(std::make_unique<Image>("../resources/lava.bmp")));
	samplers.push_back(std::make_unique<ColorSampler>(glm::vec3{ 1.0f, 0.2f, 0.2f }));
	samplers.push_back(std::make_unique<ColorSampler>(glm::vec3{ 0.2f, 1.0f, 0.2f }));
	samplers.push_back(std::make_unique<ColorSampler>(glm::vec3{ 0.2f, 0.2f, 1.0f }));
	samplers.push_back(std::make_unique<ColorSampler>(glm::vec3{ 0.2f, 1.0f, 1.0f }));
	samplers.push_back(std::make_unique<ColorSampler>(glm::vec3{ 1.0f, 1.0f, 0.2f }));
	samplers.push_back(std::make_unique<ColorSampler>(glm::vec3{ 1.0f, 0.2f, 1.0f }));
	samplers.push_back(std::make_unique<ColorSampler>(glm::vec3{ 0.8f, 0.8f, 0.8f }));

	std::shared_ptr<CheckerSampler> black_checker = std::make_unique<CheckerSampler>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 1, 1, 1 }, 5.0f);
	std::shared_ptr<CheckerSampler> red_checker = std::make_unique<CheckerSampler>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 1, 0, 0 }, 3.0f);

	// scene
	std::unique_ptr<Scene> scene = std::make_unique<Scene>();
	/*std::unique_ptr<Sphere> sphere = std::make_unique<Sphere>(glm::vec3{ 0, 0, -10 }, 3.0f);
	scene->Add(std::move(sphere));
	scene->Add(std::move(std::make_unique<Plane>(glm::vec3{ 0, -5, 0 }, glm::vec3{ 0, 1, 0 })));
	scene->Add(std::move(std::make_unique<Sphere>(glm::vec3{ 0, 0, -10 }, 3.0f, std::make_shared<Lambertian>(glm::vec3{ 1, 0, 0 }))));
	scene->Add(std::move(std::make_unique<Sphere>(glm::vec3{ 3, 3, -8 }, 1.0f, std::make_shared<Metal>(glm::vec3{ 0, 1, 0 }, 0.0f))));
	scene->Add(std::move(std::make_unique<Plane>(glm::vec3{ 0, -3, 0 }, glm::vec3{ 0, 1, 0 }, std::make_shared<Lambertian>(glm::vec3{ 0.5f, 0.5f, 0.5f }))));
	*/

	/*scene->Add(std::move(std::make_unique<Sphere>(glm::vec3{ 0, 0, -10 }, 3.0f, std::make_shared<Lambertian>(glm::vec3{ 1, 0, 0 }))));
	scene->Add(std::move(std::make_unique<Sphere>(glm::vec3{ 3, 3, -8 }, 1.0f, std::make_shared<Lambertian>(glm::vec3{ 0, 0, 0.8f }))));
	scene->Add(std::move(std::make_unique<Sphere>(glm::vec3{ -3, 4, -6 }, 1.5f, std::make_shared<Metal>(glm::vec3{ 0.8f }, 0.05f))));
	scene->Add(std::move(std::make_unique<Sphere>(glm::vec3{ 0, 1, -4 }, 1.5f, std::make_shared<Dielectric>(glm::vec3{ 0.5f, 1, 0.5f }, 2.42f))));
	scene->Add(std::move(std::make_unique<Plane>(glm::vec3{ 0, -3, 0 }, glm::vec3{ 0, 1, 0 }, std::make_shared<Lambertian>(glm::vec3{ 0.2f }))));*/

	/*scene->Add(std::move(std::make_unique<Sphere>(glm::vec3{ 0, 4, -10 }, 3.0f, std::make_shared<Lambertian>(texture1))));
	scene->Add(std::move(std::make_unique<Sphere>(glm::vec3{ 5, 0, -8 }, 2.0f, std::make_shared<Lambertian>(glm::vec3{ 0.2f, 0.2f, 0.8f }))));
	scene->Add(std::move(std::make_unique<Sphere>(glm::vec3{ -3, 4, -6 }, 1.5f, std::make_shared<Metal>(texture2, 0.05f))));
	scene->Add(std::move(std::make_unique<Sphere>(glm::vec3{ 0, 1, -4 }, 1.5f, std::make_shared<Dielectric>(glm::vec3{ 0.5f, 1, 0.5f }, 2.42f))));
	scene->Add(std::move(std::make_unique<Plane>(glm::vec3{ 0, -2, 0 }, glm::vec3{ 0, 1, 0 }, std::make_shared<Lambertian>(black_checker))));

	scene->Add(std::move(std::make_unique<Sphere>(glm::vec3{ 0, 20, 0 }, 10.0f, std::make_shared<Emissive>(glm::vec3{ 10, 10, 10 }))));*/

	for (int x = -10; x < 10; x++)
	{
		for (int z = -10; z < 10; z++)
		{
			glm::vec3 position{ x + random(0.1f, 0.9f), 0.2f, z + random(0.1f, 0.9f) };
			float radius = 0.2f; //random(0.2f, 0.5f);

			std::shared_ptr<Material> material;
			std::shared_ptr<Sampler> sampler = samplers[rand() % samplers.size()];

			float r = random01();
			if (r < 0.8f)
			{
				material = std::make_shared<Lambertian>(sampler);
			}
			else if (r < 0.95f)
			{
				material = std::make_shared<Metal>(sampler, random(0.0f, 0.5f));
			}
			else
			{
				material = std::make_shared<Dielectric>(sampler, random(1.0f, 2.5f));
			}

			scene->Add(std::move(std::make_unique<Sphere>(position, radius, material)));
		}
	}

	scene->Add(std::move(std::make_unique<Plane>(glm::vec3{ 0, -0.01f, 0 }, glm::vec3{ 0, 1, 0 }, std::make_shared<Lambertian>(black_checker))));
	scene->Add(std::move(std::make_unique<Sphere>(glm::vec3{ 0, 1, 0 }, 1.0f, std::make_shared<Metal>(glm::vec3{ 0.8f, 0.8f, 0.8f }, 0.0f))));
	scene->Add(std::move(std::make_unique<Sphere>(glm::vec3{ -4, 1, 0 }, 1.0f, std::make_shared<Dielectric>(glm::vec3{ 1, 1, 1 }, 1.5f))));

	scene->Add(std::move(std::make_unique<Sphere>(glm::vec3{ 0, 30, 0 }, 10.0f, std::make_shared<Emissive>(glm::vec3{ 10, 10, 10 }))));

	//camera
	/*float focalLength = glm::length(glm::vec3{ 5, 5, 5 } - glm::vec3{ 0, 0, -10 });
	std::unique_ptr<Camera> camera = std::make_unique<Camera>(glm::vec3{ 5, 5, 5 }, glm::vec3{ 0, 0, -10 }, glm::vec3{ 0, 1, 0 }, 90.0f, glm::ivec2{ framebuffer->colorBuffer.width, framebuffer->colorBuffer.height }, 0.2f, focalLength);*/

	/*glm::vec3 eye = glm::vec3{ 5, 5, 0 };
	glm::vec3 lookAt = glm::vec3{ 0, 0, -10 };
	float focalLength = glm::length(eye - lookAt);
	std::unique_ptr<Camera> camera = std::make_unique<Camera>(eye, lookAt, glm::vec3{ 0, 1, 0 }, 90.0f, glm::ivec2{ framebuffer->colorBuffer.width, framebuffer->colorBuffer.height }, 0.2f, focalLength);*/

	//glm::vec3 eye = glm::vec3{ 5, 1, 2 };
	//glm::vec3 lookAt = glm::vec3{ 0, 2, -10 };
	//float focalLength = glm::length(eye - lookAt);
	//std::unique_ptr<Camera> camera = std::make_unique<Camera>(eye, lookAt, glm::vec3{ 0, 1, 0 }, 90.0f, glm::ivec2{ framebuffer->colorBuffer.width, framebuffer->colorBuffer.height }, 0.2f, focalLength);

	glm::vec3 eye{ 13, 2, 3 };
	glm::vec3 lookAt{ 0, 0, 0 };
	float focalLength = glm::length(eye - lookAt);
	std::unique_ptr<Camera> camera = std::make_unique<Camera>(eye, lookAt, glm::vec3{ 0, 1, 0 }, 20.0f, glm::ivec2{ framebuffer->colorBuffer.width, framebuffer->colorBuffer.height }, 0.1f, focalLength);

	framebuffer->Clear(color_t{ 0, 0, 0, 0 });
	tracer->Trace(framebuffer->colorBuffer, scene.get(), camera.get());
	framebuffer->Update();

	bool quit = false;
	SDL_Event event;
	while (!quit)
	{

		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}

		renderer->CopyBuffer(framebuffer.get());
		renderer->Present();

		/*int clamp(int v, int min, int max)
		{
			int result = (v < min) ? min : ((v > max) ? max : v);
			return result;
		}*/
	}

	SDL_Quit();

	return 0;
}
