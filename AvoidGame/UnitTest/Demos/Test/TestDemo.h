#pragma once
#include "Geomatries/Rect.h"
#include "Gaedrip/CustomizedObjects/Entities/Player.h"
#include "Gaedrip/CustomizedObjects/Topography/Ground.h"
#include "Gaedrip/Managers/LevelsManager.h"

class TestDemo : public IObject
{
public:

	// IObject��(��) ���� ��ӵ�
	void Init() override;
	void Destroy() override;
	void Update() override;
	void Render() override;
	void PostRender() override;
	void GUI() override;

private:

	Rect* rect = nullptr;
	Collider* collider = nullptr;

	Player* player = nullptr;
	
	Wreckingball* wreckingball = nullptr;

	Ground* ground = nullptr;

	bool rendersWireFrame = false;

};

