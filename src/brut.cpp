#include "gui.cpp"
#include "filemanager.cpp"

/*	entry point of the app
*/

int main(int argc, char** args)
{
	if(GUI_Init())
	{
		return 1; // exit if initialisation fail
	}

	// setup
	GUI_OpenWindow();
	GUI_LoadResources();
	GUI_GenerateTextures();

	updateOpenFilesCount();

	while (!GUI_QUIT) // main loop
	{
		GUI_HandleEvents();
		GUI_UpdateWindow();
	}

	// freeing resources
	GUI_DestroyTextures();
	GUI_UnloadResources();
	GUI_CloseWindow();
	
	GUI_Quit();

	return 0;
}


void createNewFile() {
	openFiles.push_back({getCaption(NTABS+2), ""}); // no path means it's not saved anywhere yet
	updateOpenFilesCount();
	setMode(DOCUMENT); // switch to DOCUMENT mode if we're in another view
}