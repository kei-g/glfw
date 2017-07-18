#pragma once

#include "PS4axes.h"

class PS4joystick
{
private:
	// ID
	const int id;

public:
	// �R���X�g���N�^
	PS4joystick(int id);

	// �f�X�g���N�^
	virtual ~PS4joystick();

	// ��Ԃ��擾����
	void Poll(PS4axes &axes) const;
};
