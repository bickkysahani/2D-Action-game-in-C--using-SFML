
#include <SFML/Graphics.hpp> //to gain access to the SFML graphics library

class hero
{
    private:
    sf::Texture m_texture;
    sf::Sprite m_sprite;
    sf::Vector2f m_position;
    int jumpCount = 0; //to check the number of times the player character has jumped
    float m_mass; //player's mass
    float m_velocity; //the velocity of the player when they jump
    const float m_gravity = 9.80f; //the gravitational force when they fall back to the ground, which is a constant
    bool m_grounded; // to check whether the player is on the ground, only when the player is on the ground can they start jumping.

    //for animation
    //int m_frameCount;
    //float  m_animDuration;
    //float m_elapsedTime;;
    //sf::Vector2i m_spriteSize;


    public:
    hero(); //contructor
   ~hero();//destructor
    void init(std::string textureName, sf::Vector2f position, float mass); //we are specifying a mass here because we will be creating some very basic physics so that when we hit the jump button, the player will jump up and land back down on their feet.
    void update(float dt); //update the player position
    void jump(float velocity); //make the player jump
    sf::Sprite getSprite(); //get the sprite of the player used for drawing the player character.
};

