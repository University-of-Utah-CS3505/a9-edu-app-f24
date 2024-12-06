#ifndef BOX2DWIDGET_H
#define BOX2DWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QPainter>

// Forward declarations for Box2D classes
class b2World;
class b2Body;
class Character;  // Include your Character class forward declaration

class box2DWidget : public QWidget
{
    Q_OBJECT

    bool resized = false;
    QList<QImage*> images;
public:
    explicit box2DWidget(QWidget *parent = nullptr);
    ~box2DWidget();  // Destructor to clean up Box2D resources

    // Method to drop a radical with a specific character
    void dropRadical(Character& character);

    // Delete all objects in box2D
    void clear();

protected:
    // Override paint event to draw physics objects
    void paintEvent(QPaintEvent *event) override;

    // Override resize event to adjust physics world
    void resizeEvent(QResizeEvent *event) override;

private:
    // Box2D world pointer
    b2World* m_world;

    // Ground body
    b2Body* m_groundBody;

    // List to store dynamic bodies (radicals)
    QList<b2Body*> m_radicalBodies;

    // Physics simulation timer
    QTimer* m_physicTimer;

    // Physics world initialization method
    void initializePhysicsWorld();

    // Create ground body method
    void createGroundBody();

    // Update physics simulation
    void updatePhysics();

signals:
         // You can add signals here if needed
};

#endif // BOX2DWIDGET_H
