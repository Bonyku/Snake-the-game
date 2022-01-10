#pragma once

#include <memory>

#include <SFML/Graphics/Text.hpp>

#include "State.hpp"
#include "Game.hpp"

class Resolution : public Engine::State
{
private:
    std::shared_ptr<Context> m_context;
    sf::Text m_gameTitle;
    sf::Text m_first_resolutionButton;
    sf::Text m_second_resolutionButton;
    sf::Text m_third_resolutionButton;
    sf::Text m_fourth_resolutionButton;
    sf::Text m_backButton;


    bool m_isFirst_ResolutionButtonSelected;
    bool m_isFirst_ResolutionButtonPressed;

    bool m_isSecond_ResolutionSelected;
    bool m_isSecond_ResolutionPressed;

    bool m_isthird_ResolutionButtonSelected;
    bool m_isthird_ResolutionButtonPressed;

    bool m_isfourth_ResolutionButtonSelected;
    bool m_isfourth_ResolutionButtonPressed;

    bool m_isBackButtonSelected;
    bool m_isBackButtonPressed;

    int key_counter = 4;

public:
    Resolution(std::shared_ptr<Context>& context);
    ~Resolution();


    void Init() override;
    void ProcessInput() override;
    void Update(sf::Time deltaTime) override;
    void Draw() override;
};