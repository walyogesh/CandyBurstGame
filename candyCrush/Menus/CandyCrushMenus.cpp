#include "CandyCrushMenus.h"
#include "../States/StateManager.h"
#include "../Input/InputController.h"
#include "../Gameplay/MainBorad.h"
#include "MenuManger.h"

void StartMenu::Update(InputController& input)
{
    auto position = input.GetMouseCurrentPosition();
    if ( MouseInputState::LEFTDOWN == input.GetMouseCurrentInputState())
    {
        if (mStartGame.getGlobalBounds().contains(position) || mBack.getGlobalBounds().contains(position))
        {
            StateManger::GetInstance()->ChangeState(ICandyCrushState::GameStates::InGame);
        }
        else if (mProfile.getGlobalBounds().contains(position))
        {
            MenuManger::GetInstance()->ChangeMenu(CandyCrushMenuType::ESettingsMenu);
        }
        else if (mExit.getGlobalBounds().contains(position))
        {   
            StateManger::GetInstance()->ChangeState(ICandyCrushState::GameStates::Exit);
        }
    }
}

void StartMenu::Render(window& renderTarget)
{
    //render background of the menu
    renderTarget.draw(mMenuBackground);

    renderTarget.draw(mStartGame);
    renderTarget.draw(mProfile);
    renderTarget.draw(mExit);
}

void SettingsMenu::Update(InputController& input)
{
    auto position = input.GetMouseCurrentPosition();
    if (MouseInputState::LEFTDOWN == input.GetMouseCurrentInputState())
    {
        if (mBack.getGlobalBounds().contains(position))
        {
            MenuManger::GetInstance()->ChangeMenu(CandyCrushMenuType::EStartMenu);
        }
    }
}

void SettingsMenu::Render(window& renderTarget)
{
    //render background of the game
    renderTarget.draw(mMenuBackground);

    renderTarget.draw(mSettings);

    renderTarget.draw(mBack);
}

void HelpMenu::Update(InputController& input)
{
}

void HelpMenu::Render(window& RenderTarget)
{
}

void ProfileMenu::Update(InputController& input)
{
}

void ProfileMenu::Render(window& RenderTarget)
{
}

void GameOverMenu::Update(InputController& input)
{
    auto position = input.GetMouseCurrentPosition();
    if (MouseInputState::LEFTDOWN == input.GetMouseCurrentInputState())
    {
        if (mNewGame.getGlobalBounds().contains(position))
        {
            MenuManger::GetInstance()->ChangeMenu(CandyCrushMenuType::EStartMenu);
        } 
        else if (mExit.getGlobalBounds().contains(position))
        {
            StateManger::GetInstance()->ChangeState(ICandyCrushState::GameStates::Exit);
        }
    }
}

void GameOverMenu::Render(window& renderTarget)
{
    renderTarget.draw(mMenuBackground);
    renderTarget.draw(mScore);
    renderTarget.draw(mGameOver);
    renderTarget.draw(mNewGame);
    renderTarget.draw(mExit);
}
