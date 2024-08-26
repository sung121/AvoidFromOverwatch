#pragma once

#include "stdafx.h"
#include "gaedrip.h"

void gaedrip::Init()
{
	mainScreen = new MainScreen();
	backgroundSolid = new Rect(Vector3(WinMaxWidth / 2, WinMaxHeight / 2, 0), Vector3(WinMaxWidth, WinMaxHeight, 0), 0);
	InitRound();
	
}

void gaedrip::Destroy()
{
	DestroyRound();
}

void gaedrip::Update()
{
	
	if (mainScreen->GetIsMain() == true)
	{
		if (isDestroyed == false)
		{
			// �ı�
			DestroyRound();
			isDestroyed = true;
			isInited = false;
		}
		// �޴�ȭ��
		BringUpMainScreen();
	}
	if (mainScreen->GetIsMain() == false)
	{
		if (isInited == false)
		{
			// ����
			InitRound();
			isInited = true;
			isDestroyed = false;
		}
		// ����
		ProgressRound();
	}

	UpdateAll();



}

void gaedrip::Render()
{


	if (mainScreen->GetIsMain() == false)
		backgroundSolid->Render();

	if (mainScreen->GetIsMain() == false)
	{

		player->GetPlayerObject()->Render();



		// �����ϸ�Ʈ���� ���� ����
		{
			reinhardt->GetReinhardtObject()->Render();
			reinhardt->GetHammerRightObject()->Render();
			reinhardt->GetHammerLeftObject()->Render();
		}

		// ��ŷ�� ���� ����
		wreckingBall->GetWreckingBallObject()->Render();


		// ���� ���� ����
		{
			for (int i = 0; i < geometricObject->GetDangerBoxs().size(); i++)
			{
				geometricObject->GetDangerBoxs()[i]->Render();
			}

			for (TextureRect* tr : geometricObject->GetGeometricBoxs())
			{
				tr->Render();
			}
		}

		//�Ķ� ���� ����
		for (int i = 0; i < phara->GetPharaMissiles().size(); i++)
		{
			phara->GetPharaMissiles()[i]->Render();
		}



		userInterface->GetEnergyBar()->Render();
		userInterface->GetBlinder()->Render();


		//��ư ����
		{
			vector<TextureRect*> Buttons = userInterface->GetButtons();
			Buttons[0]->Render();
			Buttons[2]->Render();

			if (isMovingLeft == true)
				Buttons[3]->Render();
			if (isMovingRight == true)
				Buttons[1]->Render();
			userInterface->GetKeyJump()->Render();
		}

		// ����� ����
		for (int i = 0; i < player->GetLifes(); i++)
		{
			userInterface->GetLifeImages()[i]->Render();
		}
		for (int i = 0; i < userInterface->GetScoreImages().size(); i++)
		{
			userInterface->GetScoreImages()[i]->Render();
		}

		cassidy->GetWall()->Render();
		cassidy->GetSkull()->Render();
		cassidy->GetCircle()->Render();

		healPack->GetHealPack()->Render();

	}

	if ( mainScreen->GetIsMain() == true )
	{
		backgroundSolid->Render();
		mainScreen->Render();
	}



}

void gaedrip::PostRender()
{
}

void gaedrip::GUI()
{
	mainScreen->GetButtonStart()->GUI();

}

void gaedrip::UpdateAll()
{
	if (mainScreen->GetIsMain() == false)
	{
		player->Update();

		geometricObject->Update();

		wreckingBall->GetWreckingBallObject()->Update();

		reinhardt->Update();

		cassidy->Update();

		userInterface->Update();

		healPack->GetHealPack()->Update();

		for (int i = 0; i < phara->GetPharaMissiles().size(); i++)
		{
			phara->GetPharaMissiles()[i]->Update();
		}
		if (player->GetIsDead() == true)
		{
			screenDefeat->Update();
		}
	}
	else
	{
		mainScreen->Update();
	}
	backgroundSolid->Update();
	
}

void gaedrip::ProgressRound()
{
	
	player->GetPlayerObject()->MoveWidthCanFast(player->GetEnergyPointer());
	GameSystems::AdjustEnergyBar(player, userInterface);

	player->Jump(gravitySpd, standardGravitySpd);

	if (player->GetIsApplyGravity() == true)
	{
		GameSystems::ApplyGravity(player, gravitySpd, gravitySpd);
	}
	GameSystems::CheckCollideGeometricObject(geometricObject, player);

	if (GameSystems::CheckCollideDangerBox(geometricObject, player) == true)
	{
		// �������� �ƴ��� �˻�
		if (player->HasDamage() == true)
		{
			userInterface->SetLifeImages(player->GetLifes());
		}
		//�׾����� �� �׾����� �˻�
		GameSystems::CheckPlayerDead(player, screenDefeat, mainScreen);
	};

	if (GameSystems::CheckCollideHealPack(healPack, player) == true)
	{
		int lifes = player->GetLifes();
		player->SetLifes(lifes + 1);
		userInterface->SetLifeImages(player->GetLifes());
	}



	switch (level)
	{
	case 0:

		levelStart->ExcutePattern(geometricObject);
		if (levelStart->GetIsFinished() == true)
		{
			uniform_int_distribution<int> intRand(1, 4);
			level = intRand(randDevice);
		}

		break;
	case 1:	// �����ϸ�Ʈ ����
	{

		reinhardt->ExcutePatternR(geometricObject);


		if (GameSystems::CheckCollideLevelReinhardt(reinhardt, player) == true)
		{
			if (player->HasDamage() == true)
			{
				userInterface->SetLifeImages(player->GetLifes());
				//userInterface->GetLifeImages()[player->GetLifes()]->SetPosition(Vector3(2000, 2000, 0));
			}
			GameSystems::CheckPlayerDead(player, screenDefeat, mainScreen);
		}


		if (reinhardt->GetIsFinished() == true)
		{
			uniform_int_distribution<int> intRand(1, 4);
			level = intRand(randDevice);
		}
	}
	break;
	case 2:	// ��ŷ�� ����
	{
		wreckingBall->ExcutePatternW(geometricObject);
		if (GameSystems::CheckCollideLevelWreckingBall(wreckingBall, player) == true)
		{
			if (player->HasDamage() == true)
			{
				userInterface->SetLifeImages(player->GetLifes());
				//userInterface->GetLifeImages()[player->GetLifes()]->SetPosition(Vector3(2000, 2000, 0));
			}
			GameSystems::CheckPlayerDead(player, screenDefeat, mainScreen);
		}

		if (wreckingBall->GetIsFinished() == true)
		{
			uniform_int_distribution<int> intRand(1, 4);
			level = intRand(randDevice);
		}
	}
	break;
	case 3:	// �ñ׸� ����
	{
		sigma->ExcutePatternS(player, geometricObject, healPack);

		//�׾����� �� �׾����� �˻�
		bool isUsedItem = sigma->GetisUsedItem();


		if (sigma->GetIsAttacked() == true)
		{
			userInterface->SetLifeImages(player->GetLifes());
			GameSystems::CheckPlayerDead(player, screenDefeat, mainScreen);
		}
		if (sigma->GetIsFinished() == true)
		{
			uniform_int_distribution<int> intRand(1, 4);
			level = intRand(randDevice);
		}
	}
	break;
	case 4:
		cassidy->ExcutePattern(player);
		if (cassidy->GetIsAttacked() == true)
		{
			userInterface->SetLifeImages(player->GetLifes());
			GameSystems::CheckPlayerDead(player, screenDefeat, mainScreen);
		}

		if (cassidy->GetIsFinished() == true)
		{
			uniform_int_distribution<int> intRand(1, 4);
			level = intRand(randDevice);
		}
	default:
		break;
	}


	AdjustButtonsColor();


	timeAbsoulte += Time::Delta();
	GameSystems::SetScoreBoard(userInterface, timeAbsoulte);
	GameSystems::CheckPlayerImmortal(player);
	GameSystems::LimitEnergy(player);

}

void gaedrip::BringUpDeathScreen()
{

}

void gaedrip::BringUpMainScreen()
{
	mainScreen->Excute();
}


void gaedrip::AdjustButtonsColor()
{
	//��ư �¿� �̹��� ����
	{
		if (Keyboard::Get()->Press('A') || Keyboard::Get()->Up('a'))
		{
			isMovingLeft = true;
		}
		if (Keyboard::Get()->Press('D') || Keyboard::Get()->Up('d'))
		{
			isMovingRight = true;
		}
		if (Keyboard::Get()->Up('A') || Keyboard::Get()->Up('a'))
		{
			isMovingLeft = false;
		}
		if (Keyboard::Get()->Up('D') || Keyboard::Get()->Up('d'))
		{
			isMovingRight = false;
		}
	}
}

void gaedrip::InitRound()
{

	player = new Player(-200, 2000);
	userInterface = new UserInterface();
	reinhardt = new LevelReinhardt();
	wreckingBall = new LevelWreckingBall();
	sigma = new LevelSigma();
	phara = new LevelPhara();
	geometricObject = new GeometricObject();
	start = new LevelStart();
	healPack = new HealPack();
	levelStart = new LevelStart();
	cassidy = new LevelCassidy();


	for (int i = 0; i < geometricObject->GetGeometricBoxs().size(); i++)
		geometricObject->GetGeometricBoxs()[i]->Update();

	for (int i = 0; i < userInterface->GetButtons().size(); i++)
		userInterface->GetButtons()[i]->Update();

	reinhardt->GetReinhardtObject()->Update();


	for (int i = 0; i < phara->GetPharaMissiles().size(); i++)
		phara->GetPharaMissiles()[i]->Update();

	wreckingBall->GetWreckingBallObject()->Update();
	healPack->GetHealPack()->Update();

	player->SetIsImmortal(true);
	player->SetTimeImmortal(1);

	userInterface->SetLifeImages(player->GetLifes());

	backgroundSolid->SetColor(Color(0, 0, 0, 1));

	// ����� �� �ʱ�ȭ
	{
		gravitySpd = 100;
		standardGravitySpd = 100;
		level = 0;
	}

}

void gaedrip::DestroyRound()
{
	reinhardt->Destroy();
	SAFE_DELETE(reinhardt);

	player->Destroy();
	SAFE_DELETE(player);

	userInterface->Destroy();
	SAFE_DELETE(userInterface);

	wreckingBall->Destroy();
	SAFE_DELETE(wreckingBall);

	sigma->Destroy();
	SAFE_DELETE(sigma);

	phara->Destroy();
	SAFE_DELETE(phara);

	SAFE_DELETE(start);

	healPack->Destroy();
	SAFE_DELETE(healPack);

	SAFE_DELETE(levelStart);

	geometricObject->Destroy();
	SAFE_DELETE(geometricObject);

	cassidy->Destroy();
	SAFE_DELETE(cassidy);

}




