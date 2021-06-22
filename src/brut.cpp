#include "gui.cpp"

int main(int argc, char** args)
{
	if(GUI_Init())
	{
		return 1;
	}
	GUI_OpenWindow();

	while (!GUI_QUIT)
	{
		GUI_HandleEvents();
		GUI_UpdateWindow();
	}

	GUI_CloseWindow();
	GUI_Quit();

	return 0;
}
