//
// Created by goksu on 2/25/20.
//

#include <thread>
#include <fstream>
#include "Scene.hpp"
#include "Renderer.hpp"

inline float deg2rad(const float& deg) { return deg * M_PI / 180.0; }

const float EPSILON = 0.00001;

Renderer::Renderer(int screen_width, int screen_height) {
	framebuffer = std::vector<Vector3f>(screen_width * screen_height);
}


// The main render function. This where we iterate over all pixels in the image,
// generate primary rays and cast these rays into the scene. The content of the
// framebuffer is saved to a file.
void Renderer::Render(const Scene& scene) {
	float scale = tan(deg2rad(scene.fov * 0.5));
	float imageAspectRatio = scene.width / (float)scene.height;
	Vector3f eye_pos(278, 273, -800);
	int m = 0;

	// change the spp value to change sample ammount

	int spp = 160;
	int thread_n(12);

	std::cout << "SPP: " << spp << "\n";
	std::cout << "thread n: " << thread_n << "\n";

	TaskQueue queue(scene.width, scene.height);
	std::vector<std::jthread> workers;
	workers.reserve(thread_n);

	for (int i(0); i < thread_n; i++) {
		workers.emplace_back(
			[this, &queue, &scene, spp]() {
				rayCastWork(queue, scene, spp);
			}
		);
	}

	//for (uint32_t j = 0; j < scene.height; ++j) {
	//	for (uint32_t i = 0; i < scene.width; ++i) {
	//		// generate primary ray direction
	//		float x = (2 * (i + 0.5) / (float)scene.width - 1) * imageAspectRatio * scale;
	//		float y = (1 - 2 * (j + 0.5) / (float)scene.height) * scale;
	//
	//		Vector3f dir = normalize(Vector3f(-x, y, 1));
	//		Ray ray_in(eye_pos, dir);
	//		for (int k = 0; k < spp; k++) {
	//			framebuffer[m] += scene.castRay(ray_in, 0) / spp;
	//		}
	//		m++;
	//	}
	//	UpdateProgress(j / (float)scene.height);
	//}
	//UpdateProgress(1.f);
}

void Renderer::Save(const Scene& scene) {
	// save framebuffer to file
	FILE* fp = fopen("binary.ppm", "wb");
	(void)fprintf(fp, "P6\n%d %d\n255\n", scene.width, scene.height);
	for (auto i = 0; i < scene.height * scene.width; ++i) {
		static unsigned char color[3];
		color[0] = (unsigned char)(255 * std::pow(clamp(0, 1, framebuffer[i].x), 0.6f));
		color[1] = (unsigned char)(255 * std::pow(clamp(0, 1, framebuffer[i].y), 0.6f));
		color[2] = (unsigned char)(255 * std::pow(clamp(0, 1, framebuffer[i].z), 0.6f));
		fwrite(color, 1, 3, fp);
	}
	fclose(fp);
}


void Renderer::rayCastWork(TaskQueue& queue, const Scene& scene, int spp) {
	float scale = tan(deg2rad(scene.fov * 0.5f));
	float aspect = scene.width / (float)scene.height;
	Vector3f eye_pos(278, 273, -800);

	PixelTask task;
	int idx;
	while (queue.fetch(task)) {
		idx = task.y * scene.width + task.x;

		float x = (2 * (task.x + 0.5) / (float)scene.width - 1) * aspect * scale;
		float y = (1 - 2 * (task.y + 0.5) / (float)scene.height) * scale;

		Vector3f dir = normalize(Vector3f(-x, y, 1));
		Ray ray(eye_pos, dir);

		Vector3f color(0);
		for (int s = 0; s < spp; ++s) {
			color += scene.castRay(ray, 0);
		}

		framebuffer[idx] = color / static_cast<float>(spp);
	}
}
