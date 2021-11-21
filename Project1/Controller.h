/*--------------------------------------------------------------

	[Controller.h]
	Author : �o���đ�

	�v���C���[�̃R���g���[��

---------------------------------------------------------------*/
#pragma once

class Player;
class GameCamera;
class Pivot;
class Controller final
{
public:
	Controller() = delete;
	Controller(Player* pPlayer, GameCamera* pCamera, Pivot* pPivot);
	~Controller();

	void FpsCameraMode(bool fpsMode);	// �J�������[�h
	//�@�ړ�
	void MoveForward(float deltaTime);
	void MoveBackward(float deltaTime);
	void RotRight(float deltaTime);
	void RotLeft(float deltaTime);
	void RotTurretRight(float deltaTime);
	void RotTurretLeft(float deltaTime);
	void RotMaingunUp(float deltaTime);
	void RotMaingunDown(float deltaTime);
	// �C��
	void Shot();
	// �X�L��
	void UseSkill();
private:
	Player* m_Player = nullptr;
	GameCamera* m_Camera = nullptr;
	Pivot* m_Pivot = nullptr;
};

