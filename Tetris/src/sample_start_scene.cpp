//
// Created by Wouter Groeneveld on 02/08/18.
//

#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/effects/fade_out_scene.h>
#include "sample_start_scene.h"
#include "Roze.h"
#include "Blauw.h"
#include "Groen.h"
#include <string>


std::vector<Background *> SampleStartScene::backgrounds() {
    return {};
}

std::vector<Sprite *> SampleStartScene::sprites() {
    return {  rozeBlok.get(), groeneBlok.get(), blauweBlok.get() };
}

void SampleStartScene::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(SharedPal, sizeof(SharedPal)));
    //backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager());

    SpriteBuilder<Sprite> builder;

    rozeBlok = builder
            .withData(RozeTiles, sizeof(RozeTiles))
            .withSize(SIZE_16_16)
            .withLocation(10, 10)
            .buildPtr();

    blauweBlok = builder
            .withData(BlauwTiles, sizeof(BlauwTiles))
            .withSize(SIZE_16_16)
            .withLocation(22, 10)
            .buildPtr();

    //16 op 16 is het beste denk ik
    groeneBlok = builder
            .withData(GroenTiles, sizeof(GroenTiles))
            .withSize(SIZE_16_16)
            .withLocation(34, 10)
            .buildPtr();

    TextStream::instance().setText("PRESS START", 3, 8);

    //engine->getTimer()->start();
    //engine->enqueueMusic(zelda_music_16K_mono, zelda_music_16K_mono_bytes);
}

void SampleStartScene::tick(u16 keys) {
    TextStream::instance().setText(engine->getTimer()->to_string(), 18, 1);

    /*if(pressingAorB && !((keys & KEY_A) || (keys & KEY_B))) {
        engine->getTimer()->toggle();
        pressingAorB = false;
    }*/

    /*if(keys & KEY_START) {
        if(!engine->isTransitioning()) {
            engine->enqueueSound(zelda_secret_16K_mono, zelda_secret_16K_mono_bytes);

            TextStream::instance() << "entered: starting next scene";

            engine->transitionIntoScene(new FlyingStuffScene(engine), new FadeOutScene(2));
        }*/

    if(keys & KEY_A){ //z op het toetsenbord is A
        stop = true;
    }else if(keys & KEY_B){ //x op het toetsenbord is B
        stop = false;
    }
    if(timer1 == 20) {
        blauweBlok->setVelocity(0,+8);
        timer1 = 0;
    } else{
        blauweBlok->setVelocity(0,0);
    }
    if(timer2 == 20) {
        rozeBlok->setVelocity(0,+8);
        timer2 = 0;
    }else{
        rozeBlok->setVelocity(0,0);
    }
    if(timer3== 20) {
        groeneBlok->setVelocity(0,+8);
        timer3 = 0;
    }else{
        groeneBlok->setVelocity(0,0);
    }
    if(stop == false) {
        timer1 = timer1 + 1;
        timer2 = timer2 + 1;
        timer3 = timer3 + 1;
    }


}
