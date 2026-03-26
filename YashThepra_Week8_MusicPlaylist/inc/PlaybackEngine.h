#pragma once

#include <deque>
#include <list>
#include <queue>
#include <string>
#include <SFML/Audio.hpp>

#include "IPlaybackEngine.h"

class PlaybackEngine : public IPlaybackEngine
{
public:
    PlaybackEngine();

    ~PlaybackEngine() override;

    bool isPlaying() const override;

    void nextSong() override;

    void pause() override;

    void play() override;

    void previousSong() override;

    void resume() override;

    void setPlaylist(Playlist *playlist) override;

    void stop() override;
    
private:
    std::list<Song>::iterator cursor_;
    std::deque<Song *> history_;
    bool isPaused_;
    bool isPlaying_;
    sf::Music music_;
    Playlist *playlist_;
    std::queue<Song *> upNext_;

    std::string getCurrentSongTitle() const;

    bool loadCurrentSong();

    void pushToHistory();

    void queueNext(const Song &song);
};
