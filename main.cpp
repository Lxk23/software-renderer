#include <iostream>
#include <vector>
#include <limits>
#include "tgaimage.h"
#include "model.h"
#include "geometry.h"
#include "GouraudShader.h"
#include "PhongShader.h"
#include "ShadowShader.h"

using namespace std;

Model *model = nullptr;
float* shadowBuffer = nullptr;

const int width = 800;
const int height = 600;

vec3 lightDir(1, 1, 0);
vec3 camera(1, 1, 4);
vec3 center(0, 0, 0);
vec3 up(0, 1, 0);

int main(int argc, char** argv)
{
	if (2 > argc)
	{
		cerr << "Usage: " << argv[0] << "obj/model.obj" << endl;
		return 1;
	}

	float * zbuffer = new float[width*height];
	shadowBuffer = new float[width*height];

	for (int i = width * height; --i; ) {
		zbuffer[i] = shadowBuffer[i] = -std::numeric_limits<float>::max();
	}

	model = new Model(argv[1]);
	lightDir.normalize();

	/******第一个pass，相机位于光源位置******/
	{
		TGAImage depth(width, height, TGAImage::RGB);
		lookat(lightDir, center, up);
		viewport(width / 8, height / 8, width * 3 / 4, height * 3 / 4);
		projection(0);

		DepthShader dShader;
		vec4 screenCoords[3];
		for (int i = 0; i < model->nfaces(); i++) {
			for (int j = 0; j < 3; j++) {
				screenCoords[j] = dShader.vertex(i, j);
			}
			drawTriangle(screenCoords, dShader, depth, shadowBuffer);
		}
		depth.flip_vertically();
		depth.write_tga_file("depth.tga");
	}
	/******第一个pass，相机位于光源位置******/

	//m为相机位于光源位置时的mvp变换矩阵，在此处用于将世界坐标系下的坐标变换到第一个pass中的屏幕坐标
	mat<4, 4> m = Viewport * Projection*ModelView;

	/******第二个pass，决定每个像素是否加入阴影分量******/
	{
		TGAImage frame(width, height, TGAImage::RGB);
		lookat(camera, center, up);
		viewport(width / 8, height / 8, width * 3 / 4, height * 3 / 4);
		projection(-1.f / (camera - center).norm());

		FrameShader fShader(ModelView, (Projection*ModelView).invert_transpose(), m*(Viewport*Projection*ModelView).invert());
		vec4 screenCoords[3];
		for (int i = 0; i < model->nfaces(); i++) {
			for (int j = 0; j < 3; j++) {
				screenCoords[j] = fShader.vertex(i, j);
			}
			drawTriangle(screenCoords, fShader, frame, zbuffer);
		}
		frame.flip_vertically();
		frame.write_tga_file("framebuffer.tga");
	}
	/******第二个pass，决定每个像素是否加入阴影分量******/

	delete model;
	delete[] zbuffer;
	delete[] shadowBuffer;
	return 0;
}