#ifndef SCREEN_H
#define SCREEN_H

#include <QKeyEvent>
#include <map>

#include "src/engine/graphics/Graphics.h"

class Application;
class GameWorld;

class Screen : std::enable_shared_from_this<Screen>
{
public:
    Screen(Application *parent);
    virtual ~Screen();

    virtual void tick(float seconds) = 0;
    virtual void draw(Graphics *g) = 0;

    virtual void resize(int width, int height) = 0;

    virtual void onKeyPressed(QKeyEvent *event);
    virtual void onKeyReleased(QKeyEvent *event);
    virtual void onKeyRepeated(QKeyEvent *event) = 0;
    virtual void onMousePressed(QMouseEvent *event);
    virtual void onMouseReleased(QMouseEvent *event);
    virtual void onMouseDragged(int deltaX, int deltaY) = 0;
    virtual void onWheelEvent(QWheelEvent *event) = 0;

    virtual void restartScreen();

    std::shared_ptr<Screen> getSharedPtr() {
        return shared_from_this();
    }

protected:
    Application *m_parent;
    std::shared_ptr<GameWorld> m_gameworld;
};

#endif // SCREEN_H
