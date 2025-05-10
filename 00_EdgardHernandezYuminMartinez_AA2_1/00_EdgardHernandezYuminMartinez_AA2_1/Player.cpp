#include "util.h"
Player::Player()
{
	m_PosX = numRandom(1, 15);
	m_PosY = numRandom(1, 69);

}
void Player::moveForward() 
{
	m_PosX--;
	
}
void Player::moveLeft()
{
	m_PosY--;
	
}
void Player::moveBack()
{
	m_PosX++;
	
}
void Player::moveRight()
{ 
	m_PosY++;
	
}