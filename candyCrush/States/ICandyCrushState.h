#pragma once
#include "../src/window.h"
using namespace king::worksample;
class ICandyCrushState
{
public:
    enum class GameStates
    {
        Init = 0,
        Menu,
        InGame,
        Exit
    };

    ICandyCrushState(GameStates state)
        :m_state(state)
    {
    }
    virtual ~ICandyCrushState() {};
    virtual void Init() = 0;
    virtual void Update() {};
    virtual GameStates GetState() {
        return m_state;
    };
protected:
    GameStates m_state;
};

class InitState : public ICandyCrushState
{
public:
    InitState()
        : ICandyCrushState(GameStates::Init)
    {
        Init();
    }

    void Init()
    {
        
    }
private:

};

class MenuState : public ICandyCrushState
{
public:
    MenuState()
        : ICandyCrushState(GameStates::Menu)
    {
        Init();
    }

    void Init()
    {

    }
private:

};

class InGameState : public ICandyCrushState
{
public:
    InGameState()
        : ICandyCrushState(GameStates::InGame)
    {
        Init();
    }
    void Init()
    {

    }
private:

};

class ExitState : public ICandyCrushState
{
public:
    ExitState()
        : ICandyCrushState(GameStates::Exit)
    {
        Init();
    }

    void Init()
    {

    }
private:

};