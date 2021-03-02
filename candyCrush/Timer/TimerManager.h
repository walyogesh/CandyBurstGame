#pragma once
#include "../Singleton/Singleton.h"
#include "../Gameplay/CandyFactory.h"
#include "../src/text.h"

#define GAME_DURATION 30 // value is in seconds

class TimerManager :public Singleton<TimerManager>
{
public:
    TimerManager()
        : mTimerOver(false)
        , mGameStartTime(0.0f)
        , mRemainingTime(9999.0f)
    {}

    void SetGameStartTime(float startTime) { mGameStartTime = startTime; }

    bool CheckIfTimeIsUp() const { return mTimerOver; }

    bool Update(float deltaTime);

    void Reset() 
    {
        mTimerOver = false;
        mGameStartTime = 0.0f;
        mRemainingTime = 9999.0f;
    }

    int GetRemainingTime() const { return static_cast<int>(mRemainingTime); }

private:
    bool  mTimerOver;
    float mGameStartTime;
    float mRemainingTime;

};

