//
// Created by Wouter Groeneveld on 30/11/18.
//

#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/gba/tonc_core.h>
#include <libgba-sprite-engine/background/text_stream.h>

#include "SpelFase.h"
#include "ConwayScene.h"


void SpelFase::tick(u16 keys) {
    generation++;
    int totalAmountAlive = 0;
    dma3_cpy(buffer, map, sizeof(buffer));

    TextStream::instance().setText("jklsdfnmjksndfvmjksdnfjkvnsdjk: ", 2, 1);

    dma3_cpy(map, buffer, sizeof(map));
    bg.get()->updateMap(map);
}

void SpelFase::postload() {

}
