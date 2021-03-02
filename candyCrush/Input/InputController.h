#pragma once
#include "../src/mouse.h"
#include "../Singleton/Singleton.h"
#include "../Gameplay/CandyFactory.h"
#include <memory>

using namespace king::worksample;
enum class MouseInputState
{
    Default = 0,  // no action 
    LEFTDOWN =1,  // player presses left click
    LEFTHOLD =2,  //when player clicks left button and holds it 
    LEFTUP =3     // player releases left click
};

class InputController
{
public:
    InputController(window& window)
    : mMousecliked(false)
    , mMouseClickState(MouseInputState::Default)
    , mMouseInput(std::make_unique<mouse>(window))
    {};

    void Update();

    void Reset() {  mMousecliked = false; };

    const sf::Vector2f& GetMouseCurrentPosition() const { return mMouseInput->getPosition(); }
    MouseInputState GetMouseCurrentInputState() const { return mMouseClickState; }
private:
    bool mMousecliked;
    MouseInputState mMouseClickState;
    std::unique_ptr<mouse> mMouseInput;
};

