//
// Created by Wouter Groeneveld on 30/11/18.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_TETRISALGM_H
#define GBA_SPRITE_ENGINE_PROJECT_TETRISALGM_H

#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/gba_engine.h>

#define MAP_WIDTH 32
#define MAP_HEIGHT GBA_SCREEN_HEIGHT / 8
#define MAP_SIZE MAP_WIDTH * MAP_HEIGHT

#define ROZE 0x0000
#define BLAUW 0x0001
#define ORANJE 0x0002
#define PAARS 0x0003
#define GEEL 0x0004
#define LICHTBL 0x0005
#define WIT 0x0006
#define ZWART 0x0007
#define GROEN 0x0008


class TetrisAlgm : public Scene {
protected:
    std::unique_ptr<Background> bg;
    u16 map[MAP_SIZE] = {ROZE}, buffer[MAP_SIZE] = {ROZE};

    u16 getNextState(int x, int y, int pos);
    u16 getNextStateWithCount(int currentState, int count);
    int countAmountOfNeighbouringCellsAlive(int pos, int x, int y);


public:
    TetrisAlgm(const std::shared_ptr<GBAEngine> &engine) : Scene(engine) {}

    std::vector<Sprite *> sprites() override;

    std::vector<Background *> backgrounds() override;



    void load() override;

    virtual void postload() = 0;

    virtual void tick(u16 keys) = 0;
};


#endif //GBA_SPRITE_ENGINE_PROJECT_TETRISALGM_H
