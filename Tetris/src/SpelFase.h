//
// Created by Wouter Groeneveld on 30/11/18.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_NAIVE_CONWAYSCENE_H
#define GBA_SPRITE_ENGINE_PROJECT_NAIVE_CONWAYSCENE_H


#include "TetrisAlgm.h"

using namespace std;

class SpelFase : public TetrisAlgm {
private:
    bool test = false;
    vector<int> blokNext;
    vector<int> blokHuidig ;
    vector<int> bouwen;
    int timer = 20;
    int kleurNext = 0;
    int kleurHuidig ;

    bool start;
    bool begin = true;
    bool beweeg = true;
    int draai = 0;

    int ph1;
    int ph2;
    int ph3;
    int ph4;

public:
    SpelFase(const std::shared_ptr<GBAEngine> &engine) : TetrisAlgm(engine) {}


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

    void roteren(int kleur);
    void verwijderLijn();
    bool beneden();

    void postload() override;
};


#endif //GBA_SPRITE_ENGINE_PROJECT_CONWAYSCENE_H
