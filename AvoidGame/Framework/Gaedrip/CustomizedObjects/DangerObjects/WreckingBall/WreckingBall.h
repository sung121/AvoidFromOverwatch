#pragma once
#include "BasicObjects/GameObject.h"
#include "BasicObjects/Collider.h"
#include "Geomatries/TextureRect.h"

class Wreckingball : GameObject
{
public:
	Wreckingball();
	~Wreckingball();

	// GameObject��(��) ���� ��ӵ�
	void Update() override;
	void Render() override;

	Collider* getCollider() { return this->collider; }

public:
	StandardTransform& transform = GameObject::transform;

private:
	TextureRect* textureRect = nullptr;
	Collider* collider = nullptr;
};

