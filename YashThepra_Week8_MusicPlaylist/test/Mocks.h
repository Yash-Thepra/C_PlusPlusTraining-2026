#pragma once

#include <gmock/gmock.h>
#include <string>
#include <vector>

#include "IFileManager.h"
#include "IPlaybackEngine.h"

class MockFileManager : public IFileManager
{
public:
    MOCK_METHOD(bool, fileExists, (const std::string &path), (const, override));

    MOCK_METHOD(std::vector<Playlist>, loadPlaylists, (), (override));

    MOCK_METHOD(bool, savePlaylists, (const std::vector<Playlist> &playlists), (override));
};

class MockPlaybackEngine : public IPlaybackEngine
{
public:
    MOCK_METHOD(bool, isPlaying, (), (const, override));

    MOCK_METHOD(void, nextSong, (), (override));

    MOCK_METHOD(void, pause, (), (override));

    MOCK_METHOD(void, play, (), (override));
    
    MOCK_METHOD(void, previousSong, (), (override));

    MOCK_METHOD(void, resume, (), (override));

    MOCK_METHOD(void, setPlaylist, (Playlist * playlist), (override));

    MOCK_METHOD(void, stop, (), (override));
};
