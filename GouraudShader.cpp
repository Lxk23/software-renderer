#include "GouraudShader.h"

vec4 GouraudShader::vertex(int iface, int nthvert)
{
	//�������ǿ��
	varyingIntensity[nthvert] = std::max(0.f, (float)(model->normal(iface, nthvert)*lightDir));

	//��.obj�ļ��ж�ȡ��������
	vec4 objVertex = embed<4>(model->vert(iface, nthvert));

	//MVP���ӿڱ任������任����Ļ����
	return Viewport * Projection * ModelView * objVertex;
}

bool GouraudShader::fragment(const vec3 bar, TGAColor &color)
{
	//Ϊ��ǰ���ؽ��й��ղ�ֵ����
	float intensity = varyingIntensity * bar;
	color = TGAColor(255 * intensity, 255 * intensity, 255 * intensity);
	return false;
}