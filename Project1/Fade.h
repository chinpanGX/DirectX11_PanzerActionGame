/*------------------------------------------------------------
	
	[Fade.h]
	Author : �o���đ�

	�t�F�[�h����

--------------------------------------------------------------*/
#pragma once
#include "Bg.h"

class Fade final : public Bg
{
public:
	// �t�F�[�h�̃X�e�[�g
	enum EState
	{
		E_NONE,
		E_IN,
		E_OUT
	};

	Fade() = delete;
	Fade(class Application& App, class Resource& Res, class Fps& Fps);
	~Fade();
	
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
	bool CheckStateNotNone(); // �X�e�[�g��NONE�Ȃ�false��Ԃ�

	// �v���p�e�B�̃Q�b�^�[/�Z�b�^�[
	void SetNextScene(class Scene* Next);
	Scene* GetNextScene() const;
	void SetState(const EState& State);
	EState GetState() const;
private:
	static class Scene* m_Next;
	class Application& m_App;
	class Resource& m_Resource;
	class Fps& m_Fps;
	EState m_State;
	float m_Time;
	float m_Alpha;
};

