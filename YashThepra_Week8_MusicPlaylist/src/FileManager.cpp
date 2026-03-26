#include <filesystem>
#include <sstream>
#include <stdexcept>
#include <string>

#include "Constant.h"
#include "FileManager.h"

FileManager::FileManager(const std::string &savePath, const char delimiter) : delimiter_{delimiter}, inStream_{}, outStream_{}, savePath_{savePath}, writeBuffer_{}
{
}

bool FileManager::fileExists(const std::string &path) const
{
    return std::filesystem::exists(path);
}

std::vector<Playlist> FileManager::loadPlaylists()
{
    std::vector<Playlist> playlists;
    inStream_.open(savePath_);
    if (inStream_.is_open() && fileExists(savePath_))
    {
        std::string line;
        Playlist *current = nullptr;
        while (std::getline(inStream_, line))
        {
            if (line.empty())
            {
                continue;
            }
            if (line.rfind(Constant::playlistTextTwo, Constant::zero) == Constant::zero)
            {
                playlists.emplace_back(line.substr(Constant::nine));
                current = &playlists.back();
            }
            else if (current != nullptr)
            {
                current->addSong(parseSongLine(line));
            }
        }
        inStream_.close();
    }
    return playlists;
}

bool FileManager::savePlaylists(const std::vector<Playlist> &playlists)
{
    for (auto iterator : playlists)
    {
        writeBuffer_.push(Constant::playlistTextTwo + iterator.getName());
        for (auto song : iterator.getSongs())
        {
            writeBuffer_.push(serialiseSong(song));
        }
    }
    flushBuffer();
    return true;
}

void FileManager::flushBuffer()
{
    outStream_.open(savePath_, std::ios::trunc);
    if (!outStream_.is_open())
    {
        throw std::runtime_error(Constant::runtimeErrorFirst + savePath_);
    }
    while (!writeBuffer_.empty())
    {
        outStream_ << writeBuffer_.front() << Constant::newLineChar;
        writeBuffer_.pop();
    }
    outStream_.close();
}

Song FileManager::parseSongLine(const std::string &line) const
{
    std::stringstream ss{line};
    std::string duration;
    std::string filePath;
    std::string title;

    std::getline(ss, title, delimiter_);
    std::getline(ss, duration, delimiter_);
    std::getline(ss, filePath, delimiter_);

    int durationFinal = duration.empty() ? 0 : std::stoi(duration);
    return Song(durationFinal, filePath, title);
}

std::string FileManager::serialiseSong(const Song &song) const
{
    return song.getTitle() + delimiter_ + std::to_string(song.getDuration()) + delimiter_ + song.getFilePath();
}
