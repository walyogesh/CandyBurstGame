#pragma once

#include "../src/game.h"
#include "../src/mouse.h"
#include "../src/text.h"
#include "../Gameplay/CandyFactory.h"
#include "../Input/InputController.h"
#include "../Score/ScoreBoard.h"
#include <string>

static const char* FONT = "Roboto-Bold.ttf";

using namespace king::worksample;
enum class CandyCrushMenuType
{
    EStartMenu = 0,
    ESettingsMenu,
    EHelpMenu,
    EProfileMenu,
    EGameOverMenu
};

class ICandyCrushMenu
{
public:
	ICandyCrushMenu(CandyCrushMenuType menu)
		: mMenuType(menu)
		, mBack("GO BACK", fontDirectory + FONT)
	{
	}
    virtual void Update(InputController& input)=0 ;
    virtual void Render(window& RenderTarget) =0;
	virtual ~ICandyCrushMenu() {}
	CandyCrushMenuType GetMenuType() const { return mMenuType; }
protected:
	text mBack;
private:
	CandyCrushMenuType mMenuType;
};

class StartMenu : public ICandyCrushMenu
{
public:
	StartMenu()
		: ICandyCrushMenu(CandyCrushMenuType::EStartMenu)
        , mStartGame("START", fontDirectory + FONT)
		, mExit("EXIT", fontDirectory + FONT)
		, mProfile("SETTING", fontDirectory + FONT)
		, mMenuBackground(textureDirectory + "background.jpg")
	{
		mMenuBackground.setPosition(10, 100);
		mStartGame.setPosition(450, 300);
		mStartGame.setStyle(sf::Text::Bold);
		mProfile.setPosition(450, 350);
		mExit.setPosition(450, 400);
		mBack.setPosition(450, 450);
	}
	virtual void Update(InputController& input) override;
	virtual void Render(window& RenderTarget) override;
private:
	text mStartGame;
	text mExit;
	text mProfile;
	sprite mMenuBackground;
};

class SettingsMenu : public ICandyCrushMenu
{
public:
	SettingsMenu()
        : ICandyCrushMenu(CandyCrushMenuType::ESettingsMenu)
        , mSettings("SETTING", fontDirectory + FONT)
		, mBack("GO BACK", fontDirectory + FONT)
        , mMenuBackground(textureDirectory + "bg.png")
    {
		mSettings.setPosition(300, 100);
		mSettings.setStyle(sf::Text::Bold);
		mBack.setPosition(300, 150);
    }
    virtual void Update(InputController& input) override;
    virtual void Render(window& RenderTarget) override;
	
private:
	text mSettings;
	text mBack;
	sprite mMenuBackground;
};

class HelpMenu : public ICandyCrushMenu
{
public:
	HelpMenu()
        : ICandyCrushMenu(CandyCrushMenuType::EHelpMenu)
    {
    }
    virtual void Update(InputController& input) override;
    virtual void Render(window& RenderTarget) override;
};

class ProfileMenu : public ICandyCrushMenu
{
public:
	ProfileMenu()
        : ICandyCrushMenu(CandyCrushMenuType::EProfileMenu)
    {
    }
    virtual void Update(InputController& input) override;
    virtual void Render(window& RenderTarget) override;
};

class GameOverMenu : public ICandyCrushMenu
{
public:
	GameOverMenu()
        : ICandyCrushMenu(CandyCrushMenuType::EGameOverMenu)
		, mGameOver("!! GAME OVER !!", fontDirectory + FONT)
		, mScore(std::string("="+ std::to_string(ScoreBoard::GetInstance()->GetCurrentScore()) + "=") , fontDirectory + FONT)
        , mNewGame("> NEW GAME", fontDirectory + FONT)
		, mExit("> EXIT", fontDirectory + FONT)
        , mMenuBackground(textureDirectory + "bg.png")
    {
		mScore.setPosition(250, 100);
		mScore.setCharacterSize(80);
		sf::Color black;
		mScore.setFillColor(black);
        mNewGame.setPosition(280, 400);
		mExit.setPosition(280, 450);
		mGameOver.setPosition(110, 550);
		mGameOver.setCharacterSize(80);
		mGameOver.setStyle(sf::Text::Bold);
    }

    virtual void Update(InputController& input) override;
    virtual void Render(window& RenderTarget) override;

private:
    text mGameOver;
	text mScore;
    text mNewGame;
	text mExit;
    sprite mMenuBackground;
};