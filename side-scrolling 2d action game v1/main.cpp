#include <SFML/Graphics.hpp> //to gain access to the SFML graphics library
#include <vector>
#include "hero.h"
#include "Enemy.h"
#include "Rocket.h"



void spawnEnemy();

sf::Vector2f viewSize(1024, 768); //Vector2f datatype of SFML, viewSize variable for size of the window
sf::VideoMode vm(viewSize.x, viewSize.y); //VideoMode for width and height of the window
//finally create a window using RenderWindow contructor of RenderWindow class of SMFL
sf::RenderWindow window(vm, "XYZ 2D Action game !!!", sf::Style::Default);

//Adding Sprites
sf::Texture skyTexture;
sf::Sprite skySprite;
sf::Texture bgTexture;
sf::Sprite bgSprite;
hero hero; //instance of the Hero class
std::vector<Enemy*> enemies; //add a new variable called enemies of the vector type, which will store the Enemy data type in it:
std::vector<Rocket*> rockets;
float currentTime;
float prevTime = 0.0f;

int score = 0;
bool gameover = true;

// Text
sf::Font headingFont;
sf::Text headingText;
sf::Font scoreFont;
sf::Text scoreText;
//tutorial text, its implentation is in init()
sf::Text tutorialText;

////Handling player's movement
sf::Vector2f playerPosition;
bool playerMoving = false;


void spawnEnemy();
void shoot();


//collision detection
bool checkCollision(sf::Sprite sprite1, sf::Sprite sprite2);


//reset function
void reset();


void init() {
// Load sky Texture
skyTexture.loadFromFile("Assets/graphics/sky.png");
// Set and Attacha Texture to Sprite
skySprite.setTexture(skyTexture);

bgTexture.loadFromFile("Assets/graphics/bg.png");
bgSprite.setTexture(bgTexture);

// Load font
headingFont.loadFromFile("Assets/fonts/SnackerComic.ttf");

// Set Heading Text
headingText.setFont(headingFont);
headingText.setString("Tiny Bazooka");
headingText.setCharacterSize(84);
headingText.setFillColor(sf::Color::Red);


sf::FloatRect headingbounds = headingText.getLocalBounds();
headingText.setOrigin(headingbounds.width / 2, headingbounds.height / 2);
headingText.setPosition(sf::Vector2f(viewSize.x * 0.5f, viewSize.y * 0.10f));


scoreFont.loadFromFile("Assets/fonts/arial.ttf");
// Set Score Text
scoreText.setFont(scoreFont);
scoreText.setString("Score: 0");
scoreText.setCharacterSize(45);
scoreText.setFillColor(sf::Color::Red);
sf::FloatRect scorebounds = scoreText.getLocalBounds();
scoreText.setOrigin(scorebounds.width / 2, scorebounds.height /
2);
scoreText.setPosition(sf::Vector2f(viewSize.x * 0.5f, viewSize.y
* 0.10f));


// Tutorial Text
tutorialText.setFont(scoreFont);
tutorialText.setString("Press Down Arrow to Fire and Start Game, Up Arrow to Jump");
tutorialText.setCharacterSize(35);
tutorialText.setFillColor(sf::Color::Red);
sf::FloatRect tutorialbounds = tutorialText.getLocalBounds();
tutorialText.setOrigin(tutorialbounds.width / 2,
tutorialbounds.height / 2);
tutorialText.setPosition(sf::Vector2f(viewSize.x * 0.5f,
viewSize.y * 0.20f));



//Here, we set the texture picture; to do so, set the position to be at .25 (or 25%) from the left of the screen and center it along the y axis. We also set the mass to be 200 , as our character is quite chubby
hero.init("Assets/graphics/hero.png", sf::Vector2f(viewSize.x * 0.25f, viewSize.y * 0.5f), 200);
//hero.init("Assets/graphics/heroAnim.png", 4, 1.0f,sf::Vector2f(viewSize.x * 0.25f, viewSize.y * 0.5f), 200);
srand((int)time(0));
}
//srand is a pseudo-random number that is initialized by passing a seed value. In this case, we are passing in the current time as a seed value.

void spawnEnemy() {
int randLoc = rand() % 3; //random number from 0 to 2 either 0,1 or 2 each time the function is called
sf::Vector2f enemyPos;
float speed;
switch (randLoc) {
case 0: enemyPos = sf::Vector2f(viewSize.x, viewSize.y * 0.75f);
speed = -400; break;
case 1: enemyPos = sf::Vector2f(viewSize.x, viewSize.y * 0.60f);
speed = -550; break;
case 2: enemyPos = sf::Vector2f(viewSize.x, viewSize.y * 0.40f);
speed = -650; break;
default: printf("incorrect y value \n"); return;
}
Enemy* enemy = new Enemy();
enemy->init("Assets/graphics/enemy.png", enemyPos, speed);
enemies.push_back(enemy);
}


void draw()
{
    window.draw(skySprite);
    window.draw(bgSprite);
    //window.draw(heroSprite);
    window.draw(hero.getSprite());

    for (Enemy *enemy : enemies) {
    window.draw(enemy->getSprite());
    }
    for (Rocket *rocket : rockets) {
    window.draw(rocket->getSprite());
    }

if (gameover)
{
window.draw(headingText);

window.draw(tutorialText);
}
else {
window.draw(scoreText);
}
}

//Polling of event
void updateInput() {
    sf::Event event;
    while (window.pollEvent(event)) {
//    if (event.type == sf::Event::KeyPressed){
//        if (event.key.code == sf::Keyboard::Right)
//        {playerMoving = true;}
//        }
//    if (event.type == sf::Event::KeyReleased) {
//        if (event.key.code == sf::Keyboard::Right)
//        {playerMoving = false;}
//        }
        if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up)
        { hero.jump(750.0f);} //player to jump when we press the up arrow key
        }

        if (event.key.code == sf::Keyboard::Down) {
        if (gameover)
        {
        gameover = false;
        reset();}
        else {shoot();}
        }
        if (event.key.code == sf::Keyboard::Down) { shoot();}
    if (event.key.code == sf::Keyboard::Escape || event.type ==sf::Event::Closed)
    window.close(); //function to close the window
    }



}



//to update objects in the game scene
void update(float dt) {
//    if (playerMoving) {
//    heroSprite.move(50.0f * dt, 0);   //dt is timedelta, time between previous update and current update
//    }
    hero.update(dt);
    currentTime += dt;
// Spawn Enemies
if (currentTime >= prevTime + 1.125f) {
spawnEnemy();
prevTime = currentTime;
}
// Update Enemies
for (int i = 0; i < enemies.size(); i++) {
Enemy *enemy = enemies[i];
enemy->update(dt);
if (enemy->getSprite().getPosition().x < 0) {
enemies.erase(enemies.begin() + i);
delete(enemy);
}
}
// Update rockets
for (int i = 0; i < rockets.size(); i++) {
Rocket* rocket = rockets[i];
rocket->update(dt);
if (rocket->getSprite().getPosition().x > viewSize.x) {
rockets.erase(rockets.begin() + i);
delete(rocket);
}
}
// Check collision between Rocket and Enemies
for (int i = 0; i < rockets.size(); i++)
{
    for (int j = 0; j < enemies.size(); j++)
    {
    Rocket* rocket = rockets[i];
    Enemy* enemy = enemies[j];
    if (checkCollision(rocket->getSprite(), enemy->getSprite())) {


    std::string finalScore = "Score: " + std::to_string(score);
    scoreText.setString(finalScore);
    sf::FloatRect scorebounds = scoreText.getLocalBounds();
    scoreText.setOrigin(scorebounds.width / 2, scorebounds.height /2);
    scoreText.setPosition(sf::Vector2f(viewSize.x * 0.5f, viewSize.y* 0.10f));



    rockets.erase(rockets.begin() + i);
    enemies.erase(enemies.begin() + j);
    delete(rocket);
    delete(enemy);
    printf(" rocket intersects enemy \n");
    }
    }





}

// Update Enemies
for (int i = 0; i < enemies.size(); i++) {
Enemy* enemy = enemies[i];
enemy->update(dt);
if (enemy->getSprite().getPosition().x < 0) {
enemies.erase(enemies.begin() + i);
delete(enemy);
gameover = true;
}
}



}






int main() //application's main point of entry
{
    sf::Clock clock;
    window.setFramerateLimit(60);
    //while loop for handling our main game loop, this will check weather the windows is open or not so that we can add some keyboard events by updating and rendering objects in the scene and while loop will run as long as the window is open
    //Initialize Game Objects
    init();
    while (window.isOpen()) {
    // Handle Keyboard Events
    // Update Game Objects in the scene
    //To display something
//in the video, we have to clear the window and display whatever we draw in every frame.
    updateInput();
    // Update Game
    sf::Time dt = clock.restart();
    if(!gameover){
    update(dt.asSeconds());}
    window.clear(sf::Color::Red);
    // Render Game Objects
    draw();
    window.display();
        }
return 0;
}


void shoot() {
Rocket* rocket = new Rocket();
rocket->init("Assets/graphics/rocket.png",
hero.getSprite().getPosition(),400.0f);
rockets.push_back(rocket);


}
bool checkCollision(sf::Sprite sprite1, sf::Sprite sprite2) {
    sf::FloatRect shape1 = sprite1.getGlobalBounds();
    sf::FloatRect shape2 = sprite2.getGlobalBounds();
    if (shape1.intersects(shape2)) {
    return true;
    }
    else {
    return false;
    }
}

void reset() {
score = 0;
currentTime = 0.0f;
prevTime = 0.0;
for (Enemy *enemy : enemies) {
delete(enemy);
}
for (Rocket *rocket : rockets) {
delete(rocket);
}
enemies.clear();
rockets.clear();

prevTime = 0.0;
scoreText.setString("Score: 0");
}

