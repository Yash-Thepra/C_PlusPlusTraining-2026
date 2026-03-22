#pragma once

#include <list>
#include <string>

#include "Song.h"

class Playlist
{
public:
    Playlist(const std::string &name);

    Playlist(const std::string &createdDate, const std::string &name);

    void addSong(const Song &song);

    std::string getCreatedDate() const;

    std::string getName() const;

    bool isEmpty() const;

    std::size_t size() const;

    std::list<Song> &getSongs();

    const std::list<Song> &getSongs() const;

    bool moveSongDown(std::list<Song>::iterator it);

    bool moveSongUp(std::list<Song>::iterator it);

    bool removeSong(std::list<Song>::iterator it);

private:
    std::string createdDate_;
    std::string name_;
    std::list<Song> songs_;
};
