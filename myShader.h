#ifndef _MYSHADER_H_
#define _MYSHADER_H_

#include<algorithm>
#include "tgaimage.h"
#include "geometry.h"
#include "model.h"

extern mat<4, 4> ModelView;
extern mat<4, 4> Viewport;
extern mat<4, 4> Projection;


//NDC转换为带有深度的屏幕坐标系
void viewport(const int x, const int y, const int w, const int h);

void projection(const double coeff = 0); // coeff = -1/c

//模型变换和视图变换的组合
void lookat(const vec3 eye, const vec3 center, const vec3 up);

struct IShader 
{
	Model* model = NULL;
	vec3 lightDir;

	static TGAColor sample2D(const TGAImage &img, vec2 &uvf) {
		return img.get(uvf[0] * img.width(), uvf[1] * img.height());
	}

	virtual ~IShader()
	{

	}

	//顶点着色器和片段着色器设置为两个纯虚函数，要求子类必须重写
	virtual vec4 vertex(int iface, int nthvert) = 0;     //iface代表第i个面片，nthvert代表该面片的第n个顶点
	virtual bool fragment(const vec3 bar, TGAColor &color) = 0;
};

void drawTriangle(const vec4 clip_verts[3], IShader &shader, TGAImage &image, float* zbuffer);

#endif // !_MYSHADER_H_

