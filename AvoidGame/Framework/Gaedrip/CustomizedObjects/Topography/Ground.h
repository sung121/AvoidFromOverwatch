#pragma once
#include "BasicObjects/GameObject.h"
#include "Geomatries/TextureRect.h"
#include "BasicObjects/Collider.h"

class Ground : public Component
{
public:
	Ground();
	~Ground();

	// GameObject��(��) ���� ��ӵ�
	void Update() override;
	

	void ChangerRenderState();

	Collider* getCollider() { return collider; }

	//StandardTransform& getTransform() const { return transform; }

public:
	//StandardTransform& transform = GameObject::transform;

private:

	TextureRect* textureRect = nullptr;
	Collider* collider = nullptr;

};

