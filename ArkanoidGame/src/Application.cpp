#include "Application.h"

bool Application::initialize_window()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}
	
	m_pWindow = SDL_CreateWindow("Arkanoid Game - Paul Llamoja S." ,
								 SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED,
								 m_windowWidth , m_windowHeight ,
								 SDL_WINDOW_SHOWN);
	if (m_pWindow == nullptr)
	{
		std::cerr << "Window could not be created! SDL_Error " << SDL_GetError() << std::endl;
		return false;
	}

	m_pRenderer = SDL_CreateRenderer(m_pWindow , -1 , 0);
	if (m_pRenderer == nullptr)
	{
		std::cerr << "Renderer could not be created! SDL_Error " << SDL_GetError() << std::endl;
		return false;
	}

	return true;	
}


void Application::initialize_bricks()
{
	float x{38} , y{20} , width{100} , height{20};
	float xDistance{38};
	int numberColumns {9};
	float topX = x + (numberColumns - 1) * (width + xDistance);

	for (auto &brick : m_bricks)
	{
		brick.set_entity(x , y , 0 , 0 , width , height);
		x += width + xDistance;
		if (x > topX)
		{
			x = 38;
			y += 40;
		}
	}
}


bool Application::collision(Entity &paddle , Entity &ball)
{
	if ((ball.x < paddle.x + paddle.width) && (ball.x + ball.width > paddle.x) &&
		(ball.y < paddle.y + paddle.height) && (ball.y + ball.height > paddle.y))
	{
		if (ball.y <= paddle.y)
		{
			// Top edges collision
			if (ball.x < paddle.x)
			{
				ball.velX = -1 * std::fabs(ball.velX);
				ball.velY = -1 * std::fabs(ball.velY);
			}
			else if (ball.x + ball.width > paddle.x + paddle.width)
			{
				ball.velX = std::fabs(ball.velX);
				ball.velY = -1 * std::fabs(ball.velY);
			}
			// Top surface collision
			else
				ball.velY *= -1;
		}
		else if (ball.y + ball.height > paddle.y + paddle.height)
		{
			// Bottom edges collision
			if (ball.x < paddle.x)
			{
				ball.velX = -1 * std::fabs(ball.velX);
				ball.velY = std::fabs(ball.velY);
			}
			else if (ball.x + ball.width > paddle.x + paddle.width)
			{
				ball.velX = std::fabs(ball.velX);
				ball.velY = std::fabs(ball.velY);
			}
			// Bottom surface collision
			else
				ball.velY *= -1;
		}
		else
		{
			// Side collision
			ball.velX *= -1;
		}

		return true;
	}
	else
		return false;
}


bool Application::collision(std::vector<Entity> &bricks , Entity &ball)
{
	for (auto &brick : bricks)
	{
		if (collision(brick , ball))
		{
			brick.set_entity(-100 , 0 , 0 , 0 , 0 , 0);
			if (++m_bricks_taken == bricks.size())
				m_isGameRunning = false;		// Win condition
			return true;
		}
	}

	return false;
}


void Application::render_bricks()
{
	for (auto &brick : m_bricks)
	{
		SDL_Rect brickRectangle = {static_cast<int>(brick.x) ,
								   static_cast<int>(brick.y) ,
								   static_cast<int>(brick.width) ,
								   static_cast<int>(brick.height)};
		SDL_RenderFillRect(m_pRenderer , &brickRectangle);
	}
	
}


void Application::set_up()
{
	initialize_bricks();
	m_isGameRunning = initialize_window();
	m_paddle.set_entity(0 , (m_windowHeight - 40.0f) , 0 , 0 , 150 , 20);
	m_paddle.x = (m_windowWidth / 2.0f) - (m_paddle.width / 2.0f);
	m_ball.set_entity(m_paddle.x , m_paddle.y - 20 , -125 , -130 , 20 , 20);
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
			if (event.key.keysym.sym == SDLK_SPACE)
			{
				if (m_isGamePaused)
					m_isGamePaused = false;
				else
					m_isGamePaused = true;
			}
			if (event.key.keysym.sym == SDLK_LEFT)
				m_paddle.velX = -350;
			if (event.key.keysym.sym == SDLK_RIGHT)
				m_paddle.velX = 350;
			break;
		case SDL_KEYUP:
			if ((event.key.keysym.sym == SDLK_LEFT) || (event.key.keysym.sym == SDLK_RIGHT))
				m_paddle.velX = 0;
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

	if (m_isGamePaused == false)
	{
		// Move the paddle
		m_paddle.lastX = m_paddle.x;
		m_paddle.x += m_paddle.velX * deltaTime;
		if (m_paddle.x < 0 || (m_paddle.x + m_paddle.width > m_windowWidth))
			m_paddle.x = m_paddle.lastX;
		
		// Move the ball
		m_ball.lastX = m_ball.x;
		m_ball.lastY = m_ball.y;

		m_ball.x += m_ball.velX * deltaTime;
		m_ball.y += m_ball.velY * deltaTime;

		// Ball collision with the walls
		if (m_ball.x < 0 || (m_ball.x + m_ball.width > m_windowWidth))
		{
			m_ball.x = m_ball.lastX;
			m_ball.velX *= -1;
		}
		if (m_ball.y < 0)
		{
			m_ball.y = m_ball.lastY;
			m_ball.velY *= -1;
		}

		// Ball collision with the paddle
		if (collision(m_paddle , m_ball))
		{
			m_ball.x = m_ball.lastX + m_paddle.velX * deltaTime;
			m_ball.y = m_ball.lastY + m_paddle.velY * deltaTime;
			// It is needed to test another collision if there are bodies that are very close
		}

		if (collision(m_bricks , m_ball))
		{
			m_ball.x = m_ball.lastX + m_paddle.velX * deltaTime;
			m_ball.y = m_ball.lastY + m_paddle.velY * deltaTime;
			// It is needed to test another collision if there are bodies that are very close
		}

		// Check for game over if the ball hits the bottom part of the screen
		if (m_ball.y + m_ball.height > m_windowHeight)
			m_isGameRunning = false;
	}
}

void Application::render()
{
	// Set the background
	SDL_SetRenderDrawColor(m_pRenderer , 0 , 0 , 0 , 255);
	SDL_RenderClear(m_pRenderer);

	SDL_SetRenderDrawColor(m_pRenderer , 255 , 255 , 255 , 255);

	// Draw the bricks
	// TODO: Draw the bricks using m_bricks and a for loop

	// Draw a "ball"
	SDL_Rect ballRectangle = {static_cast<int>(m_ball.x) ,
							  static_cast<int>(m_ball.y) ,
							  static_cast<int>(m_ball.width) ,
							  static_cast<int>(m_ball.height)};
	SDL_RenderFillRect(m_pRenderer , &ballRectangle);

	// Draw the paddle
	SDL_Rect paddleRectangle = {static_cast<int>(m_paddle.x) ,
								static_cast<int>(m_paddle.y) ,
								static_cast<int>(m_paddle.width) ,
								static_cast<int>(m_paddle.height)};
	SDL_RenderFillRect(m_pRenderer , &paddleRectangle);

	// Draw the bricks

	render_bricks();

	// Buffer swap
	SDL_RenderPresent(m_pRenderer);	
}