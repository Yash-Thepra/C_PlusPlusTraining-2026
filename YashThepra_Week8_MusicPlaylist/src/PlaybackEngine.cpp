#include <iostream>

#include "Constant.h"
#include "PlaybackEngine.h"

PlaybackEngine::PlaybackEngine() : history_{}, isPaused_{false}, isPlaying_{false}, music_{}, playlist_{nullptr}, upNext_{}
{
}

PlaybackEngine::~PlaybackEngine()
{
    stop();
}

std::string PlaybackEngine::getCurrentSongTitle() const
{
    std::string result = playlist_->getCurrent()->getTitle();
    if (!isPlaying_ && !isPaused_)
    {
        result = Constant::noSongPlaying;
    }
    else if (playlist_ == nullptr || playlist_->isEmpty())
    {
        result = Constant::noSongPlaying;
    }
    return result;
}

bool PlaybackEngine::isPlaying() const
{
    return isPlaying_;
}

void PlaybackEngine::nextSong()
{
    if (playlist_ != nullptr && !playlist_->isEmpty())
    {
        pushToHistory();
        if (!upNext_.empty())
        {
            Song *queued = upNext_.front();
            upNext_.pop();
            for (auto iterator = playlist_->getSongs().begin(); iterator != playlist_->getSongs().end(); iterator++)
            {
                if (&(*iterator) == queued)
                {
                    playlist_->setCurrent(iterator);
                    break;
                }
            }
        }
        else
        {
            auto next = std::next(playlist_->getCurrent());
            playlist_->setCurrent(next == playlist_->getSongs().end() ? playlist_->getSongs().begin() : next);
        }
        loadCurrentSong();
    }
}

void PlaybackEngine::pause()
{
    if (isPlaying_ && !isPaused_)
    {
        music_.pause();
        isPaused_ = true;
        isPlaying_ = false;
    }
}

void PlaybackEngine::play()
{
    if (playlist_ == nullptr || playlist_->isEmpty())
    {
        std::cout << Constant::noPlaylistLoaded;
    }
    else
    {
        playlist_->setCurrent(playlist_->getSongs().begin());
        loadCurrentSong();
    }
}

void PlaybackEngine::previousSong()
{
    if (playlist_ != nullptr && !playlist_->isEmpty())
    {
        if (!history_.empty())
        {
            Song *prev = history_.back();
            history_.pop_back();
            for (auto iterator = playlist_->getSongs().begin(); iterator != playlist_->getSongs().end(); iterator++)
            {
                if (&(*iterator) == prev)
                {
                    playlist_->setCurrent(iterator);
                    break;
                }
            }
        }
        else if (playlist_->getCurrent() != playlist_->getSongs().begin())
        {
            playlist_->setCurrent(std::prev(playlist_->getCurrent()));
        }
        loadCurrentSong();
    }
}

void PlaybackEngine::queueNext(const Song &song)
{
    if (playlist_ != nullptr)
    {
        for (auto iterator = playlist_->getSongs().begin(); iterator != playlist_->getSongs().end(); iterator++)
        {
            if (iterator->getFilePath() == song.getFilePath())
            {
                upNext_.push(&(*iterator));
                break;
            }
        }
    }
}

void PlaybackEngine::resume()
{
    if (isPaused_)
    {
        music_.play();
        isPaused_ = false;
        isPlaying_ = true;
    }
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
    bool result = true;
    if (playlist_->getCurrent() == playlist_->getSongs().end())
    {
        result = false;
    }
    else
    {
        std::string path = playlist_->getCurrent()->getFilePath();
        if (!music_.openFromFile(path))
        {
            std::cerr << Constant::cannotLoad << path << Constant::newLineChar;
            std::cerr << Constant::sfmlError;
            result = false;
        }
        else
        {
            music_.play();
            isPlaying_ = true;
            isPaused_ = false;
            std::cout << Constant::nowPlaying << playlist_->getCurrent()->getTitle() << Constant::dash << Constant::newLineChar;
        }
    }
    return result;
}

void PlaybackEngine::pushToHistory()
{
    if (playlist_ != nullptr && !playlist_->isEmpty())
    {
        constexpr std::size_t maxHistory = 20;
        if (history_.size() >= maxHistory)
        {
            history_.pop_front();
        }
        history_.push_back(&(*playlist_->getCurrent()));
    }
}
