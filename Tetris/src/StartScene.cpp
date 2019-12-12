//
// Created by Wouter Groeneveld on 30/11/18.
//

#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/gba_engine.h>
#include "StartScene.h"
#include "bg.h"
#include "SpelFase.h"

StartScene::StartScene(const std::shared_ptr<GBAEngine> &engine) : Scene(engine), percentage(30), delta(0), impl(1) {}

std::vector<Background *> StartScene::backgrounds() {
    return {};
}

std::vector<Sprite *> StartScene::sprites() {
    return {
        conwaySprite.get()
    };
}

void StartScene::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(TetrisPiskelPal, sizeof(TetrisPiskelPal)));

    SpriteBuilder<Sprite> builder;
    conwaySprite = builder
            .withData(TileMap, sizeof(TileMap))
            .withSize(SIZE_32_8)
            .withLocation(GBA_SCREEN_WIDTH - 40, 8)
            .buildPtr();

    TextStream::instance().setText(std::string("TETRIS"), 1, 1);
    TextStream::instance().setText(std::string("MADE BY"), 6, 1);
    TextStream::instance().setText(std::string("BAMMENS SAM"), 7, 1);
    TextStream::instance().setText(std::string("CLAESSEN THOMAS"), 8, 1);
    TextStream::instance().setText(std::string("PAULISSEN PIETER"), 9, 1);

    TextStream::instance().setText(std::string("DRUK OP ENTER OM TE BEGINNEN"), 15, 1);
}

void StartScene::tick(u16 keys) {


    if(keys & KEY_START) {
        if(impl == 1) {
            engine.get()->setScene(new SpelFase(engine));
        }
    }
}