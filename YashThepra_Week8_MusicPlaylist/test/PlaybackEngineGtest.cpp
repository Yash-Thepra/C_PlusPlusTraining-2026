#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <string>

#include "Mocks.h"
#include "Playlist.h"
#include "Song.h"

using ::testing::Return;

class PlaybackEngineGtest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        mockEngine_ = std::make_unique<MockPlaybackEngine>();
        playlist_ = std::make_unique<Playlist>("Engine Test");
        playlist_->addSong(Song{"Artist A", 180, "a.mp3", "Song A"});
        playlist_->addSong(Song{"Artist B", 200, "b.mp3", "Song B"});
    }
    std::unique_ptr<MockPlaybackEngine> mockEngine_;
    std::unique_ptr<Playlist> playlist_;
};

TEST_F(PlaybackEngineGtest, IsPlayingReturnsTrueWhenPlaying)
{
    EXPECT_CALL(*mockEngine_, isPlaying())
        .WillOnce(Return(true));

    EXPECT_TRUE(mockEngine_->isPlaying());
}

TEST_F(PlaybackEngineGtest, NextSongIsCalled)
{
    EXPECT_CALL(*mockEngine_, nextSong()).Times(1);
    mockEngine_->nextSong();
}

TEST_F(PlaybackEngineGtest, PauseIsCalledAfterPlay)
{
    EXPECT_CALL(*mockEngine_, play()).Times(1);
    EXPECT_CALL(*mockEngine_, pause()).Times(1);

    mockEngine_->play();
    mockEngine_->pause();
}

TEST_F(PlaybackEngineGtest, PlayIsCalled)
{
    EXPECT_CALL(*mockEngine_, setPlaylist(playlist_.get())).Times(1);
    EXPECT_CALL(*mockEngine_, play()).Times(1);

    mockEngine_->setPlaylist(playlist_.get());
    mockEngine_->play();
}

TEST_F(PlaybackEngineGtest, PreviousSongIsCalled)
{
    EXPECT_CALL(*mockEngine_, previousSong()).Times(1);
    mockEngine_->previousSong();
}

TEST_F(PlaybackEngineGtest, ResumeIsCalledAfterPause)
{
    EXPECT_CALL(*mockEngine_, pause()).Times(1);
    EXPECT_CALL(*mockEngine_, resume()).Times(1);

    mockEngine_->pause();
    mockEngine_->resume();
}

TEST_F(PlaybackEngineGtest, SetPlaylistIsCalled)
{
    EXPECT_CALL(*mockEngine_, setPlaylist(playlist_.get())).Times(1);
    mockEngine_->setPlaylist(playlist_.get());
}

TEST_F(PlaybackEngineGtest, StopIsCalled)
{
    EXPECT_CALL(*mockEngine_, stop()).Times(1);
    mockEngine_->stop();
}

TEST_F(PlaybackEngineGtest, IsPlayingReturnsFalseWhenStopped)
{
    EXPECT_CALL(*mockEngine_, isPlaying())
        .WillOnce(Return(false));

    EXPECT_FALSE(mockEngine_->isPlaying());
}

struct PlaybackStateParam
{
    bool expected;
    bool returned;
};

class PlaybackStateParamGtest
    : public ::testing::TestWithParam<PlaybackStateParam>
{
protected:
    void SetUp() override
    {
        mockEngine_ = std::make_unique<MockPlaybackEngine>();
    }

    std::unique_ptr<MockPlaybackEngine> mockEngine_;
};

TEST_P(PlaybackStateParamGtest, IsPlayingReturnsExpectedState)
{
    const auto &p{GetParam()};

    EXPECT_CALL(*mockEngine_, isPlaying())
        .WillOnce(Return(p.returned));

    EXPECT_EQ(mockEngine_->isPlaying(), p.expected);
}

INSTANTIATE_TEST_SUITE_P
(
    PlaybackStateCases,
    PlaybackStateParamGtest,
    ::testing::Values(
        PlaybackStateParam{false, false},
        PlaybackStateParam{true, true}
));
