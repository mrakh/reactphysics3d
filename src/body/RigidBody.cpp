/********************************************************************************
* ReactPhysics3D physics library, http://code.google.com/p/reactphysics3d/      *
* Copyright (c) 2010 Daniel Chappuis                                            *
*********************************************************************************
*                                                                               *
* Permission is hereby granted, free of charge, to any person obtaining a copy  *
* of this software and associated documentation files (the "Software"), to deal *
* in the Software without restriction, including without limitation the rights  *
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell     *
* copies of the Software, and to permit persons to whom the Software is         *
* furnished to do so, subject to the following conditions:                      *
*                                                                               *
* The above copyright notice and this permission notice shall be included in    *
* all copies or substantial portions of the Software.                           *
*                                                                               *
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR    *
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,      *
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE   *
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER        *
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, *
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN     *
* THE SOFTWARE.                                                                 *
********************************************************************************/

// Libraries
#include "RigidBody.h"
#include "../shapes/Shape.h"

// We want to use the ReactPhysics3D namespace
using namespace reactphysics3d;

 // Constructor
 RigidBody::RigidBody(const Transform& transform, double mass, const Matrix3x3& inertiaTensorLocal, Shape* shape, long unsigned id)
           : Body(transform, shape, mass, id), inertiaTensorLocal(inertiaTensorLocal),
             inertiaTensorLocalInverse(inertiaTensorLocal.getInverse()), massInverse(1.0/mass) {

    restitution = 1.0;

    // Set the body pointer of the AABB and the shape
    aabb->setBodyPointer(this);
    shape->setBodyPointer(this);

    assert(shape);
    assert(aabb);
}

// Destructor
RigidBody::~RigidBody() {

};

