#ifndef COLLISIONCOMPONENT_H
#define COLLISIONCOMPONENT_H

#include "Component.h"
#include "src/engine/common/GameWorld.h"

class CollisionComponent : public Component
{
public:
    CollisionComponent();
    ~CollisionComponent() override;
    void addSelfToSystems(std::shared_ptr<GameWorld> gw) override;
    void removeSelfFromSystems(std::shared_ptr<GameWorld> gw) override;
};

#endif // COLLISIONCOMPONENT_H
