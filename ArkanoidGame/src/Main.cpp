#include "Application.h"


int main(int argc , char *args[])
{
	Application app;

	app.set_up();

	while (app.get_is_game_running())
	{
		app.process_input();
		app.update_data();
		app.render();
	}

	return 0;
}