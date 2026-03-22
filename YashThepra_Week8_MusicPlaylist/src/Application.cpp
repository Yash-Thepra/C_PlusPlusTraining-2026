#include <iostream>
#include <string>

#include "Application.h"
#include "Input.h"

Application::Application(IFileManager &fileManager, IPlaybackEngine &engine) : engine_{engine}, fileManager_{fileManager}, isRunning_{true}, menuHistory_{}, menuOptions_{},playlistManager_{fileManager}
{
    playlistManager_.loadAll();
}

Application::~Application()
{
    playlistManager_.saveAll();
}

void Application::run()
{
    while (isRunning_)
    {
        showMainMenu();
    }
}

void Application::showMainMenu()
{
    std::cout << "\n===== Music Playlist =====\n"
              << "  1. Create playlist\n"
              << "  2. Select playlist\n"
              << "  3. Delete playlist\n"
              << "  4. Song management\n"
              << "  5. Playback controls\n"
              << "  0. Exit\n"
              << "Choice: ";
    const int choice{promptMenuChoice(5)};
    switch (choice)
    {
    case 1:
        handleCreatePlaylist();
        break;
    case 2:
        handleSelectPlaylist();
        break;
    case 3:
        handleDeletePlaylist();
        break;
    case 4:
        showPlaylistMenu();
        break;
    case 5:
        handlePlayback();
        break;
    case 0:
        isRunning_ = false;
        break;
    default:
        break;
    }
}

void Application::showPlaylistMenu()
{
    Playlist *active{playlistManager_.getActive()};
    if (active == nullptr)
    {
        std::cout << "  No playlist selected. Please select one first.\n";
        return;
    }
    std::cout << "\n--- " << active->getName() << " ---\n"
              << "  1. Add song\n"
              << "  2. Remove song\n"
              << "  3. Move song up\n"
              << "  4. Move song down\n"
              << "  5. Display songs\n"
              << "  0. Back\n"
              << "Choice: ";
    const int choice{promptMenuChoice(5)};
    switch (choice)
    {
    case 1:
        handleAddSong();
        break;
    case 2:
        handleRemoveSong();
        break;
    case 3:
        handleMoveSong();
        break;
    case 4:
        handleMoveSong();
        break;
    case 5:
        displaySongs();
        break;
    case 0:
        break;
    default:
        break;
    }
}

void Application::handleAddSong()
{
    const std::string artist{Input::getString("  Artist       : ")};
    const std::string filePath{Input::getString("  File path    : ")};
    const std::string title{Input::getString("  Song title   : ")};
    std::cout << "  Duration (sec): ";
    const int duration{Input::getInt(3600, 1)};
    playlistManager_.getActive()->addSong(Song{artist, duration, filePath, title});
    playlistManager_.saveAll();
    std::cout << "  Song '" << title << "' added.\n";
}

void Application::handleCreatePlaylist()
{
    const std::string name{Input::getString("  Playlist name: ")};
    try
    {
        playlistManager_.createPlaylist(name);
        playlistManager_.saveAll();
        std::cout << "  Playlist '" << name << "' created.\n";
    }
    catch (const std::exception &e)
    {
        std::cout << "  Error: " << e.what() << '\n';
    }
}

void Application::handleDeletePlaylist()
{
    displayPlaylists();
    if (playlistManager_.getAll().empty())
    {
        return;
    }
    const int maximum{static_cast<int>(playlistManager_.getAll().size())};
    std::cout << "  Select playlist to delete (1-" << maximum << ", 0 to cancel): ";
    const int choice{promptMenuChoice(maximum)};
    if (choice == 0)
    {
        return;
    }
    playlistManager_.deletePlaylist(choice - 1);
    std::cout << "  Playlist deleted.\n";
}

void Application::handleMoveSong()
{
    Playlist *active{playlistManager_.getActive()};
    if (active == nullptr || active->isEmpty())
    {
        std::cout << "  No songs to move.\n";
        return;
    }
    displaySongs();
    const int maximum{static_cast<int>(active->size())};
    std::cout << "  Song number to move (1-" << maximum << ", 0 to cancel): ";
    const int idx{promptMenuChoice(maximum)};
    if (idx == 0)
    {
        return;
    }
    std::cout << "  1. Move up   2. Move down   0. Cancel\n  Choice: ";
    const int dir{promptMenuChoice(2)};
    auto it{active->getSongs().begin()};
    std::advance(it, idx - 1);
    bool moved{false};
    if (dir == 1)
    {
        moved = active->moveSongUp(it);
    }
    else if (dir == 2)
    {
        moved = active->moveSongDown(it);
    }
    if (moved)
    {
        playlistManager_.saveAll();
        std::cout << "  Song moved.\n";
    }
    else
    {
        std::cout << "  Cannot move further in that direction.\n";
    }
}

void Application::handlePlayback()
{
    displayNowPlaying();
    std::cout << "  1. Play    2. Pause    3. Resume\n"
              << "  4. Stop    5. Next     6. Previous\n"
              << "  0. Back\n"
              << "  Choice: ";
    const int choice{promptMenuChoice(6)};
    Playlist *active{playlistManager_.getActive()};
    switch (choice)
    {
    case 1:
    {
        if (active != nullptr)
        {
            engine_.setPlaylist(active);
            engine_.play();
        }
        else
        {
            std::cout << "  Select a playlist first.\n";
        }
        break;
    }
    case 2:
        engine_.pause();
        break;
    case 3:
        engine_.resume();
        break;
    case 4:
        engine_.stop();
        break;
    case 5:
        engine_.nextSong();
        break;
    case 6:
        engine_.previousSong();
        break;
    case 0:
        break;
    default:
        break;
    }
}

void Application::handleRemoveSong()
{
    Playlist *active{playlistManager_.getActive()};
    if (active == nullptr || active->isEmpty())
    {
        std::cout << "  No songs to remove.\n";
        return;
    }
    displaySongs();
    const int maximum{static_cast<int>(active->size())};
    std::cout << "  Song number to remove (1-" << maximum << ", 0 to cancel): ";
    const int idx{promptMenuChoice(maximum)};
    if (idx == 0)
    {
        return;
    }
    auto it{active->getSongs().begin()};
    std::advance(it, idx - 1);
    active->removeSong(it);
    playlistManager_.saveAll();
    std::cout << "  Song removed.\n";
}

void Application::handleSelectPlaylist()
{
    displayPlaylists();
    if (playlistManager_.getAll().empty())
    {
        return;
    }
    const int maximum{static_cast<int>(playlistManager_.getAll().size())};
    std::cout << "  Select (1-" << maximum << ", 0 to cancel): ";
    const int choice{promptMenuChoice(maximum)};
    if (choice == 0)
    {
        return;
    }
    if (playlistManager_.selectPlaylist(choice - 1))
    {
        engine_.setPlaylist(playlistManager_.getActive());
        std::cout << "  Selected: " << playlistManager_.getActive()->getName() << '\n';
    }
}

void Application::displayNowPlaying() const
{
    std::cout << "\n  Status: " << (engine_.isPlaying() ? "Playing" : "Stopped") << '\n';
}

void Application::displayPlaylists() const
{
    const auto &all{playlistManager_.getAll()};
    if (all.empty())
    {
        std::cout << "  No playlists yet.\n";
        return;
    }
    std::cout << "\n  Playlists:\n";
    for (int i{0}; i < static_cast<int>(all.size()); ++i)
    {
        std::cout << "    " << (i + 1) << ". " << all[i].getName() << "  (" << all[i].size() << " songs)\n";
    }
}

void Application::displaySongs() const
{
    Playlist *active{playlistManager_.getActive()};
    if (active == nullptr || active->isEmpty())
    {
        std::cout << "  Playlist is empty.\n";
        return;
    }
    std::cout << "\n  Songs in '" << active->getName() << "':\n";
    int i = 1;
    for (const auto &song : active->getSongs())
    {
        std::cout << "    " << i++ << ". " << song.getTitle() << " - " << song.getArtist() << "  (" << song.getDuration() << "s)\n";
    }
}

int Application::promptMenuChoice(const int maximum)
{
    return Input::getInt(maximum, 0);
}
