#pragma once

#include "Vec2.h"
#include "villainBase.h"
#include "ShotBase.h"

class SceneMain;

class villainSecond : public VillainBase
{
public:
	villainSecond();
	virtual ~villainSecond()
	{
	}
	//SceneMain�N���X�̃|�C���^�ݒ�
	void setMain(SceneMain* pMain) { m_pMain = pMain; }
	// �O���t�B�b�N�f�[�^�ݒ�
	void setHandle(int handle) { m_handle = handle; }
	//�V���b�g�J�n
	virtual void start(Vec2 pos);
	// �X�V
	virtual void update();

	virtual void draw();

	// ���̎擾
	Vec2 getPos() const { return m_pos; }
	Vec2 getSize() const { return m_size; }

	//���S�ݒ�
	virtual void setDeads(bool isDead) { m_isDead = isDead; }

private:
	//SceneMain�̃|�C���^
	SceneMain* m_pMain;
	//int m_shotInterval;
	//�G���o�����Ă���̃J�E���g
	int m_count;
	//�o���A��~�A�A��
	int m_time, m_stopTime, m_outTime;
};