#pragma once

#include "GLpoint.hpp"

struct GLcamera : public GLpoint3d
{
	// �����̌���(deg)
	GLpoint2d gaze;

	// �f�t�H���g�R���X�g���N�^
	GLcamera();

	// �R���X�g���N�^
	GLcamera(double x, double y, double z, double azimuth = 0, double elevation = 0);

	// ��������C�ӂ̃I�u�W�F�N�g�𐶐�����
	template<typename T, typename P>
	inline T Gaze(const P &predicate) const
	{
		const auto azimuth = gaze.x * M_PI / 180;
		const auto elevation = gaze.y * M_PI / 180;
		return predicate(cos(azimuth), sin(azimuth), cos(elevation), sin(elevation));
	}

	// �����x�N�g��
	GLpoint3d GetGazeVector() const;

	// ������K�p����
	void LookAt();

	// �����̕����֐i��
	void MoveAhead(double distance);

	// �������Ɉړ�����
	void Shift(double distance);
};
