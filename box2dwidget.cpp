#include "box2dwidget.h"
#include "Box2D/Box2D.h"
#include "character.h"
#include <QPainter>
#include <QRandomGenerator>
#include <QDebug>

// Physics simulation constants
const float32 TIME_STEP = 1.0f / 60.0f; // Simulation time step
const int32 VELOCITY_ITERATIONS = 6;    // Velocity constraint solver iterations
const int32 POSITION_ITERATIONS = 2;   // Position constraint solver iterations
const float32 SCALE = 50.0;            // Scaling factor for Box2D coordinates to pixels

/// <summary>
/// Constructs a box2DWidget instance and sets up the Box2D physics world.
/// Initializes the timer for physics simulation updates.
/// </summary>
box2DWidget::box2DWidget(QWidget *parent)
    : QWidget(parent),
    m_world(nullptr),
    m_groundBody(nullptr),
    m_physicTimer(nullptr)
{
    // Enable mouse tracking for potential future interactions
    setMouseTracking(true);

    // Initialize physics world
    initializePhysicsWorld();

    images = QList<QImage*>();

    // Setup physics update timer
    m_physicTimer = new QTimer(this);
    connect(m_physicTimer, &QTimer::timeout, this, &box2DWidget::updatePhysics);
    m_physicTimer->start(16); // ~60 FPS
}

/// <summary>
/// Destructor to clean up Box2D resources.
/// </summary>
box2DWidget::~box2DWidget() {
    // Cleanup physics world
    if (m_world) {
        delete m_world;
    }
}

/// <summary>
/// Initializes the Box2D physics world with gravity and creates the ground body.
/// </summary>
void box2DWidget::initializePhysicsWorld() {
    // Create gravity vector (downward)
    b2Vec2 gravity(0.0f, 9.8f);
    m_world = new b2World(gravity);

    // Create ground body
    createGroundBody();
}

/// <summary>
/// Creates the ground body and container walls in the Box2D world.
/// </summary>
void box2DWidget::createGroundBody() {
    if (!m_world) return; // Ensure the world is initialized

    // Define the static ground body
    b2BodyDef boundaryDef;
    boundaryDef.position.Set(0, 0);
    m_groundBody = m_world->CreateBody(&boundaryDef);

    // Define the container boundaries
    b2ChainShape containerShape;
    b2Vec2 vertices[4] = {
        b2Vec2(0, height() / SCALE),  // Top left
        b2Vec2(width() / SCALE, height() / SCALE),   // Top right
        b2Vec2(width() / SCALE, 0),    // Bottom right
        b2Vec2(0, 0)    // Bottom left
    };
    containerShape.CreateLoop(vertices, 4);

    // Attach the boundaries to the ground body
    b2FixtureDef containerFixtureDef;
    containerFixtureDef.shape = &containerShape;
    containerFixtureDef.density = 0.0f;
    containerFixtureDef.friction = 0.5f;
    m_groundBody->CreateFixture(&containerFixtureDef);
}

/// <summary>
/// Handles widget resizing and adjusts the physics container.
/// </summary>
void box2DWidget::resizeEvent(QResizeEvent *event){
    if(!resized){
        createGroundBody();
        resized = true;
    }
}

/// <summary>
/// Drops a radical with a specified character at a random position.
/// </summary>
void box2DWidget::dropRadical(Character& character) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;

    // Generate random starting position
    float randomX = QRandomGenerator::global()->bounded(width()/ SCALE);
    float randomY = QRandomGenerator::global()->bounded(height()/ SCALE);
    bodyDef.position.Set(randomX, randomY);

    // Create dynamic body in the world
    b2Body* body = m_world->CreateBody(&bodyDef);

    // Define the shape and properties of the radical
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 1.0f);  // 1x1 meter size
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.5f;  // Bounciness
    body->CreateFixture(&fixtureDef);

    // Store character data and add to the list
    body->SetUserData(new QString(character.getCharacter()));
    m_radicalBodies.append(body);
    images.push_back(&character.getImage());

    // Trigger a repaint
    update();
}

/// <summary>
/// Advances the physics simulation by one step.
/// </summary>
void box2DWidget::updatePhysics() {
    m_world->Step(TIME_STEP, VELOCITY_ITERATIONS, POSITION_ITERATIONS);
    update();
}

/// <summary>
/// Paints the Box2D world and rendered objects on the widget.
/// </summary>
void box2DWidget::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Draw the container outline
    painter.setPen(QPen(Qt::black, 2));
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(0, 0, width(), height());

    int index = 0;
    // Draw all radicals
    for (auto* body : m_radicalBodies) {
        b2Vec2 position = body->GetPosition();
        float angle = body->GetAngle();

        int scaledX = position.x * SCALE;
        int scaledY = position.y * SCALE;

        painter.save();
        painter.translate(scaledX, scaledY);
        painter.rotate(angle * 180.0f / b2_pi);

        QRect rect = QRect(-1.0 * SCALE, -1.0 * SCALE, SCALE, SCALE);
        painter.drawRect(rect);
        painter.drawImage(rect, *images[index++]);

        painter.restore();
    }
}

/// <summary>
/// Clears all radicals from the physics world.
/// </summary>
void box2DWidget::clear(){
    images.clear();
    m_radicalBodies.clear();
    update();
}
