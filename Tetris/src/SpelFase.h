//
// Created by Pieter Paulissen on 15/12/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_NAIVE_CONWAYSCENE_H
#define GBA_SPRITE_ENGINE_PROJECT_NAIVE_CONWAYSCENE_H


#include "TetrisMenu.h"

using namespace std;

class SpelFase : public TetrisMenu {
protected:
    bool test = false;
    vector<int> blokNext;
    vector<int> blokHuidig;
    vector<int> blokHold;
    vector<int> bouwen;
    int timer = 0;
    int kleurNext = 0;
    int kleurHuidig;
    int kleurHold = 7;
    int kleurSwitch;
    int draai = 0;
    int timerp = 0;
    int teller = 15;

    bool start;
    bool begin = true;
    bool beweeg = true;
    bool pauze = false;
    bool holdAlGebruikt = false;
    int posCurrent1;
    int posCurrent2;
    int posCurrent3;
    int posCurrent4;

public:
    SpelFase(const std::shared_ptr<GBAEngine> &engine) : TetrisMenu(engine) {}

    void tick(u16 keys) override;
    int kiesBlokjeNext() ;
    vector<int> maakBlokjeNext(int kleur);
    void tekenBlokjeNext();

    vector<int> maakBlokjeHold(int kleur);
    void tekenBlokjeHold();

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
