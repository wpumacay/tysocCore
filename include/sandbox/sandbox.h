
#pragma once

#include <tysoc_common.h>

namespace tysoc {
namespace sandbox {

    struct TJoint;

    struct TBody
    {

        std::string name;
        std::string type;
        std::string filename;

        TVec3 size;
        TMat4 worldTransform;
        TVec3 color;

        TScalar mass;
        TMat3   inertia;
        TVec3   friction;

        std::vector< TJoint* > joints;

        TBody()
        {
            name = "undefined";
            type = "box";
            filename = "";

            size = { 0.1, 0.1, 0.1 };
            color = { 0.25f, 1.0f, 0.25f };

            mass = 0.0f;
            friction = { 1.0, 0.005, 0.0001 };
        }
    };

    struct TJoint
    {
        std::string name;
        std::string type;

        TVec3 axis;
        TMat4 relTransform;
        TMat4 worldTransform;

        TVec2 limits;

        TBody* parentBodyPtr;
    };




}}