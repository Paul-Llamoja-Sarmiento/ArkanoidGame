#include "Application.h"
#include "Constants.h"


int main(int argc , char *args[])
{
	Application app(WINDOW_HEIGHT , WINDOW_WIDTH);

	bool init = app.initialize_window();

	SDL_Delay(2000);

	return 0;
}