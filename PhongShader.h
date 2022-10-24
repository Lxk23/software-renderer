#ifndef _PHONGSHADER_H_
#define _PHONGSHADER_H_

#include "myShader.h"

struct PhongShader : public IShader
{
	mat<2, 3> varyingUV;
	mat<4, 4> mvp;
	mat<4, 4> mvpIT;  //mvp±ä»»¾ØÕóµÄÄæ×ªÖÃ¾ØÕó

	virtual vec4 vertex(int iface, int nthvert);

	virtual bool fragment(const vec3 bar, TGAColor& color);
};


#endif // !_PHONGSHADER_H_

