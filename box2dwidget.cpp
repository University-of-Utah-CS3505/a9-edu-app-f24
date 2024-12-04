#include "box2dwidget.h"
#include "Box2D/Box2D.h"
#include "character.h"
#include <QPainter>
#include <QRandomGenerator>
#include <QDebug>

// Physics simulation constants
const float32 TIME_STEP = 1.0f / 60.0f;
const int32 VELOCITY_ITERATIONS = 6;
const int32 POSITION_ITERATIONS = 2;

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

    // Setup physics update timer
    m_physicTimer = new QTimer(this);
    connect(m_physicTimer, &QTimer::timeout, this, &box2DWidget::updatePhysics);
    m_physicTimer->start(16); // ~60 FPS
}

box2DWidget::~box2DWidget() {
    // Cleanup physics world
    if (m_world) {
        delete m_world;
    }
}

void box2DWidget::initializePhysicsWorld() {
    // Create gravity vector (downward)
    b2Vec2 gravity(0.0f, 9.8f);
    m_world = new b2World(gravity);

    // Create ground body
    createGroundBody();
}

void box2DWidget::createGroundBody() {
    // If world is not initialized, return
    if (!m_world) return;

    // Create container boundaries
    b2BodyDef boundaryDef;
    boundaryDef.position.Set(0, 0);
    m_groundBody = m_world->CreateBody(&boundaryDef);

    // Define container walls using b2ChainShape
    b2ChainShape containerShape;

    // Define the vertices for the container
    b2Vec2 vertices[4] = {
        b2Vec2(-150.0f, -200.0f),  // Top left
        b2Vec2(150.0f, -200.0f),   // Top right
        b2Vec2(150.0f, 200.0f),    // Bottom right
        b2Vec2(-150.0f, 200.0f)    // Bottom left
    };

    // Create a closed loop shape
    containerShape.CreateLoop(vertices, 4);

    // Create fixture for the container
    b2FixtureDef containerFixtureDef;
    containerFixtureDef.shape = &containerShape;
    containerFixtureDef.density = 0.0f;
    containerFixtureDef.friction = 0.5f;

    // Create the fixture on the ground body
    m_groundBody->CreateFixture(&containerFixtureDef);
}

void box2DWidget::dropRadical(const Character& character) {

    // Create body definition for radical
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;

    // Random horizontal position within container
    float32 randomX = QRandomGenerator::global()->generateDouble() * 300.0f - 150.0f;
    bodyDef.position.Set(randomX, -180.0f);  // Start from top of container
    bodyDef.angle = QRandomGenerator::global()->generateDouble() * 3.14f; // Random initial rotation

    // Create body in the world
    b2Body* body = m_world->CreateBody(&bodyDef);

    // Create shape for radical (using a box shape)
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(20.0f, 20.0f);  // Adjust size as needed

    // Create fixture
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.5f;  // Bouncy factor

    body->CreateFixture(&fixtureDef);

    // Store the body for later rendering/cleanup
    m_radicalBodies.append(body);

    // Trigger a repaint to show the new radical
    update();
}

void box2DWidget::updatePhysics() {
    // Step the physics world
    m_world->Step(TIME_STEP, VELOCITY_ITERATIONS, POSITION_ITERATIONS);

    // Remove bodies that are out of bounds
    for (auto it = m_radicalBodies.begin(); it != m_radicalBodies.end();) {
        b2Body* body = *it;
        b2Vec2 position = body->GetPosition();

        if (position.y > height() + 100) {  // If fallen way below widget
            m_world->DestroyBody(body);
            it = m_radicalBodies.erase(it);
        } else {
            ++it;
        }
    }

    // Update the widget
    update();
}

void box2DWidget::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Calculate container position
    int containerWidth = 300;  // Matches wall dimensions from createGroundBody
    int containerHeight = 400;
    int containerX = (width() - containerWidth) / 2;
    int containerY = (height() - containerHeight) / 2;

    // Draw container outline
    painter.setPen(QPen(Qt::black, 2));
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(containerX, containerY, containerWidth, containerHeight);

    // Draw radicals
    painter.setBrush(Qt::blue);
    for (auto* body : m_radicalBodies) {
        b2Vec2 position = body->GetPosition();
        float32 angle = body->GetAngle();

        painter.save();
        painter.translate(containerX + position.x, containerY + position.y);
        painter.rotate(angle * 180.0f / b2_pi);
        painter.drawRect(-20, -20, 40, 40);  // Match box size from body definition
        painter.restore();
    }
}

void box2DWidget::resizeEvent(QResizeEvent *) {
    // Recreate ground body when widget is resized
    if (m_world && m_groundBody) {
        m_world->DestroyBody(m_groundBody);
        createGroundBody();
    }
}
