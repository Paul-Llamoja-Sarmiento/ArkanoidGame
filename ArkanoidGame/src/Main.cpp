#include "Application.h"
#include "Constants.h"


int main(int argc , char *args[])
{
	Application app(WINDOW_HEIGHT , WINDOW_WIDTH);
	app.set_up();

	while (app.get_is_game_running())
	{
		app.process_input();
		app.render();
	}

	return 0;
}