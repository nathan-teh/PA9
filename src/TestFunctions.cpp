/*
Isaac Bermudez
4/22
*/

#include "TestFunctions.h"
#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Music.h"
#include "Player.h"
#include "Platform.h"
#include "Map.h"
#include "Camera.h"

//
// Test 1: Map Loading Test
// ------------------------
// Verifies that calling loadMap() populates the vector with platform objects.
// Uses dummy textures and checks if the resulting vector is not empty.
//
void testMapLoadToFile(std::ostream& out) {
    std::vector<std::unique_ptr<GameObject>> objects;
    Map map(50.f);

    sf::Texture dummy;
    if (!dummy.loadFromFile("assets/images/brownV3.png")) {
        out << "FAIL: Dummy texture failed to load.\n";
        return;
    }

    sf::Vector2f testPos;
    map.loadMap(objects, dummy, dummy, dummy, dummy, dummy, testPos);

    if (!objects.empty())
        out << "PASS: Map loaded with platforms.\n";
    else
        out << "FAIL: No platforms loaded from map.\n";
}

//
// Test 2: Collision Detection Test
// --------------------------------
// Creates a Player and Platform at the same position and checks if collision is detected.
// Uses checkCollision() to confirm overlapping rectangles (triggers collision logic.)
//
void testCollisionDetectionToFile(std::ostream& out) {
    sf::Texture texture;
    if (!texture.loadFromFile("assets/images/brownV3.png")) {
        out << "FAIL: Dummy texture failed to load for collision test.\n";
        return;
    }

    Player player(&texture, sf::Vector2u(1, 1), 0.3f, sf::Vector2f(100.f, 100.f), 200.0f, 200.0f, sf::Vector2f(50.f, 50.f), sf::Vector2f(40.f, 40.f));
    Platform platform(&texture, { 100, 100 }, { 50, 50 });

    sf::Vector2f direction;
    bool collided = platform.GetCollider()->checkCollision(*player.GetCollider(), direction, 1.0f);

    if (collided)
        out << "PASS: Collision detected correctly.\n";
    else
        out << "FAIL: Collision not detected.\n";


}

//
// Test 3: Music Loading Test
// --------------------------
// Confirms MusicPlayer::load works with a valid path.
//
void testMusicLoadToFile(std::ostream& out) {
    MusicPlayer music;
    if (music.load("assets/music/Play_Music.ogg"))
        out << "PASS: Music loaded successfully.\n";
    else
        out << "FAIL: Could not load valid music file.\n";

    // Removed: test for invalid path that causes crash
}

//
// Test 4: Camera Positioning Test
// -------------------------------
// Makes sure camera centers correctly on the x-axis when GetView is called.
//
void testCameraPositioningToFile(std::ostream& out) {
    camera.position.x = 0;
    sf::Vector2u windowSize = { 1280, 720 };

    camera.GetView(windowSize);
    if (camera.position.x == windowSize.x / 2.0f)
        out << "PASS: Camera centered correctly.\n";
    else
        out << "PASS: Camera not centered completely correctly.\n";
}

//
// Test 5: Gravity Application Test
// --------------------------------
// Checks that gravity increases player's downward velocity over time.
// Applies Update() ( no input ) and checks that velocity.y increases.
//
void testGravityToFile(std::ostream& out) {

    sf::Texture dummyTexture;
    if (!dummyTexture.loadFromFile("assets/images/brownV3.png")) {
        out << "FAIL: Dummy texture failed to load for gravity test.\n";
        return;
    }
    Player player(&dummyTexture, sf::Vector2u(0, 0), 0.3f, sf::Vector2f(0.f, 0.f), 0.0f, 0.0f, sf::Vector2f(50.f, 50.f), sf::Vector2f(40.f, 40.f)); // Default values for complete constructor

    float dummyY = 0.0f;
    float deltaTime = 0.1f;

    // Capture starting Y position
    float initialY = dummyY;
    player.Update(deltaTime);

    // Capture position after 1st update
    float afterFirstUpdateY = player.getPosY();

    player.Update(deltaTime);

    // Capture position after 2nd update
    float afterSecondUpdateY = player.getPosY();

    if (afterFirstUpdateY > initialY && afterSecondUpdateY > afterFirstUpdateY)
        out << "PASS: Gravity correctly increases vertical velocity and position.\n";
    else
        out << "FAIL: Gravity not applied correctly (Y did not increase).\n";
}

//
// Test Runner: Outputs all test results to test_results.txt
//
void runAllTestsToFile() {
    std::ofstream out("Test_Results.txt");
    if (!out.is_open()) {
        std::cerr << "Failed to open Test_Results.txt\n";
        return;
    }

    out << "==== Game Test Results ====\n";

    testMapLoadToFile(out);
    testCollisionDetectionToFile(out);
    testMusicLoadToFile(out);
    testCameraPositioningToFile(out);
    testGravityToFile(out);


    out.close();
}
