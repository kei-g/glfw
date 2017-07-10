#pragma once

class GLtexture
{
private:
	// �ǂݍ��ݍς�
	bool loaded;

	// ���\�[�XID
	int resourceID;

	// ���\�[�X�f�[�^
	LPVOID resourceData;

	// ���\�[�X�f�[�^�T�C�Y
	DWORD resourceSize;

	// �e�N�X�`��ID
	GLuint textureID;

private:
	// �R���X�g���N�^
	GLtexture(GLuint textureID, HGLOBAL resource, DWORD resourceSize);

	// �R���X�g���N�^
	GLtexture(GLuint textureID, HMODULE hModule, HRSRC resourceInfo);

public:
	// �R���X�g���N�^
	GLtexture(GLuint textureID, HMODULE hModule, int resourceID, LPCTSTR resourceType);

	// �f�X�g���N�^
	virtual ~GLtexture();

	// ���̃e�N�X�`�����g��
	void Bind();

	// �e�N�X�`���𐶐�����
	template<size_t N>
	static void Generate(std::vector<GLtexture> *textures, HMODULE hModule, const int(&resourceIDs)[N], LPCTSTR resourceType)
	{
		GLuint textureIDs[N] = { 0 };
		glGenTextures(N, textureIDs);
		textures->clear();
		textures->reserve(N);
		for (auto i = size_t(); i < N; i++) {
			textures->emplace_back(textureIDs[i], hModule, resourceIDs[i], resourceType);
		}
	}
};
