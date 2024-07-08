#pragma once
#include <SFML/Graphics.hpp>

#define RED 0
#define GREEN 1
#define PINK 2
#define YELLOW 3
#define BLUE 4
#define PURPLE 5
#define ORANGE 6
#define AQUA 7
#define LIGHTPINKI 8
#define LIGTHGREEN 9


namespace mt
{

	class Circle
	{
		float m_r;
		float m_x, m_y;
		sf::CircleShape m_shape;

	public:
		Circle() = default;

		Circle(float x, float y, float r)
		{
			Setup(x, y, r);
		}

		void Setup(float x, float y, float r)
		{
			m_x = x;
			m_y = y;
			m_r = r;
			m_shape.setOrigin(m_r, m_r);
			m_shape.setRadius(m_r);
			m_shape.setPosition(m_x, m_y);
			m_shape.setFillColor(getRandomColor());
		}

		void setColor(int color)
		{
			m_shape.setFillColor(getColor(color));
		}


		sf::CircleShape Get()
		{
			return m_shape;

		}
		
		static sf::Color getRandomColor()

		//sf::Color getRandomColor()
		{
			int d = rand() % 10;

			switch (d)
			{
			case RED: return sf::Color::Color(255, 0, 0);        //Задание цветов шариков

			case GREEN: return sf::Color::Color(0, 255, 0);

			case PINK: return sf::Color::Color(255, 20, 147);

			case YELLOW: return sf::Color::Color(255, 255, 0);

			case BLUE: return sf::Color::Color(0, 0, 255);

			case PURPLE: return sf::Color::Color(75, 0, 130);

			case ORANGE: return sf::Color::Color(255, 140, 0);

			case AQUA: return sf::Color::Color(0, 255, 255);

			case LIGHTPINKI: return sf::Color::Color(255, 182, 193);

			case LIGTHGREEN: return sf::Color::Color(144, 238, 144);
			}
		}

		static sf::Color getColor(int d)

			//sf::Color getRandomColor()
		{

			switch (d)
			{
			case RED: return sf::Color::Color(255, 0, 0);        //Задание цветов шариков

			case GREEN: return sf::Color::Color(0, 255, 0);

			case PINK: return sf::Color::Color(255, 20, 147);

			case YELLOW: return sf::Color::Color(255, 255, 0);

			case BLUE: return sf::Color::Color(0, 0, 255);

			case PURPLE: return sf::Color::Color(75, 0, 130);

			case ORANGE: return sf::Color::Color(255, 140, 0);

			case AQUA: return sf::Color::Color(0, 255, 255);

			case LIGHTPINKI: return sf::Color::Color(255, 182, 193);

			case LIGTHGREEN: return sf::Color::Color(144, 238, 144);
			}
		}
		sf::Color gColor() const
		{
			return m_shape.getFillColor();
		}

	};

}