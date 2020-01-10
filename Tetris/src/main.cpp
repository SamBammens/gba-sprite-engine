//
// Created by Pieter Paulissen on 15/12/2019.
//

#include "StartScene.h"
#include <libgba-sprite-engine/gba_engine.h>

/**
 * Niets aan veranderd, hetzelfde gehouden als het voorbeeldspel van Conway
 * @return
 */
int main() {
    std::shared_ptr<GBAEngine> engine(new GBAEngine());

    StartScene* startScene = new StartScene(engine);
    engine->setScene(startScene);

    while (true) {
        engine->update();
    }

    return 0;
}