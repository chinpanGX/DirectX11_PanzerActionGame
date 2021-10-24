/*-------------------------------------------------------------

	[GameScene.h]
	Author : 出合翔太

--------------------------------------------------------------*/
#pragma once
#include "Scene.h"
#include "GameBg.h"

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
		void Draw()override
		{
			Scene::Draw();
		}
	private:
		void Load()override;
		void Unload()override;
		void Thread_A();
		void Thread_B();
		void Thread_C();
		void Thread_D();
	};

	// チュートリアル
	class Tutorial final : public Scene
	{
	public:
		void Init()override;
		void Uninit()override;
		void Update()override
		{
			Scene::Update();
		}
		void Draw()override
		{
			Scene::Draw();
		}
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
		void Update()override
		{
			Scene::Update();
		}
		void Draw()override
		{
			Scene::Draw();
		}
	private:
		void Load()override;
		void Unload()override;
	};
}