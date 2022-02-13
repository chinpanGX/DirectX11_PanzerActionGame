/*--------------------------------------------------------------

	[Controller.h]
	Author : 出合翔太

	プレイヤーのコントローラ

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

	void FpsCameraMode(bool FpsMode);	// カメラモード
	//　移動
	void MoveForward(float DeltaTime);
	void MoveBackward(float DeltaTime);
	void RotRight(float DeltaTime);
	void RotLeft(float DeltaTime);
	void RotTurretRight(float DeltaTime);
	void RotTurretLeft(float DeltaTime);
	void RotMaingunUp(float DeltaTime);
	void RotMaingunDown(float DeltaTime);
	// 砲撃
	void Shot();
	// スキル
	void UseSkill();
	// 弾薬の補給
	bool ReplenishBullet();
private:
	Player* m_Player = nullptr;
	GameCamera* m_Camera = nullptr;
	Pivot* m_Pivot = nullptr;
};

