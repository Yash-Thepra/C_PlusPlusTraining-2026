#pragma once

#include <string>
#include <vector>

#include "Playlist.h"

class IFileManager
{
public:
    virtual ~IFileManager() {};

    virtual bool fileExists(const std::string &path) const = 0;

    virtual std::vector<Playlist> loadPlaylists() = 0;

    virtual bool savePlaylists(const std::vector<Playlist> &playlists) = 0;
};
