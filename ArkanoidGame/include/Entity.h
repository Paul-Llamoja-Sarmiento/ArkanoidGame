#pragma once

class Ball
{
public:
	Ball()
		: m_x {} , m_y {} , m_width {} , m_height {} { }
	
	inline void set_ball(int x , int y , int width , int height)
	{
		m_x = x;
		m_y = y;
		m_width = width;
		m_height = height;
	}

	// Member variables
	int m_x;
	int m_y;
	int m_width;
	int m_height;
};