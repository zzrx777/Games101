//
// Created by LEI XU on 4/27/19.
//
#include <Texture.hpp>

Texture::Texture(const std::string& name)
{
	image_data = cv::imread(name);
	cv::cvtColor(image_data, image_data, cv::COLOR_RGB2BGR);
	width = image_data.cols;
	height = image_data.rows;
}

Eigen::Vector3f Texture::getColor(float u, float v)
{
	std::tie(u, v) = clampUV(u, v);

	auto u_img = u * width;
	auto v_img = (1 - v) * height;
	auto color = image_data.at<cv::Vec3b>(v_img, u_img);
	return Eigen::Vector3f(color[0], color[1], color[2]);
}

Eigen::Vector3f Texture::getColorBilinear(float u, float v)
{
	std::tie(u, v) = clampUV(u, v);

	auto u_img = u * width;
	auto v_img = (1 - v) * height;

	auto u_mid = round(u_img);
	auto v_mid = round(v_img);

	int u_sign = std::signbit(u_img - u_mid) ? -1 : 1;
	int v_sign = std::signbit(v_img - v_mid) ? -1 : 1;

	auto u00 = Eigen::Vector2i(u_mid + u_sign * 0.5, v_mid + v_sign * 0.5);
	auto u01 = Eigen::Vector2i(u_mid - u_sign * 0.5, v_mid + v_sign * 0.5);
	auto u10 = Eigen::Vector2i(u_mid + u_sign * 0.5, v_mid - v_sign * 0.5);
	auto u11 = Eigen::Vector2i(u_mid - u_sign * 0.5, v_mid - v_sign * 0.5);

	auto u00_color = image_data.at<cv::Vec3b>(std::clamp(u00.y(), 0, height - 1), std::clamp(u00.x(), 0, width - 1));
	auto u01_color = image_data.at<cv::Vec3b>(std::clamp(u01.y(), 0, height - 1), std::clamp(u01.x(), 0, width - 1));
	auto u10_color = image_data.at<cv::Vec3b>(std::clamp(u10.y(), 0, height - 1), std::clamp(u10.x(), 0, width - 1));
	auto u11_color = image_data.at<cv::Vec3b>(std::clamp(u11.y(), 0, height - 1), std::clamp(u11.x(), 0, width - 1));

	float s = abs(abs(u_img - u_mid) - 0.5);
	float t = abs(abs(v_img - v_mid) - 0.5);

	auto linear_u0 = (1 - s) * u00_color + s * u01_color;
	auto linear_u1 = (1 - s) * u10_color + s * u11_color;

	auto bilinear = (1 - t) * linear_u0 + t * linear_u1;


	return Eigen::Vector3f(bilinear[0], bilinear[1], bilinear[2]);
}

// Eigen::Vector3f Texture::getColorBilinear(float u, float v)
// {
// 	std::tie(u, v) = clampUV(u, v);
//
// 	auto u_img = u * width;
// 	auto v_img = (1 - v) * height;
//
// 	int u0 = static_cast<int>(floor(u_img));
// 	int v0 = static_cast<int>(floor(v_img));
//
// 	auto u1 = std::clamp(u0 + 1, 0, width - 1);
// 	auto v1 = std::clamp(v0 + 1, 0, height - 1);
//
// 	auto c00 = image_data.at<cv::Vec3b>(v0, u0);
// 	auto c10 = image_data.at<cv::Vec3b>(v0, u1);
// 	auto c01 = image_data.at<cv::Vec3b>(v1, u0);
// 	auto c11 = image_data.at<cv::Vec3b>(v1, u1);
//
// 	float s = u_img - u0;
// 	float t = v_img - v0;
//
// 	auto linear_u0 = (1 - s) * c00 + s * c10;
// 	auto linear_u1 = (1 - s) * c01 + s * c11;
//
// 	auto bilinear = (1 - t) * linear_u0 + t * linear_u1;
//
// 	return Eigen::Vector3f(bilinear[0], bilinear[1], bilinear[2]);
// }

std::tuple<float, float> Texture::clampUV(float u, float v)
{
	u = std::fmod(u + 1, 1.0);
	v = std::fmod(v + 1, 1.0);
	return {u, v};
}
