#include "InputController.h"
#include "../Gameplay/MainBorad.h"

void InputController::Update()
{
    if (mMouseInput->isButtonDown())
    {
        mMousecliked = true;
            mMouseClickState = MouseInputState::LEFTDOWN;
    }
    else if (mMousecliked) // when mouse button will be up again 
    {
        mMouseClickState = MouseInputState::LEFTUP;
        mMousecliked = false;
    } else 
    {
        mMouseClickState = MouseInputState::Default;
    }
}