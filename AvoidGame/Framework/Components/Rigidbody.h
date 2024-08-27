#pragma once
#include "Component.h"

class Rigidbody : public Component
{
	// Component��(��) ���� ��ӵ�
	void Start() override;
	void Destroy() override;
	void PhysicsUpdate() override;
	void OnCollisionEnter() override;
	void Update() override;
};

