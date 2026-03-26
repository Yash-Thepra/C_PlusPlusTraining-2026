#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "IFileManager.h"
#include "Playlist.h"

class PlaylistManager
{
public:
    PlaylistManager(IFileManager &fileManager);

    void createPlaylist(const std::string &name);

    void deletePlaylist(const int index);

    bool loadAll();

    bool saveAll();

    bool selectPlaylist(const int index);

    int getActiveIndex() const;

    Playlist *getActive() const;

    std::vector<Playlist> &getAll();

    const std::vector<Playlist> &getAll() const;

    Playlist *findByName(const std::string &name);

private:
    int activeIndex_;
    IFileManager &fileManager_;
    std::unordered_map<std::string, int> nameIndex_;
    std::vector<Playlist> playlists_;

    void rebuildIndex();
};
