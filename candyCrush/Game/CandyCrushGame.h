#pragma once
#include "../src/game.h"
#include "../IListener.h"
#include "../States/StateManager.h"
#include "../Gameplay/GamePlay.h"
#include <memory>
using namespace king::worksample;

class CandyCrushGame : public game, public IStateListener
{
public:
    CandyCrushGame(window& renderWindow);

    void Init();

    void Reset();

    virtual void update(float deltaTime) override;

    virtual void render(window& renderTarget) override;

    virtual bool isFinished() const override { return mIsFinished; }
   
    virtual void OnStateChange(ICandyCrushState::GameStates newState) override;

    bool IsGameOver();

private:
    bool mGameOver;
    bool mIsFinished;
    InputController mCandyCrushInput;
    std::unique_ptr<GamePlay> mCandyCrushGamePlay;
    ICandyCrushState::GameStates mCurrentState;
    window* mRenderWindow;

};