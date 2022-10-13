#include "DxLib.h"
#include "SceneMain.h"
#include "ShotBound.h"
#include "ShotNormal.h"
#include "ShotFall.h"
#include "enemy.h"
#include "backImg.h"
#include <cassert>

namespace
{
	//�V���b�g�̔��ˊԊu
	constexpr int kShotInterval = 16;

	//���C�t
	constexpr int kLife = 3;

	//�O���t�B�b�N�t�@�C����
	const char* const kPlayerGraphicFilename = "data/kawamoto.png";
}

SceneMain::SceneMain()
{
	for (auto& handle : m_hPlayerGraphic)
	{
		handle = -1;
	}
	m_hShotGraphic = -1;
	m_hTestSound = -1;
	m_hEnemyGraphic = -1;
	m_count = 0;
	m_life = kLife;

	m_frame = 0;	
	m_hitFrame = 0;
	m_RepelNum = 0;
}

SceneMain::~SceneMain()
{

}

// ������
void SceneMain::init()
{
	LoadDivGraph(kPlayerGraphicFilename, Player::kGraphicDivNum,
		Player::kGraphicDivX, Player::kGraphicDivY,
		Player::kGraphicSizeX, Player::kGraphicSizeY, m_hPlayerGraphic);

	//�e�̉摜
	m_hShotGraphic = LoadGraph("data/ice.png");
	//�G�̉摜
	m_hEnemyGraphic = LoadGraph("data/kumomitu.png");
	//�T�E���h�̃��[�h
	m_hTestSound = LoadSoundMem("sound/cursor0.mp3");

	//m_player.setHandle(m_hPlayerGraphic);
	for (int i = 0; i < Player::kGraphicDivNum; i++)
	{
		m_player.setHandle(i, m_hPlayerGraphic[i]);
	}
	m_player.init();
	m_player.setMain(this);

	m_enemy.setHandle(m_hEnemyGraphic);
	m_enemy.init();
	m_enemy.setMain(this);
}

// �I������
void SceneMain::end()
{
	for (auto& handle : m_hPlayerGraphic)
	{
		DeleteGraph(handle);
		m_RepelNum++;
	}
	//�O���t�B�b�N�A�����[�h
//	DeleteGraph(m_hPlayerGraphic);
	DeleteGraph(m_hShotGraphic);
	//�T�E���h�A�����[�h
	DeleteSoundMem(m_hTestSound);

	for (auto& pShot : m_pShotVt)
	{
		assert(pShot);

		delete pShot;
		pShot = nullptr;
	}
}

// ���t���[���̏���
bool SceneMain::update()
{
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if(padState & PAD_INPUT_1)
	{
		PlaySoundMem(m_hTestSound, DX_PLAYTYPE_BACK, true);
	}

	m_backImg.update();
	m_player.update();
	m_enemy.update();

	std::vector<ShotBase*>::iterator it = m_pShotVt.begin();
	while (it != m_pShotVt.end())
	{
		auto& pShot = (*it);
		assert(pShot);
		pShot->update()
			;
		//�G�̎��S����---------------------------
		if (m_enemy.isCol(*pShot))
		{
			m_enemy.setDead(true);	//�L���������S

			if (m_hitFrame == 0)	//1��̓����蔻�莞�ɂP�񂵂����C�t�͌��炳�Ȃ�
			{
				PlaySoundFile("sound/atotyotto.mp3", DX_PLAYTYPE_NORMAL);
				m_RepelNum++;
			}
			m_hitFrame = 20;	//���G����20�t���[��

			if (m_hitFrame != 0)	//����ł��鎞
			{
				m_hitFrame--;		//���G�t���[�������炷
			}
		}
		//----------------------------------------

		if (!pShot->isExist())
		{
			delete pShot;
			pShot = nullptr;

			//vector�̗v�f�폜
			it = m_pShotVt.erase(it);
			continue;
		}
		it++;
	}
	if (m_player.isCol(m_enemy))
	{
		m_player.setDead(true);	//�L���������S

		if (m_hitFrame == 0)	//1��̓����蔻�莞�ɂP�񂵂����C�t�͌��炳�Ȃ�
		{
			m_life--;	//���S�����C�t������炷
		}
		m_hitFrame = 20;	//���G����20�t���[��
	}
	if (m_hitFrame != 0)	//����ł��鎞
	{
		m_hitFrame--;		//���G�t���[�������炷
	}
	if (true)
	{
		m_frame++;			//����ł���Ƃ�1���J�E���g
	}
	if (m_frame == 300)		//�J�E���g�����܂�ƃL����������
	{
		//m_player.setDead(false);
		m_frame = 0;
	}

	


	return false;
}

// ���t���[���̕`��
void SceneMain::draw()
{
	m_backImg.draw();
	m_player.draw();
	m_enemy.draw();

	for (auto& pShot : m_pShotVt)
	{
		assert(pShot);
		pShot->draw();
	}
	//���ݑ��݂��Ă���e�̐���\��
	DrawFormatString(460, 0, GetColor(255, 255, 255), "�e�̐�:%d", m_pShotVt.size());
	//
	DrawFormatString(460, 40, GetColor(255, 255, 255), "������:%d", m_RepelNum);
	//
	DrawFormatString(460, 60, GetColor(255, 255, 255), "SCORE:%d", m_count);
	//
	DrawFormatString(460, 80, GetColor(255, 255, 255), "LIFE:%d", m_life);
	//
	DrawFormatString(460, 100, GetColor(255, 255, 255), "ENERGY:%d", m_count);
}

bool SceneMain::createShotNormal(Vec2 pos)
{
	ShotNormal* pShot = new ShotNormal;
	pShot->setHandle(m_hShotGraphic);
	pShot->start(pos);
	m_pShotVt.push_back(pShot);

	return true;
}

bool SceneMain::createShotFall(Vec2 pos)
{
	ShotFall* pShot = new ShotFall;
	pShot->setHandle(m_hShotGraphic);
	pShot->start(pos);
	m_pShotVt.push_back(pShot);

	return true;
}

bool SceneMain::createShotBound(Vec2 pos)
{
	ShotBound* pShot = new ShotBound;
	pShot->setHandle(m_hShotGraphic);
	pShot->start(pos);
	m_pShotVt.push_back(pShot);

	return true;
}