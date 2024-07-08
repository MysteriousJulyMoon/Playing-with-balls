#include <SFML/Graphics.hpp>
#include <Circle.hpp>
#include <Game.hpp>
#include <Cannon.hpp>
#include <Bullet.hpp>

int main()
{
    mt::Game game(1000, 900, "Game");  //Размер игрового поля

    if (!game.Setup(80))  //Количество шариков на поле
        return -1;

    game.LifeCycle();

    return 0;
    
}
