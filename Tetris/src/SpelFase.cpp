//
// Created by Wouter Groeneveld on 30/11/18.
//

#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/gba/tonc_core.h>
#include <libgba-sprite-engine/background/text_stream.h>

#include "SpelFase.h"
#include "TetrisAlgm.h"
#include <cstdlib>


using namespace std;

int SpelFase::kiesBlokje() {
    int rd =  rand() % 7;
    return rd;
}

vector<int> SpelFase::maakBlokje(int kleur) {
    blok.clear();
    if(kleur == 0){
        blok.push_back((32*5)+24);
        blok.push_back((32*6)+22);
        blok.push_back((32*6)+23);
        blok.push_back((32*6)+24);
    }else if(kleur == 1){
        blok.push_back((32*5)+22);
        blok.push_back((32*6)+22);
        blok.push_back((32*6)+23);
        blok.push_back((32*6)+24);
    }else if(kleur == 2){
        blok.push_back((32*5)+22);
        blok.push_back((32*5)+23);
        blok.push_back((32*6)+23);
        blok.push_back((32*6)+24);
    }else if(kleur == 3){
        blok.push_back((32*5)+23);
        blok.push_back((32*6)+22);
        blok.push_back((32*6)+23);
        blok.push_back((32*6)+24);
    }else if(kleur == 4){
        blok.push_back((32*5)+22);
        blok.push_back((32*5)+23);
        blok.push_back((32*6)+22);
        blok.push_back((32*6)+23);
    }else if(kleur == 5){
        blok.push_back((32*5)+24);
        blok.push_back((32*6)+24);
        blok.push_back((32*7)+24);
        blok.push_back((32*8)+24);
    }else if(kleur == 6){
        blok.push_back((32*6)+22);
        blok.push_back((32*6)+23);
        blok.push_back((32*5)+23);
        blok.push_back((32*5)+24);
    }

    return blok;
}


void SpelFase::tick(u16 keys) {
    dma3_cpy(buffer, map, sizeof(buffer));
    timer = timer + 1;
    TextStream::instance().setText(to_string(timer), 1, 6);

    if(timer == 100) {
        timer = 0;
        for(int i = 5; i<9;i++){
            for(int j = 22; j<26;j++){
                int pos = (32*i)+j;
                buffer[pos] = ZWART;
            }
        }
        int kleur = kiesBlokje();
        vector<int> next = maakBlokje(kleur);
        u16 color;
        switch(kleur) {
            case 0 : color = ROZE; break;
            case 1 : color = BLAUW; break;
            case 2 : color = ORANJE; break;
            case 3 : color = PAARS; break;
            case 4 : color = GEEL; break;
            case 5 : color = LICHTBL; break;
            case 6 : color = GROEN; break;
        }

        for (int i = 0; i < blok.size(); i++) {
            buffer[next[i]] = color;
        }
    }


    dma3_cpy(map, buffer, sizeof(map));
    bg.get()->updateMap(map);
}


void SpelFase::postload() {
}
