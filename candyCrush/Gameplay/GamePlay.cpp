#include "GamePlay.h"
#include "../Gameplay/MainBorad.h"
#include "../Timer/TimerManager.h"
#include "../States/StateManager.h"
#include "../Menus/CandyCrushMenus.h"
#include "../Menus/MenuManger.h"
#include <memory>

static const char* BACKGROUND = "/bg.png";

GamePlay::GamePlay(window& renderWindow, InputController& inputController)
    : mWindowDimension(renderWindow.getSize())
    , mFirstMove(false)
    , mMouseClickDownDone(false)
    , mstartCandy(nullptr)
    , mNewlyAddedScoreTime(0.0f)
    , mScoreText("Score: 0", fontDirectory + FONT)
    , mSwapScore("", fontDirectory + FONT)
    , mPlayerNameText("Welcome Yoo ", fontDirectory + FONT)
    , mTimerText("Timer: ", fontDirectory + FONT)
    , mBackground(textureDirectory + BACKGROUND)
    , mMouseInput(inputController)
{}

void GamePlay::Init()
{ 
    //LevelManager->generateLevel();
    MainBorad::GetInstance()->InitalizeMainBoard();
    MainBorad::GetInstance()->GetWindowDimensionToBoard(mWindowDimension);
    mScoreText.setPosition(600, 10);
    mSwapScore.setCharacterSize(50);
    mSwapScore.setPosition(575, 100);
    mPlayerNameText.setPosition(10, 10);
    mTimerText.setPosition(290, 10);
}

void GamePlay::Reset()
{
    mFirstMove = false;
    mTimerText.setString("Timer:" );
    MainBorad::GetInstance()->Reset();
    ScoreBoard::GetInstance()->Reset();
    TimerManager::GetInstance()->Reset();
}

void GamePlay::Update(float deltaTime)
{
    HandleInput();

    //Update score
    mScoreText.setString(std::string("Score: " + std::to_string(ScoreBoard::GetInstance()->GetCurrentScore())));

    if (IsFirstMoveDone())
    {
        MainBorad::GetInstance()->Update();

        //check if timer is elapsed/ game is over due to time elapsed
        if (bool timerUp = TimerManager::GetInstance()->Update(deltaTime))
        {
            mTimerText.setString("-- TIME OUT ---");
            StateManger::GetInstance()->ChangeState(ICandyCrushState::GameStates::Menu);
            MenuManger::GetInstance()->ChangeMenu(CandyCrushMenuType::EGameOverMenu);
        }
        else
        {
            mTimerText.setString(std::string("Timer: " + std::to_string(TimerManager::GetInstance()->GetRemainingTime())));
        }
    }


    // timer for Newly added Score pop up
    mNewlyAddedScoreTime += deltaTime;
    mSwapScore.setString(std::string(std::to_string(MainBorad::GetInstance()->GetNewlyAddedScore()*5) + "+" ));
}

void GamePlay::HandleInput()
{
    MouseInputState mouseInputState = mMouseInput.GetMouseCurrentInputState();
    if (mouseInputState != MouseInputState::Default)
    {
        if (MouseInputState::LEFTDOWN == mouseInputState)
        {
            auto mouseInput = mMouseInput.GetMouseCurrentPosition();
            if (!mMouseClickDownDone)
            {
                if (Candy* candy = MainBorad::GetInstance()->GetCandyForPosition(mouseInput.x, mouseInput.y))
                {
                    mstartCandy = candy;
                    mstartPositions = candy->getPosition();
                    mstartCandy->setPosition(mouseInput);
                    mMouseClickDownDone = true;
                }
            }
            else if (mstartCandy)
            {
                mstartCandy->setPosition(mouseInput);
            }
        }
        else if (MouseInputState::LEFTUP == mouseInputState && mstartCandy) //when mouse button will be up again 
        {
            sf::Vector2f EndPosition = mMouseInput.GetMouseCurrentPosition();
            EndPosition.x += 30; // calibration for smooth player experience 
            EndPosition.y += 30;
            if (MainBorad::GetInstance()->IsVaildSwap(mstartPositions, EndPosition))
            {
                mFirstMove = true;
                Candy* newCandy = MainBorad::GetInstance()->GetCandyForPosition(EndPosition.x, EndPosition.y);
                mstartCandy->setPosition(mstartPositions);
                MainBorad::GetInstance()->SwapCandies(*mstartCandy, *newCandy);
                mNewlyAddedScoreTime = 0;
                newCandy = nullptr;
            }
            else // go back to original place if its not valid move
            {
                mstartCandy->setPosition(mstartPositions);
            }
            mstartCandy = nullptr;
            mMouseClickDownDone = false;
        }
    }
}

void GamePlay::Render(window& renderTarget)
{
    //render background of the game
    renderTarget.draw(mBackground);

    //render Main Play Board
    MainBorad::GetInstance()->Render(renderTarget);

    //render score
    renderTarget.draw(mScoreText);

    //render Player Name
    renderTarget.draw(mPlayerNameText);

    //render timer
    renderTarget.draw(mTimerText);

    //render newly added score
   if(mNewlyAddedScoreTime <= 1 &&mFirstMove)
   {
       renderTarget.draw(mSwapScore);
   }
}

bool GamePlay::IsGameOver()
{
    return TimerManager::GetInstance()->CheckIfTimeIsUp();
}
