#include <gtest/gtest.h>
#include <string>

#include "Playlist.h"
#include "Song.h"

class PlaylistGtest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        playlist_ = std::make_unique<Playlist>("My Playlist");
        songA_ = Song{"Artist A", 180, "a.mp3", "Song A"};
        songB_ = Song{"Artist B", 200, "b.mp3", "Song B"};
        songC_ = Song{"Artist C", 220, "c.mp3", "Song C"};
    }
    std::unique_ptr<Playlist> playlist_;
    Song songA_{"A", 1, "a.mp3", "A"};
    Song songB_{"B", 1, "b.mp3", "B"};
    Song songC_{"C", 1, "c.mp3", "C"};
};

TEST_F(PlaylistGtest, AddSongIncreasesSize)
{
    playlist_->addSong(songA_);
    EXPECT_EQ(playlist_->size(), 1u);
}

TEST_F(PlaylistGtest, AddMultipleSongsTracksCorrectSize)
{
    playlist_->addSong(songA_);
    playlist_->addSong(songB_);
    playlist_->addSong(songC_);
    EXPECT_EQ(playlist_->size(), 3u);
}

TEST_F(PlaylistGtest, GetNameReturnsCorrectName)
{
    EXPECT_EQ(playlist_->getName(), "My Playlist");
}

TEST_F(PlaylistGtest, IsEmptyOnNewPlaylist)
{
    EXPECT_TRUE(playlist_->isEmpty());
    EXPECT_EQ(playlist_->size(), 0u);
}

TEST_F(PlaylistGtest, IsEmptyReturnsFalseAfterAdd)
{
    playlist_->addSong(songA_);
    EXPECT_FALSE(playlist_->isEmpty());
}

TEST_F(PlaylistGtest, MoveSongDownChangesOrder)
{
    playlist_->addSong(songA_);
    playlist_->addSong(songB_);

    auto it{playlist_->getSongs().begin()};
    const bool moved{playlist_->moveSongDown(it)};

    EXPECT_TRUE(moved);
    EXPECT_EQ(playlist_->getSongs().front().getTitle(), "Song B");
}

TEST_F(PlaylistGtest, MoveSongUpChangesOrder)
{
    playlist_->addSong(songA_);
    playlist_->addSong(songB_);

    auto it{playlist_->getSongs().begin()};
    std::advance(it, 1);
    const bool moved{playlist_->moveSongUp(it)};

    EXPECT_TRUE(moved);
    EXPECT_EQ(playlist_->getSongs().front().getTitle(), "Song B");
}

TEST_F(PlaylistGtest, RemoveSongDecreasesSize)
{
    playlist_->addSong(songA_);
    auto it{playlist_->getSongs().begin()};

    EXPECT_TRUE(playlist_->removeSong(it));
    EXPECT_TRUE(playlist_->isEmpty());
}

TEST_F(PlaylistGtest, MoveSongDownOnLastElementReturnsFalse)
{
    playlist_->addSong(songA_);
    auto it{playlist_->getSongs().begin()};
    EXPECT_FALSE(playlist_->moveSongDown(it));
}

TEST_F(PlaylistGtest, MoveSongUpOnFirstElementReturnsFalse)
{
    playlist_->addSong(songA_);
    auto it{playlist_->getSongs().begin()};
    EXPECT_FALSE(playlist_->moveSongUp(it));
}

TEST_F(PlaylistGtest, RemoveSongOnEndIteratorReturnsFalse)
{
    auto it{playlist_->getSongs().end()};
    EXPECT_FALSE(playlist_->removeSong(it));
}

class PlaylistSizeParamGtest : public ::testing::TestWithParam<int>
{
};

TEST_P(PlaylistSizeParamGtest, SizeMatchesNumberOfSongsAdded)
{
    Playlist pl{"Param Playlist"};
    const int count{GetParam()};

    for (int i{0}; i < count; ++i)
    {
        pl.addSong(Song{"Artist", 100, "f.mp3", "Title" + std::to_string(i)});
    }

    EXPECT_EQ(static_cast<int>(pl.size()), count);
}

INSTANTIATE_TEST_SUITE_P(
    VariousSizes,
    PlaylistSizeParamGtest,
    ::testing::Values(0, 1, 3, 5, 10
));
