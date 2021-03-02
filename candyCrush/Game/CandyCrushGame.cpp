#include "CandyCrushGame.h"
#include "../Menus/MenuManger.h"

CandyCrushGame::CandyCrushGame(window& renderWindow)
    : mGameOver(false)
    , mIsFinished(false)
    , mCurrentState(ICandyCrushState::GameStates::Init)
    , mCandyCrushGamePlay(nullptr)
    , mRenderWindow(&renderWindow)
    , mCandyCrushInput(renderWindow)
{}

void CandyCrushGame::Init()
{
    StateManger::GetInstance()->AttachListener(this);
    StateManger::GetInstance()->ChangeState(ICandyCrushState::GameStates::Init);
}

void CandyCrushGame::Reset()
{
    mGameOver = false;
    mCandyCrushGamePlay->Reset();
    Init();
}

void CandyCrushGame::update(float deltaTime)
{
    StateManger::GetInstance()->Update();
    mCandyCrushInput.Update();

    switch (mCurrentState)
    {
    case ICandyCrushState::GameStates::Init:
        StateManger::GetInstance()->ChangeState(ICandyCrushState::GameStates::Menu);
        break;
    case ICandyCrushState::GameStates::Menu:
        MenuManger::GetInstance()->Update(mCandyCrushInput);
        break;
    case ICandyCrushState::GameStates::InGame:     
        mCandyCrushGamePlay->Update(deltaTime);
        break;
    case ICandyCrushState::GameStates::Exit:
        Reset();
        mIsFinished = true;
        break;
    }
   
}

void CandyCrushGame::render(window& renderTarget)
{
    switch (mCurrentState)
    {
    case ICandyCrushState::GameStates::Init:
        break;
    case ICandyCrushState::GameStates::Menu:
        MenuManger::GetInstance()->Render(renderTarget);
        break;
    case ICandyCrushState::GameStates::InGame:
        mCandyCrushGamePlay->Render(renderTarget);
        break;
    case ICandyCrushState::GameStates::Exit:
        break;
    }
}

bool CandyCrushGame::IsGameOver()
{
    return mCandyCrushGamePlay->IsGameOver();
}

void CandyCrushGame::OnStateChange(ICandyCrushState::GameStates newState)
{
    ///////////////////////////////////
    /// current State | New State    //
    /// ---------------------------  //
    /// Init State    | Menu State   //
    /// Menu State    | InGame State //
    /// Menu State    | Exit State   ///////////////////
    /// InGame State  | Menu State - Pause menu       //
    /// InGame State  | Menu State - Game over menu   //
    ////////////////////////////////////////////////////
    
    switch (mCurrentState)
    {
    case ICandyCrushState::GameStates::Init:
        break;
    case ICandyCrushState::GameStates::Menu:
        if (newState == ICandyCrushState::GameStates::InGame)
        {
            if (mCandyCrushGamePlay.get())
            {
                mCandyCrushGamePlay->Reset();
            }
            else
            {
                mCandyCrushGamePlay = std::make_unique<GamePlay>(*mRenderWindow, mCandyCrushInput);
            }
        
            mCandyCrushGamePlay->Init();
        }
        if (newState == ICandyCrushState::GameStates::Exit)
        {
            mIsFinished = true;
        }
        break;
    case ICandyCrushState::GameStates::InGame:
        break;
    case ICandyCrushState::GameStates::Exit:
        mIsFinished = true;
        break;
    }
    mCurrentState = newState;
}
