//
// Created by LEI XU on 4/27/19.
//

#ifndef RASTERIZER_TEXTURE_H
#define RASTERIZER_TEXTURE_H
#include "global.hpp"
#include <Eigen/Eigen>
#include <opencv2/opencv.hpp>

class Texture
{
private:
	cv::Mat image_data;

public:
	Texture(const std::string& name);

	int width, height;

	Eigen::Vector3f getColor(float u, float v);

	Eigen::Vector3f getColorBilinear(float u, float v);

	std::tuple<float, float> clampUV(float u, float v);
};
#endif //RASTERIZER_TEXTURE_H
