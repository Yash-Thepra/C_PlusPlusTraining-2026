#pragma once

#include <string>

class Song
{
public:
    Song(const int duration, const std::string &filePath, const std::string &title);

    int getDuration() const;

    std::string getFilePath() const;

    std::string getTitle() const;

private:
    int duration_;
    std::string filePath_;
    std::string title_;
};
