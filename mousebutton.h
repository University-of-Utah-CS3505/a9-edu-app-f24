#ifndef MOUSEBUTTON_H
#define MOUSEBUTTON_H
#include <QMouseEvent>

/**
 *  Team Name : Sam's Club
 *
 *  Team Members : Rohith Veeramachaneni, Shu Chen, Bingkun Han and PING-HSUN HSIEH
 *
 *  Contributor's Names of mouseButton.h : Shu Chen, Bingkun Han
 *
 *  Date Modified : November 10, 2024
 *
 *  Header class for mouse button
 */


/**
 * @brief The buttonType enum
 *        all the mouse actions can be used as enum
 */
enum buttonType
{
    leftButtonUp,
    leftButtonDown,
    rightButtonDown,
    rightButtonUp,
    middleButtonScroll,
    mouseMove
};

/**
 * @brief The MouseButton class
 * this class is a class to describe the mouse press action, like click scroll, or other elese
 * we will record where it happened and how many times it proceed.
 */
class MouseButton
{
    buttonType buttonType;
    QPointF pos;
    int amount;

public:
    /**
     * @brief MouseButton constructor of mouse button
     * @param btn what type action it is
     * @param pos the position of this mouse consor
     * @param amount how many times this mouse action did
     */
    MouseButton(enum buttonType btn, QPointF pos, int amount);

    /**
     * @brief getButtonType to get the type of button action
     * @return enum, name of the button action
     */
    const enum buttonType &getButtonType() const;

    /**
     * @brief getAmount, get how many times this button action done
     * @return int the number of the action
     */
    int getAmount() const;

    /**
     * @brief getPos, get the position of this mouse action
     * @return QPointF as the relative position of this action.
     */
    QPointF getPos() const;
};

#endif // MOUSEBUTTON_H
