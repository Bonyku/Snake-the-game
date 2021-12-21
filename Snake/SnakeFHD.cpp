#include "SnakeFHD.hpp"

SnakeFHD::SnakeFHD() : m_body(std::list<sf::Sprite>(4))
{
    m_head = --m_body.end();
    m_tail = m_body.begin();
}

SnakeFHD::~SnakeFHD()
{
}

void SnakeFHD::Init(const sf::Texture& texture)
{
    float x = 50.f;
    for (auto& piece : m_body)
    {
        piece.setTexture(texture);
        piece.setPosition({ x, 50.f });
        x += 50.f;
    }
}

void SnakeFHD::Move(const sf::Vector2f& direction)
{
    m_tail->setPosition(m_head->getPosition() + direction);
    m_head = m_tail;
    ++m_tail;

    if (m_tail == m_body.end())
    {
        m_tail = m_body.begin();
    }
}

bool SnakeFHD::IsOn(const sf::Sprite& other) const
{
    return other.getGlobalBounds().intersects(m_head->getGlobalBounds());
}

void SnakeFHD::Grow(const sf::Vector2f& direction)
{
    sf::Sprite newPiece;
    newPiece.setTexture(*(m_body.begin()->getTexture()));
    newPiece.setPosition(m_head->getPosition() + direction);

    m_head = m_body.insert(++m_head, newPiece);
}

bool SnakeFHD::IsSelfIntersecting() const
{
    bool flag = false;

    for (auto piece = m_body.begin(); piece != m_body.end(); ++piece)
    {
        if (m_head != piece)
        {
            flag = IsOn(*piece);

            if (flag)
            {
                break;
            }
        }
    }

    return flag;
}

void SnakeFHD::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (auto& piece : m_body)
    {
        target.draw(piece);
    }
}