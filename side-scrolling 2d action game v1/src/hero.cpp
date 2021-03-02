//we will implement the functions that we added in the .h file
#include "hero.h"

hero::hero() //contructor
{
    //ctor
}

hero::~hero() //destructor
{
    //dtor
}

void hero::init(std::string textureName, sf::Vector2f position,
float mass){
m_position = position;
m_mass = mass;
m_grounded = false;
// Load a Texture
m_texture.loadFromFile(textureName.c_str());
// Create Sprite and Attach a Texture
m_sprite.setTexture(m_texture);
m_sprite.setPosition(m_position);
m_sprite.setOrigin(m_texture.getSize().x / 2,
m_texture.getSize().y / 2);
}



void hero::update(float dt){
//m_force -= m_mass * m_gravity * dt;
// Update Position
m_velocity -= m_mass * m_gravity * dt;
m_position.y -= m_velocity * dt;
m_sprite.setPosition(m_position);
if (m_position.y >= 768 * 0.75) {
m_position.y = 768 * 0.75;
m_velocity = 0;
m_grounded = true;
jumpCount = 0;
}
}

void hero::jump(float velocity){
if (jumpCount < 2) {
jumpCount++;
//m_velocity = VELOCITY;
m_velocity = velocity;
m_grounded = false;
}
}

sf::Sprite hero::getSprite(){
return m_sprite;
}
