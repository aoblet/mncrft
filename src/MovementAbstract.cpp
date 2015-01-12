#include "MovementAbstract.hpp"
#include "Player.hpp"
#include "Game.hpp"

const float MovementAbstract::METER_WALKED_PER_FRAME = (15000/(60*60.))/Game::FRAME_PER_SECOND; //60fps 15kmh: jogging

MovementAbstract::MovementAbstract(Player &player):m_player(player){}
