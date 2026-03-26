#pragma once

#include <iostream>

namespace Constant
{
    const std::string mainMenu = 
              "\n===== Music Playlist =====\n"
              "  1. Create playlist\n"
              "  2. Select playlist\n"
              "  3. Delete playlist\n"
              "  4. Song management\n"
              "  5. Playback controls\n"
              "  6. Search song\n"
              "  0. Exit\n"
              "Choice: ";
    const std::string playbackMenu = 
                  "  1. Play    2. Pause    3. Resume\n"
                  "  4. Stop    5. Next     6. Previous\n"
                  "  0. Back\n"
                  "  Choice: ";
    const std::string noPlaylistSelected = "  No playlist selected. Please select one first.\n";
    const std::string songManagement = 
                  "  1. Add song\n"
                  "  2. Remove song\n"
                  "  3. Move song up\n"
                  "  4. Move song down\n"
                  "  5. Display songs\n"
                  "  0. Back\n"
                  "Choice: ";
    const std::string resource = "resource";
    const std::string noAudioFiles = "  No audio files found in resource/ folder.\n";
    const std::string songsAvailable = "\n  Available songs:\n";
    const std::string extraSpace = "    ";   
    const std::string dotAndSpace = ". ";
    const std::string newLine = "\n";
    const std::string selectFileFrom = "  Select file (1-";
    const std::string songExists = "  Song already exists in playlist.\n";
    const std::string added = "  Added: ";
    const std::string openingBracket = " (";
    const std::string newLineSecond = "s)\n";
    const std::string playlistName = "  Playlist name: ";
    const std::string playlistText = "  Playlist '";
    const std::string createdText = "' created.\n";
    const std::string error = "  Error: ";
    const std::string toDeletePlaylist = "  Select playlist to delete (1-";
    const std::string playlistDeleted = "  Playlist deleted.\n";
    const std::string newLineDash = "\n--- ";
    const std::string dashNewLine = " ---\n";
    const std::string ogg = ".ogg";
    const std::string wav = ".wav";
    const std::string flac = ".flac";
    const std::string resourceSlash = "resource/";
    const std::string noSongs = "  No songs to move.\n";
    const std::string toMove = "  Song number to move (1-";
    const std::string toCancel = ", 0 to cancel): ";
    const std::string moveChoice = "  1. Move up   2. Move down   0. Cancel\n  Choice: ";
    const std::string songMoved = "  Song moved.\n";
    const std::string cannotMove = "  Cannot move further in that direction.\n";
    const std::string selectPlaylistFirst = "  Select a playlist first.\n";
    const std::string songRemoved = "  Song removed.\n";
    const std::string toRemove = "  Song number to remove (1-";
    const std::string noSongsToRemove = "  No songs to remove.\n";
    const std::string select = "  Select (1-";
    const std::string selected = "  Selected: ";
    const std::string status = "\n  Status: ";
    const std::string isPlaying = "Playing";
    const std::string isStopped = "Stopped";
    const std::string songs = " songs)\n";
    const std::string noPlaylists = "  No playlists yet.\n";
    const std::string playlists = "\n  Playlists:\n";
    const std::string searchResult = "Search Results";
    const int six = 6;
    const std::string dash = " - ";
    const std::string playlistIsEmpty = "  Playlist is empty.\n";
    const std::string newLineThird = "':\n";
    const std::string songsIn = "\n  Songs in '";
    const std::string search = "  Search: ";
    const std::string searchResultTwo = "\n  Search results:\n";
    const std::string selectToPlay = "  Select to play (1-";
    const int zero = 0;
    const std::string noMatchingSong = "  No matching songs found.\n";
    const char space = ' ';
    const char dashChar = '-';
    const std::string invalidInput = "  Invalid input. Enter a number between ";
    const std::string andWord = " and ";
    const std::string colonSpace = ": ";
    const std::string cannotEmpty = "  Cannot be empty. ";
    const std::string yesOrNo = " (y/n): ";
    const char newLineChar = '\n';
    const char yUpper = 'Y';
    const char yLower = 'y';
    const char delimiter = '|';
    const std::string noSongPlaying = "No song playing";
    const std::string noPlaylistLoaded = "  No playlist loaded or playlist is empty.\n";
    const std::string cannotLoad = "  Could not load: ";
    const std::string sfmlError = "  Tip: SFML supports .ogg .wav .flac -- not .mp3\n";
    const std::string nowPlaying = "  Now playing: ";
    const std::string playlistTextTwo = "PLAYLIST:";
    const int nine = 9;
    const std::string runtimeErrorFirst = "Cannot open save file: ";
    const std::string exists =  "' already exists.";
    const int one = 1;
    const std::string invalidIndex = "Invalid playlist index.";
    const std::string playlistTxt = "playlists.txt";
}
