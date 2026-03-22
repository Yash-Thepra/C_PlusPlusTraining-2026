#include "Application.h"
#include "FileManager.h"
#include "PlaybackEngine.h"

int main()
{
    FileManager fileManager{"playlists.txt"};

    PlaybackEngine engine{};

    IFileManager &fm{fileManager};

    IPlaybackEngine &pe{engine};

    Application app{fm, pe};

    app.run();

    return 0;
}
