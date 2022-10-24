#include "GouraudShader.h"

vec4 GouraudShader::vertex(int iface, int nthvert)
{
	//漫反射光强度
	varyingIntensity[nthvert] = std::max(0.f, (float)(model->normal(iface, nthvert)*lightDir));

	//从.obj文件中读取顶点数据
	vec4 objVertex = embed<4>(model->vert(iface, nthvert));

	//MVP加视口变换将顶点变换到屏幕坐标
	return Viewport * Projection * ModelView * objVertex;
}

bool GouraudShader::fragment(const vec3 bar, TGAColor &color)
{
	//为当前像素进行光照插值计算
	float intensity = varyingIntensity * bar;
	color = TGAColor(255 * intensity, 255 * intensity, 255 * intensity);
	return false;
}
