#include "sample.h"
#include "../../candyCrush/Game/CandyCrushGame.h"

int main(int /*argc*/, char* /*argv*/[]) {
	window mainWindow(780, 780);
	CandyCrushGame sampleApp(mainWindow);
	sampleApp.Init();
	return gameRunner::run(sampleApp, mainWindow);
}