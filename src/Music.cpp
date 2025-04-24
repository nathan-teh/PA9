#include "Music.h"
#include <iostream>

void MusicPlayer::play() {
    music.setLooping(true);
    music.play();
}
