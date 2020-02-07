#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include <memory>
#include <map>

#include "src/engine/common/component/Component.h"
#include "src/engine/util/TypeMap.h"

class Component;
class GameWorld;

/**
 * To properly create a GameObject, we first make a shared_ptr<GameObject>. Next, we
 * create components and add those components to the GameObject. Finally, we add the
 * object to the GameWorld. The Components of the GameObject indicate which systems
 * the GameObject's components will be added to.
 *
 * To remove a GameObject from the GameWorld, we call the GameWorld's removeGameObject
 * method. This will also remove the GameObject's components from the GameWorld's
 * systems
 */
class GameObject
{
public:
    GameObject();
    ~GameObject();

    template <typename Comp>
    void addComponent(std::shared_ptr<Comp> &&c) {
      comps.put<Comp>(std::forward<std::shared_ptr<Comp>>(c));
    }
    void removeComponent(std::string name);
    template <typename Comp>
    Comp* getComponent() {
        auto it = comps.find<Comp>();
        assert(it != comps.end());
        return static_cast<Comp*>(it->second.get());
    }
    //void addComponent(std::shared_ptr<Component> component);
    //std::shared_ptr<Component> getComponent(std::string name);
    void addComponentsToSystems();
    void removeComponentsFromSystems();
    std::shared_ptr<GameWorld> getGameWorld();

private:
    std::map<std::string, std::shared_ptr<Component>> m_components;
    TypeMap<std::shared_ptr<Component>> comps;
    std::shared_ptr<GameWorld> m_gw;

};

#endif // GAMEOBJECT_H
