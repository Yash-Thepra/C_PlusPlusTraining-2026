#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <stdexcept>
#include <string>
#include <vector>

#include "Mocks.h"
#include "PlaylistManager.h"

using ::testing::_;
using ::testing::Return;

class GivenAnPlaylistManagerGtest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        EXPECT_CALL(mockFM_, loadPlaylists())
            .WillRepeatedly(Return(std::vector<Playlist>{}));

        EXPECT_CALL(mockFM_, savePlaylists(_))
            .WillRepeatedly(Return(true));

        manager_ = std::make_unique<PlaylistManager>(mockFM_);
    }
    MockFileManager mockFM_;
    std::unique_ptr<PlaylistManager> manager_;
};

TEST_F(GivenAnPlaylistManagerGtest, WhenActiveIndexIsMinusOneInitially)
{
    EXPECT_EQ(manager_->getActiveIndex(), -1);
}

TEST_F(GivenAnPlaylistManagerGtest, WhenCreatePlaylistAddsToCollection)
{
    manager_->createPlaylist("Chill");
    EXPECT_EQ(manager_->getAll().size(), 1u);
}

TEST_F(GivenAnPlaylistManagerGtest, WhenCreatePlaylistStoresCorrectName)
{
    manager_->createPlaylist("Workout");
    EXPECT_EQ(manager_->getAll().front().getName(), "Workout");
}

TEST_F(GivenAnPlaylistManagerGtest, WhenDeletePlaylistRemovesFromCollection)
{
    manager_->createPlaylist("Pop");
    manager_->createPlaylist("Rock");
    manager_->deletePlaylist(0);

    EXPECT_EQ(manager_->getAll().size(), 1u);
    EXPECT_EQ(manager_->getAll().front().getName(), "Rock");
}

TEST_F(GivenAnPlaylistManagerGtest, WhenDeleteActivePlaylistResetsActiveIndex)
{
    manager_->createPlaylist("Lofi");
    manager_->selectPlaylist(0);
    manager_->deletePlaylist(0);

    EXPECT_EQ(manager_->getActiveIndex(), -1);
    EXPECT_EQ(manager_->getActive(), nullptr);
}

TEST_F(GivenAnPlaylistManagerGtest, WhenFindByName_ThenReturnsCorrectPlaylist)
{
    manager_->createPlaylist("Blues");
    Playlist *found{manager_->findByName("Blues")};

    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->getName(), "Blues");
}

TEST_F(GivenAnPlaylistManagerGtest, WhenGetActive_ThenReturnsCorrectPlaylist)
{
    manager_->createPlaylist("Jazz");
    manager_->selectPlaylist(0);

    ASSERT_NE(manager_->getActive(), nullptr);
    EXPECT_EQ(manager_->getActive()->getName(), "Jazz");
}

TEST_F(GivenAnPlaylistManagerGtest, WhenLoadAllPopulatesPlaylists)
{
    std::vector<Playlist> stored{};
    stored.emplace_back("Stored");

    EXPECT_CALL(mockFM_, loadPlaylists())
        .WillOnce(Return(stored));

    manager_->loadAll();

    EXPECT_EQ(manager_->getAll().size(), 1u);
    EXPECT_EQ(manager_->getAll().front().getName(), "Stored");
}

TEST_F(GivenAnPlaylistManagerGtest, WhenSaveAllDelegatesToFileManager)
{
    EXPECT_CALL(mockFM_, savePlaylists(_))
        .Times(1)
        .WillOnce(Return(true));

    EXPECT_TRUE(manager_->saveAll());
}

TEST_F(GivenAnPlaylistManagerGtest, WhenSelectPlaylistSetsActiveIndex)
{
    manager_->createPlaylist("Alpha");
    manager_->createPlaylist("Beta");

    EXPECT_TRUE(manager_->selectPlaylist(1));
    EXPECT_EQ(manager_->getActiveIndex(), 1);
}

TEST_F(GivenAnPlaylistManagerGtest, WhenCreateDuplicatePlaylistThrows)
{
    manager_->createPlaylist("Duplicate");
    EXPECT_THROW(manager_->createPlaylist("Duplicate"), std::invalid_argument);
}

TEST_F(GivenAnPlaylistManagerGtest, WhenDeleteInvalidNegativeIndexThrows)
{
    EXPECT_THROW(manager_->deletePlaylist(-1), std::out_of_range);
}

TEST_F(GivenAnPlaylistManagerGtest, WhenDeleteInvalidPositiveIndexThrows)
{
    EXPECT_THROW(manager_->deletePlaylist(0), std::out_of_range);
}

TEST_F(GivenAnPlaylistManagerGtest, WhenFindByNameReturnsNullForUnknownName)
{
    EXPECT_EQ(manager_->findByName("NonExistent"), nullptr);
}

TEST_F(GivenAnPlaylistManagerGtest, WhenGetActive_ThenReturnsNullWhenNoneSelected)
{
    manager_->createPlaylist("Solo");
    EXPECT_EQ(manager_->getActive(), nullptr);
}

TEST_F(GivenAnPlaylistManagerGtest, WhenSelectInvalidIndex_ThenReturnsFalse)
{
    EXPECT_FALSE(manager_->selectPlaylist(-1));
    EXPECT_FALSE(manager_->selectPlaylist(99));
}

class GivenAnPlaylistManagerCreateParamGtest : public ::testing::TestWithParam<std::string>
{
protected:
    void SetUp() override
    {
        EXPECT_CALL(mockFM_, loadPlaylists())
            .WillRepeatedly(Return(std::vector<Playlist>{}));

        EXPECT_CALL(mockFM_, savePlaylists(_))
            .WillRepeatedly(Return(true));

        manager_ = std::make_unique<PlaylistManager>(mockFM_);
    }

    MockFileManager mockFM_;
    std::unique_ptr<PlaylistManager> manager_;
};

TEST_P(GivenAnPlaylistManagerCreateParamGtest, CreatePlaylistWithVariousNames)
{
    const std::string name{GetParam()};
    manager_->createPlaylist(name);

    ASSERT_EQ(manager_->getAll().size(), 1u);
    EXPECT_EQ(manager_->getAll().front().getName(), name);
}

INSTANTIATE_TEST_SUITE_P(
    PlaylistNames,
    GivenAnPlaylistManagerCreateParamGtest,
    ::testing::Values(
        std::string{"Chill"},
        std::string{"Focus"},
        std::string{"Late Night"},
        std::string{"Road Trip"},
        std::string{"Workout Mix"}));
