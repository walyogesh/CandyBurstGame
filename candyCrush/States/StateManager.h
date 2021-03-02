#pragma once
#include "ICandyCrushState.h"
#include "../Singleton/Singleton.h"
#include "../Gameplay/GamePlay.h"
#include "../ISender.h"

class StateManger :public Singleton<StateManger>, public ISender
{
public:
    StateManger()
        : m_gameState(nullptr)
    {
    }
    ~StateManger()
    {
    }
    void Update();
    ICandyCrushState::GameStates GetCurrentState() const { return m_gameState->GetState(); };
    void ChangeState(ICandyCrushState::GameStates gameState);
private:
    std::unique_ptr<ICandyCrushState> m_gameState;
};



