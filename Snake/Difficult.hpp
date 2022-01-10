#pragma once

#include <memory>

#include <SFML/Graphics/Text.hpp>

#include "State.hpp"
#include "Game.hpp"


class Difficult : public Engine::State
{
private:
    std::shared_ptr<Context> m_context;
    sf::Text m_gameTitle;
    sf::Text m_largeButton;
    sf::Text m_smallButton;
    sf::Text m_exitButton;

    bool m_isLargeButtonSelected;
    bool m_isLargeButtonPressed;

    bool m_isSmallButtonSelected;
    bool m_isSmallButtonPressed;

    bool m_isExitButtonSelected;
    bool m_isExitButtonPressed;

    int key_counter = 2;

public:
    Difficult(std::shared_ptr<Context>& context);
    ~Difficult();

    void Init() override;
    void ProcessInput() override;
    void Update(sf::Time deltaTime) override;
    void Draw() override;
};