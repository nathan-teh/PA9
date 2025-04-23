/*
Isaac Bermudez
4/22
*/

#ifndef MUSIC_HPP
#define MUSIC_HPP

#include <SFML/Audio.hpp>

class MusicPlayer {
public:
    MusicPlayer();
    ~MusicPlayer();

    bool load(const std::string& filename); //load music from file
    void play(); //play music
    void stop(); //stop the music (if needed)
    void setVolume(float volume); //set volume 

private:
    sf::Music music; //Music object
};

#endif
