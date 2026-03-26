#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <string>
#include <vector>

#include "Mocks.h"
#include "Playlist.h"
#include "Song.h"

using ::testing::_;
class GivenAnFileManagerGtest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        mockFM_   = std::make_unique<MockFileManager>();
        playlist_ = std::make_unique<Playlist>("Test Playlist");
        playlist_->addSong(Song(180, "a.mp3", "Song A" ));
        playlist_->addSong(Song(200, "b.mp3", "Song B" ));
    }

    std::unique_ptr<MockFileManager> mockFM_;
    std::unique_ptr<Playlist>        playlist_;
};

TEST_F(GivenAnFileManagerGtest, WhenFileExists_ThenReturnsTrueForExistingFile)
{
    EXPECT_CALL(*mockFM_, fileExists("playlists.txt"))
        .WillOnce(::testing::Return(true));

    EXPECT_TRUE(mockFM_->fileExists("playlists.txt"));
}

TEST_F(GivenAnFileManagerGtest, WhenLoadPlaylists_ThenReturnsMultiplePlaylists)
{
    std::vector<Playlist> stored{};
    stored.emplace_back("Playlist One");
    stored.emplace_back("Playlist Two");

    EXPECT_CALL(*mockFM_, loadPlaylists())
        .WillOnce(::testing::Return(stored));

    const auto result{ mockFM_->loadPlaylists() };
    EXPECT_EQ(result.size(), 2u);
}

TEST_F(GivenAnFileManagerGtest, WhenLoadPlaylists_ThenReturnsStoredName)
{
    std::vector<Playlist> stored{};
    stored.emplace_back("Stored");

    EXPECT_CALL(*mockFM_, loadPlaylists())
        .WillOnce(::testing::Return(stored));

    const auto result{ mockFM_->loadPlaylists() };
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result.front().getName(), "Stored");
}

TEST_F(GivenAnFileManagerGtest, WhenSaveCalledExactlyOnce)
{
    std::vector<Playlist> pls{};
    pls.emplace_back("Once");

    EXPECT_CALL(*mockFM_, savePlaylists(_))
        .Times(1)
        .WillOnce(::testing::Return(true));

    mockFM_->savePlaylists(pls);
}

TEST_F(GivenAnFileManagerGtest, WhenSavePlaylists_ThenReturnsTrueOnSuccess)
{
    std::vector<Playlist> pls{};
    pls.emplace_back("Alpha");

    EXPECT_CALL(*mockFM_, savePlaylists(_))
        .WillOnce(::testing::Return(true));

    EXPECT_TRUE(mockFM_->savePlaylists(pls));
}

TEST_F(GivenAnFileManagerGtest, WhenFileExists_ThenReturnsFalseForMissingFile)
{
    EXPECT_CALL(*mockFM_, fileExists("missing.txt"))
        .WillOnce(::testing::Return(false));

    EXPECT_FALSE(mockFM_->fileExists("missing.txt"));
}

TEST_F(GivenAnFileManagerGtest, WhneLoadPlaylists_ThenReturnsEmptyWhenNoFile)
{
    EXPECT_CALL(*mockFM_, loadPlaylists())
        .WillOnce(::testing::Return(std::vector<Playlist>{}));

    EXPECT_TRUE(mockFM_->loadPlaylists().empty());
}

TEST_F(GivenAnFileManagerGtest, WhenSavePlaylists_ThenReturnsFalseOnFailure)
{
    std::vector<Playlist> pls{};

    EXPECT_CALL(*mockFM_, savePlaylists(_))
        .WillOnce(::testing::Return(false));

    EXPECT_FALSE(mockFM_->savePlaylists(pls));
}

struct FileExistsParam
{
    bool        expected;
    std::string path;
};

class GivenAnFileExistsParamGtest
    : public ::testing::TestWithParam<FileExistsParam>
{
protected:
    void SetUp() override
    {
        mockFM_ = std::make_unique<MockFileManager>();
    }

    std::unique_ptr<MockFileManager> mockFM_;
};

TEST_P(GivenAnFileExistsParamGtest, WhenFileExists_ThenReturnsExpectedResult)
{
    const auto& p{ GetParam() };

    EXPECT_CALL(*mockFM_, fileExists(p.path))
        .WillOnce(::testing::Return(p.expected));

    EXPECT_EQ(mockFM_->fileExists(p.path), p.expected);
}

INSTANTIATE_TEST_SUITE_P(
    FileExistsCases,
    GivenAnFileExistsParamGtest,
    ::testing::Values(
        FileExistsParam{ false, "missing.txt"},
        FileExistsParam{ false, "nonexistent/x.txt"},
        FileExistsParam{ true,  "data/save.txt"},
        FileExistsParam{ true,  "playlists.txt"}
    )
);
