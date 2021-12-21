#pragma once

#include <memory>
#include <array>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <iostream>
#include <string>
#include <cstdio>

#include "Game.hpp"
#include "State.hpp"
#include "Snake.hpp"

class Nickname : public Engine::State
{
private:
    std::shared_ptr<Context> m_context;
    sf::Text Question;
    sf::String playerInput;
    sf::Text m_nickname;
    std::string nickname;




public:
    Nickname(std::shared_ptr<Context>& context);
    ~Nickname();

    void Init() override;
    void ProcessInput() override;
    void Update(sf::Time deltaTime) override;
    void Draw() override;
};