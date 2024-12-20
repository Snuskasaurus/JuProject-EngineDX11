#include "Engine/GameWindow.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow)
{
	JuProject::CreateGameWindow(hInstance);

	while (true)
	{
		const float dt = 0.01f;
		JuProject::DoFrame(dt);
		const JuProject::SExitResult ExitResult = JuProject::HandleGameWindowMessage();
		if (ExitResult.Exiting == true) return ExitResult.Reason; // Exit application
	}
}