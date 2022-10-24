#include "ShadowShader.h"

vec4 DepthShader::vertex(int iface, int nthvert)
{
	vec4 objVertex = embed<4>(model->vert(iface, nthvert)); // ��.obj�ļ��ж�ȡ��������
	objVertex = Viewport * Projection * ModelView * objVertex;          // �任����Ļ����
	varyingTri.set_col(nthvert, proj<3>(objVertex / objVertex[3]));
	return objVertex;
}

bool DepthShader::fragment(vec3 bar, TGAColor& color)
{
	vec3 p = varyingTri * bar;
	color = TGAColor(255, 255, 255)*(p.z / depth);
	return false;
}

vec4 FrameShader::vertex(int iface, int nthvert)
{
	varyingUV.set_col(nthvert, model->uv(iface, nthvert));
	vec4 objVertex = Viewport * Projection*ModelView*embed<4>(model->vert(iface, nthvert));
	varyingTri.set_col(nthvert, proj<3>(objVertex / objVertex[3]));
	return objVertex;
}

bool FrameShader::fragment(vec3 bar, TGAColor& color)
{
	vec4 shadowPoint = mvpShadow * embed<4>(varyingTri*bar); // ��shadow map�еĶ�Ӧ��
	shadowPoint = shadowPoint / shadowPoint[3];

	int idx = int(shadowPoint[0]) + int(shadowPoint[1])*screenWidth; // ��shadow map�е�����

	float shadow = .3 + .7*(shadowBuffer[idx] < shadowPoint[2]);
	//float shadow = .3 + .7*(shadowbuffer[idx] < sb_p[2] + 43.34); // magic coeff ���� z-fighting

	vec2 uv = varyingUV * bar;        // Ϊ��ǰ���ز�ֵuv����

	vec3 normal = proj<3>(mvpIT*embed<4>(model->normal(uv))).normalize();
	vec3 incidentDir = proj<3>(mvp  *embed<4>(lightDir)).normalize(); // ����ⷽ������
	vec3 reflectionDir = (normal*(normal*incidentDir*2.f) - incidentDir).normalize();   // ����ⷽ������

	float specular = pow(std::max(reflectionDir.z, 0.), sample2D(model->specular(), uv)[0]);
	float diffuse = std::max(0., normal*incidentDir);

	TGAColor c = sample2D(model->diffuse(), uv);
	for (int i = 0; i < 3; i++) color[i] = std::min<float>(20 + c[i] * shadow*(1.2*diffuse + .6*specular), 255);

	return false;
}