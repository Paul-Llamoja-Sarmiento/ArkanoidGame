#pragma once

#include <SDL.h>
#include <iostream>
#include "Constants.h"
#include "Entity.h"


class Application
{
public:
	Application()
		: m_pWindow {nullptr} , m_pRenderer {nullptr} , m_isGameRunning {false} ,
		  m_windowHeight {WINDOW_HEIGHT} , m_windowWidth {WINDOW_WIDTH} ,
		  m_frameTargetTime {FRAME_TARGET_TIME} , m_lastFrameTime {0} { }
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
	void update_data();
	void render();

private:
	// Window parameters
	int m_windowHeight;
	int m_windowWidth;

	// Game parameters
	bool m_isGameRunning;
	SDL_Window *m_pWindow;
	SDL_Renderer *m_pRenderer;

	// Update time parameters
	int m_frameTargetTime;	// Time in miliseconds between frames that we want to achieve
	int m_lastFrameTime;	// Time in miliseconds from the last frame

	// Entities
	Entity m_ball;
	Entity m_paddle;
};