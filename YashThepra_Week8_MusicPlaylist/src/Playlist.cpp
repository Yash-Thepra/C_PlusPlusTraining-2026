#include <chrono>
#include <iomanip>
#include <iterator>
#include <sstream>

#include "Playlist.h"

static std::string currentDateString()
{
    auto now = std::chrono::system_clock::now();
    const time_t time = std::chrono::system_clock::to_time_t(now);
    std::ostringstream oss;
    oss << std::put_time(std::localtime(&time), "%Y-%m-%d");
    return oss.str();
}

Playlist::Playlist(const std::string &name) : createdDate_{currentDateString()}, current_{}, name_{name}, songs_{}
{
    current_ = songs_.end();
}

std::list<Song>::iterator Playlist::getCurrent()
{
    return current_;
}

void Playlist::setCurrent(std::list<Song>::iterator iterator)
{
    current_ = iterator;
}

std::string Playlist::getCreatedDate() const
{
    return createdDate_;
}

void Playlist::addSong(const Song &song)
{
    songs_.push_back(song);
}

std::string Playlist::getName() const
{
    return name_;
}

bool Playlist::isEmpty() const
{
    return songs_.empty();
}

int Playlist::getSize() const
{
    return songs_.size();
}

std::list<Song> &Playlist::getSongs()
{
    return songs_;
}

const std::list<Song> &Playlist::getSongs() const
{
    return songs_;
}

bool Playlist::moveSongDown(std::list<Song>::iterator iterator)
{
    bool result = true;
    if (iterator == songs_.end())
    {
        result = false;
    }
    else
    {
        std::list<Song>::iterator next = std::next(iterator);
        if (next == songs_.end())
        {
            result = false;
        }
        else
        {
            songs_.splice(std::next(next), songs_, iterator);
        }
    }
    return result;
}

bool Playlist::moveSongUp(std::list<Song>::iterator iterator)
{
    bool result = true;
    if (iterator == songs_.begin() || iterator == songs_.end())
    {
        result = false;
    }
    else
    {
        std::list<Song>::iterator prev = std::prev(iterator);
        songs_.splice(prev, songs_, iterator);
    }
    return result;
}

bool Playlist::removeSong(std::list<Song>::iterator iterator)
{
    bool result = true;
    if (iterator == songs_.end())
    {
        result = false;
    }
    else
    {
        songs_.erase(iterator);
    }
    return result;
}
