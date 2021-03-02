#pragma once
#include "../src/sprite.h"
#include "../Singleton/Singleton.h"

static const std::string assetDirectory = SAMPLE_ASSETS_DIR;
static const std::string textureDirectory = assetDirectory + "textures/";
static const std::string fontDirectory = assetDirectory + "fonts/";
//static const std::string soundDirectory = assetDirectory + "sounds/";
using namespace king::worksample;

class Candy :public sprite
{
public:
    enum class Color
    {
        GREEN = 0,
        YELLOW,
        RED,
        BLUE,
        PURPULE
    };
  
    bool operator==(const Candy& rhs) const
    {
        return (mColor == rhs.mColor);
    }
protected:
    Candy(const std::string& filename, Color color)
        :sprite(filename)
        , mColor(color)
    {}
private:
    Color mColor;    
};

class GreenCandy :public Candy
{
public:
    GreenCandy()
        :Candy(textureDirectory + "gem_green.png", Candy::Color::GREEN)
    {}
};

class BlueCandy :public Candy
{
public:
    BlueCandy()
        :Candy(textureDirectory + "gem_blue.png", Candy::Color::BLUE)
    {}
};

class YellowCandy :public Candy
{
public:
    YellowCandy()
        :Candy(textureDirectory + "gem_yellow.png", Candy::Color::YELLOW)
    {}
};

class PurpleCandy :public Candy
{
public:
    PurpleCandy()
        :Candy(textureDirectory + "gem_purple.png", Candy::Color::PURPULE)
    {}
};

class RedCandy :public Candy
{
public:
    RedCandy()
        :Candy(textureDirectory + "gem_red.png", Candy::Color::RED)
    {}
};

class CandyFactory :public Singleton<CandyFactory>
{
public:
    Candy* GetRandomCandy() const
    { 
        unsigned int randomValue= rand() %4; 
        switch (randomValue)
        {
        case 0:
            return new RedCandy();
        case 1:
            return new YellowCandy();
        case 2:
            return new GreenCandy();
        case 3:
            return new PurpleCandy();
        case 4:
            return new BlueCandy();
        default:
            return nullptr;
            break;
        }    
    } 

    CandyFactory()
    {
        srand(time(nullptr));
    }
};

