#pragma once
#include "States/ICandyCrushState.h"

class IStateListener
{
public:
    IStateListener() {}
    virtual ~IStateListener() {}
    virtual void OnStateChange(ICandyCrushState::GameStates newState) = 0;
};