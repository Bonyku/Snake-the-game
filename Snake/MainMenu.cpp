#include "MainMenu.hpp"
#include "GamePlay.hpp"


#include <SFML/Window/Event.hpp>

MainMenu::MainMenu(std::shared_ptr<Context>& context)
    : m_context(context), m_isPlayButtonSelected(true),
    m_isPlayButtonPressed(false), m_isExitButtonSelected(false),
    m_isExitButtonPressed(false)
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
    m_gameTitle.setString("Snake Game");
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

    // Online Button
    m_onlineButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_onlineButton.setString("Online");
    m_onlineButton.setOrigin(m_onlineButton.getLocalBounds().width / 2,
        m_onlineButton.getLocalBounds().height / 2);
    m_onlineButton.setPosition(m_context->m_window->getSize().x / 2,
        m_context->m_window->getSize().y / 2 + 25.f);
    m_onlineButton.setCharacterSize(20);

    // Exit Button
    m_exitButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_exitButton.setString("Exit");
    m_exitButton.setOrigin(m_exitButton.getLocalBounds().width / 2,
        m_exitButton.getLocalBounds().height / 2);
    m_exitButton.setPosition(m_context->m_window->getSize().x / 2,
        m_context->m_window->getSize().y / 2 + 75.f);
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
                if (!m_isPlayButtonSelected)
                {
                    m_isPlayButtonSelected = true;
                    m_isExitButtonSelected = false;
                    m_isOnlineButtonSelected = false;
                }
                break;
            }
            case sf::Keyboard::Down:
            {
                if (!m_isExitButtonSelected)
                {
                    m_isPlayButtonSelected = false;
                    m_isExitButtonSelected = false;
                    m_isOnlineButtonSelected = true;
                }
                break;
            }
            case sf::Keyboard::Escape:
            {
                if (!m_isExitButtonSelected)
                {
                    m_isPlayButtonSelected = false;
                    m_isExitButtonSelected = true;
                    m_isOnlineButtonSelected = false;
                }
                break;
            }
            case sf::Keyboard::Return:
            {
                m_isPlayButtonPressed = false;
                m_isExitButtonPressed = false;
                m_isOnlineButtonSelected = false;

                if (m_isPlayButtonSelected)
                {
                    m_isPlayButtonPressed = true;
                }
                else if (m_isExitButtonPressed)
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
        m_exitButton.setFillColor(sf::Color::White);
        m_onlineButton.setFillColor(sf::Color::White);
    }
    else if (m_isExitButtonSelected)
    {
        m_exitButton.setFillColor(sf::Color::Red);
        m_playButton.setFillColor(sf::Color::White);
        m_onlineButton.setFillColor(sf::Color::White);
    }
    else if (m_isOnlineButtonSelected)
    {
        m_playButton.setFillColor(sf::Color::White);
        m_exitButton.setFillColor(sf::Color::White);
        m_onlineButton.setFillColor(sf::Color::Red);
    }

    if (m_isPlayButtonPressed)
    {
        m_context->m_states->Add(std::make_unique<GamePlay>(m_context), true);
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
    m_context->m_window->draw(m_onlineButton);
    m_context->m_window->draw(m_exitButton);
    m_context->m_window->display();
}