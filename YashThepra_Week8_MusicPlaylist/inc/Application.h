#pragma once

#include <stack>
#include <string>
#include <vector>

#include "IFileManager.h"
#include "IPlaybackEngine.h"
#include "PlaylistManager.h"

class Application
{
public:
    Application(IFileManager &fileManager, IPlaybackEngine &engine);

    ~Application();

    void run();

private:
    IPlaybackEngine &engine_;
    IFileManager &fileManager_;
    bool isRunning_;
    std::stack<std::string> menuHistory_;
    std::vector<std::string> menuOptions_;
    PlaylistManager playlistManager_;

    void handleAddSong();

    void handleCreatePlaylist();

    void handleDeletePlaylist();

    void handleMoveSong();

    void handlePlayback();

    void handleRemoveSong();

    void handleSelectPlaylist();

    void displayNowPlaying() const;

    void displayPlaylists() const;

    void displaySongs() const;

    int promptMenuChoice(const int max);

    void showMainMenu();

    void showPlaylistMenu();
};
