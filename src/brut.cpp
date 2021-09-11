#include "gui.cpp"
#include "files.cpp"
#include "utils.cpp"

/*	entry point of the app
*/

int main(int argc, char** args)
{
	if (setup(argc, args)) {
		return 0;
	}

	if(GUI_Init())
	{
		return 1; // exit if initialisation fail
	}

	// setup
	GUI_OpenWindow();
	GUI_LoadResources();
	setAppID("io.sourceforge.brut:100DKILA");
	std::string path = getResourcePath(RES_LANG, "en");
	int status = loadLanguage(path);
	if (status) {
		switch (status) {
		case LANGERR_UNKNOWN:
			logError("LANGUAGES : Unknown error happened while trying to load "+path, 0);
			break;
		case LANGERR_FAILEDTOOPEN:
			logError("LANGUAGES : Couldn't open "+path, 0);
			break;
		case LANGERR_MISSINGFIELD:
			logError("LANGUAGES : Misssing header field(s) in file "+path, 0);
			break;
		case LANGERR_FOREIGNAPP:
			logError("LANGUAGES : The file "+path+" doesn't belong to this app", 0);
			break;
		}
		logInfo("LANGUAGES : Couldn't load default language file. Using a blank language instead.");
	}
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
	selectedDocument = appendFile({getCaption(NTABS+2), "", "Test text"}); // no path means it's not saved anywhere yet
	textChanged = true;
	GUI_ChangeWindowTitle("Brut: "+openFiles[selectedDocument].name);
	updateDocnameTexture(selectedDocument);
	switchToView(DOCUMENT); // switch to DOCUMENT mode if we're in another view
}


void closeFile() {
	selectedDocument = removeFile(selectedDocument);
	GUI_ChangeWindowTitle("Brut.");
	switchToView(NOFILE);
}