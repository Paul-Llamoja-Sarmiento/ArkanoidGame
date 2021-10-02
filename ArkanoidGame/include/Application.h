#pragma once

#include <SDL.h>
#include <iostream>

class Application
{
public:
	Application(const int windowHeight , const int windowWidth)
		: m_pWindow {nullptr} , m_pRenderer {nullptr} ,
		  m_windowHeight {windowHeight} , m_windowWidth {windowWidth} { }

	bool initialize_window();

private:
	int m_windowHeight;
	int m_windowWidth;

	SDL_Window *m_pWindow;
	SDL_Renderer *m_pRenderer;
};