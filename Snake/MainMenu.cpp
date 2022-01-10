#include "MainMenu.hpp"
#include "GamePlay.hpp"
#include "GamePlayFHD.hpp"
#include "Resolution.hpp"
#include "Difficult.hpp"

#include <iostream>
#include <SFML/Window/Event.hpp>

MainMenu::MainMenu(std::shared_ptr<Context>& context)
    : m_context(context), m_isPlayButtonSelected(true),
    m_isPlayButtonPressed(false), m_isResolutionButtonSelected(false), m_isResolutionButtonPressed(false), 
    m_isOnlineButtonSelected(false), m_isOnlineButtonPressed(false), m_isExitButtonSelected(false), m_isExitButtonPressed(false)
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::Init()
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
    m_playButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_playButton.setString("Play");
    m_playButton.setOrigin(m_playButton.getLocalBounds().width / 2,
        m_playButton.getLocalBounds().height / 2);
    m_playButton.setPosition(m_context->m_window->getSize().x / 2,
        m_context->m_window->getSize().y / 2 - 25.f);
    m_playButton.setCharacterSize(20);

    // Resolution Button
    m_resolutionButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_resolutionButton.setString("Resolution");
    m_resolutionButton.setOrigin(m_resolutionButton.getLocalBounds().width / 2,
        m_resolutionButton.getLocalBounds().height / 2);
    m_resolutionButton.setPosition(m_context->m_window->getSize().x / 2 + 10.f,
        m_context->m_window->getSize().y / 2 + 25.f);
    m_resolutionButton.setCharacterSize(20);

    // Online Button
    m_onlineButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_onlineButton.setString("Online");
    m_onlineButton.setOrigin(m_onlineButton.getLocalBounds().width / 2,
        m_onlineButton.getLocalBounds().height / 2);
    m_onlineButton.setPosition(m_context->m_window->getSize().x / 2,
        m_context->m_window->getSize().y / 2 + 75.f);
    m_onlineButton.setCharacterSize(20);

    // Exit Button
    m_exitButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_exitButton.setString("Exit");
    m_exitButton.setOrigin(m_exitButton.getLocalBounds().width / 2,
        m_exitButton.getLocalBounds().height / 2);
    m_exitButton.setPosition(m_context->m_window->getSize().x / 2,
        m_context->m_window->getSize().y / 2 + 125.f);
    m_exitButton.setCharacterSize(20);
}

void MainMenu::ProcessInput()
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
                if (key_counter == 4) {
                    key_counter = 0;
                }
               if (key_counter == 3)
                {
                    m_isPlayButtonSelected = true;
                    m_isResolutionButtonSelected = false;
                    m_isOnlineButtonSelected = false;
                    m_isExitButtonSelected = false;   
                }
               else
                   if (key_counter == 1)
                   {
                       m_isPlayButtonSelected = false;
                       m_isResolutionButtonSelected = false;
                       m_isOnlineButtonSelected = true;
                       m_isExitButtonSelected = false;
                   }
                    else
                        if (key_counter == 2)
                        {
                            m_isPlayButtonSelected = false;
                            m_isResolutionButtonSelected = true;
                            m_isOnlineButtonSelected = false;
                            m_isExitButtonSelected = false;
                        }
                        else
                            if (key_counter == 0)
                            {
                                m_isPlayButtonSelected = false;
                                m_isResolutionButtonSelected = false;
                                m_isOnlineButtonSelected = false;
                                m_isExitButtonSelected = true;
                            }
                        
                        
                break;
            }
            case sf::Keyboard::Down:
            {
                key_counter--;
                if (key_counter == -1) {
                    key_counter = 3;
                }
                if (key_counter == 3)
                {
                    m_isPlayButtonSelected = true;
                    m_isResolutionButtonSelected = false;
                    m_isOnlineButtonSelected = false;
                    m_isExitButtonSelected = false;
                }
                else
                    if (key_counter == 2)
                    {
                        m_isPlayButtonSelected = false;
                        m_isResolutionButtonSelected = true;
                        m_isOnlineButtonSelected = false;
                        m_isExitButtonSelected = false;
                    }
                    else
                        if (key_counter == 1)
                        {
                            m_isPlayButtonSelected = false;
                            m_isResolutionButtonSelected = false;
                            m_isOnlineButtonSelected = true;
                            m_isExitButtonSelected = false; 
                        }
                        else
                            if (key_counter == 0)
                            {
                                m_isPlayButtonSelected = false;
                                m_isResolutionButtonSelected = false;
                                m_isOnlineButtonSelected = false;
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
                m_isPlayButtonPressed = false;
                m_isResolutionButtonPressed = false;
                m_isExitButtonPressed = false;
                m_isOnlineButtonSelected = false;

                if (m_isPlayButtonSelected)
                {
                    m_isPlayButtonPressed = true;
                }
                else if (m_isResolutionButtonSelected)
                {
                    m_isResolutionButtonPressed = true;
                }
                else if (m_isExitButtonSelected)
                {
                    m_isExitButtonPressed = true;
                }
                else if (m_isOnlineButtonSelected)
                {
                    m_isOnlineButtonSelected = true;
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

void MainMenu::Update(sf::Time deltaTime)
{
    if (m_isPlayButtonSelected)
    {
        m_playButton.setFillColor(sf::Color::Red);
        m_resolutionButton.setFillColor(sf::Color::White);
        m_onlineButton.setFillColor(sf::Color::White);
        m_exitButton.setFillColor(sf::Color::White);
    }
    else if (m_isResolutionButtonSelected)
    { 
        m_playButton.setFillColor(sf::Color::White);
        m_resolutionButton.setFillColor(sf::Color::Red);
        m_onlineButton.setFillColor(sf::Color::White);
        m_exitButton.setFillColor(sf::Color::White);
    }
    else if (m_isExitButtonSelected)
    {
        m_playButton.setFillColor(sf::Color::White);
        m_resolutionButton.setFillColor(sf::Color::White);
        m_onlineButton.setFillColor(sf::Color::White);
        m_exitButton.setFillColor(sf::Color::Red);
    }
    else if (m_isOnlineButtonSelected)
    {
        m_playButton.setFillColor(sf::Color::White);
        m_resolutionButton.setFillColor(sf::Color::White);
        m_onlineButton.setFillColor(sf::Color::Red);
        m_exitButton.setFillColor(sf::Color::White);

    }

    if (m_isPlayButtonPressed)
    {
        m_context->m_states->Add(std::make_unique<Difficult>(m_context), true);
    }
    if (m_isResolutionButtonPressed)
    {
        m_context->m_states->Add(std::make_unique<Resolution>(m_context), true);
    }
    else if (m_isExitButtonPressed)
    {
        m_context->m_window->close();
    }

}

void MainMenu::Draw()
{
    m_context->m_window->clear(sf::Color::Black);
    m_context->m_window->draw(m_gameTitle);
    m_context->m_window->draw(m_playButton);
    m_context->m_window->draw(m_resolutionButton);
    m_context->m_window->draw(m_onlineButton);
    m_context->m_window->draw(m_exitButton);
    m_context->m_window->display();
}