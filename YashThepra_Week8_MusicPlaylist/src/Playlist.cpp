#include <chrono>
#include <iomanip>
#include <iterator>
#include <sstream>

#include "Playlist.h"

static std::string currentDateString()
{
    const auto now{std::chrono::system_clock::now()};
    const std::time_t t{std::chrono::system_clock::to_time_t(now)};
    std::ostringstream oss{};
    oss << std::put_time(std::localtime(&t), "%Y-%m-%d");
    return oss.str();
}

Playlist::Playlist(const std::string &name) : createdDate_{currentDateString()}, name_{name}, songs_{}
{
}

Playlist::Playlist(const std::string &createdDate, const std::string &name) : createdDate_{createdDate}, name_{name}, songs_{}
{
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

std::size_t Playlist::size() const
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

bool Playlist::moveSongDown(std::list<Song>::iterator it)
{
    if (it == songs_.end())
    {
        return false;
    }
    std::list<Song>::iterator next{std::next(it)};
    if (next == songs_.end())
    {
        return false;
    }
    songs_.splice(std::next(next), songs_, it);
    return true;
}

bool Playlist::moveSongUp(std::list<Song>::iterator it)
{
    if (it == songs_.begin() || it == songs_.end())
    {
        return false;
    }
    std::list<Song>::iterator prev{std::prev(it)};
    songs_.splice(prev, songs_, it);
    return true;
}

bool Playlist::removeSong(std::list<Song>::iterator it)
{
    if (it == songs_.end())
    {
        return false;
    }
    songs_.erase(it);
    return true;
}
