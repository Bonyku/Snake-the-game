#include "Resolution.hpp"
#include "MainMenu.hpp"
#include "Game.hpp"

#include <iostream>
#include <SFML/Window/Event.hpp>

Resolution::Resolution(std::shared_ptr<Context>& context)
    : m_context(context), m_isFirst_ResolutionButtonSelected(true),
    m_isFirst_ResolutionButtonPressed(false), m_isSecond_ResolutionSelected(false), m_isSecond_ResolutionPressed(false),
    m_isBackButtonSelected(false), m_isBackButtonPressed(false)

{
}

Resolution::~Resolution()
{
}

void Resolution::Init()
{
    m_context->m_assets->AddFont(MAIN_FONT, "Pacifico-Regular.ttf");

    // Title
    m_gameTitle.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_gameTitle.setString("Snake The Game");
    m_gameTitle.setOrigin(m_gameTitle.getLocalBounds().width / 2,
        m_gameTitle.getLocalBounds().height / 2);
    m_gameTitle.setPosition(m_context->m_window->getSize().x / 2,
        m_context->m_window->getSize().y / 2 - 150.f);

    // Play Button
    m_first_resolutionButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_first_resolutionButton.setString("1280px x 720px");
    m_first_resolutionButton.setOrigin(m_first_resolutionButton.getLocalBounds().width / 2,
        m_first_resolutionButton.getLocalBounds().height / 2);
    m_first_resolutionButton.setPosition(m_context->m_window->getSize().x / 2+25.f,
        m_context->m_window->getSize().y / 2 - 25.f);
    m_first_resolutionButton.setCharacterSize(20);

    // Resolution Button
    m_second_resolutionButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_second_resolutionButton.setString("1920px x 1080px");
    m_second_resolutionButton.setOrigin(m_second_resolutionButton.getLocalBounds().width / 2,
        m_second_resolutionButton.getLocalBounds().height / 2);
    m_second_resolutionButton.setPosition(m_context->m_window->getSize().x / 2 + +25.f,
        m_context->m_window->getSize().y / 2 + 25.f);
    m_second_resolutionButton.setCharacterSize(20);

    // Online Button
    m_backButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_backButton.setString("Back");
    m_backButton.setOrigin(m_backButton.getLocalBounds().width / 2,
        m_backButton.getLocalBounds().height / 2);
    m_backButton.setPosition(m_context->m_window->getSize().x / 2,
        m_context->m_window->getSize().y / 2 + 75.f);
    m_backButton.setCharacterSize(20);

}

void Resolution::ProcessInput()
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
                    m_isFirst_ResolutionButtonSelected = true;
                    m_isSecond_ResolutionSelected = false;
                    m_isBackButtonSelected = false;
                }
                else
                    if (key_counter == 1)
                    {
                        m_isFirst_ResolutionButtonSelected = false;
                        m_isSecond_ResolutionSelected = true;
                        m_isBackButtonSelected = false;
                    }
                    else
                        if (key_counter == 0)
                        {
                            m_isFirst_ResolutionButtonSelected = false;
                            m_isSecond_ResolutionSelected = false;
                            m_isBackButtonSelected = true;
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
                    m_isFirst_ResolutionButtonSelected = true;
                    m_isSecond_ResolutionSelected = false;
                    m_isBackButtonSelected = false;
                }
                else
                    if (key_counter == 1)
                    {
                        m_isFirst_ResolutionButtonSelected = false;
                        m_isSecond_ResolutionSelected = true;
                        m_isBackButtonSelected = false;
                    }
                    else
                        if (key_counter == 0)
                        {
                            m_isFirst_ResolutionButtonSelected = false;
                            m_isSecond_ResolutionSelected = false;
                            m_isBackButtonSelected = true;
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
                m_isFirst_ResolutionButtonPressed = false;
                m_isSecond_ResolutionPressed = false;
                m_isBackButtonPressed = false;

                if (m_isFirst_ResolutionButtonSelected)
                {
                    m_isFirst_ResolutionButtonPressed = true;
                }
                else if (m_isSecond_ResolutionSelected)
                {
                    m_isSecond_ResolutionPressed = true;
                }
                else if (m_isBackButtonSelected)
                {
                    m_isBackButtonPressed = true;
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

void Resolution::Update(sf::Time deltaTime)
{
    if (m_isFirst_ResolutionButtonSelected)
    {
        m_first_resolutionButton.setFillColor(sf::Color::Red);
        m_second_resolutionButton.setFillColor(sf::Color::White);
        m_backButton.setFillColor(sf::Color::White);
    }
    else if (m_isSecond_ResolutionSelected)
    {
        m_first_resolutionButton.setFillColor(sf::Color::White);
        m_second_resolutionButton.setFillColor(sf::Color::Red);
        m_backButton.setFillColor(sf::Color::White);
    }
    else if (m_isBackButtonSelected)
    {
        m_first_resolutionButton.setFillColor(sf::Color::White);
        m_second_resolutionButton.setFillColor(sf::Color::White);
        m_backButton.setFillColor(sf::Color::Red);
    }

    if (m_isFirst_ResolutionButtonPressed)
    {
        //first_res = 1280;
       // second_res = 720;
    }
    if (m_isSecond_ResolutionPressed)
    {
    }
    else if (m_isBackButtonPressed)
    {
        m_context->m_states->Add(std::make_unique<MainMenu>(m_context), true);
    }

}

void Resolution::Draw()
{
    m_context->m_window->clear(sf::Color::Black);
    m_context->m_window->draw(m_gameTitle);
    m_context->m_window->draw(m_first_resolutionButton);
    m_context->m_window->draw(m_second_resolutionButton);
    m_context->m_window->draw(m_backButton);
    m_context->m_window->display();
}