#pragma once

class Entity
{
public:
	Entity()
		: m_x {} , m_y {} ,
		  m_velX {} , m_velY {} ,
		  m_width {} , m_height {} { }
	
	inline void set_entity(float x , float y , float velX , float velY , float width , float height)
	{
		m_x = x;
		m_y = y;
		m_velX = velX;
		m_velY = velY;
		m_width = width;
		m_height = height;
	}

	// Member variables
	float m_x;
	float m_y;
	float m_velX;
	float m_velY;
	float m_width;
	float m_height;
};