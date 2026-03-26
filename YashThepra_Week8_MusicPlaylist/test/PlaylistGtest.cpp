#include <gtest/gtest.h>
#include <string>

#include "Playlist.h"
#include "Song.h"

class GivenAnPlaylistGtest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        playlist_ = std::make_unique<Playlist>("My Playlist");
        songA_ = Song{180, "a.mp3", "Song A"};
        songB_ = Song{200, "b.mp3", "Song B"};
        songC_ = Song{220, "c.mp3", "Song C"};
    }
    std::unique_ptr<Playlist> playlist_;
    Song songA_{1, "a.mp3", "A"};
    Song songB_{1, "b.mp3", "B"};
    Song songC_{1, "c.mp3", "C"};
};

TEST_F(GivenAnPlaylistGtest, WhenAddSong_ThenIncreasesSize)
{
    playlist_->addSong(songA_);
    EXPECT_EQ(playlist_->getSize(), 1u);
}

TEST_F(GivenAnPlaylistGtest, WhenAddMultipleSongs_ThenTracksCorrectSize)
{
    playlist_->addSong(songA_);
    playlist_->addSong(songB_);
    playlist_->addSong(songC_);
    EXPECT_EQ(playlist_->getSize(), 3u);
}

TEST_F(GivenAnPlaylistGtest, WhenGetName_ThenReturnsCorrectName)
{
    EXPECT_EQ(playlist_->getName(), "My Playlist");
}

TEST_F(GivenAnPlaylistGtest, WhenIsEmptyOnNewPlaylist)
{
    EXPECT_TRUE(playlist_->isEmpty());
    EXPECT_EQ(playlist_->getSize(), 0u);
}

TEST_F(GivenAnPlaylistGtest, WhenIsEmpty_ThenReturnsFalseAfterAdd)
{
    playlist_->addSong(songA_);
    EXPECT_FALSE(playlist_->isEmpty());
}

TEST_F(GivenAnPlaylistGtest, WhenMoveSongDown_ThenChangesOrder)
{
    playlist_->addSong(songA_);
    playlist_->addSong(songB_);

    auto it{playlist_->getSongs().begin()};
    const bool moved{playlist_->moveSongDown(it)};

    EXPECT_TRUE(moved);
    EXPECT_EQ(playlist_->getSongs().front().getTitle(), "Song B");
}

TEST_F(GivenAnPlaylistGtest, WhenMoveSongUp_ThenChangesOrder)
{
    playlist_->addSong(songA_);
    playlist_->addSong(songB_);

    auto it{playlist_->getSongs().begin()};
    std::advance(it, 1);
    const bool moved{playlist_->moveSongUp(it)};

    EXPECT_TRUE(moved);
    EXPECT_EQ(playlist_->getSongs().front().getTitle(), "Song B");
}

TEST_F(GivenAnPlaylistGtest, WhenRemoveSong_ThenDecreasesSize)
{
    playlist_->addSong(songA_);
    auto it{playlist_->getSongs().begin()};

    EXPECT_TRUE(playlist_->removeSong(it));
    EXPECT_TRUE(playlist_->isEmpty());
}

TEST_F(GivenAnPlaylistGtest, WhenMoveSongDownOnLastElement_ThenReturnsFalse)
{
    playlist_->addSong(songA_);
    auto it{playlist_->getSongs().begin()};
    EXPECT_FALSE(playlist_->moveSongDown(it));
}

TEST_F(GivenAnPlaylistGtest, WhenMoveSongUpOnFirstElement_ThenReturnsFalse)
{
    playlist_->addSong(songA_);
    auto it{playlist_->getSongs().begin()};
    EXPECT_FALSE(playlist_->moveSongUp(it));
}

TEST_F(GivenAnPlaylistGtest, WhenRemoveSongOnEndIterator_ReturnsFalse)
{
    auto it{playlist_->getSongs().end()};
    EXPECT_FALSE(playlist_->removeSong(it));
}

class GivenAnPlaylistSizeParamGtest : public ::testing::TestWithParam<int>
{
};

TEST_P(GivenAnPlaylistSizeParamGtest, WhenSizeMatchesNumberOfSongsAdded)
{
    Playlist pl{"Param Playlist"};
    const int count{GetParam()};

    for (int index = 0; index < count; index++)
    {
        pl.addSong(Song(100, "f.mp3", "Title" + std::to_string(index)));
    }
    EXPECT_EQ(static_cast<int>(pl.getSize()), count);
}

INSTANTIATE_TEST_SUITE_P(
    VariousSizes,
    GivenAnPlaylistSizeParamGtest,
    ::testing::Values(0, 1, 3, 5, 10
));
