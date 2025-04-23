//
// Created by Nathan Teh on 4/20/25.
//

#include "Player.h"
#include <iostream>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

Camera camera(1000);

SOCKET sock = INVALID_SOCKET;
sockaddr_in serverHint;
bool socketInitialized = false;

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f pos, float speed,
    float jumpHeight, sf::Vector2f size, sf::Vector2f collisionSize) : animation(texture, imageCount, switchTime), pos(pos) {

    this->mSpeed = speed;
    this->jumpHeight = jumpHeight;
    this->canJump = true;

    collisionBox.setSize(collisionSize);
    collisionBox.setOrigin((collisionSize) / 2.0f);
    collisionBox.setPosition(pos);

    this->mBody.setSize(size);
    this->mBody.setOrigin((size) / 2.0f);
    this->mBody.setTexture(texture);
    this->mBody.setPosition(pos);
    isGrounded = false;
    row = 0;
    faceRight = true;

    if (!jump.openFromFile("assets/sounds/Sequence-01.ogg")) {
        std::cerr << "Failed to load jump sound!" << std::endl;
    }
    if (!victoryMusic.openFromFile("assets/sounds/Victory_SFX.ogg")) {
        std::cerr << "Failed to load victory music!" << std::endl;
    }

    // Initialize socket
    WSAData data;
    WORD ver = MAKEWORD(2, 2);
    int wsResult = WSAStartup(ver, &data);
    if (wsResult == 0) {
        sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock != INVALID_SOCKET) {
            serverHint.sin_family = AF_INET;
            serverHint.sin_port = htons(54000);  // Changed to match the server port
            serverHint.sin_addr.s_addr = inet_addr("127.0.0.1");

            if (connect(sock, (sockaddr*)&serverHint, sizeof(serverHint)) == 0) {
                socketInitialized = true;
            }
        }
    }
}

void Player::Update(float deltaTime, float& playerY) {
    velocity.x = 0.0f;
    isGrounded = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) velocity.x -= mSpeed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) velocity.x += mSpeed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && canJump) {
        canJump = false;
        jump.play();
        velocity.y = -sqrtf(2.0f * 981.0f * jumpHeight);
    }
    if (velocity.x == 0.0f) row = 0;
    else {
        row = 3;
        if (velocity.x > 0.0) faceRight = true;
        else faceRight = false;
    }
    if (velocity.y != 0) row = 1;
    velocity.y += 981.0f * deltaTime;
    sf::Vector2f newPos = collisionBox.getPosition() + velocity * deltaTime;
    collisionBox.setPosition(newPos);
    mBody.setPosition(collisionBox.getPosition());
    this->pos = newPos;

    if (!isGrounded) canJump = false;
    animation.Update(row, deltaTime, faceRight);
    mBody.setTextureRect(animation.uvRect);

    if (mBody.getPosition().y > 9430) {
        camera.position.y = 9985;
    }
    else if (mBody.getPosition().y > 8575) {
        camera.position.y = 9085;
    }
    else if (mBody.getPosition().y > 7720) {
        camera.position.y = 8185;
    }
    else if (mBody.getPosition().y > 6865) {
        camera.position.y = 7285;
    }
    else if (mBody.getPosition().y > 5825) {
        camera.position.y = 6385;
    }
    else if (mBody.getPosition().y > 4980) {
        camera.position.y = 5485;
    }
    else if (mBody.getPosition().y > 4125) {
        camera.position.y = 4585;
    }
    else if (mBody.getPosition().y > 3270) {
        camera.position.y = 3685;
    }
    else if (mBody.getPosition().y > 2420) {
        camera.position.y = 2785;
    }
    else if (mBody.getPosition().y > 1873) {
        camera.position.y = 2450;
    }
    else if (mBody.getPosition().y > 1000) {
        camera.position.y = 1420;
    }

    playerY = mBody.getPosition().y;
    if (mBody.getPosition().y <= 1790.0 && !playedVictory) {
        victoryMusic.play();
        playedVictory = true;
    }

    // Send player position to server if socket is initialized
    if (socketInitialized) {
        std::string posData = std::to_string(pos.x) + "," + std::to_string(pos.y);
        send(sock, posData.c_str(), posData.size() + 1, 0);
    }
}

void Player::Draw(sf::RenderWindow& window) {
    window.draw(mBody);
}

void Player::OnCollision(sf::Vector2f direction) {
    if (direction.x > 0.0f || direction.x < 0.0f) velocity.x = 0.0f;
    if (direction.y < 0.0f) {
        velocity.y = 0.0f;
        canJump = true;
        isGrounded = true;
    }
    else if (direction.y > 0.0f) velocity.y = 0.0f;
}

// Clean up socket on shutdown
Player::~Player() {
    if (socketInitialized) {
        closesocket(sock);
        WSACleanup();
    }
}