#pragma once
#include "BasicObjects/GameObject.h"
#include "Geomatries/Rect.h"

class Background : public Component
{
public:
	Background(GameObject& gameObject);
	~Background();

	// GameObject��(��) ���� ��ӵ�
	void Update() override;

private:

	Rect* rect = nullptr;

};

