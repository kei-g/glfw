// stdafx.h : �W���̃V�X�e�� �C���N���[�h �t�@�C���̃C���N���[�h �t�@�C���A�܂���
// �Q�Ɖ񐔂������A�����܂�ύX����Ȃ��A�v���W�F�N�g��p�̃C���N���[�h �t�@�C��
// ���L�q���܂��B
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Windows �w�b�_�[����g�p����Ă��Ȃ����������O���܂��B
// Windows �w�b�_�[ �t�@�C��:
#include <windows.h>

#define _USE_MATH_DEFINES
#include <cmath>
#include <deque>
#include <functional>
#include <iomanip>
#include <memory>
#include <sstream>
#include <thread>
#include <vector>

#define GLFW_INCLUDE_GLU

#include <GLFW/glfw3.h>

constexpr GLdouble GLepsilon = static_cast<double>(1) / 8192;
