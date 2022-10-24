#ifndef _MYSHADER_H_
#define _MYSHADER_H_

#include<algorithm>
#include "tgaimage.h"
#include "geometry.h"
#include "model.h"

extern mat<4, 4> ModelView;
extern mat<4, 4> Viewport;
extern mat<4, 4> Projection;


//NDCת��Ϊ������ȵ���Ļ����ϵ
void viewport(const int x, const int y, const int w, const int h);

void projection(const double coeff = 0); // coeff = -1/c

//ģ�ͱ任����ͼ�任�����
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

	//������ɫ����Ƭ����ɫ������Ϊ�������麯����Ҫ�����������д
	virtual vec4 vertex(int iface, int nthvert) = 0;     //iface�����i����Ƭ��nthvert�������Ƭ�ĵ�n������
	virtual bool fragment(const vec3 bar, TGAColor &color) = 0;
};

void drawTriangle(const vec4 clip_verts[3], IShader &shader, TGAImage &image, float* zbuffer);

#endif // !_MYSHADER_H_

