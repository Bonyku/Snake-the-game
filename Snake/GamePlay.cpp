#include "GamePlay.hpp"
#include "GameOver.hpp"
#include "PauseGame.hpp"

#include <SFML/Window/Event.hpp>

#include <stdlib.h>
#include <time.h>
#include <cstdio>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "Client.h"



GamePlay::GamePlay(std::shared_ptr<Context>& context)
    : m_context(context),
    m_score(0),
    m_snakeDirection({ 16.f, 0.f }),
    m_elapsedTime(sf::Time::Zero),
    m_isPaused(false)
{
    srand(time(nullptr));
}

GamePlay::~GamePlay()
{
}

std::string RandomFood()
{
    srand(time(NULL));
    std::vector<std::string> Vector_food = { "", "food1.png", "food2.png", "food3.png", "food4.png", "food5.png", "food6.png", "food7.png", "food8.png" };

    int randomInt = rand() % 8 + 1;
    return Vector_food[randomInt];
}

void GamePlay::Init()
{
    std::string food = RandomFood();

    m_context->m_assets->AddTexture(GRASS, "grass.png", true);
    m_context->m_assets->AddTexture(FOOD, food);
    m_context->m_assets->AddTexture(WALL, "wall.png", true);
    m_context->m_assets->AddTexture(SNAKE, "body.png");

    m_grass.setTexture(m_context->m_assets->GetTexture(GRASS));
    m_grass.setTextureRect(m_context->m_window->getViewport(m_context->m_window->getDefaultView()));


    for (auto& wall : m_walls)
    {
        wall.setTexture(m_context->m_assets->GetTexture(WALL));
    }

    m_walls[0].setTextureRect({ 0, 0, (int)m_context->m_window->getSize().x, 16 });
    m_walls[1].setTextureRect({ 0, 0, (int)m_context->m_window->getSize().x, 16 });
    m_walls[1].setPosition(0, m_context->m_window->getSize().y - 16);

    m_walls[2].setTextureRect({ 0, 0, 16, (int)m_context->m_window->getSize().y });
    m_walls[3].setTextureRect({ 0, 0, 16, (int)m_context->m_window->getSize().y });
    m_walls[3].setPosition(m_context->m_window->getSize().x - 16, 0);

    m_food.setTexture(m_context->m_assets->GetTexture(FOOD));
    m_food.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2);

    m_snake.Init(m_context->m_assets->GetTexture(SNAKE));

    m_scoreText.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_scoreText.setString("Score : " + std::to_string(m_score));
    m_scoreText.setCharacterSize(15);
}

void GamePlay::ProcessInput()
{
    sf::Event event;
    while (m_context->m_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            m_context->m_window->close();
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            sf::Vector2f newDirection = m_snakeDirection;
            switch (event.key.code)
            {
            case sf::Keyboard::Up:
                newDirection = { 0.f, -16.f };
                break;
            case sf::Keyboard::Down:
                newDirection = { 0.f, 16.f };
                break;
            case sf::Keyboard::Left:
                newDirection = { -16.f, 0.f };
                break;
            case sf::Keyboard::Right:
                newDirection = { 16.f, 0.f };
                break;
            case sf::Keyboard::Escape:
                m_context->m_states->Add(std::make_unique<PauseGame>(m_context));
                break;

            default:
                break;
            }

            if (std::abs(m_snakeDirection.x) != std::abs(newDirection.x) ||
                std::abs(m_snakeDirection.y) != std::abs(newDirection.y))
            {
                m_snakeDirection = newDirection;
            }
        }

    }
}

void GamePlay::Update(sf::Time deltaTime)
{
    if (!m_isPaused)
    {
        m_elapsedTime += deltaTime;

        if (m_elapsedTime.asSeconds() > 0.1)
        {
            for (auto& wall : m_walls)
            {
                if (m_snake.IsOn(wall))
                {
                    m_score;

                    std::ofstream myfile;         
                    myfile.open("Score.txt", std::ios_base::app);

                    myfile << "This is a score: ";
                    myfile << m_score;
                    myfile << "\n";
                    myfile.close();

                    std::ifstream myfile2("Score.txt");
                    std::string wynik;
                    char tablica[512];
                    while (std::getline(myfile2, wynik)) {
                        strcat_s(tablica, wynik.c_str());
                        strcat_s(tablica, "\n");
                    };
                    std::cout << tablica;
                    Klient(tablica);
                    myfile2.close();

                    m_context->m_states->Add(std::make_unique<GameOver>(m_context), true);
                    break;
                }
            }

            if (m_snake.IsOn(m_food))
            {
                m_snake.Grow(m_snakeDirection);

                int x = 0, y = 0;
                x = std::clamp<int>(rand() % m_context->m_window->getSize().x, 16, m_context->m_window->getSize().x - 2 * 16);
                y = std::clamp<int>(rand() % m_context->m_window->getSize().y, 16, m_context->m_window->getSize().y - 2 * 16);

                std::string food = RandomFood();
                m_context->m_assets->AddTexture(FOOD, food);
                m_food.setTexture(m_context->m_assets->GetTexture(FOOD));
                m_food.setPosition(x, y);
                
                m_score += 1;
                m_scoreText.setString("Score : " + std::to_string(m_score));
            }
            else
            {
                m_snake.Move(m_snakeDirection);
            }

            if (m_snake.IsSelfIntersecting())
            {
                std::ofstream myfile;
                myfile.open("Score.txt", std::ios_base::app);

                myfile << "This is a score: ";
                myfile << m_score;
                myfile << "\n";
                myfile.close();

                std::ifstream myfile2("Score.txt");
                std::string wynik;
                char tablica[512];
                while (std::getline(myfile2, wynik)) {
                    strcat_s(tablica, wynik.c_str());
                    strcat_s(tablica, "\n");
                };
                    std::cout << tablica;
                Klient(tablica);
                myfile2.close();

                /*std::ifstream file;
                file.open("Score.txt");
                char tablica[512];
                file >> tablica;
                for (int i=0; i<512; i++)
                    std::cout << tablica[i];
                file.close();*/
                

                m_context->m_states->Add(std::make_unique<GameOver>(m_context), true);
            }

            m_elapsedTime = sf::Time::Zero;
        }
    }
}

void GamePlay::Draw()
{
    m_context->m_window->clear();
    m_context->m_window->draw(m_grass);

    for (auto& wall : m_walls)
    {
        m_context->m_window->draw(wall);
    }
    m_context->m_window->draw(m_food);
    m_context->m_window->draw(m_snake);
    m_context->m_window->draw(m_scoreText);

    m_context->m_window->display();
}

void GamePlay::Pause()
{
    m_isPaused = true;
}

void GamePlay::Start()
{
    m_isPaused = false;
}

