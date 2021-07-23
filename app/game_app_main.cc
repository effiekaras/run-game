#include <run_game_app.h>

using run_game::RunGameApp;

void prepareSettings(RunGameApp::Settings* settings) {
    settings->setResizable(false);
}
CINDER_APP(run_game::RunGameApp, ci::app::RendererGl, prepareSettings);
