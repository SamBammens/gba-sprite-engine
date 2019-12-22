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

using namespace std;

StartScene::StartScene(const std::shared_ptr<GBAEngine> &engine) : Scene(engine){}

vector<Background *> StartScene::backgrounds() {
    return {};
}

vector<Sprite *> StartScene::sprites() {
    return {
        sprite.get()
    };
}


/**
 * Hierin wordt het eerste scherm aangemaakt
 */
void StartScene::load() {

    SpriteBuilder<Sprite> builder;
    sprite = builder
            .withData(TileMap, sizeof(TileMap))
            .withSize(SIZE_32_8)
            .withLocation(GBA_SCREEN_WIDTH - 40, 8)
            .buildPtr();

    TextStream::instance().setText(string("TETRIS"), 1, 1);
    TextStream::instance().setText(string("MADE BY"), 6, 1);
    TextStream::instance().setText(string("BAMMENS SAM"), 7, 1);
    TextStream::instance().setText(string("CLAESEN THOMAS"), 8, 1);
    TextStream::instance().setText(string("PAULISSEN PIETER"), 9, 1);

    TextStream::instance().setText(string("DRUK OP ENTER OM TE BEGINNEN"), 15, 1);
}

void StartScene::tick(u16 keys) {


    if(keys & KEY_START) {
            engine.get()->setScene(new SpelFase(engine));
    }
}