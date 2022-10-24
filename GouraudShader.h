#ifndef _GOURAUDSHADER_H_
#define _GOURAUDSHADER_H_

#include "my_gl.h"

struct GouraudShader :public IShader
{
	vec3 varyingIntensity;  //在顶点着色器中写入，在片段着色器中读取

	virtual vec4 vertex(int iface, int nthvert);
	virtual bool fragment(const vec3 bar, TGAColor &color);
};


#endif // !_GOURAUDSHADER_H_

