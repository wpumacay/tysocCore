#pragma once

#include <tysoc_common.h>

namespace tysoc {

    enum class eShapeType
    {
        NONE = 0,
        BOX, 
        PLANE, 
        SPHERE, 
        CYLINDER, 
        CAPSULE, 
        MESH
    };

    enum class eJointType
    {
        FREE = 0,
        REVOLUTE,
        PRISMATIC,
        SPHERICAL,
        PLANAR,
        FIXED
    };

    std::string toString( const eShapeType& type );
    std::string toString( const eJointType& type );

    struct TShapeData
    {
        eShapeType  type;       // type of collision shape (see enum above)
        TVec3       size;       // size of the collision shape (e.g. x->radius for sphere shapes)
        TVec3       localPos;   // relative position w.r.t. parent body
        TMat3       localRot;   // relative orientation w.r.t. parent body
        std::string filename;   // in case of a mesh shape, abs-path for the resource
    };

    std::string toString( const TShapeData& shapeData );

    struct TJointData
    {
        eJointType  type;               // type of joint (see enum above)
        TVec3       axis;               // axis of joint to be constructed
        TMat4       tfParentBody2Joint; // current body's parent w.r.t. this joint
        TMat4       tfThisBody2Joint;   // current body w.r.t. this joint
        TVec2       limits;             // motion range (lo==hi: fixed, lo>hi: continuous, lo<hi: limited)
    };

    struct TCollisionData : public TShapeData
    {
        int     collisionGroup;
        int     collisionMask;
        TScalar density;
        TScalar friction;
    };

    struct TVisualData : public TShapeData
    {
        TVec3    ambient;   // ambient-color (rgb) of the renderable associated with this shape
        TVec3    diffuse;   // diffuse-color (rgb) of the renderable associated with this shape
        TVec3    specular;  // specular-color (rgb) of the renderable associated with this shape
        TScalar  shininess; // shininess-value for the specular-component of the color material
    };

}