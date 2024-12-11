#ifndef BOX2DWIDGET_H
#define BOX2DWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QPainter>

// Forward declarations for Box2D classes
class b2World;
class b2Body;
class Character;  // Include your Character class forward declaration

/// <summary>
/// The box2DWidget class provides a custom QWidget for simulating and displaying a Box2D physics world.
/// It manages the creation, updating, and rendering of physics objects, including dynamic bodies and the ground.
/// Team Members: Bingkun Han, Shu Chen, Rohith Veeramachaneni, Ping-Hsun Hsieh
/// Course: CS3500 - A9 Educational App
/// </summary>
class box2DWidget : public QWidget
{
    Q_OBJECT

    bool resized = false;
    QList<QImage*> images;
public:
    /// <summary>
    /// Constructs a box2DWidget instance.
    /// Initializes the physics world and sets up the widget.
    /// </summary>
    explicit box2DWidget(QWidget *parent = nullptr);

    /// <summary>
    /// Destructor for cleaning up Box2D resources.
    /// </summary>
    ~box2DWidget();  // Destructor to clean up Box2D resources

    /// <summary>
    /// Drops a radical with a specified character into the physics world.
    /// </summary>
    void dropRadical(Character& character);

    /// <summary>
    /// Deletes all objects in the Box2D world.
    /// </summary>
    void clear();

protected:
    /// <summary>
    /// Paints the physics objects on the widget.
    /// </summary>
    void paintEvent(QPaintEvent *event) override;

    /// <summary>
    /// Handles widget resizing and adjusts the physics world accordingly.
    /// </summary>
    void resizeEvent(QResizeEvent *event) override;

private:
    b2World* m_world;             ///< Pointer to the Box2D world
    b2Body* m_groundBody;         ///< Ground body in the Box2D world
    QList<b2Body*> m_radicalBodies; ///< List to store dynamic bodies (radicals)
    QTimer* m_physicTimer;        ///< Timer for updating the physics simulation

    /// <summary>
    /// Initializes the Box2D physics world.
    /// </summary>
    void initializePhysicsWorld();

    /// <summary>
    /// Creates the ground body in the physics world.
    /// </summary>
    void createGroundBody();

    /// <summary>
    /// Updates the physics simulation at each time step.
    /// </summary>
    void updatePhysics();

signals:
};

#endif // BOX2DWIDGET_H
