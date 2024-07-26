#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Pong_PP4");

    sf::RectangleShape leftPaddle(sf::Vector2f(20.0f, 100.0f));
    leftPaddle.setOrigin(10.0f, 50.0f);
    leftPaddle.setPosition(10.0f, 300.0f);

    sf::RectangleShape rightPaddle(sf::Vector2f(20.0f, 100.0f));
    rightPaddle.setOrigin(10.0f, 50.0f);
    rightPaddle.setPosition(790.0f, 300.0f);

    sf::CircleShape ball(10.0f);
    ball.setOrigin(10.0f, 10.0f);
    ball.setPosition(400.0f, 300.0f);

    sf::Vector2f ballVelocity(200.5f, 200.5f);

    int leftScore = 0;
    int rightScore = 0;

    sf::Texture pongTexture;
    if (!pongTexture.loadFromFile("/Users/edwardvas/Desktop/SFML/pong.png")) {
    }

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Time deltaTime = clock.restart();
        float dt = deltaTime.asSeconds();

        // Manejar eventos
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Configuracion de los controles
        leftPaddle.move(0, (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && leftPaddle.getPosition().y - 50.0f > 0) ? -175.5f * dt : 0);
        leftPaddle.move(0, (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && leftPaddle.getPosition().y + 50.0f < 600) ? 175.5f * dt : 0);
        rightPaddle.move(0, (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && rightPaddle.getPosition().y - 50.0f > 0) ? -175.5f * dt : 0);
        rightPaddle.move(0, (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && rightPaddle.getPosition().y + 50.0f < 600) ? 175.5f * dt : 0);

        // Logica del juego
        ball.move(ballVelocity.x * dt, ballVelocity.y * dt);

        // Colisiones de los lados
        if (ball.getPosition().y - 10.0f <= 0 || ball.getPosition().y + 10.0f >= 600) {
            ballVelocity.y = -ballVelocity.y;
        }

        // Colision de las raquetas
        if (ball.getGlobalBounds().intersects(leftPaddle.getGlobalBounds()) || ball.getGlobalBounds().intersects(rightPaddle.getGlobalBounds())) {
            ballVelocity.x = -ballVelocity.x;
        }

        // Condicion de cuando anota el player1
        if (ball.getPosition().x - 10.0f <= 0) {
            rightScore++;
            ball.setPosition(400.0f, 300.0f);
        }

        // Condicion de cuando anota el player2
        if (ball.getPosition().x + 10.0f >= 800) {
            leftScore++;
            ball.setPosition(400.0f, 300.0f);
        }

        window.clear();

        sf::Sprite pongSprite(pongTexture);
        pongSprite.setScale(window.getSize().x / pongSprite.getLocalBounds().width, window.getSize().y / pongSprite.getLocalBounds().height);
        window.draw(pongSprite);

        window.draw(leftPaddle);
        window.draw(rightPaddle);
        window.draw(ball);

        sf::Font font;
        if (!font.loadFromFile("/Users/edwardvas/Desktop/SFML/Fonts/arial.ttf")) {
        }

        sf::Text leftScoreText;
        leftScoreText.setFont(font);
        leftScoreText.setString("Player 1: " + std::to_string(leftScore));
        leftScoreText.setCharacterSize(24);
        leftScoreText.setFillColor(sf::Color::White);
        leftScoreText.setPosition(10, 10);

        sf::Text rightScoreText;
        rightScoreText.setFont(font);
        rightScoreText.setString("Player 2: " + std::to_string(rightScore));
        rightScoreText.setCharacterSize(24);
        rightScoreText.setFillColor(sf::Color::White);
        rightScoreText.setPosition(780 - rightScoreText.getLocalBounds().width, 10);

        window.draw(leftScoreText);
        window.draw(rightScoreText);

        window.display();
    }

    return 0;
}