#include <gtest/gtest.h>
#include <string>

#include "Song.h"

class SongGtest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        song_ = std::make_unique<Song>(
            "The Weeknd",
            200,
            "resource/blinding_lights.mp3",
            "Blinding Lights"
        );
    }
    std::unique_ptr<Song> song_;
};

TEST_F(SongGtest, GetArtistReturnsCorrectArtist)
{
    EXPECT_EQ(song_->getArtist(), "The Weeknd");
}

TEST_F(SongGtest, GetDurationReturnsCorrectDuration)
{
    EXPECT_EQ(song_->getDuration(), 200);
}

TEST_F(SongGtest, GetFilePathReturnsCorrectPath)
{
    EXPECT_EQ(song_->getFilePath(), "resource/blinding_lights.mp3");
}

TEST_F(SongGtest, GetTitleReturnsCorrectTitle)
{
    EXPECT_EQ(song_->getTitle(), "Blinding Lights");
}

TEST_F(SongGtest, ZeroDurationIsAccepted)
{
    Song s{ "Artist", 0, "path.mp3", "Title" };
    EXPECT_EQ(s.getDuration(), 0);
}

TEST_F(SongGtest, ArtistDoesNotMatchWrongValue)
{
    EXPECT_NE(song_->getArtist(), "Wrong Artist");
}

TEST_F(SongGtest, DurationDoesNotMatchWrongValue)
{
    EXPECT_NE(song_->getDuration(), 999);
}

TEST_F(SongGtest, TitleDoesNotMatchWrongValue)
{
    EXPECT_NE(song_->getTitle(), "Wrong Title");
}

struct SongParam
{
    std::string artist;
    int duration;
    std::string filePath;
    std::string title;
};

class SongParamGtest : public ::testing::TestWithParam<SongParam> {};

TEST_P(SongParamGtest, ConstructsWithVariousValidData)
{
    const auto& p{ GetParam() };
    const Song  s{ p.artist, p.duration, p.filePath, p.title };

    EXPECT_EQ(s.getArtist(),   p.artist);
    EXPECT_EQ(s.getDuration(), p.duration);
    EXPECT_EQ(s.getFilePath(), p.filePath);
    EXPECT_EQ(s.getTitle(),    p.title);
}

INSTANTIATE_TEST_SUITE_P(
    SongVariants,
    SongParamGtest,
    ::testing::Values(
        SongParam{ "Artist A", 180, "a.mp3", "Song A" },
        SongParam{ "Artist B", 240, "b.mp3", "Song B" },
        SongParam{ "Artist C",   1, "c.mp3", "Song C" }
    )
);
