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
	m_ball.set_entity(20 , 20 , 150 , 200 , 15 , 15);
	m_paddle.set_entity(0 , (m_windowHeight - 40.0f) , 0 , 0 , 150 , 20);
	m_paddle.m_x = (m_windowWidth / 2.0f) - (m_paddle.m_width / 2.0f);
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
			if (event.key.keysym.sym == SDLK_LEFT)
				m_paddle.m_velX = -150;
			if (event.key.keysym.sym == SDLK_RIGHT)
				m_paddle.m_velX = 150;
			break;
		case SDL_KEYUP:
			if (event.key.keysym.sym == SDLK_LEFT)
				m_paddle.m_velX = 0;
			if (event.key.keysym.sym == SDLK_RIGHT)
				m_paddle.m_velX = 0;
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

	// Move the ball
	float ballLastX = m_ball.m_x;
	float ballLastY = m_ball.m_y;

	m_ball.m_x += m_ball.m_velX * deltaTime;
	if (m_ball.m_x < 0 || m_ball.m_x > (m_windowWidth - m_ball.m_width))
	{
		m_ball.m_x = ballLastX;
		m_ball.m_velX *= -1;
	}
		
	m_ball.m_y += m_ball.m_velY * deltaTime;
	if (m_ball.m_y < 0 || m_ball.m_y > (m_windowHeight - m_ball.m_height))
	{
		m_ball.m_y = ballLastY;
		m_ball.m_velY *= -1;
	}

	// Move the paddle
	float paddleLastX = m_paddle.m_x;
	m_paddle.m_x += m_paddle.m_velX * deltaTime;
	if (m_paddle.m_x < 0 || m_paddle.m_x > (m_windowWidth - m_paddle.m_width))
		m_paddle.m_x = paddleLastX;
}

void Application::render()
{
	// Set the background
	SDL_SetRenderDrawColor(m_pRenderer , 0 , 0 , 0 , 255);
	SDL_RenderClear(m_pRenderer);

	SDL_SetRenderDrawColor(m_pRenderer , 255 , 255 , 255 , 255);

	// Draw a "ball"
	SDL_Rect ballRectangle = {static_cast<int>(m_ball.m_x) ,
							  static_cast<int>(m_ball.m_y) ,
							  static_cast<int>(m_ball.m_width) ,
							  static_cast<int>(m_ball.m_height)};
	SDL_RenderFillRect(m_pRenderer , &ballRectangle);

	// Draw the paddle
	SDL_Rect paddleRectangle = {static_cast<int>(m_paddle.m_x) ,
								static_cast<int>(m_paddle.m_y) ,
								static_cast<int>(m_paddle.m_width) ,
								static_cast<int>(m_paddle.m_height)};
	SDL_RenderFillRect(m_pRenderer , &paddleRectangle);

	// Buffer swap
	SDL_RenderPresent(m_pRenderer);	
}