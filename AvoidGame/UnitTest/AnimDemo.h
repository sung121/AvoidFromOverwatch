#pragma once
#include "Geomatries/AnimationRect.h"

class AnimDemo : public IObject
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
	AnimationRect* ar = nullptr;



};

