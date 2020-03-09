#include "UISystem.h"

UISystem::UISystem(GameWorld *gameworld) :
    System(gameworld),
    orthographic_camera(std::make_shared<Camera>())
{
    g = Graphics::getGlobalInstance();
    orthographic_camera->setUI(true);
    orthographic_camera->setOrthographicUI(true);
}

UISystem::~UISystem()
{

}

void UISystem::resizeCamera(int width, int height) {
    orthographic_camera->setScreenSize(glm::vec2(width,height));
}

void UISystem::addComponent(UIComponent *component) {
    m_components.insert(component);
}

void UISystem::removeComponent(UIComponent *component) {
    m_components.erase(component);
}

void UISystem::tick(float seconds) {
    for (auto it = m_components.begin(); it != m_components.begin(); it++) {
        UIComponent *comp = *it;
        comp->tick(seconds);
    }
}

void UISystem::draw(Graphics *g) {
    g->setCamera(orthographic_camera);
    auto it = m_components.begin();
    while(it != m_components.end()) {
        UIComponent *comp = *it;
        comp->drawSelf();
        it++;
    }
}
