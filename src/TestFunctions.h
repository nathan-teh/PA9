////////////////////////////////////////////////////////////////////////////////
/// \file         TestFunctions.h
/// \author       Issac Bermudez
/// \date         4/22/25
/// \brief        This file sets up the class for testing functions (5 test cases)
///               from Yo-Ho Jump!
///////////////////////////////////////////////////////////////////////////////

#ifndef TESTFUNCTIONS_H
#define TESTFUNCTIONS_H

#include <ostream>

void runAllTestsToFile();

void testMapLoadToFile(std::ostream& out);
void testCollisionDetectionToFile(std::ostream& out);
void testMusicLoadToFile(std::ostream& out);
void testCameraPositioningToFile(std::ostream& out);
void testGravityToFile(std::ostream& out);

#endif
