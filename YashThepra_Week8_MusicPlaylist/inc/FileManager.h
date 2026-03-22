#pragma once

#include <fstream>
#include <queue>
#include <string>
#include <vector>

#include "IFileManager.h"

class FileManager : public IFileManager
{
public:
    FileManager(const std::string &savePath, const char delimiter = '|');

    bool fileExists(const std::string &path) const override;

    std::vector<Playlist> loadPlaylists() override;

    bool savePlaylists(const std::vector<Playlist> &playlists) override;

private:
    char delimiter_;
    std::ifstream inStream_;
    std::ofstream outStream_;
    std::string savePath_;
    std::queue<std::string> writeBuffer_;

    void flushBuffer();

    Song parseSongLine(const std::string &line) const;

    std::string serialiseSong(const Song &song) const;
};
