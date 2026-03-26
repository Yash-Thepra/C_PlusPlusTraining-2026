#include <gtest/gtest.h>
#include <string>

#include "Song.h"

class GivenAnSongGtest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        song_ = std::make_unique<Song>(
            200,
            "resource/blinding_lights.mp3",
            "Blinding Lights"
        );
    }
    std::unique_ptr<Song> song_;
};

TEST_F(GivenAnSongGtest, WhenGetDuration_ThenReturnsCorrectDuration)
{
    EXPECT_EQ(song_->getDuration(), 200);
}

TEST_F(GivenAnSongGtest, WhenGetFilePath_ThenReturnsCorrectPath)
{
    EXPECT_EQ(song_->getFilePath(), "resource/blinding_lights.mp3");
}

TEST_F(GivenAnSongGtest, WhenGetTitle_ThenReturnsCorrectTitle)
{
    EXPECT_EQ(song_->getTitle(), "Blinding Lights");
}

TEST_F(GivenAnSongGtest, WhenZeroDurationIsAccepted)
{
    Song s{0, "path.mp3", "Title" };
    EXPECT_EQ(s.getDuration(), 0);
}

TEST_F(GivenAnSongGtest, WhenDurationDoesNotMatchWrongValue)
{
    EXPECT_NE(song_->getDuration(), 999);
}

TEST_F(GivenAnSongGtest, WhenTitleDoesNotMatchWrongValue)
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

class GivenAnSongParamGtest : public ::testing::TestWithParam<SongParam> {};

TEST_P(GivenAnSongParamGtest, WhenConstructsWithVariousValidData)
{
    const auto& p{ GetParam() };
    const Song  s{p.duration, p.filePath, p.title };
    EXPECT_EQ(s.getDuration(), p.duration);
    EXPECT_EQ(s.getFilePath(), p.filePath);
    EXPECT_EQ(s.getTitle(),    p.title);
}

INSTANTIATE_TEST_SUITE_P(
    SongVariants,
    GivenAnSongParamGtest,
    ::testing::Values(
        SongParam{ "Artist A", 180, "a.mp3", "Song A" },
        SongParam{ "Artist B", 240, "b.mp3", "Song B" },
        SongParam{ "Artist C",   1, "c.mp3", "Song C" }
    )
);
