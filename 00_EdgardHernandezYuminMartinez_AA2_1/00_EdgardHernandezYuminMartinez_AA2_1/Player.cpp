#include "util.h"
Player::Player()
{
	m_PosX = numRandom(1, 15);
	m_PosY = numRandom(1, 69);

}
void Player::moveForward() 
{
	m_PosY--;
}
void Player::moveLeft()
{
	m_PosX--;
}
void Player::moveBack()
{
	m_PosY++;
}
void Player::moveRight()
{
	m_PosX++;
}