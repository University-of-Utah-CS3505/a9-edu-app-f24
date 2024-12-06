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
const float32 SCALE = 50.0;

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
        b2Vec2(0, height() / SCALE),  // Top left
        b2Vec2(width() / SCALE, height() / SCALE),   // Top right
        b2Vec2(width() / SCALE, 0),    // Bottom right
        b2Vec2(0, 0)    // Bottom left
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

// Override resize event to adjust physics world
void box2DWidget::resizeEvent(QResizeEvent *event){
    if(!resized){
        createGroundBody();
        resized = true;
    }
}


void box2DWidget::dropRadical(Character& character) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;

    // Use widget's width for random positioning
    float randomX = QRandomGenerator::global()->bounded(width()/ SCALE);
    float randomY = QRandomGenerator::global()->bounded(height()/ SCALE);
    bodyDef.position.Set(randomX, randomY);
    // Create body in the world
    b2Body* body = m_world->CreateBody(&bodyDef);

    // Create shape for radical (using a box shape)
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 1.0f);  // Size is in meters

    // Debug: Show body position and container position
    qDebug() << "Body Position:" << body->GetPosition().x << body->GetPosition().y;

    // Create fixture
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.5f;  // Bouncy factor
    body->CreateFixture(&fixtureDef);

    Character tempCharacter = character;
    body->SetUserData(new QString(tempCharacter.getCharacter()));    // Store the body for later rendering/cleanup
    m_radicalBodies.append(body);

    images.push_back(&character.getImage());

    // Trigger a repaint to show the new radical
    update();
}

void box2DWidget::updatePhysics() {
    // Step the physics world
    m_world->Step(TIME_STEP, VELOCITY_ITERATIONS, POSITION_ITERATIONS);

    // // Remove bodies that are out of bounds
    // for (auto it = m_radicalBodies.begin(); it != m_radicalBodies.end();) {
    //     b2Body* body = *it;
    //     b2Vec2 position = body->GetPosition();

    //     if (position.y > height() + 100) {  // If fallen way below widget
    //         m_world->DestroyBody(body);
    //         it = m_radicalBodies.erase(it);
    //     } else {
    //         ++it;
    //     }
    // }

    // Update the widget
    update();
}

void box2DWidget::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Draw container outline
    painter.setPen(QPen(Qt::black, 2));
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(0, 0, width(), height());

    int index = 0;
    // Draw radicals with updated scaling
    for (auto* body : m_radicalBodies) {
        b2Vec2 position = body->GetPosition();
        float angle = body->GetAngle();

        qDebug() << "X:" << position.x << ", Y:" << position.y;

        // Apply scaling to Box2D world coordinates
        int scaledX = position.x * SCALE;
        int scaledY = position.y * SCALE;

        painter.save();
        painter.translate(scaledX, scaledY);
        painter.rotate(angle * 180.0f / b2_pi);

        // Adjusted box size based on scaling
        QRect rect = QRect(-1.0 * SCALE , -1.0 * SCALE, SCALE, SCALE);
        painter.drawRect(rect);
        painter.drawImage(rect, *images[index++]);

        painter.restore();
    }
}

void box2DWidget::clear(){
    images.clear();
    m_radicalBodies.clear();
    update();
}
