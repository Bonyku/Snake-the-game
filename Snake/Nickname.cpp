#include "GamePlay.hpp"
#include "GameOver.hpp"
#include "PauseGame.hpp"
#include "Nickname.hpp"

#include <SFML/Window/Event.hpp>

#include <stdlib.h>
#include <time.h>
#include <cstdio>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>



Nickname::Nickname(std::shared_ptr<Context>& context)
    : m_context(context)
{
    srand(time(nullptr));
}

Nickname::~Nickname()
{
}



void Nickname::Init()
{
    Question.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    Question.setString("Write your nickname");
    Question.setOrigin(Question.getLocalBounds().width / 2,
        Question.getLocalBounds().height / 2);
    Question.setPosition(m_context->m_window->getSize().x / 2,
        m_context->m_window->getSize().y / 2 - 150.f);
}

void Nickname::ProcessInput()
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
            if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode < 128)
                {
                    playerInput += static_cast<char>(event.text.unicode);
                    m_nickname.setFillColor(sf::Color::White);
                    m_nickname.setString(playerInput);
                }
            }
        } 
    }
}

void Nickname::Update(sf::Time deltaTime)
{
}

void Nickname::Draw()
{
    m_context->m_window->clear();

    m_context->m_window->draw(Question);
    m_context->m_window->draw(m_nickname);
    m_context->m_window->display();
}







