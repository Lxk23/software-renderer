#ifndef _SHADOWSHADER_H_
#define _SHADOWSHADER_H_

#include "myShader.h"

struct DepthShader :public IShader
{
	mat<3, 3> varyingTri;
	float depth;

	DepthShader() : varyingTri() {}

	virtual vec4 vertex(int iface, int nthvert);

	virtual bool fragment(vec3 bar, TGAColor &color);
};


struct FrameShader : public IShader {
	mat<4, 4> mvp;   //  Projection*ModelView
	mat<4, 4> mvpIT; // (Projection*ModelView).invert_transpose()
	mat<4, 4> mvpShadow; //�ѵڶ���pass����Ļ����ת��Ϊ��һ��pass����Ļ����
	mat<2, 3> varyingUV;  // �����ζ����uv����
	mat<3, 3> varyingTri; // �����ζ����NDC����, written by VS, read by FS

	int screenWidth;
	float* shadowBuffer;

	FrameShader(mat<4, 4> M, mat<4, 4> MIT, mat<4, 4> MS) : mvp(M), mvpIT(MIT), mvpShadow(MS), varyingUV(), varyingTri() {}

	virtual vec4 vertex(int iface, int nthvert);
	
	virtual bool fragment(vec3 bar, TGAColor &color);
};

#endif // !_SHADOWSHADER_H_

