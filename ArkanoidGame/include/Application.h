#pragma once

#include <SDL.h>
#include <iostream>
#include "Entity.h"


class Application
{
public:
	Application(const int windowHeight , const int windowWidth)
		: m_pWindow {nullptr} , m_pRenderer {nullptr} , m_isGameRunning {false} ,
		  m_windowHeight {windowHeight} , m_windowWidth {windowWidth} { }
	~Application()
	{
		SDL_DestroyRenderer(m_pRenderer);
		SDL_DestroyWindow(m_pWindow);
		SDL_Quit();
	}

	inline bool get_is_game_running() { return m_isGameRunning; }
	void initialize_window();

	// Game-loop methods
	void set_up();
	void process_input();
	void update_data() { }
	void render();

private:
	// Window parameters
	int m_windowHeight;
	int m_windowWidth;

	// Game parameters
	bool m_isGameRunning;
	SDL_Window *m_pWindow;
	SDL_Renderer *m_pRenderer;

	// Entities
	Ball m_ball;
};