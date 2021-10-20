#pragma once

class Entity
{
public:
	Entity()
		: x {} , y {} , velX {} , velY {} , width {} , height {} , lastX {0} , lastY {0} { }
	
	inline void set_entity(float xVal , float yVal , float velXVal , float velYVal , float widthVal , float heightVal)
	{
		x = xVal;
		y = yVal;
		velX = velXVal;
		velY = velYVal;
		width = widthVal;
		height = heightVal;
	}

	// Member variables
	float x;
	float y;
	float velX;
	float velY;
	float width;
	float height;
	float lastX;
	float lastY;
};