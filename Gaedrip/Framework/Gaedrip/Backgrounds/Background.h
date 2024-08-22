#pragma once
#include "BasicObjects/GameObject.h"
#include "Geomatries/Rect.h"

class Background : public GameObject
{
public:
	Background();
	~Background();

	// GameObject��(��) ���� ��ӵ�
	void Update() override;

	void Render() override;

private:

	Rect* rect = nullptr;

};

