#include "TimerManager.h"

//calculates remaining time for game
bool TimerManager::Update(float deltaTime)
{
    mGameStartTime += deltaTime;
    mRemainingTime = GAME_DURATION - mGameStartTime;
    if (mRemainingTime <= 0)
    {
        mTimerOver = true;
    }
    return mTimerOver;
}

