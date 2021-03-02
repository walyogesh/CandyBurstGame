#pragma once
#include "../candyCrush/IListener.h"
#include <vector>

class ISender
{
public:
    ISender() {}

    virtual ~ISender() {}

    void AttachListener(IStateListener* listener)
    {
        mListeners.push_back(listener);
    }

    void NotifyListeners(ICandyCrushState::GameStates newState)
    {
        for (const auto& i : mListeners)
        {
            i->OnStateChange(newState);
        }
    }
private:
    std::vector<IStateListener*> mListeners;
};




