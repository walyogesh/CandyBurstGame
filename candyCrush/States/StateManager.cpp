#include "StateManager.h"

 void StateManger::Update()
 {
     m_gameState->Update();
 }

 void StateManger::ChangeState(ICandyCrushState::GameStates gameState)
 {
	 switch (gameState)
	 {
		case ICandyCrushState::GameStates::Init:
			m_gameState = std::make_unique<InitState>();
			break;
        case ICandyCrushState::GameStates::Menu:
            m_gameState = std::make_unique<MenuState>();
            break;
        case ICandyCrushState::GameStates::InGame:
            m_gameState = std::make_unique<InGameState>();
            break;
        case ICandyCrushState::GameStates::Exit:
            m_gameState = std::make_unique<ExitState>();
            break;
	 }
     NotifyListeners(m_gameState->GetState());
 }