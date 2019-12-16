//
// Created by Wouter Groeneveld on 30/11/18.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_NAIVE_CONWAYSCENE_H
#define GBA_SPRITE_ENGINE_PROJECT_NAIVE_CONWAYSCENE_H


#include "TetrisMenu.h"

using namespace std;

class SpelFase : public TetrisMenu {
protected:
    bool test = false;
    vector<int> blokNext;
    vector<int> blokHuidig ;
    vector<int> bouwen;
    int timer = 0;
    int kleurNext = 0;
    int kleurHuidig ;
    int draai = 0;
    int timerp = 0;
    int teller = 10;

    bool start;
    bool begin = true;
    bool beweeg = true;
    bool pauze = false;
    int ph1;
    int ph2;
    int ph3;
    int ph4;

public:
    SpelFase(const std::shared_ptr<GBAEngine> &engine) : TetrisMenu(engine) {}


    void tick(u16 keys) override;
    int kiesBlokjeNext() ;
    vector<int> maakBlokjeNext(int kleur);
    void tekenBlokjeNext();

    vector<int> maakBlokjeHuidig(int kleur);
    void tekenBlokjeHuidig(u16 keys);
    bool binnenBlijvenLinks();
    bool binnenBlijvenRechts();

    bool binnenBlijvenLinksR();
    bool binnenBlijvenRechtsR();

    bool checkRechts();
    bool checkLinks();

    void roteren(int kleur);
    void verwijderLijn();
    bool beneden();
    bool dood();

    void postload() override;
};


#endif //GBA_SPRITE_ENGINE_PROJECT_CONWAYSCENE_H
