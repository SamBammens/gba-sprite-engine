//
// Created by Wouter Groeneveld on 30/11/18.
//

#include "ConwayScene.h"
#include "bg.h"

#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/gba/tonc_core.h>
#include <libgba-sprite-engine/background/text_stream.h>


// See http://www.coranac.com/tonc/text/gfx.htm#cd-qran
int __qran_seed= 42;     // Seed / rnd holder

std::vector<Sprite *> ConwayScene::sprites() {
    return {};
}

std::vector<Background *> ConwayScene::backgrounds() {
    return { bg.get() };
}



void ConwayScene::load() {
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(TetrisPiskelPal, sizeof(TetrisPiskelPal)));


    bg = std::unique_ptr<Background>(new Background(1, TileMap, sizeof(TileMap), map, sizeof(map)));
    bg.get()->useMapScreenBlock(16);

    postload();
}



