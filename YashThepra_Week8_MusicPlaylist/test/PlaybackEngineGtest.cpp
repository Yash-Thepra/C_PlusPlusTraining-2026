#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <string>

#include "Mocks.h"
#include "Playlist.h"
#include "Song.h"

class GivenAnPlaybackEngineGtest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        mockEngine_ = std::make_unique<MockPlaybackEngine>();
        playlist_ = std::make_unique<Playlist>("Engine Test");
        playlist_->addSong(Song{180, "a.mp3", "Song A"});
        playlist_->addSong(Song{200, "b.mp3", "Song B"});
    }
    std::unique_ptr<MockPlaybackEngine> mockEngine_;
    std::unique_ptr<Playlist> playlist_;
};

TEST_F(GivenAnPlaybackEngineGtest, WhenIsPlaying_ThenReturnsTrueWhenPlaying)
{
    EXPECT_CALL(*mockEngine_, isPlaying())
        .WillOnce(::testing::Return(true));

    EXPECT_TRUE(mockEngine_->isPlaying());
}

TEST_F(GivenAnPlaybackEngineGtest, WhenNextSongIsCalled)
{
    EXPECT_CALL(*mockEngine_, nextSong()).Times(1);
    mockEngine_->nextSong();
}

TEST_F(GivenAnPlaybackEngineGtest, WhenPauseIsCalledAfterPlay)
{
    EXPECT_CALL(*mockEngine_, play()).Times(1);
    EXPECT_CALL(*mockEngine_, pause()).Times(1);

    mockEngine_->play();
    mockEngine_->pause();
}

TEST_F(GivenAnPlaybackEngineGtest, WhenPlayIsCalled)
{
    EXPECT_CALL(*mockEngine_, setPlaylist(playlist_.get())).Times(1);
    EXPECT_CALL(*mockEngine_, play()).Times(1);

    mockEngine_->setPlaylist(playlist_.get());
    mockEngine_->play();
}

TEST_F(GivenAnPlaybackEngineGtest, WhenPreviousSongIsCalled)
{
    EXPECT_CALL(*mockEngine_, previousSong()).Times(1);
    mockEngine_->previousSong();
}

TEST_F(GivenAnPlaybackEngineGtest, ResumeIsCalledAfterPause)
{
    EXPECT_CALL(*mockEngine_, pause()).Times(1);
    EXPECT_CALL(*mockEngine_, resume()).Times(1);

    mockEngine_->pause();
    mockEngine_->resume();
}

TEST_F(GivenAnPlaybackEngineGtest, WhenSetPlaylistIsCalled)
{
    EXPECT_CALL(*mockEngine_, setPlaylist(playlist_.get())).Times(1);
    mockEngine_->setPlaylist(playlist_.get());
}

TEST_F(GivenAnPlaybackEngineGtest, WhenStopIsCalled)
{
    EXPECT_CALL(*mockEngine_, stop()).Times(1);
    mockEngine_->stop();
}

TEST_F(GivenAnPlaybackEngineGtest, WhenIsPlayingReturnsFalseWhenStopped)
{
    EXPECT_CALL(*mockEngine_, isPlaying())
        .WillOnce(::testing::Return(false));

    EXPECT_FALSE(mockEngine_->isPlaying());
}

struct PlaybackStateParam
{
    bool expected;
    bool returned;
};

class GivenAnPlaybackStateParamGtest
    : public ::testing::TestWithParam<PlaybackStateParam>
{
protected:
    void SetUp() override
    {
        mockEngine_ = std::make_unique<MockPlaybackEngine>();
    }

    std::unique_ptr<MockPlaybackEngine> mockEngine_;
};

TEST_P(GivenAnPlaybackStateParamGtest, IsPlayingReturnsExpectedState)
{
    const auto &p{GetParam()};

    EXPECT_CALL(*mockEngine_, isPlaying())
        .WillOnce(::testing::Return(p.returned));

    EXPECT_EQ(mockEngine_->isPlaying(), p.expected);
}

INSTANTIATE_TEST_SUITE_P
(
    PlaybackStateCases,
    GivenAnPlaybackStateParamGtest,
    ::testing::Values(
        PlaybackStateParam{false, false},
        PlaybackStateParam{true, true}
));
