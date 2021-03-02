#include "MenuManger.h"

void MenuManger::Update(InputController& candyCrushInput)
{
    mMenu->Update(candyCrushInput);
}

void MenuManger::Render(window& renderTarget)
{
    mMenu->Render(renderTarget);
}

void MenuManger::ChangeMenu(CandyCrushMenuType menu)
{
	switch (menu)
	{
	case CandyCrushMenuType::EStartMenu:
		mMenu = std::make_unique<StartMenu>();
		break;
	case CandyCrushMenuType::ESettingsMenu:
		mMenu = std::make_unique<SettingsMenu>();
		break;
	case CandyCrushMenuType::EHelpMenu:
		mMenu = std::make_unique<HelpMenu>();
		break;
	case CandyCrushMenuType::EProfileMenu:
		mMenu = std::make_unique<ProfileMenu>();
		break;
	case CandyCrushMenuType::EGameOverMenu:
		mMenu = std::make_unique<GameOverMenu>();
		break;
	default:
		break;
	}
}

