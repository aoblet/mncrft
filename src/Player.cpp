#include "Player.hpp"

Player::Player(Game * game, glm::vec3 const& position, std::string const& name, int life)
               :m_game(game),m_position(position),m_name(name),m_life(life),m_movementModule(*this),
                m_gameInteraction(*this),m_current_CubeType(DIRT){
    m_game = game;
    m_camera.setPosition(glm::vec3(position.x,position.y+1.5,position.z));
}

glm::vec3 Player::position() const{
    return m_position;
}

CameraFirstPerson Player::camera() const{
    return m_camera;
}

CameraFirstPerson& Player::camera(){
    return m_camera;
}

Game* Player::game(){
    return m_game;
}

int Player::life() const{
    return m_life;
}
std::string Player::name() const{
    return m_name;
}

void Player::movePosition(glm::vec3 const& vectorMovement){
    m_position += vectorMovement;
}

void Player::setPosition(glm::vec3 const& position){
    m_position = position;
    m_camera.setPosition(glm::vec3(position.x,position.y+1.4, position.z));
}

void Player::setName(std::string const& name){
    m_name = name;
}

void Player::setGame(Game * game){
    m_game = game;
}

void Player::handleMove(glimac::SDLWindowManager const& events){
    m_movementModule.updatePositionPlayer(events);
}

GameInteraction& Player::gameInteraction(){
    return m_gameInteraction;
}

GameInteraction Player::gameInteraction() const{
    return m_gameInteraction;
}

CubeType Player::currentCubeType() const{
    return m_current_CubeType;
}

void Player::setCurrentCubeType(const CubeType &type){
    m_current_CubeType = type;
}
