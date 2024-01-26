#include "ball.h"

Ball::Ball(float startX, float startY)
{
	m_Position.x = startX;
	m_Position.y = startY;
	m_Shape.setSize(sf::Vector2f(15, 15));
	m_Shape.setPosition(m_Position);
}
FloatRect Ball::getPosition()
{
	return m_Shape.getGlobalBounds();
}
RectangleShape Ball::getShape()
{
	return m_Shape;
}
float Ball::getXVelocity()
{
	return m_DirectionX;
}

void Ball::reboundSides()
{
	m_DirectionX = -m_DirectionX;
}

void Ball::reboundBatOrTop()
{
	m_DirectionY = -m_DirectionY;
	if (m_Speed < 2000)
	{
		m_Speed = m_Speed + 100.0f;
	}
	else if (m_Speed < 2500)
	{
		m_Speed = m_Speed + 50.0f;
	}
	else
	{
		m_Speed = m_Speed;
	}
	
}
void Ball::reboundBottom()
{
	m_Position.y = 0;
	m_Position.x = 500;
	m_DirectionY = -m_DirectionY;
}
void Ball::update(Time dt)
{
	m_Position.y += m_DirectionY * m_Speed * dt.asSeconds();
	m_Position.x += m_DirectionX * m_Speed * dt.asSeconds();

	m_Shape.setPosition(m_Position);
}
void Ball::resetSpeed()
{
	m_Speed = 1000.0f;

}