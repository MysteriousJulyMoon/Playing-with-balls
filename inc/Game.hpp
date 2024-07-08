#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <thread>
#include <Circle.hpp>
#include <Cannon.hpp>
#include <Bullet.hpp>

namespace mt
{
	class Game
	{
		struct Place
		{
			bool isEmpty = true;        //ячейка для шарика свободно или занято
			bool isAttachable = false;		//можно стрельнуть или нет
			int m_x, m_y;
			sf::CircleShape m_circle;
			mt::Circle m_c;
		};

		int m_width;
		int m_height;
		int m_n;
		std::string m_capture;
		mt::Circle* m_c;
		mt::Bullet m_b;
        sf::RenderWindow m_window;
		sf::Texture m_textureBackground;
		sf::Sprite m_spriteBackground;
		sf::Font m_font;
		sf::Text m_fpsText;
		Cannon m_cannon;
		//Bullet m_bullet;
		bool isVisible = true;
		bool isTouchBorder = true;

		int m_placeR = 60;
		int m_placeX = 16;
		int m_placeY = 10;

		Place m_table[16][10];

	public:
		Game(int width, int height, const std::string& capture)
		{
			m_width = width;
			m_height = height;
			m_capture = capture;
		}

		bool Setup(int n)
		{
			m_n = n;
			// Создание окна
			m_window.create(sf::VideoMode(m_width, m_height), m_capture);
			// Создание текстуры фона
			if (!m_textureBackground.loadFromFile("assets\\sky.jpg"))
			{
				std::cout << "Error while loading sky.jpg" << std::endl;
				return false;
			}
			m_spriteBackground.setTexture(m_textureBackground);

			if (!m_cannon.Setup(500, 850))  //Расположение пушки
				return false;

			
			srand(time(0));

			m_c = new mt::Circle[m_n];

			float circleRadius = 30.0f; // Фиксированный радиус для всех шариков
			int circlesPerRow = 16; // Количество шариков в одной строке
			float distanceBetweenCircles = 2.0f; // Расстояние между шариками
			float startX = circleRadius + distanceBetweenCircles; // Начальная позиция X для первого шарика
			float startY = circleRadius + distanceBetweenCircles; // Начальная позиция Y для первой строки

			// Создание шариков в нескольких строках
			for (int i = 0; i < m_n; i++)
			{
				int row = i / circlesPerRow; // Текущая строка
				int col = i % circlesPerRow; // Текущий столбец в строке

				

				float x = startX + col * (2 * circleRadius + distanceBetweenCircles); // Позиция X для шарика
				float y = startY + row * (2 * circleRadius + distanceBetweenCircles); // Позиция Y для шарика
				m_c[i].Setup(x, y, circleRadius);

				m_table[col][row].isEmpty = false;
				m_table[col][row].isAttachable = false;
				m_table[col][row].m_c.Setup(x,y,circleRadius);
			}

			for(int i=0;i<10;i++)
				for (int j = 0; j < 16; j++)
				{
					m_table[j][i].m_x = startX + j * (2 * circleRadius + distanceBetweenCircles);
					m_table[j][i].m_y = startY + i * (2 * circleRadius + distanceBetweenCircles);
					//std::cout << m_table[j][i].m_x << " " << m_table[j][i].m_y << " " << m_table[j][i].isEmpty << std::endl;
				}

			
			for (int i = 0; i < 16; i++)
			{
				for (int j = 0; j < 10; j++)
					if (m_table[i][j].isEmpty == true)
					{
						m_table[i][j].isAttachable = true;

						break;
					}
			}
		}
		/*
		void CheckBalls()
		{
			// Проверка наличия трех одинаковых шариков по горизонтали
			for (int i = 0; i < m_placeX; ++i)
			{
				for (int j = 0; j < m_placeY - 2; ++j)
				{
					if (!m_table[i][j].isEmpty &&
						m_table[i][j].m_c.getColor == m_table[i][j + 1].m_c.getColor &&
						m_table[i][j].m_c.getColor == m_table[i][j + 2].m_c.getColor)
					{
						m_table[i][j].isEmpty = true;
						m_table[i][j + 1].isEmpty = true;
						m_table[i][j + 2].isEmpty = true;
					}
				}
			}

			// Проверка наличия трех одинаковых шариков по вертикали
			for (int j = 0; j < m_placeY; ++j)
			{
				for (int i = 0; i < m_placeX - 2; ++i)
				{
					if (!m_table[i][j].isEmpty &&
						m_table[i][j].m_c.getColor == m_table[i + 1][j].m_c.getColor &&
						m_table[i][j].m_c.getColor == m_table[i + 2][j].m_c.getColor)
					{
						m_table[i][j].isEmpty = true;
						m_table[i + 1][j].isEmpty = true;
						m_table[i + 2][j].isEmpty = true;
					}
				}
			}
		}*/

		// удаление шариков
		void CheckAndRemoveBalls()
		{
			for (int i = 0; i < 16; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					if (!m_table[i][j].isEmpty)
					{
						// Проверяем по горизонтали
						if (i > 1 && m_table[i][j].m_c.gColor() == m_table[i - 1][j].m_c.gColor() &&
							m_table[i][j].m_c.gColor() == m_table[i - 2][j].m_c.gColor())
						{
							m_table[i][j].isEmpty = true;
							m_table[i - 1][j].isEmpty = true;
							m_table[i - 2][j].isEmpty = true;
							m_table[i][j].isAttachable = true;
							m_table[i - 1][j].isAttachable = true;
							m_table[i - 2][j].isAttachable = true;
							m_table[i][j].isAttachable = false;
							m_table[i - 1][j + 1].isAttachable = false;
							m_table[i - 2][j + 2].isAttachable = false;

						}
						// Проверяем по вертикали
						if (j > 1 && m_table[i][j].m_c.gColor() == m_table[i][j - 1].m_c.gColor() &&
							m_table[i][j].m_c.gColor() == m_table[i][j - 2].m_c.gColor())
						{
							m_table[i][j].isEmpty = true;
							m_table[i][j - 1].isEmpty = true;
							m_table[i][j - 2].isEmpty = true;
							m_table[i][j].isAttachable = false;
							m_table[i][j - 1].isAttachable = false;
							m_table[i][j - 2].isAttachable = true;
							m_table[i][j + 1].isAttachable = false;
						}
					}
				}
			}
		}
		
		void LifeCycle()
		{
			sf::Clock clock;

			while (m_window.isOpen())
			{
				// Обработка событий
				sf::Event event;
				while (m_window.pollEvent(event))
				{
					if (event.type == sf::Event::Closed)
						m_window.close();

					//Управление пушкой с клавиатуры, поворот в стороны, для выбора траектории

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
					{
						m_cannon.Rotate(-1);
					}

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
					{
						m_cannon.Rotate(1);
					}


					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
					{

						m_cannon.Attack();

						/*m_cannon.Attack();
						float m_v = m_cannon.V();
						float m_x = m_cannon.X();
						float m_y = m_cannon.Y();
						float m_alpha = m_cannon.Alpha();
						float m_v_bullet = 200;
						float alphaRad = acos(-1) * m_alpha / 180;
						m_b.Setup(m_x, m_y, m_bulletR, (m_v + m_v_bullet) * cos(alphaRad), (m_v + m_v_bullet) * sin(alphaRad));
						bullet.push_back(m_b);*/
					}

				}

				// Логика
				float dt = clock.getElapsedTime().asSeconds();
				clock.restart();

				m_cannon.Move();

				for (int i = 0; i < 16; i++)
				{
					for (int j = 0; j < 10; j++)
						if (m_table[i][j].isAttachable == true)
						{
							int bx = m_cannon.BulletX();
							int by = m_cannon.BulletY();
							int px = m_table[i][j].m_x;
							int py = m_table[i][j].m_y;

							//std::cout << (bx - px) * (bx - px) + (by - py) * (by - py) << std::endl;

							if ((bx - px) * (bx - px) + (by - py) * (by - py) <= 30 * 30)
							{
								m_table[i][j].isAttachable = false;
								m_table[i][j].isEmpty = false;
								m_table[i][j].m_c.Setup(m_table[i][j].m_x, m_table[i][j].m_y, 30);
								m_table[i][j].m_c.setColor(m_cannon.getBulletColor());
								m_cannon.BulletReset();
								std::cout << "reset" << std::endl;


								m_table[i][j + 1].isAttachable = true;

							}
						}
				}



				CheckAndRemoveBalls(); // Вызов функции для проверки и удаления шариков



				// Отображение
				m_window.clear();
				m_window.draw(m_spriteBackground);
				m_window.draw(m_cannon.Get());       //Отрисовка пушки
				m_window.draw(m_fpsText);

				for (int i = 0; i < 10; i++)
					for (int j = 0; j < 16; j++)
					{
						if (m_table[j][i].isEmpty)
						{
							m_table[j][i].m_circle = sf::CircleShape(10);
							m_table[j][i].m_circle.setOrigin(10,10);     
							/*if (m_table[j][i].isAttachable)
							{
								m_table[j][i].m_circle.setFillColor(sf::Color::Red);
							}
							m_table[j][i].m_circle.setPosition(m_table[j][i].m_x, m_table[j][i].m_y);
							m_window.draw(m_table[j][i].m_circle);*/
						}
						else
						{
							/*m_table[j][i].m_circle = sf::CircleShape(10);
							m_table[j][i].m_circle.setOrigin(5, 5);
							m_table[j][i].m_circle.setFillColor(sf::Color::Green);
							m_table[j][i].m_circle.setPosition(m_table[j][i].m_x, m_table[j][i].m_y);*/
							m_window.draw(m_table[j][i].m_c.Get());
						}
					}

				//for (int i = 0; i < m_n; i++)
				//	m_window.draw(m_c[i].Get());
				//
				/*if (m_cannon.BulletAvailable())
					for (int i = 0; i < bullet.size(); i++)
						m_window.draw(bullet[i].Get());
				if (isVisible)
					m_window.draw(m_cannon.Get());*/

					//std::cout << m_cannon.BulletAvailable() << std::endl;
				if (m_cannon.BulletAvailable())
					m_window.draw(m_cannon.GetBullet());


				if (isVisible)
					m_window.draw(m_cannon.Get());

				m_window.display();
			}

		}
	};
}

 
