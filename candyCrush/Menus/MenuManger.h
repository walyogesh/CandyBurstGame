#pragma once
#include "CandyCrushMenus.h"
class MenuManger :public Singleton<MenuManger>
{
public:
    MenuManger()
        : mMenu(std::make_unique<StartMenu>())
    {
    }
    void Update(InputController& mCandyCrushInput);
    void Render(window& renderTarget);
    void ChangeMenu(CandyCrushMenuType menu);
    CandyCrushMenuType GetCurrentMenu() { return mMenu->GetMenuType(); }
private:
    std::unique_ptr<ICandyCrushMenu> mMenu;
};

