//
// Created by Pieter Paulissen on 15/12/2019.
//

#include "TetrisMenu.h"
#include "bg.h"


#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/gba/tonc_core.h>
#include <libgba-sprite-engine/background/text_stream.h>

using namespace std;



vector<Sprite *> TetrisMenu::sprites() {
    return {};
}

vector<Background *> TetrisMenu::backgrounds() {
    return { bg.get() };
}

/**
 * het menu wordt geupdatet wanneer deze functie opgeroepen wordt
 */
void TetrisMenu::update() {
    TextStream::instance().setText(string("LEVEL:") + to_string(level), 9, 17);
    TextStream::instance().setText(string("SCORE:") + to_string(score), 13, 17);
}

/**
 * Hierin wordt u backgroundpalette aangemaakt net als de tilemap
 *
 * Daarna wordt alles ins de buffergestoken
 * Dan wordt het volledige scherm zwart gemaakt, behalve de grenzen van het speelveld wordt wit gemaakt
 * Dit wordt allemaal aangepast in de buffer, daarna worden de gegevens van de buffer in de map gestoken die ervoorzorgt dat alles op het
 * scherm zich aanpast
 *
 * tot slot maken we het menuscherm klaar
 */
void TetrisMenu::load() {
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(TetrisPiskelPal, sizeof(TetrisPiskelPal)));

    bg = std::unique_ptr<Background>(new Background(1, TileMap, sizeof(TileMap), map, sizeof(map)));
    bg.get()->useMapScreenBlock(16);

    dma3_cpy(buffer, map, sizeof(buffer));

    for(int h = 0; h < MAP_HEIGHT; h++) {
        int hw = h * MAP_WIDTH;
        for(int w = 0; w < MAP_WIDTH; w++) {
            int pos = hw + w;
            if(w == 4 || w == 15 ) {
                buffer[pos] = WIT;
            }else {
                buffer[pos] = ZWART;
            }
        }
    }
    dma3_cpy(map, buffer, sizeof(map));
    bg.get()->updateMap(map);


    TextStream::instance().setText(string("HOLD"), 1, 18);
    TextStream::instance().setText(string("NEXT"), 1, 25);
    TextStream::instance().setText(string("LEVEL:") + to_string(level), 9, 17);
    TextStream::instance().setText(string("SCORE:") + to_string(score), 13, 17);
    TextStream::instance().setText(string("HOLD= SELECT"), 16, 17);
    TextStream::instance().setText(string("PAUZE= A"), 17, 17);
    TextStream::instance().setText(string("START OVER= B"), 18, 17);

    postload();
}



