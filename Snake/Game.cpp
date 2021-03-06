#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Window.hpp>

#include "Game.hpp"
#include "MainMenu.hpp"
#include "Resolution.hpp"

/*Game::Game() : m_context(std::make_shared<Context>())
{

    m_context->m_window->create(sf::VideoMode(first_res, second_res), "Snake The Game", sf::Style::Fullscreen);
    m_context->m_states->Add(std::make_unique<MainMenu>(m_context));
}*/

Game::Game(int first, int second) : m_context(std::make_shared<Context>()) {
    this->first_res = first;
    this->second_res = second;

    m_context->m_window->create(sf::VideoMode(first_res, second_res), "Snake The Game");
    m_context->m_states->Add(std::make_unique<MainMenu>(m_context));
}

Game::~Game()
{
}

void Game::Run()
{
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Red);

    sf::Clock clock;
    sf::Time timeSinceLastFrame = sf::Time::Zero;

    while (m_context->m_window->isOpen())
    {
        timeSinceLastFrame += clock.restart();

        while (timeSinceLastFrame > TIME_PER_FRAME)
        {
            timeSinceLastFrame -= TIME_PER_FRAME;

            m_context->m_states->ProcessStateChange();
            m_context->m_states->GetCurrent()->ProcessInput();
            m_context->m_states->GetCurrent()->Update(TIME_PER_FRAME);
            m_context->m_states->GetCurrent()->Draw();
        }
    }
}