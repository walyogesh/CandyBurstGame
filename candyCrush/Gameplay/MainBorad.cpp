#include "MainBorad.h"
#include "CandyFactory.h"
#include "../Score/ScoreBoard.h"
#include "../Input/InputController.h"
#include "SFML/System/Sleep.hpp"
#include <windows.h>

#define BORDERWIDTH 150
#define BORDERLENGTH 150 
#define GRIDSIZE 60

void MainBorad::InitalizeMainBoard()
{
    int xPos = BORDERWIDTH;

    for (auto& i : mBorad)
    {
        int yPos = BORDERLENGTH;
        for (auto& j : i)
        {
            if (j = CandyFactory::GetInstance()->GetRandomCandy())
            {
                j->setPosition(xPos,yPos );
                yPos += GRIDSIZE;
            }           
        }
        xPos += GRIDSIZE;
    }
}

void MainBorad::Update()
{
     FindMatchAndErase(3);
     if (mIsAnyGridEmpty)
     {
        FillEmptyFeilds();
     }
}

void MainBorad::Reset()
{
    mIsBoardStable = false;
    mIsAnyGridEmpty = false;
    mNewlyAddedScore = 0;
    for (auto &i:mBorad)
    {
        for (auto&j:i)
        {
            delete j;
            j = nullptr;
        }
    }
}

void MainBorad::FindMatchAndErase(int matchcount)
{
    if (matchcount > 1 && !mIsBoardStable)
    {
        //vertical match
        for (int i = 0; i < ROWS; ++i)
        {
            for (int j = 0; j < COLUMNS - 2; ++j)
            {
                int k = j + 1;
                int tempCount = 1;
                for (; k < COLUMNS; ++k)
                {
                    Candy* prevCandy = mBorad[i][j];
                    if(!(prevCandy
                        && mBorad[i][k]
                        && *prevCandy == *mBorad[i][k]))
                    {
                        break;
                    }
                    tempCount++;
                }
                if (tempCount >= matchcount)
                {
                    for (k=k-1; k >= j; --k)
                    {
                        if (mBorad[i][k])
                        {
                            mIsAnyGridEmpty = true;
                            delete mBorad[i][k];
                            mBorad[i][k] = nullptr;
                        }
                        ScoreBoard::GetInstance()->IncrementScoreBy(tempCount);
                        mNewlyAddedScore += tempCount;
                    }
                }
            }
        }

        //Horizontal match
        for (int i = 0; i < COLUMNS; ++i)
        {
            for (int j = 0; j < ROWS - 2; ++j)
            {
                int k = j + 1;
                int tempCount = 1;
                for (; k < ROWS; ++k)
                {
                    Candy* prevCandy = mBorad[j][i];
                    if (!(prevCandy
                        && mBorad[k][i]
                        && *prevCandy == *mBorad[k][i]))
                    {
                        break;
                    }
                    tempCount++;
                }
                if (tempCount >= matchcount)
                {
                    for (k=k-1; k >= j; --k)
                    {
                        if (mBorad[k][i])
                        {
                            mIsAnyGridEmpty = true;
                            delete mBorad[k][i];
                            mBorad[k][i] = nullptr;
                        }
                        ScoreBoard::GetInstance()->IncrementScoreBy(tempCount);
                        mNewlyAddedScore += tempCount;
                    }
                }
            }
        }
    }
    if (!mIsAnyGridEmpty)
    {
        mIsBoardStable = true;
    }
    else
    {
        mIsBoardStable = false;
    }
}

void MainBorad::FillEmptyFeilds()
{
    if (mIsAnyGridEmpty)
    {
        for (int i = 0; i < ROWS; ++i)
        {
            for (int j = 0; j < COLUMNS; ++j)
            {
                if (!mBorad[i][j])
                {
                    ShiftCandies(i, j);
                }
            }
        }
        mIsAnyGridEmpty = false;
    }
}

void MainBorad::ShiftCandies(int row, int column)
{
    for(int i=column; i>0; --i)
    {
        if (!mBorad[row][i] && mBorad[row][i-1])
        {
            mBorad[row][i] = mBorad[row][i-1];
            mBorad[row][i]->setPosition(BORDERWIDTH + (row * GRIDSIZE), BORDERLENGTH + (i * GRIDSIZE));
            mBorad[row][i-1] = nullptr;
        }
    }

    for (int firstrowcandy = 0; firstrowcandy < ROWS; ++firstrowcandy)
    {
        if (!mBorad[firstrowcandy][0])
        {
            Candy* newCandy = CandyFactory::GetInstance()->GetRandomCandy();
            newCandy->setPosition(BORDERWIDTH + (firstrowcandy * GRIDSIZE), BORDERLENGTH);
            mBorad[firstrowcandy][0] = newCandy;
            newCandy = nullptr;
        }
    }
}

/// <summary>
/// valid swap: One move in any straight direction
/// Invalid swap: Diagonal move, out of game play move, move more than one grid
/// </summary>
/// <param name="startPositions">: Position of the first candy to be swapped</param>
/// <param name="endPositions">: Position of second candy to be swapped</param>
/// <returns>If valid swap it returns true otherwise false </returns>
bool MainBorad::IsVaildSwap(sf::Vector2f startPositions, sf::Vector2f endPositions)
{
    if (IsInputInWindow(startPositions.x, startPositions.y) && IsInputInWindow(endPositions.x, endPositions.y))
    {
        int xOld = (startPositions.x - BORDERWIDTH) / GRIDSIZE;
        int yOld = (startPositions.y - BORDERLENGTH) / GRIDSIZE;
        int xNew = (endPositions.x - BORDERWIDTH) / GRIDSIZE;
        int yNew = (endPositions.y - BORDERLENGTH) / GRIDSIZE;
   
        //candies should be swappable only if they share same border 
        // and both has different color
        if ((  (xOld + 1 == xNew && yOld == yNew)
            || (xOld - 1 == xNew && yOld == yNew)
            || (xOld == xNew && yOld + 1 == yNew)
            || (xOld == xNew && yOld - 1 == yNew))
            && (mBorad[xNew][yNew])
            && (mBorad[xNew][yNew]) != (mBorad[xOld][yOld])) 
        {
            return true;
        }
    }   
    return false;
}

Candy* MainBorad::GetCandyForPosition(float xPosition, float yPosition)
{
    if (IsInputInWindow(xPosition, yPosition))
    {
        int x = (xPosition - BORDERWIDTH)/GRIDSIZE;
        int y = (yPosition - BORDERLENGTH)/GRIDSIZE;
        return mBorad[x][y];
    }
    return nullptr;
}

const bool MainBorad::IsInputInWindow(float xPosition, float yPosition) const
{
    return (xPosition < (mWindowDimension.x - BORDERWIDTH)
        && xPosition >= BORDERWIDTH
        && yPosition < (mWindowDimension.y - BORDERLENGTH)
        && yPosition >= BORDERLENGTH) ? true: false;

}

void MainBorad:: Render(window& renderTarget) 
{
    for (const auto& i : mBorad)
    {
        for (const Candy* j : i)
        {
            if (j)
            {
                renderTarget.draw(*j);
            }
        }         
    }
}

bool MainBorad::SwapCandies(Candy& oldCandy, Candy& newCandy)
{
    auto mstartPositions = oldCandy.getPosition();
    auto mNewPositions = newCandy.getPosition();
    int xOld = (mstartPositions.x - BORDERLENGTH) / GRIDSIZE;
    int yOld = (mstartPositions.y - BORDERWIDTH) / GRIDSIZE;
    int xNew = (mNewPositions.x - BORDERLENGTH) / GRIDSIZE;
    int yNew = (mNewPositions.y - BORDERWIDTH) / GRIDSIZE;

    mBorad[xOld][yOld] = &newCandy;
    mBorad[xNew][yNew] = &oldCandy;

    oldCandy.setPosition(mNewPositions);
    newCandy.setPosition(mstartPositions);
    mIsBoardStable = false;
    mNewlyAddedScore = 0;
    return true;

}
