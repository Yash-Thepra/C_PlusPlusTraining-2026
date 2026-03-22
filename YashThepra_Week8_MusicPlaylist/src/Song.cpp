#include "Song.h"

Song::Song(const std::string &artist, const int duration, const std::string &filePath, const std::string &title) : artist_{artist}, duration_{duration}, filePath_{filePath}, title_{title}
{
}

std::string Song::getArtist() const
{
    return artist_;
}

int Song::getDuration() const
{
    return duration_;
}

std::string Song::getFilePath() const
{
    return filePath_;
}

std::string Song::getTitle() const
{
    return title_;
}
