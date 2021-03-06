#include "og_fly.h"

using namespace og;

struct OGFlyImpl
{
    OGPhysicsBody* pBody;
};

OGFly::OGFly(OGPhysicsBody* body)
{
    pImpl_ = new OGFlyImpl;
    pImpl_->pBody = body;
}

OGFly::~OGFly()
{
    delete pImpl_;
}
