#include <iostream>

#include "PlaybackEngine.h"

PlaybackEngine::PlaybackEngine() : cursor_{}, history_{}, isPaused_{false}, isPlaying_{false}, music_{}, playlist_{nullptr}, upNext_{}
{
}

PlaybackEngine::~PlaybackEngine()
{
    stop();
}

std::string PlaybackEngine::getCurrentSongTitle() const
{
    if (!isPlaying_ && !isPaused_)
    {
        return "No song playing";
    }
    if (playlist_ == nullptr || playlist_->isEmpty())
    {
        return "No song playing";
    }
    return cursor_->getTitle();
}

bool PlaybackEngine::isPaused() const
{
    return isPaused_;
}

bool PlaybackEngine::isPlaying() const
{
    return isPlaying_;
}

void PlaybackEngine::nextSong()
{
    if (playlist_ == nullptr || playlist_->isEmpty())
    {
        return;
    }
    pushToHistory();
    if (!upNext_.empty())
    {
        Song *queued{upNext_.front()};
        upNext_.pop();

        for (auto it{playlist_->getSongs().begin()};
             it != playlist_->getSongs().end(); ++it)
        {
            if (&(*it) == queued)
            {
                cursor_ = it;
                break;
            }
        }
    }
    else
    {
        std::list<Song>::iterator next{std::next(cursor_)};
        cursor_ = (next == playlist_->getSongs().end()) ? playlist_->getSongs().begin() : next;
    }
    loadCurrentSong();
}

void PlaybackEngine::pause()
{
    if (!isPlaying_ || isPaused_)
    {
        return;
    }
    music_.pause();
    isPaused_ = true;
    isPlaying_ = false;
}

void PlaybackEngine::play()
{
    if (playlist_ == nullptr || playlist_->isEmpty())
    {
        std::cout << "  No playlist loaded or playlist is empty.\n";
        return;
    }
    cursor_ = playlist_->getSongs().begin();
    loadCurrentSong();
}

void PlaybackEngine::previousSong()
{
    if (playlist_ == nullptr || playlist_->isEmpty())
    {
        return;
    }
    if (!history_.empty())
    {
        Song *prev{history_.back()};
        history_.pop_back();

        for (auto it{playlist_->getSongs().begin()};
             it != playlist_->getSongs().end(); ++it)
        {
            if (&(*it) == prev)
            {
                cursor_ = it;
                break;
            }
        }
    }
    else if (cursor_ != playlist_->getSongs().begin())
    {
        --cursor_;
    }
    loadCurrentSong();
}

void PlaybackEngine::queueNext(const Song &song)
{
    if (playlist_ == nullptr)
    {
        return;
    }
    for (auto it{playlist_->getSongs().begin()};
         it != playlist_->getSongs().end(); ++it)
    {
        if (it->getFilePath() == song.getFilePath())
        {
            upNext_.push(&(*it));
            return;
        }
    }
}

void PlaybackEngine::resume()
{
    if (!isPaused_)
    {
        return;
    }
    music_.play();
    isPaused_ = false;
    isPlaying_ = true;
}

void PlaybackEngine::setPlaylist(Playlist *playlist)
{
    stop();
    playlist_ = playlist;
}

void PlaybackEngine::stop()
{
    music_.stop();
    isPlaying_ = false;
    isPaused_ = false;
}

bool PlaybackEngine::loadCurrentSong()
{
    if (cursor_ == playlist_->getSongs().end())
    {
        return false;
    }
    if (!music_.openFromFile(cursor_->getFilePath()))
    {
        std::cerr << "  Could not load: " << cursor_->getFilePath() << '\n';
        return false;
    }
    music_.play();
    isPlaying_ = true;
    isPaused_ = false;
    std::cout << "  Now playing: " << cursor_->getTitle() << " - " << cursor_->getArtist() << '\n';
    return true;
}

void PlaybackEngine::pushToHistory()
{
    if (playlist_ == nullptr || playlist_->isEmpty())
    {
        return;
    }
    constexpr std::size_t maxHistory{20};
    if (history_.size() >= maxHistory)
    {
        history_.pop_front();
    }
    history_.push_back(&(*cursor_));
}
