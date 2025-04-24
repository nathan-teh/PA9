///////////////////////////////////////////////////////////////////////////////
/// \file         Music.h
/// \author       Issac Bermudez
/// \date         4/22/25
/// \brief        This file sets up the music player for main menu and
///               gameplay music for Yo-Ho Jump!
///////////////////////////////////////////////////////////////////////////////

#ifndef MUSIC_HPP
#define MUSIC_HPP

#include <SFML/Audio.hpp>

class MusicPlayer {
public:
    MusicPlayer() {}; // default constructor
    ~MusicPlayer() {music.stop();} // destructor
    bool load(const std::string& filename) {return music.openFromFile(filename);} // loads songs
    void play(){music.setLooping(true); music.play();} //play music
    void stop() {music.stop();} 
    void setVolume(float volume) {music.setVolume(volume);}
    sf::Music::Status getStatus() {return music.getStatus();}; //get status of music

private:
    sf::Music music; //Music object
};

#endif
