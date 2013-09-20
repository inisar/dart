#include "RigidBody.h"
#include "renderer/RenderInterface.h"
#include <iostream>

using namespace Eigen;

void RigidBody::draw(renderer::RenderInterface* _ri) {
    if (!_ri)
        return;

    _ri->setPenColor(mColor);

    _ri->pushMatrix();
    _ri->translate(mPosition);
    if (mShape->getShapeType() == kinematics::Shape::P_BOX)
        _ri->drawCube(mShape->getDim());
    else if (mShape->getShapeType() == kinematics::Shape::P_ELLIPSOID)
        _ri->drawEllipsoid(mShape->getDim());
    else
        std::cout << "Unknown shape" << std::endl;
    _ri->popMatrix();
}