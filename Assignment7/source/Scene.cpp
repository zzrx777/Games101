//
// Created by Göksu Güvendiren on 2019-05-14.
//

#include "Scene.hpp"


void Scene::buildBVH() {
	printf(" - Generating BVH...\n\n");
	this->bvh = new BVHAccel(objects, 1, BVHAccel::SplitMethod::NAIVE);
}

Intersection Scene::intersect(const Ray& ray) const {
	return this->bvh->Intersect(ray);
}

void Scene::sampleLight(Intersection& pos, float& pdf) const {
	float emit_area_sum = 0;
	for (uint32_t k = 0; k < objects.size(); ++k) {
		if (objects[k]->hasEmit()) {
			emit_area_sum += objects[k]->getArea();
		}
	}
	float p = get_random_float() * emit_area_sum;
	emit_area_sum = 0;
	for (uint32_t k = 0; k < objects.size(); ++k) {
		if (objects[k]->hasEmit()) {
			emit_area_sum += objects[k]->getArea();
			if (p <= emit_area_sum) {
				objects[k]->Sample(pos, pdf);
				break;
			}
		}
	}
}

bool Scene::trace(
	const Ray& ray,
	const std::vector<Object*>& objects,
	float& tNear, uint32_t& index, Object** hitObject) {
	*hitObject = nullptr;
	for (uint32_t k = 0; k < objects.size(); ++k) {
		float tNearK = kInfinity;
		uint32_t indexK;
		Vector2f uvK;
		if (objects[k]->intersect(ray, tNearK, indexK) && tNearK < tNear) {
			*hitObject = objects[k];
			tNear = tNearK;
			index = indexK;
		}
	}
	return (*hitObject != nullptr);
}

// Implementation of Path Tracing
Vector3f Scene::castRay(const Ray& ray, int depth) const {
	Vector3f color = Vector3f{0.0, 0.0, 0.0};

	Intersection ray_intersection = intersect(ray);
	if (ray_intersection.m->hasEmission()) {
		if (depth == 0) { //视线与光源直接相交
			color = ray_intersection.m->getEmission();
		}
		for (auto light : lights) {
			Intersection light_sample_point;
			float sample_point_pdf;
			sampleLight(light_sample_point, sample_point_pdf);
			Ray pointToLight = Ray(ray.origin, (light_sample_point.coords - ray.origin).normalized());
			pointToLight.transformToLine(light_sample_point.coords);
			Intersection pointToLight_intersection = intersect(ray);
			if (pointToLight_intersection.distance < pointToLight.t_max) { //被遮挡
				continue;
			}
		}
	}
}
