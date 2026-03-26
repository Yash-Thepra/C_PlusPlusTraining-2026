#pragma once

#include <string>
#include <vector>

#include "IFileManager.h"
#include "IPlaybackEngine.h"
#include "Playlist.h"
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
    std::vector<std::string> mainMenu_;
    PlaylistManager playlistManager_;
    Playlist searchPlaylist_;
    
    void handleAddSong();

    void handleCreatePlaylist();

    void handleDeletePlaylist();

    void handleMoveSong();

    void handlePlayback();

    void handleRemoveSong();

    void handleSelectPlaylist();

    void handleSearch();

    void searchInPlaylist(const std::string& userInput);

    void searchInResource(const std::string& userInput);
    
    void displayNowPlaying() const;

    void displayPlaylists() const;

    void displaySongs() const;

    int promptMenuChoice(const int maximum);

    void showMainMenu();

    void showPlaylistMenu();

    std::vector<std::string> displayResourceContent() const;
};
