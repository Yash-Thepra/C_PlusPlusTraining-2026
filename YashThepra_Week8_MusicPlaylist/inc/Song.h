#pragma once

#include <string>

class Song
{
public:
    Song(const std::string &artist, const int duration, const std::string &filePath, const std::string &title);

    std::string getArtist() const;

    int getDuration() const;

    std::string getFilePath() const;

    std::string getTitle() const;

private:
    std::string artist_;
    int duration_;
    std::string filePath_;
    std::string title_;
};
