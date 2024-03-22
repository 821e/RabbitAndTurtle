#include "Game.h"
#include <iostream>

Game::Game() : window(sf::VideoMode(1920, 600), "The Rabbit and the Turtle"), gameState(State::Ready) {
    initialize();
}

void Game::initialize() {
    loadAssets();
    setupRace();

    // Set up text for displaying the winner
    if (!gameFont.loadFromFile("/Users/rakan/Developer/cpp/TheRabbitAndTheTurtle/assets/fonts/game_font.ttf")) {
        std::cout << "Failed to load game font!" << std::endl;
    }
    winnerText.setFont(gameFont);
    winnerText.setCharacterSize(25);
    winnerText.setFillColor(sf::Color::White);
    winnerText.setPosition(300.f, 10.f);

    // Set up race start and end logic using Fox as the umpire
    fox.setRaceStartCallback([this]() {
        gameState = State::InProgress;
        rabbit.setPosition(0, 270);
        turtle.setPosition(0, 330);
    });

    fox.setRaceEndCallback([this](const std::string& winner) {
        gameState = State::Finished;
        declareWinner(winner);
    });

    // Start the race as per the story
    fox.startRace();
    if (!backgroundMusic.openFromFile("/Users/rakan/Developer/cpp/TheRabbitAndTheTurtle/assets/sounds/humorous_tune.ogg")) {
        std::cerr << "Failed to load background music" << std::endl;
    }

    backgroundMusic.setLoop(true);
    backgroundMusic.setVolume(10.0f);
    backgroundMusic.play();

}



void Game::loadAssets() {
    // Load textures for all entities
    if (!rabbitTexture.loadFromFile("/Users/rakan/Developer/cpp/TheRabbitAndTheTurtle/assets/images/rabbit_running.png")) {
        std::cout << "Failed to load rabbit texture" << std::endl;
    }
    if (!rabbitTexture.loadFromFile("/Users/rakan/Developer/cpp/TheRabbitAndTheTurtle/assets/images/rabbit_walking.png")) {
        std::cout << "Failed to load rabbit texture" << std::endl;
    }

    if (!foxTexture.loadFromFile("/Users/rakan/Developer/cpp/TheRabbitAndTheTurtle/assets/images/fox.png")) {
        std::cout << "Failed to load fox texture" << std::endl;
    }
    if (!startScreenTexture.loadFromFile("/Users/rakan/Developer/cpp/TheRabbitAndTheTurtle/assets/images/start_screen.png")) {
        std::cerr << "Failed to load start screen texture" << std::endl;
    }
    startScreenSprite.setTexture(startScreenTexture);
    if (!trackTexture.loadFromFile("/Users/rakan/Developer/cpp/TheRabbitAndTheTurtle/assets/images/background.png")) {
        std::cout << "Failed to load new track background texture" << std::endl;

    }
    std::vector<sf::Texture> turtleTextures;
    turtleTextures.reserve(4); // Optional but improves performance
    for (int i = 0; i < 4; ++i) {
        sf::Texture texture;
        if (!texture.loadFromFile("/Users/rakan/Developer/cpp/TheRabbitAndTheTurtle/assets/images/turtle_frame_" + std::to_string(i + 1) + ".png")) {
            std::cerr << "Failed to load turtle texture for frame " << i + 1 << std::endl;
        } else {
            turtleTextures.push_back(texture); // Add the texture to the vector
        }
    }

    // Set the loaded textures to the turtle
    turtle.setTextures(turtleTextures);

    // Set textures for each entity
    rabbit.setTexture(rabbitTexture);
    turtle.setTexture(turtleTexture); // Turtle has only one texture state
    fox.setTexture(foxTexture);
    raceTrack.setTexture(trackTexture); // Use the new background texture for the racetrack
}

void Game::setupRace() {
    // Set initial positions or any other setup required before the race starts
    rabbit.setPosition(0, 250);
    turtle.setPosition(0, 300);
    fox.setPosition(100, 150); // Centered on the x-axis and above the track
}


void Game::run() {
    sf::Clock clock;
    sf::Time startScreenTimer;

    // Set the initial state to Starting
    gameState = State::Starting;
    startScreenTimer = sf::seconds(0);

    while (window.isOpen()) {
        sf::Time deltaTime = clock.restart();
        processEvents();

        // Handle the Starting state separately
        if (gameState == State::Starting) {
            startScreenTimer += deltaTime;
            if (startScreenTimer.asSeconds() >= 6) {
                gameState = State::Ready;
            }
        }

        if (gameState == State::InProgress) {
            update(deltaTime);
        }
        render();
    }
}


void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space && gameState == State::Ready) {
            // Start the race
            gameState = State::InProgress;
            fox.startRace();
        }
    }
}


void Game::update(sf::Time deltaTime) {
    switch (gameState) {
        case State::InProgress:
            rabbit.update(deltaTime);
            turtle.update(deltaTime);
            fox.update(deltaTime);
            raceTrack.update(deltaTime);


            fox.checkForWinner(rabbit, turtle);


            if (gameState == State::Finished) {
            }
            break;
        case State::Finished:

            break;
        default:
            break; // Other states can be handled if needed
    }
}


void Game::render() {
    window.clear(sf::Color::White);

    if (gameState == State::Starting) {
        window.draw(startScreenSprite);
    } else {
        // Existing rendering code for the game
        raceTrack.draw(window);
        rabbit.draw(window);
        turtle.draw(window);
        fox.draw(window);

        if (gameState == State::Finished) {
            window.draw(winnerText);
        }
    }

    window.display();
}


void Game::declareWinner(const std::string& winner) {
    winnerText.setString(winner + " wins the race!");
    winnerText.setCharacterSize(48);
    winnerText.setFillColor(sf::Color::Green);
    winnerText.setPosition(800.f, 300.f);


    if (winner == "Turtle") {
        if (!celebrationSoundBuffer.loadFromFile("/Users/rakan/Developer/cpp/TheRabbitAndTheTurtle/assets/sounds/victory.ogg")) {
            std::cerr << "Failed to load celebration sound" << std::endl;
        } else {
            celebrationSound.setBuffer(celebrationSoundBuffer);
            celebrationSound.play();
        }
    }
}