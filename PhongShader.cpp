#include "PhongShader.h"

vec4 PhongShader::vertex(int iface, int nthvert)
{
	varyingUV.set_col(nthvert, model->uv(iface, nthvert));
	//从.obj文件中读取顶点数据
	vec4 objVertex = embed<4>(model->vert(iface, nthvert));
	return Viewport * Projection*ModelView*objVertex;
}

bool PhongShader::fragment(const vec3 bar, TGAColor& color)
{
	vec2 uv = varyingUV * bar;
	vec3 normal = proj<3>(mvpIT*embed<4>(model->normal(uv))).normalize();
	vec3 incidentDir = proj<3>(mvp*embed<4>(lightDir)).normalize();
	vec3 reflectionDir = (normal*(normal*incidentDir*2.f) - incidentDir).normalize();

	float specular = pow(std::max(reflectionDir.z, 0.), sample2D(model->specular(), uv)[0]);
	float diffuse = std::max(0., normal*incidentDir);

	TGAColor c = sample2D(model->diffuse(), uv);
	color = c;

	for (int i = 0; i < 3; i++)
		color[i] = std::min<float>(5 + c[i] * (diffuse + 0.*specular), 255);
	return false;
}