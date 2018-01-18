#pragma once

#include "OGLib/pointf.h"
#include "OGLib/size.h"

namespace og
{
class Camera
{
    oglib::Size mSize;
    oglib::PointF mPosition;
    float mZoom;

public:
    Camera()
        : mZoom(1)
    {
    }

    void SetSize(int aWidth, int aHeight)
    {
        mSize.Set(aWidth, aHeight);
    }

    int GetWidth() const
    {
        return mSize.width();
    }

    int GetHeight() const
    {
        return mSize.height();
    }

    float GetScaledWidth() const
    {
        return mSize.width() * mZoom;
    }

    float GetScaledHeight() const
    {
        return mSize.height() * mZoom;
    }

    void SetPosition(float aX, float aY)
    {
        mPosition.Set(aX, aY);
    }

    const oglib::PointF& GetPosition() const
    {
        return mPosition;
    }

    void SetZoom(float aZoom)
    {
        Q_ASSERT_X(aZoom != 0.0f, "SetZoom", "aZoom equal to zero");
        mZoom = aZoom;
    }

    float GetZoom() const
    {
        return mZoom;
    }
};
} // ns:og