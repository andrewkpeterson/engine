#ifndef UISYSTEM_H
#define UISYSTEM_H

#include "System.h"
#include "src/engine/common/GameObject.h"
#include "src/engine/common/component/DrawableComponent.h"
#include "src/engine/common/system/CameraSystem.h"
#include "src/engine/common/component/CameraComponent.h"
#include "src/engine/common/component/UIComponent.h"

class UISystem : public System
{
public:
    UISystem(GameWorld *gameworld);
    ~UISystem();
    void addComponent(UIComponent *component);
    void removeComponent(UIComponent *component);
    void resizeCamera(int width, int height);
    void draw(Graphics *g);
    void tick(float seconds);

private:
    Graphics *g;
    std::unordered_set<UIComponent*> m_components;
    std::shared_ptr<Camera> orthographic_camera;
};

#endif // UISYSTEM_H
