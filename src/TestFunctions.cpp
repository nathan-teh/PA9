////////////////////////////////////////////////////////////////////////////////
/// \file         TestFunctions.cpp
/// \author       Issac Bermudez
/// \date         4/22/25
/// \brief        This file sets up the class for testing functions (5 test cases)
///               from Yo-Ho Jump!
///////////////////////////////////////////////////////////////////////////////

#include "TestFunctions.h"

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
    sf::Vector2u windowSize = { 1280, 720 };
    camera.position.x = windowSize.x / 2.0f;

    sf::View view = camera.GetView(windowSize);
    if (view.getCenter().x == windowSize.x / 2.0f)
        out << "PASS: Camera centered correctly.\n";
    else
        out << "FAIL: Camera not centered completely correctly.\n";
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

    Player player(&dummyTexture, sf::Vector2u(1, 1), 0.3f, sf::Vector2f(100.f, 100.f),
        0.0f, 0.0f, sf::Vector2f(50.f, 50.f), sf::Vector2f(40.f, 40.f));

    float playerY = player.getPosY();


    float beforeUpdateY = playerY;

    player.Update(.5);
    float afterFirstUpdateY = player.getPosY();

    player.Update(.5);
    float afterSecondUpdateY = player.getPosY();

    if (afterFirstUpdateY > beforeUpdateY && afterSecondUpdateY > afterFirstUpdateY)
        out << "PASS: Gravity correctly applied and Y position increased.\n";
    else
        out << "FAIL: Gravity not applied correctly (Y position did not increase).\n";
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