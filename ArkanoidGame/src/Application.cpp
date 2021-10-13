#include "Application.h"

void Application::initialize_window()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		m_isGameRunning = false;
	}
	
	m_pWindow = SDL_CreateWindow("Arkanoid Game - Paul Llamoja S." ,
								 SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED,
								 m_windowWidth , m_windowHeight ,
								 SDL_WINDOW_SHOWN);
	if (m_pWindow == nullptr)
	{
		std::cerr << "Window could not be created! SDL_Error " << SDL_GetError() << std::endl;
		m_isGameRunning = false;
	}

	m_pRenderer = SDL_CreateRenderer(m_pWindow , -1 , 0);
	if (m_pRenderer == nullptr)
	{
		std::cerr << "Renderer could not be created! SDL_Error " << SDL_GetError() << std::endl;
		m_isGameRunning = false;
	}

	m_isGameRunning = true;	
}


void Application::set_up()
{
	initialize_window();
	m_ball.set_entity(20 , 20 ,
					  70 , 50 ,
					  15 , 15);
}


void Application::process_input()
{
	SDL_Event event;
	SDL_PollEvent(&event);	

	switch (event.type)
	{
		case SDL_QUIT:
			m_isGameRunning = false;
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE)
				m_isGameRunning = false;
			break;
	}
}


void Application::update_data()
{
	// Delay the update function to match with the Frame Target Time
	int timeToWait = m_frameTargetTime - (SDL_GetTicks() - m_lastFrameTime);
	if (timeToWait > 0 && timeToWait <= m_frameTargetTime)
		SDL_Delay(timeToWait);

	// Get a delta time factor converted to seconds to be used to update my objects
	float deltaTime = (SDL_GetTicks() - m_lastFrameTime) / 1000.0f;

	m_lastFrameTime = SDL_GetTicks();

	m_ball.m_x += m_ball.m_velX * deltaTime;
	m_ball.m_y += m_ball.m_velY * deltaTime;
}

void Application::render()
{
	// Set the background
	SDL_SetRenderDrawColor(m_pRenderer , 0 , 0 , 0 , 255);
	SDL_RenderClear(m_pRenderer);

	// Draw a "ball"
	SDL_Rect ballRectangle = {static_cast<int>(m_ball.m_x) ,
							  static_cast<int>(m_ball.m_y) ,
							  static_cast<int>(m_ball.m_width) ,
							  static_cast<int>(m_ball.m_height)};
	SDL_SetRenderDrawColor(m_pRenderer , 255 , 255 , 255 , 255);
	SDL_RenderFillRect(m_pRenderer , &ballRectangle);

	// Buffer swap
	SDL_RenderPresent(m_pRenderer);	
}