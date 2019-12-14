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
    vector<int> blok;
    int timer = 0;

public:
    SpelFase(const std::shared_ptr<GBAEngine> &engine) : TetrisAlgm(engine) {}


    void tick(u16 keys) override;
    int kiesBlokje() ;
    vector<int> maakBlokje(int kleur);
    void postload() override;
};


#endif //GBA_SPRITE_ENGINE_PROJECT_CONWAYSCENE_H
