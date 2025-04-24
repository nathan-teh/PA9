////////////////////////////////////////////////////////////////////////////////
/// \file         TestFunctions.h
/// \author       Issac Bermudez
/// \date         4/22/25
/// \brief        This file sets up the class for testing functions (5 test cases)
///               from Yo-Ho Jump!
///////////////////////////////////////////////////////////////////////////////

#ifndef TESTFUNCTIONS_H
#define TESTFUNCTIONS_H

#include "Camera.h"
#include "Music.h"
#include "Platform.h"
#include "Player.h"
#include "Map.h"
#include <fstream>
#include <ostream>
#include <iostream>

void runAllTestsToFile(); // runs all test cases and writes results to file

void testMapLoadToFile(std::ostream& out); // tests map loading 
void testCollisionDetectionToFile(std::ostream& out); // tests collision detection
void testMusicLoadToFile(std::ostream& out); // tests music loading
void testCameraPositioningToFile(std::ostream& out); // tests camera positioning
void testGravityToFile(std::ostream& out); // tests gravity physics on player movement

#endif
