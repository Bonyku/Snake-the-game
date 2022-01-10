#include "Difficult.hpp"
#include "GamePlay.hpp"
#include "GamePlayFHD.hpp"
#include "Resolution.hpp"
#include "MainMenu.hpp"

#include <iostream>
#include <SFML/Window/Event.hpp>

Difficult::Difficult(std::shared_ptr<Context>& context)
    : m_context(context), m_isLargeButtonSelected(true),
    m_isLargeButtonPressed(false), m_isSmallButtonSelected(false), m_isSmallButtonPressed(false),
    m_isExitButtonSelected(false), m_isExitButtonPressed(false)
{
}
Difficult::~Difficult()
{
}

void Difficult::Init()
{
    m_context->m_assets->AddFont(MAIN_FONT, "Pacifico-Regular.ttf");

    // Title
    m_gameTitle.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_gameTitle.setString("Choose size of your map");
    m_gameTitle.setOrigin(m_gameTitle.getLocalBounds().width / 2,
        m_gameTitle.getLocalBounds().height / 2);
    m_gameTitle.setPosition(m_context->m_window->getSize().x / 2,
        m_context->m_window->getSize().y / 2 - 150.f);

    // Play Button
    m_playButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_playButton.setString("Small");
    m_playButton.setOrigin(m_playButton.getLocalBounds().width / 2,
        m_playButton.getLocalBounds().height / 2);
    m_playButton.setPosition(m_context->m_window->getSize().x / 2,
        m_context->m_window->getSize().y / 2 - 25.f);
    m_playButton.setCharacterSize(20);

    // Resolution Button
    m_resolutionButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_resolutionButton.setString("Large");
    m_resolutionButton.setOrigin(m_resolutionButton.getLocalBounds().width / 2,
        m_resolutionButton.getLocalBounds().height / 2);
    m_resolutionButton.setPosition(m_context->m_window->getSize().x / 2 ,
        m_context->m_window->getSize().y / 2 + 25.f);
    m_resolutionButton.setCharacterSize(20);

    // Exit Button
    m_exitButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_exitButton.setString("Go back");
    m_exitButton.setOrigin(m_exitButton.getLocalBounds().width / 2,
        m_exitButton.getLocalBounds().height / 2);
    m_exitButton.setPosition(m_context->m_window->getSize().x / 2,
        m_context->m_window->getSize().y / 2 + 75.f);
    m_exitButton.setCharacterSize(20);
}

void Difficult::ProcessInput()
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
            switch (event.key.code)
            {
            case sf::Keyboard::Up:
            {

                key_counter++;
                if (key_counter == 3) {
                    key_counter = 0;
                }
                if (key_counter == 2)
                {
                    m_isLargeButtonSelected = true;
                    m_isSmallButtonSelected = false;
                    m_isExitButtonSelected = false;
                }
                else
                    if (key_counter == 1)
                    {
                        m_isLargeButtonSelected = false;
                        m_isSmallButtonSelected = true;
                        m_isExitButtonSelected = false;
                    }
                    else
                            if (key_counter == 0)
                            {
                                m_isLargeButtonSelected = false;
                                m_isSmallButtonSelected = false;
                                m_isExitButtonSelected = true;
                            }


                break;
            }
            case sf::Keyboard::Down:
            {
                key_counter--;
                if (key_counter == -1) {
                    key_counter = 2;
                }
                if (key_counter == 2)
                {
                    m_isLargeButtonSelected = true;
                    m_isSmallButtonSelected = false;
                    m_isExitButtonSelected = false;
                }
                else
                    if (key_counter == 1)
                    {
                        m_isLargeButtonSelected = false;
                        m_isSmallButtonSelected = true;
                        m_isExitButtonSelected = false;
                    }
                    else

                            if (key_counter == 0)
                            {
                                m_isLargeButtonSelected = false;
                                m_isSmallButtonSelected = false;
                                m_isExitButtonSelected = true;

                            }
                break;
            }
            case sf::Keyboard::Escape:
            {
                m_context->m_window->close();
                break;
            }
            case sf::Keyboard::Return:
            {
                m_isLargeButtonPressed = false;
                m_isSmallButtonPressed = false;
                m_isExitButtonPressed = false;

                if (m_isLargeButtonSelected)
                {
                    m_isLargeButtonPressed = true;
                }
                else if (m_isSmallButtonSelected)
                {
                    m_isLargeButtonPressed = true;
                }
                else if (m_isExitButtonSelected)
                {
                    m_isExitButtonPressed = true;
                }

                break;
            }
            default:
            {
                break;
            }
            }
        }
    }
}

void Difficult::Update(sf::Time deltaTime)
{
    if (m_isLargeButtonSelected)
    {
        m_playButton.setFillColor(sf::Color::Red);
        m_resolutionButton.setFillColor(sf::Color::White);
        m_exitButton.setFillColor(sf::Color::White);
    }
    else if (m_isSmallButtonSelected)
    {
        m_playButton.setFillColor(sf::Color::White);
        m_resolutionButton.setFillColor(sf::Color::Red);
        m_exitButton.setFillColor(sf::Color::White);
    }
    else if (m_isExitButtonSelected)
    {
        m_playButton.setFillColor(sf::Color::White);
        m_resolutionButton.setFillColor(sf::Color::White);
        m_exitButton.setFillColor(sf::Color::Red);
    }
   

    if (m_isLargeButtonPressed)
    {
        m_context->m_states->Add(std::make_unique<GamePlayFHD>(m_context), true);
    }
    if (m_isSmallButtonPressed)
    {
        m_context->m_states->Add(std::make_unique<GamePlay>(m_context), true);
    }
    else if (m_isExitButtonPressed)
    {
        m_context->m_states->Add(std::make_unique<MainMenu>(m_context), true);
    }

}

void Difficult::Draw()
{
    m_context->m_window->clear(sf::Color::Black);
    m_context->m_window->draw(m_gameTitle);
    m_context->m_window->draw(m_playButton);
    m_context->m_window->draw(m_resolutionButton);
    m_context->m_window->draw(m_exitButton);
    m_context->m_window->display();
}