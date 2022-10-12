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
}
SceneMain::~SceneMain()
{

}

// ������
void SceneMain::init()
{
	//m_hPlayerGraphic = LoadGraph("data/kyara.png");
	LoadDivGraph(kPlayerGraphicFilename, Player::kGraphicDivNum,
		Player::kGraphicDivX, Player::kGraphicDivY,
		Player::kGraphicSizeX, Player::kGraphicSizeY, m_hPlayerGraphic);

	m_hShotGraphic = LoadGraph("data/ice.png");
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
	//bgm�I��
//	StopSoundMem()

	for (auto& handle : m_hPlayerGraphic)
	{
		DeleteGraph(handle);
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

//void SceneMain::count()
//{
//	m_count++;
//}
// ���t���[���̏���
void SceneMain::update()
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
		pShot->update();
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
	DrawFormatString(0, 0, GetColor(255, 255, 255), "�e�̐�:%d", m_pShotVt.size());
	//DrawFormatString(0, 50, GetColor(255, 255, 255), "�J�E���g��:%d", m_count);
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