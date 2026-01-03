//
// Created by goksu on 2/25/20.
//
#include "Scene.hpp"
#include "TaskQueue.hpp"

#pragma once
struct hit_payload {
	float tNear;
	uint32_t index;
	Vector2f uv;
	Object* hit_obj;
};

class Renderer {
public:
	Renderer(int screen_width, int screen_height);
	void Render(const Scene& scene);
	void Save(const Scene& scene);

private:
	void rayCastWork(TaskQueue& queue, const Scene& scene, int spp);

	std::vector<Vector3f> framebuffer;
};
