#pragma once
#include "..\Singleton\Singleton.h"
#include "..\src\text.h"
#include "..\Gameplay\CandyFactory.h"
#include <string>

class ScoreBoard :public Singleton<ScoreBoard>
{
public:
    ScoreBoard()
        : mCurrentScore(0)
        , mPreviousScore(0){}
    int GetCurrentScore() const { return mCurrentScore; }

    // each crushed candy gets 5 points
    void IncrementScoreBy(int candies) 
    { 
        mPreviousScore = mCurrentScore;
        mCurrentScore += (candies*5); 
    }

    void Reset() {
        mCurrentScore = 0; 
        mPreviousScore = 0;
    }
    int GetPreviousScore() const { return mPreviousScore; }
private:
    int mCurrentScore;
    int mPreviousScore;
};

