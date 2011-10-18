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

#ifndef CONTACT_H
#define CONTACT_H

// Libraries
#include "Constraint.h"
#include "../collision/ContactInfo.h"
#include "../body/RigidBody.h"
#include "../constants.h"
#include "../mathematics/mathematics.h"
#include "../memory/MemoryPool.h"
#include <new>
#ifdef VISUAL_DEBUG
    #include <GLUT/glut.h>
    #include <OpenGL/gl.h>
#endif

// ReactPhysics3D namespace
namespace reactphysics3d {

/*  -------------------------------------------------------------------
    Class Contact :
        This class represents a collision contact between two bodies in
        the physics engine. The contact class inherits from the
        Constraint class. Each Contact represent a contact between two bodies
        and contains the two contact points on each body. The contact has 3
        mathematical constraints (1 for the contact constraint, and 2
        for the friction constraints).
    -------------------------------------------------------------------
*/
class Contact : public Constraint {
    protected :
        const Vector3 normal;                   // Normal vector of the contact (From body1 toward body2) in world space
        double penetrationDepth;                // Penetration depth
        const Vector3 localPointOnBody1;        // Contact point on body 1 in local space of body 1
        const Vector3 localPointOnBody2;        // Contact point on body 2 in local space of body 2
        Vector3 worldPointOnBody1;              // Contact point on body 1 in world space
        Vector3 worldPointOnBody2;              // Contact point on body 2 in world space
        std::vector<Vector3> frictionVectors;   // Two orthogonal vectors that span the tangential friction plane
        double mu_mc_g;
        
        void computeFrictionVectors();                  // Compute the two friction vectors that span the tangential friction plane

    public :
        Contact(const ContactInfo* contactInfo);        // Constructor
        virtual ~Contact();                             // Destructor

        Vector3 getNormal() const;                                                     // Return the normal vector of the contact
        void setPenetrationDepth(double penetrationDepth);                             // Set the penetration depth of the contact
        Vector3 getLocalPointOnBody1() const;                                          // Return the contact local point on body 1
        Vector3 getLocalPointOnBody2() const;                                          // Return the contact local point on body 2
        Vector3 getWorldPointOnBody1() const;                                          // Return the contact world point on body 1
        Vector3 getWorldPointOnBody2() const;                                          // Return the contact world point on body 2
        void setWorldPointOnBody1(const Vector3& worldPoint);                          // Set the contact world point on body 1
        void setWorldPointOnBody2(const Vector3& worldPoint);                          // Set the contact world point on body 2
        virtual void computeJacobian(int noConstraint, Matrix1x6**& J_SP) const;       // Compute the jacobian matrix for all mathematical constraints
        virtual void computeLowerBound(int noConstraint, Vector& lowerBounds) const;   // Compute the lowerbounds values for all the mathematical constraints
        virtual void computeUpperBound(int noConstraint, Vector& upperBounds) const;   // Compute the upperbounds values for all the mathematical constraints
        virtual void computeErrorValue(int noConstraint, Vector& errorValues) const;   // Compute the error values for all the mathematical constraints
        double getPenetrationDepth() const;                                            // Return the penetration depth
        #ifdef VISUAL_DEBUG
           void draw() const;                                                          // Draw the contact (for debugging)
        #endif

        //void* operator new(size_t, MemoryPool<Contact>& pool) throw(std::bad_alloc);                 // Overloaded new operator for customized memory allocation
        //void operator delete(void* p, MemoryPool<Contact>& pool);                               // Overloaded delete operator for customized memory allocation
};

// Compute the two unit orthogonal vectors "v1" and "v2" that span the tangential friction plane
// The two vectors have to be such that : v1 x v2 = contactNormal
inline void Contact::computeFrictionVectors() {
    // Delete the current friction vectors
    frictionVectors.clear();

    // Compute the first orthogonal vector
    Vector3 vector1 = normal.getOneOrthogonalVector();
    frictionVectors.push_back(vector1);

    // Compute the second orthogonal vector using the cross product
    frictionVectors.push_back(normal.cross(vector1));
}

// Return the normal vector of the contact
inline Vector3 Contact::getNormal() const {
    return normal;
}

// Set the penetration depth of the contact
inline void Contact::setPenetrationDepth(double penetrationDepth) {
    this->penetrationDepth = penetrationDepth;
}

// Return the contact point on body 1
inline Vector3 Contact::getLocalPointOnBody1() const {
    return localPointOnBody1;
}

// Return the contact point on body 2
inline Vector3 Contact::getLocalPointOnBody2() const {
    return localPointOnBody2;
}

// Return the contact world point on body 1
inline Vector3 Contact::getWorldPointOnBody1() const {
    return worldPointOnBody1;
}

// Return the contact world point on body 2
inline Vector3 Contact::getWorldPointOnBody2() const {
    return worldPointOnBody2;
}

// Set the contact world point on body 1
inline void Contact::setWorldPointOnBody1(const Vector3& worldPoint) {
    worldPointOnBody1 = worldPoint;
}

// Set the contact world point on body 2
inline void Contact::setWorldPointOnBody2(const Vector3& worldPoint) {
    worldPointOnBody2 = worldPoint;
}

// Return the penetration depth of the contact
inline double Contact::getPenetrationDepth() const {
    return penetrationDepth;
}


#ifdef VISUAL_DEBUG
// TODO : Delete this (Used to debug collision detection)
inline void Contact::draw() const {
    glColor3f(1.0, 0.0, 0.0);
    glutSolidSphere(0.3, 20, 20);
}
#endif

} // End of the ReactPhysics3D namespace

#endif
