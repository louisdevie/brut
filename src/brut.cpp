#include "gui.cpp"
#include "filemanager.cpp"
#include "utils.cpp"

/*	entry point of the app
*/

int main(int argc, char** args)
{
	setup(argc, args);

	if(GUI_Init())
	{
		return 1; // exit if initialisation fail
	}

	// setup
	GUI_OpenWindow();
	GUI_LoadResources();
	GUI_GenerateTextures();

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
	selectedDocument = appendFile({getCaption(NTABS+2), ""}); // no path means it's not saved anywhere yet
	updateDocnameTexture(selectedDocument);
	setMode(DOCUMENT); // switch to DOCUMENT mode if we're in another view
}


void closeFile() {
	selectedDocument = removeFile(selectedDocument);
	setMode(NOFILE);
}