#pragma once
#include "CandyFactory.h"
#include "../src/sprite.h"
#include "../src/window.h"
#include "../src/text.h"
#include "../Singleton/Singleton.h"
#include <array>
#include "../Menus/CandyCrushMenus.h"

#define ROWS 8
#define COLUMNS 8 
typedef std::array< std::array<Candy*, ROWS>, COLUMNS> MAINBOARD;

class MainBorad :public Singleton<MainBorad>
{
public:   
    MainBorad()
        :mIsAnyGridEmpty(false)
        , mIsBoardStable(false)
        , mNewlyAddedScore(0)
    { 
    }
    ~MainBorad() { }

    void InitalizeMainBoard();
    void Update();
    void Reset();
    void FindMatchAndErase(int matchCount);
    void FillEmptyFeilds();
    void ShiftCandies(int row, int column);
    bool IsVaildSwap(sf::Vector2f startPositions,sf::Vector2f endPositions);
    void Render(window& renderTarget);
    bool SwapCandies(Candy& oldCandy,Candy& newCandy);
    const MAINBOARD& GetMainBorad() const { return mBorad; }
    Candy* GetCandyForPosition(float xPosition, float yPosition);
    const bool IsInputInWindow(float xPosition, float yPosition) const;
    void GetWindowDimensionToBoard(sf::Vector2f windowdimension) { mWindowDimension = windowdimension; };
    int GetNewlyAddedScore() const { return mNewlyAddedScore; }
private:
    bool mIsAnyGridEmpty;
    bool mIsBoardStable;
    int mNewlyAddedScore;
    sf::Vector2f mWindowDimension;
    MAINBOARD mBorad;
};


