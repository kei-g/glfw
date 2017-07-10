#include "GLsphere.h"

// �ԓ��X�Ίp
constexpr auto Obliquity = 23.43;

GLsphere::GLsphere(GLdouble radius, GLint slices, GLint stacks)
	: radius(radius), slices(slices), stacks(stacks)
{
}

void GLsphere::Draw(GLdouble rotation)
{
	glRotated(rotation, 0, cos(Obliquity * M_PI / 180), sin(Obliquity * M_PI / 180)); // �n���ɑ΂����]
	glRotated(Obliquity - 90, 1, 0, 0); // �n���̌X�����Č�����
	Sphere(radius, slices, stacks);
}
