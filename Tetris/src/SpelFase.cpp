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

int SpelFase::kiesBlokjeNext() {
    int rd =  rand() % 7;
    return rd;
}

vector<int> SpelFase::maakBlokjeNext(int kleur)  {
    blokNext.clear();
    if(kleur == 0){
        blokNext.push_back((32*5)+24);
        blokNext.push_back((32*6)+22);
        blokNext.push_back((32*6)+23);
        blokNext.push_back((32*6)+24);
    }else if(kleur == 1){
        blokNext.push_back((32*5)+22);
        blokNext.push_back((32*6)+22);
        blokNext.push_back((32*6)+23);
        blokNext.push_back((32*6)+24);
    }else if(kleur == 2){
        blokNext.push_back((32*5)+22);
        blokNext.push_back((32*5)+23);
        blokNext.push_back((32*6)+23);
        blokNext.push_back((32*6)+24);
    }else if(kleur == 3){
        blokNext.push_back((32*5)+23);
        blokNext.push_back((32*6)+22);
        blokNext.push_back((32*6)+23);
        blokNext.push_back((32*6)+24);
    }else if(kleur == 4){
        blokNext.push_back((32*5)+22);
        blokNext.push_back((32*5)+23);
        blokNext.push_back((32*6)+22);
        blokNext.push_back((32*6)+23);
    }else if(kleur == 5){
        blokNext.push_back((32*5)+24);
        blokNext.push_back((32*6)+24);
        blokNext.push_back((32*7)+24);
        blokNext.push_back((32*8)+24);
    }else if(kleur == 6){
        blokNext.push_back((32*6)+22);
        blokNext.push_back((32*6)+23);
        blokNext.push_back((32*5)+23);
        blokNext.push_back((32*5)+24);
    }

    return blokNext;
}

void SpelFase::tekenBlokjeNext() {

    if(beneden() == true || begin == true) {
        begin = false;
        start = true;
        kleurHuidig = kleurNext;
        for(int i = 5; i<9;i++){
            for(int j = 22; j<26;j++){
                int pos = (32*i)+j;
                buffer[pos] = ZWART;
            }
        }
        kleurNext = kiesBlokjeNext();
        vector<int> next = maakBlokjeNext(kleurNext);
        u16 color;
        switch(kleurNext) {
            case 0 : color = ROZE; break;
            case 1 : color = BLAUW; break;
            case 2 : color = ORANJE; break;
            case 3 : color = PAARS; break;
            case 4 : color = GEEL; break;
            case 5 : color = LICHTBL; break;
            case 6 : color = GROEN; break;
        }

        for (int i = 0; i < next.size(); i++) {
            buffer[next[i]] = color;
        }
    }

}

vector<int> SpelFase::maakBlokjeHuidig(int kleur) {

    blokHuidig.clear();
    if(start == true) {
        if (kleur == 0) {
            ph1 = (32 * 0) + 10;
            ph2 = (32 * 1) + 10;
            ph3 = (32 * 1) + 8;
            ph4 = (32 * 1) + 9;
        } else if (kleur == 1) {
            ph1 = (32 * 0) + 8;
            ph2 = (32 * 1) + 8;
            ph3 = (32 * 1) + 10;
            ph4 = (32 * 1) + 9;
        } else if (kleur == 2) {
            ph1 = (32 * 0) + 8;
            ph2 = (32 * 0) + 9;
            ph3 = (32 * 1) + 10;
            ph4 = (32 * 1) + 9;
        } else if (kleur == 3) {
            ph1 = (32 * 0) + 9;
            ph2 = (32 * 1) + 8;
            ph3 = (32 * 1) + 10;
            ph4 = (32 * 1) + 9;
        } else if (kleur == 4) {
            ph1 = (32 * 0) + 8;
            ph2 = (32 * 0) + 9;
            ph3 = (32 * 1) + 8;
            ph4 = (32 * 1) + 9;
        } else if (kleur == 5) {
            ph1 = (32 * 0) + 9;
            ph2 = (32 * 1) + 9;
            ph3 = (32 * 2) + 9;
            ph4 = (32 * 3) + 9;
        } else if (kleur == 6) {
            ph1 = (32 * 0) + 9;
            ph2 = (32 * 0) + 10;
            ph3 = (32 * 1) + 8;
            ph4 = (32 * 1) + 9;
        }
        start = false;
    }

    blokHuidig.push_back(ph1);
    blokHuidig.push_back(ph2);
    blokHuidig.push_back(ph3);
    blokHuidig.push_back(ph4);

    return blokHuidig;
}

bool SpelFase::binnenBlijvenLinks() {
    for(int i =0; i<MAP_HEIGHT; i++){
        int x = i*32;
        if (ph1 == 5+x || ph2 == 5+x || ph3 == 5+x || ph4 == 5+x) {
            return false;
        }
    }
    return true;
}

bool SpelFase::binnenBlijvenRechts() {
    for(int i =0; i<MAP_HEIGHT; i++){
        int x = i*32;
        if(ph1 == 14+x || ph2 == 14+x || ph3 == 14+x || ph4 == 14+x){
            return false;
        }
    }
    return true;
}

void SpelFase::roteren(int kleur) {
    if(kleur == 0){
        if (draai == 0) {
            ph1 = ph1 + 64;
            ph2 = ph2 + 31;
            ph3 = ph3 - 31;
            ph4 = ph4 + 0;
            draai = 1;
        } else if (draai == 1) {
            ph1 = ph1 - 2;
            ph2 = ph2 - 33;
            ph3 = ph3 + 33;
            ph4 = ph4 + 0;
            draai = 2;
        } else if (draai == 2) {
            ph1 = ph1 - 64;
            ph2 = ph2 - 31;
            ph3 = ph3 + 31;
            ph4 = ph4 + 0;
            draai = 3;
        } else if (draai == 3) {
            ph1 = ph1 + 2;
            ph2 = ph2 + 33;
            ph3 = ph3 - 33;
            ph4 = ph4 - 0;
            draai = 0;
        }
    }else if(kleur == 1){
        if (draai == 0) {
            ph1 = ph1 + 2;
            ph2 = ph2 - 31;
            ph3 = ph3 + 31;
            ph4 = ph4 + 0;
            draai = 1;
        } else if (draai == 1) {
            ph1 = ph1 + 64;
            ph2 = ph2 + 33;
            ph3 = ph3 - 33;
            ph4 = ph4 + 0;
            draai = 2;
        } else if (draai == 2) {
            ph1 = ph1 - 2;
            ph2 = ph2 + 31;
            ph3 = ph3 - 31;
            ph4 = ph4 + 0;
            draai = 3;
        } else if (draai == 3) {
            ph1 = ph1 - 64;
            ph2 = ph2 - 33;
            ph3 = ph3 + 33;
            ph4 = ph4 - 0;
            draai = 0;
        }
    }else if(kleur == 2){
        if (draai == 0) {
            ph1 = ph1 + 1;
            ph2 = ph2 + 32;
            ph3 = ph3 + 30;
            ph4 = ph4 - 1;
            draai = 1;
        } else if (draai == 1) {
            ph1 = ph1 - 1;
            ph2 = ph2 - 32;
            ph3 = ph3 - 30;
            ph4 = ph4 + 1;
            draai = 2;
        } else if (draai == 2) {
            ph1 = ph1 + 1;
            ph2 = ph2 + 32;
            ph3 = ph3 + 30;
            ph4 = ph4 - 1;
            draai = 3;
        } else if (draai == 3) {
            ph1 = ph1 - 1;
            ph2 = ph2 - 32;
            ph3 = ph3 - 30;
            ph4 = ph4 + 1;
            draai = 0;
        }
    }else if(kleur == 3) {
        if (draai == 0) {
            ph1 = ph1 + 33;
            ph2 = ph2 - 31;
            ph3 = ph3 + 31;
            ph4 = ph4 + 0;
            draai = 1;
        } else if (draai == 1) {
            ph1 = ph1 + 31;
            ph2 = ph2 + 33;
            ph3 = ph3 - 33;
            ph4 = ph4 + 0;
            draai = 2;
        } else if (draai == 2) {
            ph1 = ph1 - 33;
            ph2 = ph2 + 31;
            ph3 = ph3 - 31;
            ph4 = ph4 + 0;
            draai = 3;
        } else if (draai == 3) {
            ph1 = ph1 - 31;
            ph2 = ph2 - 33;
            ph3 = ph3 + 33;
            ph4 = ph4 - 0;
            draai = 0;
        }
    }else if(kleur == 5){
        if (draai == 0) {
            ph1 = ph1 + 31;
            ph2 = ph2 - 0;
            ph3 = ph3 - 31;
            ph4 = ph4 - 62;
            draai = 1;
        } else if (draai == 1) {
            ph1 = ph1 - 31;
            ph2 = ph2 + 00;
            ph3 = ph3 + 31;
            ph4 = ph4 + 62;
            draai = 2;
        } else if (draai == 2) {
            ph1 = ph1 + 31;
            ph2 = ph2 - 0;
            ph3 = ph3 - 31;
            ph4 = ph4 - 62;
            draai = 3;
        } else if (draai == 3) {
            ph1 = ph1 - 31;
            ph2 = ph2 + 00;
            ph3 = ph3 + 31;
            ph4 = ph4 + 62;
            draai = 0;
        }
    }else if(kleur == 6){
        if (draai == 0) {
            ph1 = ph1 + 33;
            ph2 = ph2 + 64;
            ph3 = ph3 - 31;
            ph4 = ph4 - 0;
            draai = 1;
        } else if (draai == 1) {
            ph1 = ph1 - 33;
            ph2 = ph2 - 64;
            ph3 = ph3 + 31;
            ph4 = ph4 + 0;
            draai = 2;
        } else if (draai == 2) {
            ph1 = ph1 + 33;
            ph2 = ph2 + 64;
            ph3 = ph3 - 31;
            ph4 = ph4 - 0;
            draai = 3;
        } else if (draai == 3) {
            ph1 = ph1 - 33;
            ph2 = ph2 - 64;
            ph3 = ph3 + 31;
            ph4 = ph4 + 0;
            draai = 0;
        }
    }

}

bool SpelFase::beneden() {
    for(int i = 5; i < 15; i++){
        if(ph1 == 608+i || ph2 == 608+i || ph3 == 608+i || ph4 == 608+i ){
            return true;
        }
    }
    return false;
}

void SpelFase::tekenBlokjeHuidig(u16 keys) {


        if(beneden() != true) {
            for (int i = 0; i < 4; i++) {
                buffer[blokHuidig[i]] = ZWART;
            }
        }
        if((keys & KEY_RIGHT) && binnenBlijvenRechts() == true && beweeg == true){
            ph1 = ph1 + 1;
            ph2 = ph2 + 1;
            ph3 = ph3 + 1;
            ph4 = ph4 + 1;
            beweeg = false;
        }else if((keys & KEY_LEFT) && binnenBlijvenLinks() == true && beweeg == true){
            ph1 = ph1 - 1;
            ph2 = ph2 - 1;
            ph3 = ph3 - 1;
            ph4 = ph4 - 1;
            beweeg = false;
        }else if((keys & KEY_UP) && beweeg == true){
            roteren(kleurHuidig);
            beweeg = false;

        }
    if(timer == 30) {
        timer = 0;
        ph1 = ph1 + 32;
        ph2 = ph2 + 32;
        ph3 = ph3 + 32;
        ph4 = ph4 + 32;
        beweeg =true;
    }
        TextStream::instance().setText(to_string(ph4), 0, 1);
        vector<int> huidig = maakBlokjeHuidig(kleurHuidig);
        u16 color;
        switch(kleurHuidig) {
            case 0 : color = ROZE; break;
            case 1 : color = BLAUW; break;
            case 2 : color = ORANJE; break;
            case 3 : color = PAARS; break;
            case 4 : color = GEEL; break;
            case 5 : color = LICHTBL; break;
            case 6 : color = GROEN; break;
        }


        for (int i = 0; i < huidig.size(); i++) {
            buffer[huidig[i]] = color;
        }
        if(beneden() == true) {
            draai = 0;
        }
    timer = timer + 1;


}


void SpelFase::tick(u16 keys) {
    dma3_cpy(buffer, map, sizeof(buffer));

    tekenBlokjeNext();
    tekenBlokjeHuidig(keys);


    dma3_cpy(map, buffer, sizeof(map));
    bg.get()->updateMap(map);
}


void SpelFase::postload() {
}
