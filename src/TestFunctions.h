/*
Isaac Bermudez
4/22
*/

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
