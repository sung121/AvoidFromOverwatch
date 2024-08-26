#pragma once
#include "BasicObjects/GameObject.h"
#include "BasicObjects/Collider.h"
#include "Geomatries/TextureRect.h"

class HealPack : public GameObject
{
public:
	HealPack();
	~HealPack();

	// GameObject��(��) ���� ��ӵ�
	void Update() override;
	void Render() override;

	void Reset();

	Collider* getCollider() { return this->collider; }

private:
	
	TextureRect* textureRect = nullptr;
	Collider* collider = nullptr;

	int healAmount = 0;


};

