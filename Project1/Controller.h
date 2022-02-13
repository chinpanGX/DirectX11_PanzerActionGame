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
	Controller(Player* Player, GameCamera* Camera, Pivot* Pivot);
	~Controller();

	void FpsCameraMode(bool FpsMode);	// �J�������[�h
	//�@�ړ�
	void MoveForward(float DeltaTime);
	void MoveBackward(float DeltaTime);
	void RotRight(float DeltaTime);
	void RotLeft(float DeltaTime);
	void RotTurretRight(float DeltaTime);
	void RotTurretLeft(float DeltaTime);
	void RotMaingunUp(float DeltaTime);
	void RotMaingunDown(float DeltaTime);
	// �C��
	void Shot();
	// �X�L��
	void UseSkill();
	// �e��̕⋋
	bool ReplenishBullet();
private:
	Player* m_Player = nullptr;
	GameCamera* m_Camera = nullptr;
	Pivot* m_Pivot = nullptr;
};

