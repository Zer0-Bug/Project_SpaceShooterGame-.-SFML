#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace sf;

class Bullet {
public:
    Sprite shape;
    Bullet(Texture* texture, Vector2f pos) {
        this->shape.setTexture(*texture);
        this->shape.setScale(0.45f, 0.45f);
        this->shape.setPosition(pos);
    }
};

class Player {
public:
    Sprite shape;
    Texture* texture;
    int HP;
    int HPMax;
    std::vector<Bullet> bullets;

    Player(Texture* texture) {
        this->HPMax = 1;
        this->HP = this->HPMax;
        this->texture = texture;
        this->shape.setTexture(*texture);
        this->shape.setScale(0.1f, 0.1f);
    }
};

class Enemy {
public:
    Sprite shape;
    int HP;
    int HPMax;

    Enemy(Texture* texture, Vector2u windowSize) {
        this->HPMax = 1;
        this->HP = this->HPMax;
        this->shape.setTexture(*texture);
        this->shape.setScale(0.05f, 0.05f);
        this->shape.setPosition(windowSize.x - this->shape.getGlobalBounds().width, rand() % (int)(windowSize.y - this->shape.getGlobalBounds().height));
    }
};

int main() {
    srand(time(NULL));

    // Creating the game window
    RenderWindow window(VideoMode(800, 600), "Space Shooter | Zer0-Bug", Style::Default);
    window.setFramerateLimit(15);

    // Loading textures
    Texture backgroundTex;
    backgroundTex.loadFromFile("background.jpg");
    Sprite background(backgroundTex);

    // Loading font
    Font font;
    font.loadFromFile("arial.ttf");

    // Loading player, enemy, and bullet textures
    Texture playerTex;
    playerTex.loadFromFile("player.png");

    Texture enemyTex;
    enemyTex.loadFromFile("enemy.png");

    Texture bulletTex;
    bulletTex.loadFromFile("bullet.png");

    // Setting up text objects for score, game over, and health
    Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(20);
    scoreText.setFillColor(Color::Cyan);
    scoreText.setPosition(10.f, 570.f);

    Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(30);
    gameOverText.setFillColor(Color::Red);
    gameOverText.setPosition(300.f, 300.f);
    gameOverText.setString("G a m e  O v e r !");

    Text hpText;
    hpText.setFont(font);
    hpText.setCharacterSize(12);
    hpText.setFillColor(Color::White);

    Text eHpText;
    eHpText.setFont(font);
    eHpText.setCharacterSize(12);
    eHpText.setFillColor(Color::White);

    // Initializing variables for game logic
    int score = 0;
    int shootTimer = 20;

    std::vector<Enemy> enemies;

    // Creating the player object
    Player player(&playerTex);
    bool gameOver = false;
    bool enemySpawned = false;

    // Game loop
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        if (!gameOver) {

            // Handling player movement
            if (Keyboard::isKeyPressed(Keyboard::W)) {
                player.shape.move(0.f, -5.f);
            }

            if (Keyboard::isKeyPressed(Keyboard::S)) {
                player.shape.move(0.f, 5.f);
            }

            // Ensuring player stays within window bounds
            if (player.shape.getPosition().y <= 0) {
                player.shape.setPosition(player.shape.getPosition().x, 0.f);
            }

            if (player.shape.getPosition().y >= window.getSize().y - player.shape.getGlobalBounds().height) {
                player.shape.setPosition(player.shape.getPosition().x, window.getSize().y - player.shape.getGlobalBounds().height);
            }

            // Handling shooting logic
            if (shootTimer < 15) {
                shootTimer++;
            }

            if (Keyboard::isKeyPressed(Keyboard::Space) && shootTimer >= 15) {
                player.bullets.push_back(Bullet(&bulletTex, Vector2f(player.shape.getPosition().x, player.shape.getPosition().y + player.shape.getGlobalBounds().height / 2 - 15)));
                shootTimer = 0;
            }

            // Updating bullet positions and checking for collisions
            for (size_t i = 0; i < player.bullets.size(); i++) {
                player.bullets[i].shape.move(20.f, 0.f); // Bullet speed

                if (player.bullets[i].shape.getPosition().x > window.getSize().x) {
                    player.bullets.erase(player.bullets.begin() + i);   // Removing bullets when they leave the screen
                    break;
                }

                for (size_t k = 0; k < enemies.size(); k++) {
                    if (player.bullets[i].shape.getGlobalBounds().intersects(enemies[k].shape.getGlobalBounds())) {
                        score++;
                        enemies.erase(enemies.begin() + k);
                        player.bullets.erase(player.bullets.begin() + i);
                        enemySpawned = false;
                        break;
                    }
                }
            }

            // Spawning enemies and handling enemy logic
            if (!enemySpawned) {
                enemies.push_back(Enemy(&enemyTex, window.getSize()));
                enemySpawned = true;
            }

            for (size_t i = 0; i < enemies.size(); i++) {
                enemies[i].shape.move(-7.f, 0.f);
                if (enemies[i].shape.getPosition().x <= 0 - enemies[i].shape.getGlobalBounds().width) {
                    gameOver = true; // // End game if an enemy reaches the left side of the screen
                }

                if (enemies[i].shape.getGlobalBounds().intersects(player.shape.getGlobalBounds())) {
                    enemies.erase(enemies.begin() + i);
                    player.HP--;
                    if (player.HP <= 0)
                        gameOver = true; // End game if player health drops to zero
                    break;
                }
            }

            scoreText.setString("Score: " + std::to_string(score));
        }

        window.clear();
        window.draw(background);
        window.draw(player.shape);


        // Drawing bullets and enemies
        for (size_t i = 0; i < player.bullets.size(); i++) {
            window.draw(player.bullets[i].shape);
        }

        for (size_t i = 0; i < enemies.size(); i++) {
            window.draw(enemies[i].shape);
        }

        window.draw(scoreText);

        // Drawing game over text if game is over
        if (gameOver) {
            window.draw(gameOverText);
        }

        window.display();
    }

    return 0;
}
