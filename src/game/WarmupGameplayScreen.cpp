#include "WarmupGameplayScreen.h"
#include "src/engine/util/Input.h"
#include "src/engine/common/component/TransformComponent.h"
#include "src/engine/common/component/DrawableComponent.h"

WarmupGameplayScreen::WarmupGameplayScreen(Graphics *g, WarmupApplication *parent_app) :
    Screen(parent_app)
{

    initializeGameWorld();
    off_ground = false;
    y_vel = 0.0f;

    m_camera = std::make_shared<Camera>();
    m_camera->setEye(glm::vec3(1,1,1));
    m_camera->setLook(glm::vec3(0,0,1));
    Material myFirstMaterial;
    myFirstMaterial.color = glm::vec3(0, 1, 0);
    g->addMaterial("boringGreen", myFirstMaterial);

    Material mySecondMaterial;
    mySecondMaterial.textureName = "grass";
    mySecondMaterial.textureRepeat = glm::vec2(10,10);
    g->addMaterial("grassMaterial", mySecondMaterial);
}

WarmupGameplayScreen::~WarmupGameplayScreen() {
}

void WarmupGameplayScreen::initializeGameWorld() {
    m_gameworld->addSystem<DrawSystem>(std::make_shared<DrawSystem>(m_gameworld));
    m_gameworld->addSystem<TickSystem>(std::make_shared<TickSystem>(m_gameworld));
    m_gameworld->addSystem<ControlCallbackSystem>(std::make_shared<ControlCallbackSystem>(m_gameworld));
    m_gameworld->addSystem<CollisionSystem>(std::make_shared<CollisionSystem>(m_gameworld));

    //make floor
    std::shared_ptr<GameObject> floor = std::make_shared<GameObject>(m_gameworld);
    floor->addComponent<TransformComponent>(std::make_shared<TransformComponent>(floor, glm::vec3(0,0,0)));
    Material floor_mat;
    floor_mat.textureName = "grass";
    floor_mat.textureRepeat = glm::vec2(10,10);
    floor->addComponent<DrawableComponent>(std::make_shared<DrawableComponent>(floor, "quad", "grassTexture", floor_mat));
    m_gameworld->addGameObject(floor);
    std::cout << "hello" << std::endl;

    //make camera


}

void WarmupGameplayScreen::draw(Graphics *g) {
    g->setCamera(m_camera);
    g->clearTransform();
    g->scale(20.0);
    g->setMaterial("grassMaterial");
    g->drawShape("quad");

    g->clearTransform();
    g->setDefaultMaterial();
    g->translate(glm::vec3(1.0f, 1.0f, 10.0f));
    g->scale(5);
    g->drawShape("cylinder");
}

void WarmupGameplayScreen::tick(float seconds) {
    glm::vec3 look = m_camera->getLook();
    glm::vec3 dir = glm::normalize(glm::vec3(look.x, 0, look.z));
    glm::vec3 perp = glm::vec3(dir.z, 0, -dir.x);

    if (Input::getPressed("W")) m_camera->translate(dir * WALK_SPEED);
    if (Input::getPressed("S")) m_camera->translate(-dir * WALK_SPEED);
    if (Input::getPressed("A")) m_camera->translate(perp * WALK_SPEED);
    if (Input::getPressed("D")) m_camera->translate(-perp * WALK_SPEED);
    if (Input::getPressed("R")) {
        restartApplication();
    }

    // handle jumping
    if (Input::getPressed("SPACE") && !off_ground) {
        std::cout << "jumped" << std::endl;
        off_ground = true;
        y_vel = JUMP_SPEED;
    }

    // handle falling back to ground
    if (m_camera->getEye().y < 1) {
        std::cout << "hit ground" << std::endl;
        off_ground = false;
        y_vel = 0;
        m_camera->setEye(glm::vec3(m_camera->getEye().x, 1.0f, m_camera->getEye().z));
    }

    // handle chaning y value
    m_camera->setEye(glm::vec3(m_camera->getEye().x, m_camera->getEye().y + y_vel, m_camera->getEye().z));
    if (off_ground) {
        y_vel += GRAVITY * seconds;
    }
}


void WarmupGameplayScreen::onMouseDragged(int deltaX, int deltaY) {
    m_camera->rotate(-deltaX / 100.0f * MOUSE_SENSITIVITY, -deltaY / 100.0f * MOUSE_SENSITIVITY);
}


void WarmupGameplayScreen::restartApplication() {
    m_parent->restart();
}

void WarmupGameplayScreen::restartScreen() {
    Screen::restartScreen();
    off_ground = false;
    y_vel = 0.0f;

    m_camera = std::make_shared<Camera>();
    m_camera->setEye(glm::vec3(1,1,1));
    m_camera->setLook(glm::vec3(0,0,1));
}

void WarmupGameplayScreen::resize(int w, int h) {
    m_camera->setScreenSize(glm::vec2(w, h));
}


