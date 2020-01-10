//
// Created by Pieter Paulissen on 15/12/2019.
//

#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/gba/tonc_core.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <bits/stdc++.h>

#include "SpelFase.h"
#include "TetrisMenu.h"
#include <cstdlib>


using namespace std;

/**
 * berekent een random nummer van 0 tot 6
 * @return die random waarde
 */
int SpelFase::kiesBlokjeNext() {
    int rd =  rand() % 7;
    return rd;
}

/**
 * hier worden afhankelijk van welke kleur er gegenereerd is het blokje zijn posities gemaakt
 * @param kleur is de waarde van het gegenereerde random nummer
 * @return een vector met de posities in
 */
vector<int> SpelFase::maakBlokjeNext(int kleur)  {
    blokNext.clear();
    if(kleur == 0){
        blokNext.push_back((32*4)+27);
        blokNext.push_back((32*5)+25);
        blokNext.push_back((32*5)+26);
        blokNext.push_back((32*5)+27);
    }else if(kleur == 1){
        blokNext.push_back((32*4)+25);
        blokNext.push_back((32*5)+25);
        blokNext.push_back((32*5)+26);
        blokNext.push_back((32*5)+27);
    }else if(kleur == 2){
        blokNext.push_back((32*4)+25);
        blokNext.push_back((32*4)+26);
        blokNext.push_back((32*5)+26);
        blokNext.push_back((32*5)+27);
    }else if(kleur == 3){
        blokNext.push_back((32*4)+26);
        blokNext.push_back((32*5)+25);
        blokNext.push_back((32*5)+26);
        blokNext.push_back((32*5)+27);
    }else if(kleur == 4){
        blokNext.push_back((32*4)+25);
        blokNext.push_back((32*4)+26);
        blokNext.push_back((32*5)+25);
        blokNext.push_back((32*5)+26);
    }else if(kleur == 5){
        blokNext.push_back((32*4)+27);
        blokNext.push_back((32*5)+27);
        blokNext.push_back((32*6)+27);
        blokNext.push_back((32*7)+27);
    }else if(kleur == 6){
        blokNext.push_back((32*5)+25);
        blokNext.push_back((32*5)+26);
        blokNext.push_back((32*4)+26);
        blokNext.push_back((32*4)+27);
    }

    return blokNext;
}

/**
 * hier worden afhankelijk van welke kleur het huidige blokje heeft zijn posities gemaakt
 * @param kleur is de waarde van de kleur van het blokje
 * @return een vector met de posities in
 */
vector<int> SpelFase::maakBlokjeHold(int kleur)  {
    blokHold.clear();
    if(kleur == 0){
        blokHold.push_back((32*4)+21);
        blokHold.push_back((32*5)+19);
        blokHold.push_back((32*5)+20);
        blokHold.push_back((32*5)+21);
    }else if(kleur == 1){
        blokHold.push_back((32*4)+19);
        blokHold.push_back((32*5)+19);
        blokHold.push_back((32*5)+20);
        blokHold.push_back((32*5)+21);
    }else if(kleur == 2){
        blokHold.push_back((32*4)+19);
        blokHold.push_back((32*4)+20);
        blokHold.push_back((32*5)+20);
        blokHold.push_back((32*5)+21);
    }else if(kleur == 3){
        blokHold.push_back((32*4)+20);
        blokHold.push_back((32*5)+19);
        blokHold.push_back((32*5)+20);
        blokHold.push_back((32*5)+21);
    }else if(kleur == 4){
        blokHold.push_back((32*4)+19);
        blokHold.push_back((32*4)+20);
        blokHold.push_back((32*5)+19);
        blokHold.push_back((32*5)+20);
    }else if(kleur == 5){
        blokHold.push_back((32*4)+20);
        blokHold.push_back((32*5)+20);
        blokHold.push_back((32*6)+20);
        blokHold.push_back((32*7)+20);
    }else if(kleur == 6){
        blokHold.push_back((32*5)+19);
        blokHold.push_back((32*5)+20);
        blokHold.push_back((32*4)+20);
        blokHold.push_back((32*4)+21);
    }

    return blokHold;
}

/**
 * hier wordt eerst de ruimte waar het blokje hold getekend wordt zwart gemaakt om vervolgens het blokje te tekenen
 * door middel van het in de buffer te steken
 * Als het spel begint, blijft deze ruimte zwart, dit wordt aangeduid met de kleur 7
 */
void SpelFase::tekenBlokjeHold() {
    if (holdAlGebruikt == false & !(kleurHuidig == kleurHold)){
        holdAlGebruikt = true;
        start = true;
        if (kleurHold == 7){
            kleurHold = kleurHuidig;
            kleurHuidig = kleurNext;
            tekenBlokjeNext();
        }else{
            kleurSwitch = kleurHuidig;
            kleurHuidig = kleurHold;
            kleurHold = kleurSwitch;
        }


        for(int i = 4; i<8;i++){
            for(int j = 19; j<22;j++){
                int pos = (32*i)+j;
                buffer[pos] = ZWART;
            }
        }

        vector<int> hold = maakBlokjeHold(kleurHold);
        u16 color;
        switch(kleurHold) {
            case 0 : color = ROZE; break;
            case 1 : color = BLAUW; break;
            case 2 : color = ORANJE; break;
            case 3 : color = PAARS; break;
            case 4 : color = GEEL; break;
            case 5 : color = LICHTBL; break;
            case 6 : color = GROEN; break;
            case 7 : color = ROZE; break;
        }

        for (int i = 0; i < hold.size(); i++) {
            buffer[hold[i]] = color;
        }

    }
}

/**
 * hier wordt eerst de ruimte waar het blokje next getekend wordt zwart gemaakt om vervolgens het blokje te tekenen
 * door middel van het in de buffer te steken
 */
void SpelFase::tekenBlokjeNext() {

    if(beneden() == true || begin == true) {
        begin = false;
        start = true;
        kleurHuidig = kleurNext;
        for(int i = 4; i<8;i++){
            for(int j = 25; j<28;j++){
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

/**
 * hier worden afhankelijk van welke kleur er gegenereerd is het blokje zijn posities gemaakt
 * @param kleur is de waarde van het gegenereerde random nummer
 * @return een vector met de posities in
 */
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

/**
 * zorgt ervoor dat je niet langs links het speelveld kan verlaten
 * @return true indien je je nog naar links kan begeven
 */
bool SpelFase::binnenBlijvenLinks() {
    for(int i =0; i<MAP_HEIGHT; i++){
        int x = i*32;
        if (ph1 == 5+x || ph2 == 5+x || ph3 == 5+x || ph4 == 5+x) {
            return false;
        }
    }
    return true;
}

/**
 * kijkt of we het blokje kunnen roteren zonder dat we het speelveld verlaten langs de linkerkant
 * @return true indien je nog kan roteren
 */
bool SpelFase::binnenBlijvenLinksR() {
    for(int i =0; i<MAP_HEIGHT; i++){
        int x = i*32;
        if (ph1 == 4+x || ph2 == 4+x || ph3 == 4+x || ph4 == 4+x) {
            return false;
        }
    }
    return true;
}

/**
 * zorgt ervoor dat je niet langs rechts het speelveld kan verlaten
 * @return true indien je je nog naar rechts kan begeven
 */
bool SpelFase::binnenBlijvenRechts() {
    for(int i =0; i<MAP_HEIGHT; i++){
        int x = i*32;
        if(ph1 == 14+x || ph2 == 14+x || ph3 == 14+x || ph4 == 14+x){
            return false;
        }
    }
    return true;
}


/**
 * kijkt of we het blokje kunnen roteren zonder dat we het speelveld verlaten langs de rechterkant
 * @return true indien je nog kan roteren
 */
bool SpelFase::binnenBlijvenRechtsR() {
    for(int i =0; i<MAP_HEIGHT; i++){
        int x = i*32;
        if(ph1 == 15+x || ph2 == 15+x || ph3 == 15+x || ph4 == 15+x){
            return false;
        }
    }
    return true;
}

/**
 * afhankelijk van de huidige positie wordt het blokje gedraaid
 * er wordt altijd gecontroleerd of we het blokje kunnen draaien
 * @param kleur de kleur van het huidige blokje
 */
void SpelFase::roteren(int kleur) {
    if(kleur == 0){
        if (draai == 0) {
            ph1 = ph1 + 64;
            ph2 = ph2 + 31;
            ph3 = ph3 - 31;
            ph4 = ph4 + 0;
            if(binnenBlijvenLinksR() == true && binnenBlijvenRechtsR() == true){
                draai = 1;
            }else{
                ph1 = ph1 - 64;
                ph2 = ph2 - 31;
                ph3 = ph3 + 31;
                ph4 = ph4 + 0;
            }

        } else if (draai == 1) {
            ph1 = ph1 - 2;
            ph2 = ph2 - 33;
            ph3 = ph3 + 33;
            ph4 = ph4 + 0;
            if(binnenBlijvenLinksR() == true && binnenBlijvenRechtsR() == true){
                draai = 2;
            }else{
                ph1 = ph1 + 2;
                ph2 = ph2 + 33;
                ph3 = ph3 - 33;
                ph4 = ph4 - 0;
            }
        } else if (draai == 2) {
            ph1 = ph1 - 64;
            ph2 = ph2 - 31;
            ph3 = ph3 + 31;
            ph4 = ph4 + 0;
            if(binnenBlijvenLinksR() == true && binnenBlijvenRechtsR() == true){
                draai = 3;
            }else{
                ph1 = ph1 - 2;
                ph2 = ph2 - 33;
                ph3 = ph3 + 33;
                ph4 = ph4 - 0;
            }
        } else if (draai == 3) {
            ph1 = ph1 + 2;
            ph2 = ph2 + 33;
            ph3 = ph3 - 33;
            ph4 = ph4 - 0;
            if(binnenBlijvenLinksR() == true && binnenBlijvenRechtsR() == true){
                draai = 0;
            }else{
                ph1 = ph1 - 2;
                ph2 = ph2 - 33;
                ph3 = ph3 + 33;
                ph4 = ph4 - 0;
            }
        }
    }else if(kleur == 1){
        if (draai == 0) {
            ph1 = ph1 + 2;
            ph2 = ph2 - 31;
            ph3 = ph3 + 31;
            ph4 = ph4 + 0;
            if(binnenBlijvenLinksR() == true && binnenBlijvenRechtsR() == true){
                draai = 1;
            }else{
                ph1 = ph1 - 2;
                ph2 = ph2 + 31;
                ph3 = ph3 - 31;
                ph4 = ph4 + 0;
            }
        } else if (draai == 1) {
            ph1 = ph1 + 64;
            ph2 = ph2 + 33;
            ph3 = ph3 - 33;
            ph4 = ph4 + 0;
            if(binnenBlijvenLinksR() == true && binnenBlijvenRechtsR() == true){
                draai = 2;
            }else{
                ph1 = ph1 - 64;
                ph2 = ph2 - 33;
                ph3 = ph3 + 33;
                ph4 = ph4 + 0;
            }
        } else if (draai == 2) {
            ph1 = ph1 - 2;
            ph2 = ph2 + 31;
            ph3 = ph3 - 31;
            ph4 = ph4 + 0;
            if(binnenBlijvenLinksR() == true && binnenBlijvenRechtsR() == true){
                draai = 3;
            }else{
                ph1 = ph1 + 2;
                ph2 = ph2 - 31;
                ph3 = ph3 + 31;
                ph4 = ph4 + 0;
            }
        } else if (draai == 3) {
            ph1 = ph1 - 64;
            ph2 = ph2 - 33;
            ph3 = ph3 + 33;
            ph4 = ph4 - 0;
            if(binnenBlijvenLinksR() == true && binnenBlijvenRechtsR() == true){
                draai = 0;
            }else{
                ph1 = ph1 + 64;
                ph2 = ph2 + 33;
                ph3 = ph3 - 33;
                ph4 = ph4 - 0;
            }
        }
    }else if(kleur == 2){
        if (draai == 0) {
            ph1 = ph1 + 1;
            ph2 = ph2 + 32;
            ph3 = ph3 + 30;
            ph4 = ph4 - 1;
            if(binnenBlijvenLinksR() == true && binnenBlijvenRechtsR() == true){
                draai = 1;
            }else{
                ph1 = ph1 - 1;
                ph2 = ph2 - 32;
                ph3 = ph3 - 30;
                ph4 = ph4 + 1;
            }
        } else if (draai == 1) {
            ph1 = ph1 - 1;
            ph2 = ph2 - 32;
            ph3 = ph3 - 30;
            ph4 = ph4 + 1;
            if(binnenBlijvenLinksR() == true && binnenBlijvenRechtsR() == true){
                draai = 0;
            }else{
                ph1 = ph1 + 1;
                ph2 = ph2 + 32;
                ph3 = ph3 + 30;
                ph4 = ph4 - 1;
            }
        }
    }else if(kleur == 3) {
        if (draai == 0) {
            ph1 = ph1 + 33;
            ph2 = ph2 - 31;
            ph3 = ph3 + 31;
            ph4 = ph4 + 0;
            if(binnenBlijvenLinksR() == true && binnenBlijvenRechtsR() == true){
                draai = 1;
            }else{
                ph1 = ph1 - 33;
                ph2 = ph2 + 31;
                ph3 = ph3 - 31;
                ph4 = ph4 + 0;
            }
        } else if (draai == 1) {
            ph1 = ph1 + 31;
            ph2 = ph2 + 33;
            ph3 = ph3 - 33;
            ph4 = ph4 + 0;
            if(binnenBlijvenLinksR() == true && binnenBlijvenRechtsR() == true){
                draai = 2;
            }else{
                ph1 = ph1 - 31;
                ph2 = ph2 - 33;
                ph3 = ph3 + 33;
                ph4 = ph4 + 0;
            }
        } else if (draai == 2) {
            ph1 = ph1 - 33;
            ph2 = ph2 + 31;
            ph3 = ph3 - 31;
            ph4 = ph4 + 0;
            if(binnenBlijvenLinksR() == true && binnenBlijvenRechtsR() == true){
                draai = 3;
            }else{
                ph1 = ph1 + 33;
                ph2 = ph2 - 31;
                ph3 = ph3 + 31;
                ph4 = ph4 + 0;
            }
        } else if (draai == 3) {
            ph1 = ph1 - 31;
            ph2 = ph2 - 33;
            ph3 = ph3 + 33;
            ph4 = ph4 - 0;
            if(binnenBlijvenLinksR() == true && binnenBlijvenRechtsR() == true){
                draai = 0;
            }else{
                ph1 = ph1 + 31;
                ph2 = ph2 + 33;
                ph3 = ph3 - 33;
                ph4 = ph4 - 0;
            }
        }
    }else if(kleur == 5){
        if (draai == 0) {
            ph1 = ph1 + 31;
            ph2 = ph2 - 0;
            ph3 = ph3 - 31;
            ph4 = ph4 - 62;
            if(binnenBlijvenLinksR() == true && binnenBlijvenRechtsR() == true){
                draai = 1;
            }else{
                ph1 = ph1 - 31;
                ph2 = ph2 - 0;
                ph3 = ph3 + 31;
                ph4 = ph4 + 62;
            }
        } else if (draai == 1) {
            ph1 = ph1 - 31;
            ph2 = ph2 + 0;
            ph3 = ph3 + 31;
            ph4 = ph4 + 62;
            if(binnenBlijvenLinksR() == true && binnenBlijvenRechtsR() == true){
                draai = 0;
            }else{
                ph1 = ph1 + 31;
                ph2 = ph2 - 0;
                ph3 = ph3 - 31;
                ph4 = ph4 - 62;
            }
        }
    }else if(kleur == 6){
        if (draai == 0) {
            ph1 = ph1 + 33;
            ph2 = ph2 + 64;
            ph3 = ph3 - 31;
            ph4 = ph4 - 0;
            if(binnenBlijvenLinksR() == true && binnenBlijvenRechtsR() == true){
                draai = 1;
            }else{
                ph1 = ph1 - 33;
                ph2 = ph2 - 64;
                ph3 = ph3 + 31;
                ph4 = ph4 - 0;
            }
        } else if (draai == 1) {
            ph1 = ph1 - 33;
            ph2 = ph2 - 64;
            ph3 = ph3 + 31;
            ph4 = ph4 + 0;
            if(binnenBlijvenLinksR() == true && binnenBlijvenRechtsR() == true){
                draai = 0;
            }else{
                ph1 = ph1 + 33;
                ph2 = ph2 + 64;
                ph3 = ph3 - 31;
                ph4 = ph4 - 0;
            }
        }
    }

}

/**
 * controleert of het blokje beneden is of dat het blokje op een ander blokje staat
 * @return true indien hij beneden is
 */
bool SpelFase::beneden() {
    for(int j = 0; j<bouwen.size(); j++){
        if(bouwen[j] == ph1 + 32 || bouwen[j] == ph2 + 32 || bouwen[j] == ph3 + 32 || bouwen[j] == ph4 + 32 ){
            return true;
        }
    }
    for(int i = 5; i < 15; i++){
        if(ph1 == 608+i || ph2 == 608+i || ph3 == 608+i || ph4 == 608+i ){
            return true;
        }
    }
    return false;
}

/**
 * er wordt gecontroleerd of je met het dalende blokje naar links kan bewegen
 * @return false indien je nog kan bewegen
 */
bool SpelFase::checkLinks() {
    for(int j = 0; j<bouwen.size(); j++){
        if(bouwen[j] == ph1 -1 || bouwen[j] == ph2 -1 || bouwen[j] == ph3 -1 || bouwen[j] == ph4 -1 ){
            return true;
        }
    }
    return false;
}

/**
 * er wordt gecontroleerd of je met het dalende blokje naar rechts kan bewegen
 * @return false indien je nog kan bewegen
 */
bool SpelFase::checkRechts()  {
    for(int j = 0; j<bouwen.size(); j++){
        if(bouwen[j] == ph1 +1 || bouwen[j] == ph2 +1 || bouwen[j] == ph3 +1 || bouwen[j] == ph4 +1 ){
            return true;
        }
    }
    return false;
}

/**
 * controleert of je nog verder kan spelen
 * @return true indien je dood bent
 */
bool SpelFase::dood() {
    sort(bouwen.begin(), bouwen.end());
        for(int j = 5; j<15; j++){
            if(bouwen[0] == j){
                return true;
            }
        }
    return false;
}

/**
 * controleert of er een lijn verwijderd kan worden
 * indien dat zo is, worden alle bovenliggende blokken naar beneden verplaatst met de juist kleur
 */
void SpelFase::verwijderLijn() {
    sort(bouwen.begin(), bouwen.end());
    for(int i = 0; i < 20; i++){
        int tss = (i*32) + 5 ;
        if(bouwen.size() > 10) {
            for (int j = 0; j < bouwen.size(); j++) {
                if(bouwen.size() >= j + 9  && tss == bouwen[j]) {
                    if (tss + 1 == bouwen[j + 1]){
                        if(tss + 2 == bouwen[j + 2]){
                            if(tss + 3 == bouwen[j + 3]){
                                if(tss + 4 == bouwen[j + 4]){
                                    if(tss + 5 == bouwen[j + 5]){
                                        if(tss + 6 == bouwen[j + 6]){
                                            if(tss + 7 == bouwen[j + 7] ){
                                                if (tss + 8 == bouwen[j + 8]) {
                                                    if (tss + 9 == bouwen[j + 9]) {
                                                        for (int z = j; z > -1; z--) {
                                                            bouwen[z] = bouwen[z] + 32;
                                                        }
                                                        bouwen.erase(bouwen.begin() + j + 9);
                                                        bouwen.erase(bouwen.begin() + j + 8);
                                                        bouwen.erase(bouwen.begin() + j + 7);
                                                        bouwen.erase(bouwen.begin() + j + 6);
                                                        bouwen.erase(bouwen.begin() + j + 5);
                                                        bouwen.erase(bouwen.begin() + j + 4);
                                                        bouwen.erase(bouwen.begin() + j + 3);
                                                        bouwen.erase(bouwen.begin() + j + 2);
                                                        bouwen.erase(bouwen.begin() + j + 1);
                                                        bouwen.erase(bouwen.begin() + j);


                                                        for (int k = i - 1; k > -1; k--) {
                                                            int lijn = k * 32;
                                                            for (int l = 5; l < 15; l++) {
                                                                int pos = lijn + l;
                                                                u16 color = map[pos];
                                                                buffer[pos + 32] = color;
                                                            }
                                                        }
                                                        score = score + 100;
                                                        level = (score / 500) + 1;
                                                        for (int n = 1; n < 16; n++) {
                                                            if (score == 500 * n) {
                                                                if (teller > 1) {
                                                                    teller = teller - 1;
                                                                }
                                                            }
                                                        }
                                                        dma3_cpy(map, buffer, sizeof(map));
                                                        bg.get()->updateMap(map);
                                                        verwijderLijn();
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

/**
 * Hierin wordt het huidig blokje getekend
 * of het wordt in positie lager getekend afhankelijk van de fase waarin het zich bevindt
 * @param keys
 */
void SpelFase::tekenBlokjeHuidig(u16 keys) {
        if(beneden() != true) {
            for (int i = 0; i < 4; i++) {
                buffer[blokHuidig[i]] = ZWART;
            }
        }else{
            for (int i = 0; i < 4; i++) {
                bouwen.push_back(blokHuidig[i]);
            }
            holdAlGebruikt = false;
            verwijderLijn();
        }
        if((keys & KEY_RIGHT) && binnenBlijvenRechts() == true && checkRechts() == false && beweeg == true){
            ph1 = ph1 + 1;
            ph2 = ph2 + 1;
            ph3 = ph3 + 1;
            ph4 = ph4 + 1;
            beweeg = false;
        }
        if((keys & KEY_LEFT) && binnenBlijvenLinks() == true &&  checkLinks() == false && beweeg == true){
            ph1 = ph1 - 1;
            ph2 = ph2 - 1;
            ph3 = ph3 - 1;
            ph4 = ph4 - 1;
            beweeg = false;
        }
        if((keys & KEY_UP) && beweeg == true){
            roteren(kleurHuidig);
            beweeg = false;
        }
        if((keys & KEY_DOWN) && beweeg == true){
            ph1 = ph1 + 32;
            ph2 = ph2 + 32;
            ph3 = ph3 + 32;
            ph4 = ph4 + 32;
            beweeg = false;
        }
        if(timer == teller /2){
            beweeg == true;
        }

        if(timer == teller) {
            timer = 0;
            ph1 = ph1 + 32;
            ph2 = ph2 + 32;
            ph3 = ph3 + 32;
            ph4 = ph4 + 32;
            beweeg =true;

        }
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

/**
 * er wordt een controler gedaan op pauze dood of opnieuw beginnen
 * anders gaat het spel gewoon verder
 * hierin wordt de map steeds geupdatet
 * @param keys
 */
void SpelFase::tick(u16 keys) {
    dma3_cpy(buffer, map, sizeof(buffer));
    timerp = timerp + 1;
    if(pauze == false && dood() == false) {
        tekenBlokjeNext();
        tekenBlokjeHuidig(keys);
        update();
        TextStream::instance().setText("", 6, 7);
    }else if(pauze == true){
        TextStream::instance().setText("PAUZE", 6, 7);
    }else if(dood() == true){
        TextStream::instance().setText("DOOD", 6, 7);
    }
    if((keys & KEY_A) && timerp == 5){
        timerp == 0;
        if(pauze == false){
            pauze = true;
        }else{
            pauze = false;
        }
    }else if((keys & KEY_SELECT) && holdAlGebruikt == false){
        tekenBlokjeHold();
        tekenBlokjeHuidig(keys);
    }
    else if((keys & KEY_B) && timerp == 5){
        timerp == 0;
        timer = 0;
        kleurNext = 0;
        kleurHold = 7;
        draai = 0;
        begin = true;
        beweeg = true;
        pauze = false;
        bouwen.clear();
        score = 0;
        level = 1;
        teller = 15;
        update();

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
        tekenBlokjeNext();
        tekenBlokjeHuidig(keys);

    }

    if(timerp == 5){
        timerp = 0;
    }

    dma3_cpy(map, buffer, sizeof(map));
    bg.get()->updateMap(map);
}


void SpelFase::postload() {
}
