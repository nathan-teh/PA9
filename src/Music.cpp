#include "Music.h"
#include <iostream>

MusicPlayer::MusicPlayer() {}

MusicPlayer::~MusicPlayer() {
    music.stop();
}

bool MusicPlayer::load(const std::string& filename) {
    return music.openFromFile(filename);
}

void MusicPlayer::play() {
    music.setLooping(true);
    music.play();
}

void MusicPlayer::stop() {
    music.stop();
}

void MusicPlayer::setVolume(float volume) {
    music.setVolume(volume);
}
