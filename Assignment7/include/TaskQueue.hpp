#pragma once
#include <atomic>

struct PixelTask {
	int x;
	int y;
};

class TaskQueue {
public:
	TaskQueue(int w, int h)
		: width(w), height(h), index(0) {
	}

	bool fetch(PixelTask& task) {
		int i = index.fetch_add(1, std::memory_order_relaxed);
		if (i >= width * height) return false;

		task.x = i % width;
		task.y = i / width;
		return true;
	}

private:
	int width, height;
	std::atomic<int> index;
};
