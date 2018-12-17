
#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <map>

typedef float TScalar;

#define TRANDOM( a, b ) ( a + ( b - a ) * ( rand() / ( float )RAND_MAX ) )

namespace tysoc
{

    struct TVec3
    {
        TScalar x; 
        TScalar y; 
        TScalar z;

        TVec3();
        TVec3( TScalar x, TScalar y, TScalar z );

        TVec3 operator* ( TScalar factor );
        TVec3 operator+ ( const TVec3& other );
        TVec3 operator- ( const TVec3& other );

        static TScalar dot( const TVec3& v1, const TVec3& v2 );
        static TVec3 cross( const TVec3& v1, const TVec3& v2 );
        static TScalar length( const TVec3& v );
        static std::string toString( const TVec3& v );
    };

    struct TVec4
    {
        TScalar x;
        TScalar y;
        TScalar z;
        TScalar w;

        TVec4();
        TVec4( TScalar x, TScalar y, TScalar z, TScalar w );
    };

    struct TMat3
    {
        TScalar buff[9];

        TMat3();
        TMat3( TScalar m00, TScalar m01, TScalar m02,
               TScalar m10, TScalar m11, TScalar m12,
               TScalar m20, TScalar m21, TScalar m22 );

        static TMat3 fromQuaternion( const TVec4& quat );
        static TMat3 fromEuler( const TVec3& euler );
    };

    struct TMat4
    {
        TScalar buff[16];

        TMat4();
        TMat4( const TMat4& other );
        TMat4( TScalar m00, TScalar m01, TScalar m02, TScalar m03,
               TScalar m10, TScalar m11, TScalar m12, TScalar m13,
               TScalar m20, TScalar m21, TScalar m22, TScalar m23,
               TScalar m30, TScalar m31, TScalar m32, TScalar m33 );

        TMat4& operator= ( const TMat4& other );

        void setPosition( const TVec3& position );
        void setRotation( const TMat3& rotation );

        TVec3 getPosition() const;
        TMat3 getRotation() const;

        TMat4 operator* ( const TMat4& other )
        {
            TMat4 _res;

            for ( int i = 0; i < 4; i++ )
            {
                for ( int j = 0; j < 4; j++ )
                {
                    _res.buff[ j + i * 4 ] = 0;

                    for ( int k = 0; k < 4; k++ )
                    {
                        // Matrices are stored in column major form, so ...
                        // we use this indexing for the multiplication
                        // k + 4 * (fixed) -> over column
                        // (fixed) + 4 * k -> over row
                        _res.buff[ j + i * 4 ] += this->buff[ j + k * 4 ] * 
                                                  other.buff[ k + i * 4 ];
                    }
                }
            }

            return _res;
        }

        static TMat4 fromPositionAndRotation( const TVec3& pos, const TMat3& rot );
    };

    /**
    * Extracted from bullet btQuaternion implementation (where they use the gameprogramminggems (v1?) 2.10 impl.)
    */
    TVec4 shortestArcQuat( TVec3 v, TVec3 vTarget );

    struct TGeometry
    {
        std::string     type;           // type of geometry (box,sphere,mesh,etc.)
        std::string     filename;       // file name in case of a mesh
        TVec3           size;           // size params for primitives, scale for mesh
        TMat4           worldTransform; // position part of the world-transform
    };

    std::vector< TScalar > generateRandomArray( int size, TScalar min, TScalar max );

}