#pragma once
#include "../src/text.h"
#include "../Input/InputController.h"
#include "../Score/ScoreBoard.h"
#include "../Player/Player.h"
#include <chrono> 
using namespace king::worksample;

class GamePlay 
{
public:
    GamePlay(window& renderWindow, InputController& inputController);

    void Init();

    void Reset();

    void Update(float deltaTime) ;

	void HandleInput();

    void Render(window& renderTarget);

    bool IsGameOver();

    bool IsFirstMoveDone() const { return mFirstMove; }

    const sf::Vector2f& GetWindowDimension() const { return mWindowDimension; }
private:
    float mNewlyAddedScoreTime;
    sf::Vector2f mWindowDimension;
    text mPlayerNameText;
    text mScoreText;
    text mSwapScore;
    text mTimerText;
    sprite mBackground;

    //input actions
    bool mFirstMove;
    bool mMouseClickDownDone;
    Candy* mstartCandy;
    sf::Vector2f mstartPositions;
    sf::Vector2f mendPositions;
    const InputController& mMouseInput;
};
