#pragma once

#include "Playlist.h"

class IPlaybackEngine
{
public:
    virtual ~IPlaybackEngine() = default;

    virtual bool isPaused() const = 0;

    virtual bool isPlaying() const = 0;

    virtual void nextSong() = 0;

    virtual void pause() = 0;

    virtual void play() = 0;

    virtual void previousSong() = 0;

    virtual void resume() = 0;

    virtual void setPlaylist(Playlist *playlist) = 0;

    virtual void stop() = 0;
};
