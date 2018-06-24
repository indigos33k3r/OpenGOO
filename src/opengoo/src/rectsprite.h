#pragma once

#include "GameEngine/graphic.h"

class RectSprite : public og::Graphic
{
public:
    RectSprite(const QSizeF& aSize, const QColor aColor = Qt::green)
        : mRect(QPointF(), aSize)
        , mColor(aColor)
    {
        mRect.moveCenter(mRect.topLeft());
    }

    float GetAngle() const
    {
        return mAngle;
    }

    void SetAngle(float aAngle)
    {
        mAngle = aAngle;
    }

    void SetScaleX(float)
    {
    }

    void SetScaleY(float)
    {
    }

    float GetScaleX() const
    {
        return 1;
    }

    float GetScaleY() const
    {
        return 1;
    }

private:
    void Update()
    {
    }

    void Render(QPainter& aPainter, float aX, float aY)
    {
        aPainter.save();
        aPainter.setPen(mColor);
        aPainter.translate(aX, aY);
        aPainter.rotate(mAngle);
        aPainter.drawRect(mRect);
        aPainter.restore();
    }

    void Render(QPainter& aPainter, const QVector2D& aPos)
    {
        Render(aPainter, aPos.x(), aPos.y());
    }

private:
    QRectF mRect;
    QColor mColor;
    float mAngle;
};