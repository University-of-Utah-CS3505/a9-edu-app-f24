#include "mousebutton.h"

/**
 *  Team Name : Sam's Club
 *
 *  Team Members : Rohith Veeramachaneni, Shu Chen, Bingkun Han and PING-HSUN HSIEH
 *
 *  Contributor's Names of mouseButton.cpp : Shu Chen, Bingkun Han
 *
 *  Date Modified : November 10, 2024
 *
 *  MouseButton class has an enum to determine the mouse buttonType from list of leftButton up, down,
 *  rightMouse button up and down and also scrollWheel and moveMouse
 */

// this is the constructor of Mouse Button class, auto set button type, mouse position, and amout
MouseButton::MouseButton(enum buttonType btn, QPointF pos, int amount)
    : buttonType(btn), pos(pos), amount(amount)
{
}

// to get what type action this mouse button is
const enum buttonType &MouseButton::getButtonType() const
{
    return buttonType;
}

// to get how many types this mouse buttons did
int MouseButton::getAmount() const
{
    return amount;
}

// get co-ordinates in floating point type for where mouse cursor is at.
QPointF MouseButton::getPos() const
{
    return pos;
}
