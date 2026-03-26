#include "Song.h"

Song::Song(const int duration, const std::string &filePath, const std::string &title) : duration_{duration}, filePath_{filePath}, title_{title}
{
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
