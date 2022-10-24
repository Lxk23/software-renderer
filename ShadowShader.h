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
	mat<4, 4> mvpShadow; //把第二个pass的屏幕坐标转换为第一个pass的屏幕坐标
	mat<2, 3> varyingUV;  // 三角形顶点的uv坐标
	mat<3, 3> varyingTri; // 三角形顶点的NDC坐标, written by VS, read by FS

	int screenWidth;
	float* shadowBuffer;

	FrameShader(mat<4, 4> M, mat<4, 4> MIT, mat<4, 4> MS) : mvp(M), mvpIT(MIT), mvpShadow(MS), varyingUV(), varyingTri() {}

	virtual vec4 vertex(int iface, int nthvert);
	
	virtual bool fragment(vec3 bar, TGAColor &color);
};


#endif // !_SHADOWSHADER_H_

