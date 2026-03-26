#include "Application.h"
#include "FileManager.h"
#include "PlaybackEngine.h"

int main()
{
    FileManager fileManager(Constant::playlistTxt);
    PlaybackEngine engine;
    IFileManager &manager(fileManager);
    IPlaybackEngine &playback(engine);
    Application app(manager, playback);
    app.run();
    return 0;
}
