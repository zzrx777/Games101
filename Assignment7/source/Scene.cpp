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
Vector3f Scene::castRay(const Ray& ray_in, int depth) const {
	Vector3f L_dir = Vector3f();
	Vector3f L_indir = Vector3f();

	Intersection ray_in_isect = intersect(ray_in);

	if (!ray_in_isect.happened) {
		return {};
	}

	if (ray_in_isect.m->hasEmission()) {
		if (depth == 0) {
			return ray_in_isect.m->getEmission();
		}
	}

	Intersection light_sample_point;
	float light_sample_point_pdf;
	sampleLight(light_sample_point, light_sample_point_pdf);

	Vector3f ray_out_ori = ray_in_isect.coords;
	Vector3f ray_out_dir = (light_sample_point.coords - ray_in_isect.coords).normalized();
	Ray ray_ori_to_light = Ray(ray_out_ori, ray_out_dir);

	Intersection ray_ori_to_light_isect = intersect(ray_ori_to_light);

	Vector3f ori_to_isect_line = (ray_ori_to_light_isect.coords - ray_ori_to_light.origin);
	float ori_to_isect_distance_square = dotProduct(ori_to_isect_line, ori_to_isect_line);

	if (ray_ori_to_light_isect.happened && ray_ori_to_light_isect.m->hasEmission()) {
		L_dir =
			ray_ori_to_light_isect.m->getEmission()
			* ray_in_isect.m->eval(ray_in.direction, ray_ori_to_light.direction, ray_in_isect.normal)
			* dotProduct(-ray_ori_to_light.direction, ray_ori_to_light_isect.normal)
			* dotProduct(ray_ori_to_light.direction, ray_in_isect.normal)
			/ ori_to_isect_distance_square
			/ light_sample_point_pdf;
	}


	float fire = get_random_float();
	if (fire < RussianRoulette) {
		Vector3f ray_out_ori = ray_in_isect.coords;
		Vector3f ray_out_dir = ray_in_isect.m->sample(ray_in.direction, ray_in_isect.normal);
		Ray ray_out = Ray(ray_out_ori, ray_out_dir.normalized());

		Intersection ray_out_isect = intersect(ray_out);
		if (ray_out_isect.happened && !ray_out_isect.m->hasEmission()) {
			L_indir =
				castRay(ray_out, depth + 1)
				* dotProduct(ray_out.direction, ray_in_isect.normal)
				* ray_in_isect.m->eval(ray_in.direction, ray_out.direction, ray_in_isect.normal)
				/ ray_in_isect.m->pdf(ray_in.direction, ray_out.direction, ray_in_isect.normal)
				/ RussianRoulette;
		}
	}

	return L_dir + L_indir;
}
