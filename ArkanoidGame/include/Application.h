#pragma once

#include <SDL.h>
#include <iostream>

class Application
{
public:
	Application(const int windowHeight , const int windowWidth)
		: m_pWindow {nullptr} , m_pRenderer {nullptr} , isGameRunning {false} ,
		  m_windowHeight {windowHeight} , m_windowWidth {windowWidth} { }
	~Application()
	{
		SDL_DestroyRenderer(m_pRenderer);
		SDL_DestroyWindow(m_pWindow);
		SDL_Quit();
	}

	void initialize_window();
	void process_input();

public:
	bool isGameRunning;

private:
	int m_windowHeight;
	int m_windowWidth;

	SDL_Window *m_pWindow;
	SDL_Renderer *m_pRenderer;
};