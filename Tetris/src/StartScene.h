//
// Created by Wouter Groeneveld on 30/11/18.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_STARTSCENE_H
#define GBA_SPRITE_ENGINE_PROJECT_STARTSCENE_H


#include <libgba-sprite-engine/scene.h>

using namespace std;

class StartScene : public Scene {
private:

    unique_ptr<Sprite> sprite;

public:
    StartScene(const shared_ptr<GBAEngine> &engine);

    vector<Sprite *> sprites() override;

    vector<Background *> backgrounds() override;

    void load() override;

    void tick(u16 keys) override;

};


#endif //GBA_SPRITE_ENGINE_PROJECT_STARTSCENE_H
