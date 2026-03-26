#include <algorithm>
#include <filesystem>
#include <iostream>
#include <string>
#include <SFML/Audio.hpp>

#include "Application.h"
#include "Constant.h"
#include "Input.h"

Application::Application(IFileManager &fileManager, IPlaybackEngine &engine) : engine_(engine), fileManager_(fileManager), isRunning_(true), playlistManager_(fileManager), searchPlaylist_(Constant::searchResult)
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
    std::cout << Constant::mainMenu;
    int choice = promptMenuChoice(Constant::six);
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
    case 6:
        handleSearch();
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
    Playlist *active = playlistManager_.getActive();
    if (active != nullptr)
    {
        bool inMenu{true};
        while (inMenu)
        {
            std::cout << Constant::newLineDash << active->getName() << Constant::dashNewLine << Constant::songManagement;
            int choice = promptMenuChoice(5);
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
                inMenu = false;
                break;
            default:
                break;
            }
        }
    }
    else 
    {
        std::cout << Constant::noPlaylistSelected;
    }
}

std::vector<std::string> Application::displayResourceContent() const
{
    std::vector<std::string> files;
    std::string resourcePath = Constant::resource;
    if (!std::filesystem::exists(resourcePath))
    {
        return files;
    }
    for (auto entry : std::filesystem::directory_iterator(resourcePath))
    {
        std::string extension = entry.path().extension().string();
        if (extension == Constant::ogg || extension == Constant::wav || extension == Constant::flac)
        {
            files.push_back(entry.path().filename().string());
        }
    }
    std::sort(files.begin(), files.end());
    return files;
}

void Application::handleAddSong()
{
    auto files = displayResourceContent();
    if (files.empty())
    {
        std::cout << Constant::noAudioFiles;
        return;
    }
    std::cout << Constant::songsAvailable;
    for (int index = 0; index < files.size(); index++)
    {
        std::cout << Constant::extraSpace << (index + 1) << Constant::dotAndSpace << files[index] << Constant::newLine;
    }
    std::cout << Constant::selectFileFrom << files.size() << Constant::toCancel;
    int index = promptMenuChoice(files.size());
    if (index == 0)
    {
        return;
    }
    std::string filePath = Constant::resourceSlash + files[index - 1];
    for (auto song : playlistManager_.getActive()->getSongs())
    {
        if (song.getFilePath() == filePath)
        {
            std::cout << Constant::songExists;
            return;
        }
    }
    std::string title = std::filesystem::path(filePath).stem().string();
    sf::Music music;
    int duration = music.openFromFile(filePath) ? music.getDuration().asSeconds() : 0;
    playlistManager_.getActive()->addSong(Song(duration, filePath, title));
    playlistManager_.saveAll();
    std::cout << Constant::added << title << Constant::openingBracket << duration << Constant::newLineSecond;
}

void Application::handleCreatePlaylist()
{
    std::string name = Input::readNonEmptyString(Constant::playlistName);
    try
    {
        playlistManager_.createPlaylist(name);
        playlistManager_.saveAll();
        std::cout << Constant::playlistText << name << Constant::createdText;
    }
    catch (const std::exception &exception)
    {
        std::cout << Constant::error << exception.what() << Constant::newLine;
    }
}

void Application::handleDeletePlaylist()
{
    displayPlaylists();
    if (!playlistManager_.getAll().empty())
    {
        int size = playlistManager_.getAll().size();
        std::cout << Constant::toDeletePlaylist << size << Constant::toCancel;
        int choice = promptMenuChoice(size);
        if (choice != 0)
        {
            playlistManager_.deletePlaylist(choice - 1);
            std::cout << Constant::playlistDeleted;
        }
    }
}

void Application::handleMoveSong()
{
    Playlist *active = playlistManager_.getActive();
    if (active != nullptr && !active->isEmpty())
    {
        displaySongs();
        int size = active->getSize();
        std::cout << Constant::toMove << size << Constant::toCancel;
        int index = promptMenuChoice(size);
        if (index != 0)
        {
            std::cout << Constant::moveChoice;
            int direction = promptMenuChoice(2);
            auto iterator = active->getSongs().begin();
            std::advance(iterator, index - 1);
            bool moved = false;
            if (direction == 1)
            {
                moved = active->moveSongUp(iterator);
            }
            else if (direction == 2)
            {
                moved = active->moveSongDown(iterator);
            }
            if (moved)
            {
                playlistManager_.saveAll();
                std::cout << Constant::songMoved;
            }
            else
            {
                std::cout << Constant::cannotMove;
            }
        }
    }
    else
    {
        std::cout << Constant::noSongs;
    }
}

void Application::handlePlayback()
{
    bool inMenu = true;
    while (inMenu)
    {
        displayNowPlaying();
        std::cout << Constant::playbackMenu;
        int choice = promptMenuChoice(6);
        Playlist *active = playlistManager_.getActive();
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
                std::cout << Constant::selectPlaylistFirst;
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
            inMenu = false;
            break;
        default:
            break;
        }
    }
}

void Application::handleRemoveSong()
{
    Playlist *active = playlistManager_.getActive();
    if (active != nullptr && !active->isEmpty())
    {
        displaySongs();
        int size = static_cast<int>(active->getSize());
        std::cout << Constant::toRemove << size << Constant::toCancel;
        int index = promptMenuChoice(size);
        if (index != 0)
        {
            auto iterator = active->getSongs().begin();
            std::advance(iterator, index - 1);
            active->removeSong(iterator);
            playlistManager_.saveAll();
            std::cout << Constant::songRemoved;
        }
    }
    else
    {
        std::cout << Constant::noSongsToRemove;
    }
}

void Application::handleSelectPlaylist()
{
    displayPlaylists();
    if (!playlistManager_.getAll().empty())
    {
        int size = playlistManager_.getAll().size();
        std::cout << Constant::select << size << Constant::toCancel;
        int choice = promptMenuChoice(size);
        if (choice != 0)
        {
            if (playlistManager_.selectPlaylist(choice - 1))
            {
                engine_.setPlaylist(playlistManager_.getActive());
                std::cout << Constant::selected << playlistManager_.getActive()->getName() << Constant::newLine;
            }
        }
    }
}

void Application::displayNowPlaying() const
{
    std::cout << Constant::status << (engine_.isPlaying() ? Constant::isPlaying : Constant::isStopped) << Constant::newLine;
}

void Application::displayPlaylists() const
{
    auto all = playlistManager_.getAll();
    if (!all.empty())
    {
        std::cout << Constant::playlists;
        for (int index = 0; index < all.size(); index++)
        {
            std::cout << Constant::extraSpace << (index + 1) << Constant::dotAndSpace << all[index].getName() << Constant::openingBracket << all[index].getSize() << Constant::songs;
        }
    }
    else
    {
        std::cout << Constant::noPlaylists;
    }
}

void Application::displaySongs() const
{
    Playlist *active = playlistManager_.getActive();
    if (active != nullptr && !active->isEmpty())
    {
        std::cout << Constant::songsIn << active->getName() << Constant::newLineThird;
        int index = 1;
        for (auto song : active->getSongs())
        {
            std::cout << Constant::extraSpace << index++ << Constant::dotAndSpace << song.getTitle() << Constant::dash << song.getDuration() << Constant::newLineSecond;
        }
    }
    else
    {
        std::cout << Constant::playlistIsEmpty;
    }
}

int Application::promptMenuChoice(const int maximum)
{
    return Input::readValidInteger(maximum, 0);
}

void Application::handleSearch()
{
    std::string userInput = Input::readNonEmptyString(Constant::search);
    std::transform(userInput.begin(), userInput.end(), userInput.begin(), ::tolower);
    if (playlistManager_.getActive() == nullptr)
    {
        searchInResource(userInput);
    }
    else
    {
        searchInPlaylist(userInput);
    }
}

void Application::searchInResource(const std::string &userInput)
{
    auto allFiles = displayResourceContent();
    std::vector<std::string> results;
    for (auto file : allFiles)
    {
        std::string lower = file;
        std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
        if (lower.find(userInput) != std::string::npos)
        {
            results.push_back(file);
        }
    }
    if (!results.empty())
    {
        std::cout << Constant::searchResultTwo;
        for (int index = 0; index < results.size(); index++)
        {
            std::cout << Constant::extraSpace << (index + 1) << Constant::dotAndSpace << std::filesystem::path(results[index]).stem().string() << Constant::newLine;
        }
        std::cout << Constant::selectToPlay << results.size() << Constant::toCancel;
        int index = promptMenuChoice(results.size());
        if (index != 0)
        {
            std::string filePath = Constant::resourceSlash + results[index - 1];
            std::string title = std::filesystem::path(filePath).stem().string();
            sf::Music music;
            int duration = music.openFromFile(filePath) ? music.getDuration().asSeconds() : Constant::zero;
            searchPlaylist_.getSongs().clear();
            searchPlaylist_.addSong(Song(duration, filePath, title));
            searchPlaylist_.setCurrent(searchPlaylist_.getSongs().begin());
            engine_.setPlaylist(&searchPlaylist_);
            engine_.play();
            handlePlayback();
        }
    }
    else
    {
        std::cout << Constant::noMatchingSong;
    }
}

void Application::searchInPlaylist(const std::string &userInput)
{
    std::vector<std::list<Song>::iterator> results;
    Playlist *active = playlistManager_.getActive();
    for (auto iterator = active->getSongs().begin(); iterator != active->getSongs().end(); iterator++)
    {
        std::string lower = iterator->getTitle();
        std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
        if (lower.find(userInput) != std::string::npos)
        {
            results.push_back(iterator);
        }
    }
    if (!results.empty())
    {
        std::cout << Constant::searchResultTwo;
        for (int index = 0; index < results.size(); index++)
        {
            std::cout << Constant::extraSpace << (index + 1) << Constant::dotAndSpace << results[index]->getTitle() << Constant::newLine;
        }
        std::cout << Constant::selectToPlay << results.size() << Constant::toCancel;
        int index = promptMenuChoice(results.size());
        if (index != 0)
        {
            active->setCurrent(results[index - 1]);
            engine_.setPlaylist(active);
            engine_.play();
            handlePlayback();
        }
    }
    else
    {
        std::cout << Constant::noMatchingSong;
    }
}
