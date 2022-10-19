#include "DxLib.h"
#include "SceneMain.h"
#include "ShotBound.h"
#include "ShotNormal.h"
#include "ShotEnemy.h"
#include "ShotEnemy3way.h"
#include "ShotEnemy1way.h"
#include "ShotEnemy2way.h"
#include "enemy.h"
#include "backImg.h"
#include "villainFirst.h"
#include <cassert>

#include "SceneTitle.h"
#include "SceneTest.h"
#include "SceneEnd.h"


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
	m_hShotGraphic1 = -1;
	m_hTestSound = -1;
	m_hEnemyGraphic = -1;
	m_VillainGraphic = -1;
	m_count = 0;
	m_life = kLife;

	frame = 0;
	m_frame = 0;	
	m_hitFrame = 0;
	m_RepelNum = 0;

	m_textPosX = 0;
	m_textVecX = 4;
	m_isEnd = false;
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
	m_hShotGraphic1 = LoadGraph("data/shot.png");
	//�G�̉摜
	m_hEnemyGraphic = LoadGraph("data/kumomitu.png");
	//�T�E���h�̃��[�h
	m_hTestSound = LoadSoundMem("sound/yone.mp3");
	//�G�̉摜
	m_VillainGraphic = LoadGraph("data/yone.png");

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
	}
	DeleteGraph(m_hShotGraphic);
	DeleteGraph(m_hShotGraphic1);
	DeleteGraph(m_VillainGraphic);
	//�T�E���h�A�����[�h
	DeleteSoundMem(m_hTestSound);

	for (auto& pShot : m_pShotVt)
	{
		assert(pShot);

		delete pShot;
		pShot = nullptr;
	}

	for (auto& pVillain : m_villainVt)
	{
		assert(pVillain);

		delete pVillain;
		pVillain = nullptr;
	}

}

// ���t���[���̏���
SceneBase* SceneMain::update()
{
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	m_backImg.update();
	m_player.update();
	m_enemy.update();

	frame++;
	std::vector<ShotBase*>::iterator it = m_pShotVt.begin();
	std::vector<VillainBase*>::iterator its = m_villainVt.begin();
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
				//PlaySoundMem(m_hTestSound, DX_PLAYTYPE_NORMAL,true);
				m_RepelNum++;		//�������J�E���g
			}
			m_hitFrame = 20;	//���G����20�t���[��

			if (m_hitFrame != 0)	//����ł��鎞
			{
				m_hitFrame--;		//���G�t���[�������炷
			}
		}
		//---------------------------------------------------------------
	
		//�����̒e�̓����蔻��-------------------------------------------

		if (m_player.isColShot(*pShot))
		{
			m_player.setDead(true);	//�L���������S

			if (m_hitFrame == 0)	//1��̓����蔻�莞�ɂP�񂵂����C�t�͌��炳�Ȃ�
			{
				m_life--;	//���S�����C�t������炷
			}
			m_hitFrame = 20;	//���G����20�t���[��

			if (m_hitFrame != 0)	//����ł��鎞
			{
				m_hitFrame--;		//���G�t���[�������炷
			}
		}

		if (!pShot->isExist())
		{
			delete pShot;
			pShot = nullptr;

			//vector�̗v�f�폜
			it = m_pShotVt.erase(it);
			continue;
		}
		it++;

		//------------------------------------------------------------
	}


	//�G�N���X�̏���------------------------------------------------
	while(its != m_villainVt.end())
	{
		auto& pVillain = (*its);
		assert(pVillain);
		pVillain->update();
		if (!pVillain->isExist())
		{
			delete pVillain;
			pVillain = nullptr;

			//vector�̗v�f�폜
			its = m_villainVt.erase(its);
			continue;
		}
		its++;
	}
	//-------------------------------------------------------------


	//���L�����̔���-----------------------------------------------
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
	if (m_frame == 30)		//�J�E���g�����܂�ƃL����������
	{
		m_player.setDead(false);
		m_frame = 0;
	}

	//�I�v�V�������
	/*if (padState & PAD_INPUT_8)
	{
		return(new SceneTest);
	}*/
	//�I������
	if (frame > 12000 || m_life == 0)
	{
		return (new SceneEnd);		//�����B������ƏI����ʂɈڂ�
	}
	return this;
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
	for (auto& pVillain : m_villainVt)
	{
		assert(pVillain);
		pVillain->draw();
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
	DrawFormatString(460, 140, GetColor(255, 255, 255), "%d", frame);
}


//�e�̐���--------------------------------------------------------------
bool SceneMain::createShotNormal(Vec2 pos)
{
	ShotNormal* pShot = new ShotNormal;
	pShot->setHandle(m_hShotGraphic);
	pShot->start(pos);

	pShot->setPlayerShot(true);		//�����Ă���̂��G������������
	
	m_pShotVt.push_back(pShot);

	return true;
}

bool SceneMain::createShotEnemy(Vec2 pos)
{
	ShotEnemy* pShot = new ShotEnemy;
	pShot->setHandle(m_hShotGraphic1);
	pShot->start(pos);

	pShot->setPlayerShot(false);		//�����Ă���̂��G������������

	m_pShotVt.push_back(pShot);

	return true;
}

bool SceneMain::createShotBound(Vec2 pos)
{
	ShotBound* pShot = new ShotBound;
	pShot->setHandle(m_hShotGraphic);
	pShot->start(pos);

	pShot->setPlayerShot(true);		//�����Ă���̂��G������������

	m_pShotVt.push_back(pShot);

	return true;
}

bool SceneMain::createShotEnemy1way(Vec2 pos)
{
	ShotEnemy1way* pShot = new ShotEnemy1way;
	pShot->setHandle(m_hShotGraphic1);
	pShot->start(pos);

	pShot->setPlayerShot(false);		//�����Ă���̂��G������������

	m_pShotVt.push_back(pShot);

	return true;
}

bool SceneMain::createShotEnemy2way(Vec2 pos)
{
	ShotEnemy2way* pShot = new ShotEnemy2way;
	pShot->setHandle(m_hShotGraphic1);
	pShot->start(pos);

	pShot->setPlayerShot(false);		//�����Ă���̂��G������������

	m_pShotVt.push_back(pShot);

	return true;
}

bool SceneMain::createShotEnemy3way(Vec2 pos)
{
	ShotEnemy3way* pShot = new ShotEnemy3way;
	pShot->setHandle(m_hShotGraphic1);
	pShot->start(pos);

	pShot->setPlayerShot(false);		//�����Ă���̂��G������������

	m_pShotVt.push_back(pShot);

	return true;
}
//-------------------------------------------------

bool SceneMain::createVillainFirst(Vec2 pos)
{
	VillainFirst* pVillain = new VillainFirst;
	pVillain->setHandle(m_VillainGraphic);
	pVillain->start(pos);
	m_villainVt.push_back(pVillain);

	return true;
}