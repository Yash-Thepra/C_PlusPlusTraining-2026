#pragma once

#include <list>
#include <string>

#include "Song.h"

class Playlist
{
public:
    Playlist(const std::string &name);

    void addSong(const Song &song);

    std::string getCreatedDate() const;

    std::list<Song>::iterator getCurrent();

    std::string getName() const;

    bool isEmpty() const;

    int getSize() const;

    std::list<Song> &getSongs();

    const std::list<Song> &getSongs() const;

    bool moveSongDown(std::list<Song>::iterator iterator);

    bool moveSongUp(std::list<Song>::iterator iterator);

    bool removeSong(std::list<Song>::iterator iterator);

    void setCurrent(std::list<Song>::iterator iterator);

private:
    std::string createdDate_;
    std::list<Song>::iterator current_;
    std::string name_;
    std::list<Song> songs_;
};
