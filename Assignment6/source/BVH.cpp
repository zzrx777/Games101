#include <algorithm>
#include <cassert>
#include "BVH.hpp"


BVHAccel::BVHAccel(std::vector<Object*> p, int maxPrimsInNode, SplitMethod splitMethod)
	: maxPrimsInNode(std::min(255, maxPrimsInNode)), splitMethod(splitMethod), primitives(std::move(p)) {
	time_t start, stop;
	time(&start);
	if (primitives.empty()) {
		return;
	}

	//root = BVHBuild(primitives);
	root = SAHBuild(primitives);

	time(&stop);
	double diff = difftime(stop, start);
	int hrs = (int)diff / 3600;
	int mins = ((int)diff / 60) - (hrs * 60);
	int secs = (int)diff - (hrs * 3600) - (mins * 60);

	printf("\rBVH Generation complete: \nTime Taken: %i hrs, %i mins, %i secs\n\n", hrs, mins, secs);
}

BVHBuildNode* BVHAccel::BVHBuild(std::vector<Object*> objects) {
	BVHBuildNode* node = new BVHBuildNode();

	// Compute bounds of all primitives in BVH node
	Bounds3 bounds;
	for (int i = 0; i < objects.size(); ++i) {
		bounds = Union(bounds, objects[i]->getBounds());
	}
	if (objects.size() == 1) {
		// Create leaf _BVHBuildNode_
		node->bounds = objects[0]->getBounds();
		node->object = objects[0];
		node->left = nullptr;
		node->right = nullptr;
		return node;
	}
	else if (objects.size() == 2) {
		node->left = BVHBuild(std::vector{objects[0]});
		node->right = BVHBuild(std::vector{objects[1]});

		node->bounds = Union(node->left->bounds, node->right->bounds);
		return node;
	}
	else {
		Bounds3 centroidBounds;
		for (int i = 0; i < objects.size(); ++i) {
			centroidBounds = Union(centroidBounds, objects[i]->getBounds().Centroid());
		}
		int dim = centroidBounds.maxExtent();
		switch (dim) {
		case 0:
			std::sort(objects.begin(), objects.end(), [](auto f1, auto f2) {
				return f1->getBounds().Centroid().x < f2->getBounds().Centroid().x;
			});
			break;
		case 1:
			std::sort(objects.begin(), objects.end(), [](auto f1, auto f2) {
				return f1->getBounds().Centroid().y < f2->getBounds().Centroid().y;
			});
			break;
		case 2:
			std::sort(objects.begin(), objects.end(), [](auto f1, auto f2) {
				return f1->getBounds().Centroid().z < f2->getBounds().Centroid().z;
			});
			break;
		}

		auto beginning = objects.begin();
		auto middling = objects.begin() + (objects.size() / 2);
		auto ending = objects.end();

		auto leftshapes = std::vector<Object*>(beginning, middling);
		auto rightshapes = std::vector<Object*>(middling, ending);

		assert(objects.size() == (leftshapes.size() + rightshapes.size()));

		node->left = BVHBuild(leftshapes);
		node->right = BVHBuild(rightshapes);

		node->bounds = Union(node->left->bounds, node->right->bounds);
	}

	return node;
}

BVHBuildNode* BVHAccel::SAHBuild(std::vector<Object*> objects) {
	BVHBuildNode* node = new BVHBuildNode();
	if (objects.size() == 1) {
		node->bounds = objects[0]->getBounds();
		node->object = objects[0];
		node->left = nullptr;
		node->right = nullptr;
		return node;
	}

	const static float tTisect = 1;
	const static float tTrav = 0.125;
	const static int buckets_num = 7;

	Bounds3 bounds3;
	for (auto& object : objects) {
		bounds3 = Union(bounds3, object->getBounds());
	}
	node->bounds = bounds3;
	double bounds3_S = bounds3.SurfaceArea();

	int axis = bounds3.maxExtent();
	std::ranges::sort(objects, [axis](auto f1, auto f2) {
		return f1->getBounds().Centroid()[axis] < f2->getBounds().Centroid()[axis];
	});

	unsigned int best_mid = 0;
	double min_cost = std::numeric_limits<double>::max();

	for (int i(1); i < buckets_num; i++) {
		float mid = bounds3.pMin[axis] + i * bounds3.Diagonal()[axis] / buckets_num;
		unsigned int current_mid = 0;
		double cost = min_cost;
		Bounds3 left_bounds3;
		Bounds3 right_bounds3;
		for (unsigned j(0); j < objects.size(); j++) {
			if (objects[j]->getBounds().Centroid()[axis] <= mid) {
				left_bounds3 = Union(left_bounds3, objects[j]->getBounds());
			}
			else {
				if (current_mid == 0) {
					current_mid = j;
				}
				right_bounds3 = Union(right_bounds3, objects[j]->getBounds());
			}
		}
		cost = (
			left_bounds3.SurfaceArea() * (current_mid - 1) +
			right_bounds3.SurfaceArea() * (objects.size() - current_mid)
		) * tTisect / bounds3.SurfaceArea() + tTrav;

		if (cost < min_cost) {
			min_cost = cost;
			best_mid = current_mid;
		}
	}
	if (best_mid == 0 || best_mid == objects.size() - 1) {
		best_mid = std::ceil((objects.size() - 1) / 2.0f);
	}

	auto mid = objects.begin() + best_mid;
	std::vector<Object*> leftshapes(objects.begin(), mid);
	std::vector<Object*> rightshapes(mid, objects.end());
	assert(objects.size() == (leftshapes.size() + rightshapes.size()));

	node->left = SAHBuild(leftshapes);
	node->right = SAHBuild(rightshapes);

	return node;
}


Intersection BVHAccel::Intersect(const Ray& ray) const {
	Intersection isect;
	if (!root)
		return isect;
	isect = BVHAccel::getIntersection(root, ray);
	return isect;
}

Intersection BVHAccel::getIntersection(BVHBuildNode* node, const Ray& ray) const {
	// TODO Traverse the BVH to find intersection
	Intersection isect;
	const std::array<int, 3> dirIsNeg{int(ray.direction.x > 0), int(ray.direction.y > 0), int(ray.direction.z > 0)};
	if (node->bounds.IntersectP(ray, ray.direction_inv, dirIsNeg)) {
		if (node->left == nullptr && node->right == nullptr) {
			isect = node->object->getIntersection(ray);
			return isect;
		}
		else {
			Intersection left_isect;
			Intersection right_isect;
			if (node->left != nullptr) {
				left_isect = BVHAccel::getIntersection(node->left, ray);
			}
			if (node->right != nullptr) {
				right_isect = BVHAccel::getIntersection(node->right, ray);
			}
			isect = left_isect.distance < right_isect.distance ? left_isect : right_isect;
		}
	}
	return isect;
}
