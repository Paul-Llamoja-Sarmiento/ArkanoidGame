#include "Application.h"
#include "Constants.h"


int main(int argc , char *args[])
{
	Application app(WINDOW_HEIGHT , WINDOW_WIDTH);
	app.initialize_window();

	while (app.isGameRunning)
	{
		app.process_input();
	}

	return 0;
}