#pragma once

#include "stdafx.h"
#include "Geomatries/Rect.h"
#include "Geomatries/TextureRect.h"
#include "LevelObject.h"
#include "../GameSystems.h"

class LevelStart : public LevelObject
{
public:
	// LevelObject��(��) ���� ��ӵ�
	void ExcutePattern() override;
	void Collide() override;
	bool GetIsFinished() override;

	void ExcutePattern(GeometricObject*);

private:

	float timeStart = 0;
	bool isFinished = false;

	random_device randDevice;

};

