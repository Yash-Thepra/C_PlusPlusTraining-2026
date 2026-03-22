#include <filesystem>
#include <sstream>
#include <stdexcept>
#include <string>

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
    std::vector<Playlist> playlists{};
    if (!fileExists(savePath_))
    {
        return playlists;
    }
    inStream_.open(savePath_);
    if (!inStream_.is_open())
    {
        return playlists;
    }
    std::string line{};
    Playlist *current{nullptr};
    while (std::getline(inStream_, line))
    {
        if (line.empty())
        {
            continue;
        }
        if (line.rfind("PLAYLIST:", 0) == 0)
        {
            playlists.emplace_back(line.substr(9));
            current = &playlists.back();
        }
        else if (current != nullptr)
        {
            current->addSong(parseSongLine(line));
        }
    }
    inStream_.close();
    return playlists;
}

bool FileManager::savePlaylists(const std::vector<Playlist> &playlists)
{
    for (const auto &pl : playlists)
    {
        writeBuffer_.push("PLAYLIST:" + pl.getName());

        for (const auto &song : pl.getSongs())
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
        throw std::runtime_error("Cannot open save file: " + savePath_);
    }
    while (!writeBuffer_.empty())
    {
        outStream_ << writeBuffer_.front() << '\n';
        writeBuffer_.pop();
    }
    outStream_.close();
}

Song FileManager::parseSongLine(const std::string &line) const
{
    std::stringstream ss{line};
    std::string artist{};
    std::string durationStr{};
    std::string filePath{};
    std::string title{};

    std::getline(ss, title, delimiter_);
    std::getline(ss, artist, delimiter_);
    std::getline(ss, durationStr, delimiter_);
    std::getline(ss, filePath, delimiter_);

    const int duration{durationStr.empty() ? 0 : std::stoi(durationStr)};
    return Song{artist, duration, filePath, title};
}

std::string FileManager::serialiseSong(const Song &song) const
{
    return song.getTitle() + delimiter_ + song.getArtist() + delimiter_ + std::to_string(song.getDuration()) + delimiter_ + song.getFilePath();
}
