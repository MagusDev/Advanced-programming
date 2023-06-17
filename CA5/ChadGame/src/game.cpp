#include "../include/game.hpp"



using namespace std;




Game::Game(){
    this->initWindow();
    this->map = new Map();   
    this->map->loadMap(LEVEL1);
    sf::Vector2f spawnPoint = map->getPortal().getSprite().getPosition();
    this->player = new Player(spawnPoint.x, spawnPoint.y);
}

void Game::initWindow(){
    this->window.create(sf::VideoMode(TILE_SIZE * MAP_WIDTH,TILE_SIZE * MAP_HEIGHT),"chadGame", sf::Style::Close| sf::Style::Titlebar);
    view.setCenter(player->getSprite().getPosition());
    view.setSize(sf::Vector2f(MAP_WIDTH*60, MAP_HEIGHT*60));
    window.setView(view);
}

const sf::RenderWindow& Game::getWindow() const {
    return this->window;
}

void Game::update(){
     // Handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::A)
                    player->setMovingLeft(true);
                else if (event.key.code == sf::Keyboard::D)
                    player->setMovingRight(true);
                else if (event.key.code == sf::Keyboard::R)
                    player->reset();
                else if (event.key.code == sf::Keyboard::Q)
                    for(auto& baby : map->getBabies())
                        baby.toggleCanJump();
                else if (event.key.code == sf::Keyboard::E){
                    sf::Vector2f position = player->getSprite().getPosition();
                    position.y += TILE_SIZE;
                    map->addPlatformAtPosition(position);
                }
                else if (event.key.code == sf::Keyboard::W)
                    player->jump();
                else if (event.key.code == sf::Keyboard::H){
                    player->gotHurt();
                }
            }
            else if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::A)
                    player->setMovingLeft(false);
                else if (event.key.code == sf::Keyboard::D)
                    player->setMovingRight(false);
            }
        }

    player->update(0.015f, *map);
    for (auto& enemy : map->getEnemies())
    {
        enemy.update(0.015f, map->getPlatforms());
    }
    for (auto& baby : map->getBabies())
    {
        baby.update(0.015f, map->getPlatforms());
    }
    babyCollisionWithPortalHandler();
    gameOverCheck();
    
}


void Game::render(){
    window.clear();
    map->draw(window);
    view.setCenter(player->getSprite().getPosition());
    window.setView(view);
    player->draw(window);
    drawScore(player->getScore());
    window.display();  
}

void Game::drawScore(int score){
    sf::Font font;
    if (!font.loadFromFile("./fonts/kenvector_future.ttf")) {
        cerr << "CANT LOAD FONT ./fonts/kenvector_future.ttf" << endl;
    }
    sf::Text scoreText("Score: " + std::to_string(score), font, 25);
    scoreText.setFillColor(sf::Color::Green);
    scoreText.setPosition(player->getSprite().getPosition().x + 420, player->getSprite().getPosition().y - 280);
    window.draw(scoreText);
}

void Game::loadLevel(){
    switch (currLevel)
        {
        case 0:
            this->map->loadMap(LEVEL1);
            break;
        case 1:
            this->map->loadMap(LEVEL2);
            break;
        case 2:
            this->map->loadMap(LEVEL3);
            break;
        case 3:
            window.close();
            break;
        default:
            break;
        }
}

void Game::gameOverCheck(){
    if (player->getWinState() == 1){
        currLevel ++;
        //this->map->loadMap(map->getLevels()[map->getCurrentLevel]);
        loadLevel();       
        player->setOrigPos(map->getPortal().getSprite().getPosition());
        player->setWinState(0);
        player->reset();
        //map->setCurrentLevel(map->getCurrentLevel()+1);
    }
    
}

void Game::babyCollisionWithPortalHandler(){
    for (auto baby = this->map->getBabies().begin(); baby != this->map->getBabies().end(); baby++) {
        if (this->map->getPortal().getSprite().getGlobalBounds().intersects((*baby).getBounds())) {
            this->map->getBabies().erase(baby);
            this->player->setScore(this->player->getScore() + DIOMOND_SCORE);
            break;
        }
    }
}

