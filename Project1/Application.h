/*------------------------------------------------------------
	
	[Application.h]
	Author : èoçá„ƒëæ

-------------------------------------------------------------*/
#pragma once
#include "Fade.h"
#include "Scene.h"

class Graphics;
class Application final
{
public:
	Application(Graphics& graphics);
	~Application();
	void Init();
	void Update();
	void Draw();
	Scene* GetScene() const;
	void ChangeScene(Scene* scene);
	template<typename T>
	inline void SetScene()
	{
		if (m_Fade->ChackState())
		{
			return;
		}
		m_Fade->SetState(Fade::E_OUT);
		
		T* scene = new T;
		m_Fade->SetNextScene(scene);
	}

private:
	std::unique_ptr<Fade> m_Fade;
	Graphics& m_Graphics;
	Scene* m_Scene;
};
