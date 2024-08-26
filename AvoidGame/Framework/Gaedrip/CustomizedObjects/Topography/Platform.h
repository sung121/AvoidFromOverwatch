#pragma once
#include "BasicObjects/GameObject.h"
#include "Geomatries/TextureRect.h"
#include "BasicObjects/Collider.h"

class Platform : GameObject
{
public:
	Platform();
	~Platform();

	// GameObject��(��) ���� ��ӵ�
	void Update() override;
	void Render() override;


private:

	Collider* collider = nullptr;
	TextureRect* textureRect = nullptr;


};

