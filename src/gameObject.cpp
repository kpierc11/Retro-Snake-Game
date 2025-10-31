#include "gameObject.hpp"
#include "game.hpp"

GameObject::GameObject(Game *game) : m_game(game)
{
}

GameObject::~GameObject()
{
}

void GameObject::Update(float deltaTime)
{
}

void GameObject::Draw()
{
}
