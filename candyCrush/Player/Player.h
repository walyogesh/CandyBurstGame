#pragma once
#include "..\Singleton\Singleton.h"

#include<string>

using namespace std;

class Player  :public Singleton<Player>
{
private:
    string mName;
    int mHighestLevel;//highest level of
public:

    Player();
    const string& GetName() const;
    void SetName(const string& name);
    int GetHighestLevel() const;
    void SetHighestLevel(int highestLevel);
};
