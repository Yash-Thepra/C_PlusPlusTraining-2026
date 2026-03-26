#include <stdexcept>

#include "Constant.h"
#include "PlaylistManager.h"

PlaylistManager::PlaylistManager(IFileManager &fileManager) : activeIndex_{-1}, fileManager_{fileManager}, nameIndex_{}, playlists_{}
{
}

void PlaylistManager::createPlaylist(const std::string &name)
{
    if (nameIndex_.count(name) > 0)
    {
        throw std::invalid_argument(Constant::playlistText + name + Constant::exists);
    }
    playlists_.emplace_back(name);
    nameIndex_[name] = static_cast<int>(playlists_.size()) - Constant::one;
}

void PlaylistManager::deletePlaylist(const int index)
{
    int size = playlists_.size();
    if (index < 0 || index >= size)
    {
        throw std::out_of_range(Constant::invalidIndex);
    }
    playlists_.erase(playlists_.begin() + index);
    if (activeIndex_ == index)
    {
        activeIndex_ = -Constant::one;
    }
    else if (activeIndex_ > index)
    {
        --activeIndex_;
    }
    rebuildIndex();
    fileManager_.savePlaylists(playlists_);
}

bool PlaylistManager::loadAll()
{
    playlists_ = fileManager_.loadPlaylists();
    rebuildIndex();
    return !playlists_.empty();
}

bool PlaylistManager::saveAll()
{
    return fileManager_.savePlaylists(playlists_);
}

bool PlaylistManager::selectPlaylist(const int index)
{
    bool result = true;
    int size = playlists_.size();
    if (index < 0 || index >= size)
    {
        result = false;
    }
    else
    {
        activeIndex_ = index;
    }
    return result;
}

int PlaylistManager::getActiveIndex() const
{
    return activeIndex_;
}

Playlist *PlaylistManager::getActive() const
{
    int size = playlists_.size();
    if (activeIndex_ < 0 || activeIndex_ >= size)
    {
        return nullptr;
    }
    return const_cast<Playlist *>(&playlists_[activeIndex_]);
}

std::vector<Playlist> &PlaylistManager::getAll()
{
    return playlists_;
}

const std::vector<Playlist> &PlaylistManager::getAll() const
{
    return playlists_;
}

Playlist *PlaylistManager::findByName(const std::string &name)
{
    auto iterator = nameIndex_.find(name);
    if (iterator == nameIndex_.end())
    {
        return nullptr;
    }
    return &playlists_[iterator->second];
}

void PlaylistManager::rebuildIndex()
{
    nameIndex_.clear();
    for (int index = 0; index < playlists_.size(); index++)
    {
        nameIndex_[playlists_[index].getName()] = index;
    }
}
