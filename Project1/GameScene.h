/*-------------------------------------------------------------

	[GameScene.h]
	Author : 出合翔太

--------------------------------------------------------------*/
#pragma once
#include "Scene.h"
#include "GameBg.h"
#include "Engine.h"
#include "Graphics.h"

namespace GameScene
{
	// 戦車選択
	class PanzerSelect final : public Scene
	{
	public:
		void Init()override;
		void Uninit()override;
		void Update()override
		{
			Scene::Update();
		}
		void Draw()override;
	private:
		void Load()override;
		void Unload()override;
		void Thread_Audio();
		void Thread_Texture_A();
		void Thread_Texture_B();
		void Thread_Model();
	};

	// チュートリアル
	class Tutorial final : public Scene
	{
	public:
		void Init()override;
		void Uninit()override;
		void Update()override;
		void Draw()override;
	private:
		void Load()override;
		void Unload()override;
	};

	// ゲーム
	class Game final : public Scene
	{
	public:
		void Init()override;
		void Uninit()override;
		void Update()override;
		void Draw()override;
	private:
		void Load()override;
		void Unload()override;
	};
}