/*--------------------------------------------------------------

	[Controller.h]
	Author : 出合翔太

	プレイヤーのコントローラ

---------------------------------------------------------------*/
#pragma once

class Pawn;
class GameCamera;
class Pivot;
class Controller final
{
public:
	Controller() = delete;
	Controller(Pawn* pPawn, GameCamera* pCamera, Pivot* pPivot);
	~Controller();

	void FpsCameraMode(bool fpsMode);	// カメラモード
	//　移動
	void MoveForward(float deltaTime);
	void MoveBackward(float deltaTime);
	void RotRight(float deltaTime);
	void RotLeft(float deltaTime);
	void RotTurretRight(float deltaTime);
	void RotTurretLeft(float deltaTime);
	void RotMaingunUp(float deltaTime);
	void RotMaingunDown(float deltaTime);
	// 砲撃
	void Shot();
	// スキル
	void UseSkill();
private:
	Pawn* m_Pawn = nullptr;
	GameCamera* m_Camera = nullptr;
	Pivot* m_Pivot = nullptr;
};

