
#include <pytysoc_common.h>

namespace py = pybind11;

namespace pytysoc
{

    tysoc::TVec2 numpyToVec2( py::array_t<TScalar>& nparray )
    {
        auto _bufferInfo = nparray.request();
        auto _data = ( TScalar* ) _bufferInfo.ptr;
        if ( _bufferInfo.size != 2 )
        {
            TYSOC_CORE_WARN( "numpyToVec2() >>> vec2 conversion requires an array with 2 elements" );
            return tysoc::TVec2();
        }

        return tysoc::TVec2( _data[0], _data[1] );
    }

    tysoc::TVec3 numpyToVec3( py::array_t<TScalar>& nparray )
    {
        auto _bufferInfo = nparray.request();
        auto _data = ( TScalar* ) _bufferInfo.ptr;
        if ( _bufferInfo.size != 3 )
        {
            TYSOC_CORE_WARN( "numpyToVec3() >>> vec3 conversion requires an array with 3 elements" );
            return tysoc::TVec3();
        }

        return tysoc::TVec3( _data[0], _data[1], _data[2] );
    }

    tysoc::TVec4 numpyToVec4( py::array_t<TScalar>& nparray )
    {
        auto _bufferInfo = nparray.request();
        auto _data = ( TScalar* ) _bufferInfo.ptr;
        if ( _bufferInfo.size != 4 )
        {
            TYSOC_CORE_WARN( "numpyToVec4() >>> vec4 conversion requires an array with 4 elements" );
            return tysoc::TVec4();
        }

        return tysoc::TVec4( _data[0], _data[1], _data[2], _data[3] );
    }

    tysoc::TMat3 numpyToMat3( py::array_t<TScalar>& nparray )
    {
        auto _bufferInfo = nparray.request();
        auto _data = ( TScalar* ) _bufferInfo.ptr;
        if ( _bufferInfo.size != 9 )
        {
            TYSOC_CORE_WARN( "numpyToMat3() >>> mat3 conversion requires an array with 9 elements" );
            return tysoc::TMat3();
        }

        return tysoc::TMat3( _data[0], _data[1], _data[2],
                             _data[3], _data[4], _data[5],
                             _data[6], _data[7], _data[8] );
    }

    tysoc::TMat4 numpyToMat4( py::array_t<TScalar>& nparray )
    {
        auto _bufferInfo = nparray.request();
        auto _data = ( TScalar* ) _bufferInfo.ptr;
        if ( _bufferInfo.size != 16 )
        {
            TYSOC_CORE_WARN( "numpyToMat4() >>> mat4 conversion requires an array with 16 elements" );
            return tysoc::TMat4();
        }

        return tysoc::TMat4( _data[0], _data[1], _data[2], _data[3],
                             _data[4], _data[5], _data[6], _data[7],
                             _data[8], _data[9], _data[10], _data[11],
                             _data[12], _data[13], _data[14], _data[15] );
    }

    std::vector<TScalar> numpyToVecArray( py::array_t<TScalar>& nparray )
    {
        auto _bufferInfo = nparray.request();
        auto _data = ( TScalar* ) _bufferInfo.ptr;

        std::vector<TScalar> _vecarray;
        for ( size_t q = 0; q < _bufferInfo.size; q++ )
            _vecarray.push_back( _data[q] );

        return _vecarray;
    }

    py::array_t<TScalar> vec2ToNumpy( const tysoc::TVec2& vec2 )
    {
        auto _nparray = py::array_t<TScalar>( 2 );
        auto _bufferInfo = _nparray.request();
        auto _data = ( TScalar* ) _bufferInfo.ptr;

        _data[0] = vec2.x;
        _data[1] = vec2.y;

        return _nparray;
    }

    py::array_t<TScalar> vec3ToNumpy( const tysoc::TVec3& vec3 )
    {
        auto _nparray = py::array_t<TScalar>( 3 );
        auto _bufferInfo = _nparray.request();
        auto _data = ( TScalar* ) _bufferInfo.ptr;

        _data[0] = vec3.x;
        _data[1] = vec3.y;
        _data[2] = vec3.z;

        return _nparray;
    }

    py::array_t<TScalar> vec4ToNumpy( const tysoc::TVec4& vec4 )
    {
        auto _nparray = py::array_t<TScalar>( 4 );
        auto _bufferInfo = _nparray.request();
        auto _data = ( TScalar* ) _bufferInfo.ptr;

        _data[0] = vec4.x;
        _data[1] = vec4.y;
        _data[2] = vec4.z;
        _data[3] = vec4.w;

        return _nparray;
    }

    // from: https://github.com/pybind/pybind11/issues/27
    py::array_t<TScalar> mat3ToNumpy( const tysoc::TMat3& mat3 )
    {
        std::vector< ssize_t > _shape = { 3, 3 };
        std::vector< ssize_t > _strides = { sizeof( TScalar ), sizeof( TScalar ) };

        return py::array( py::buffer_info( (TScalar*) mat3.buff,
                                           sizeof( TScalar ),
                                           py::format_descriptor<TScalar>::value,
                                           2, _shape, _strides ) );
    }

    py::array_t<TScalar> mat4ToNumpy( const tysoc::TMat4& mat4 )
    {
        std::vector< ssize_t > _shape = { 4, 4 };
        std::vector< ssize_t > _strides = { sizeof( TScalar ), sizeof( TScalar ) };

        return py::array( py::buffer_info( (TScalar*) mat4.buff,
                                           sizeof( TScalar ),
                                           py::format_descriptor<TScalar>::value,
                                           2, _shape, _strides ) );
    }

    py::array_t<TScalar> vecArrayToNumpy( const std::vector<TScalar>& vecarray )
    {
        std::vector< ssize_t > _shape = { (ssize_t) vecarray.size() };
        std::vector< ssize_t > _strides = { sizeof( TScalar ) };

        return py::array( py::buffer_info( (TScalar*) vecarray.data(),
                                           sizeof( TScalar ),
                                           py::format_descriptor<TScalar>::value,
                                           1, _shape, _strides ) );
    }

    py::array_t<TScalar> vecArrayVec3ToNumpy( const std::vector<tysoc::TVec3>& vec3array )
    {
        std::vector< ssize_t > _shape = { 3, (ssize_t) vec3array.size() };
        std::vector< ssize_t > _strides = { sizeof( TScalar ), sizeof( tysoc::TVec3 ) };

        return py::array( py::buffer_info( (TScalar*) vec3array.data(),
                                           sizeof( TScalar ),
                                           py::format_descriptor<TScalar>::value,
                                           2, _shape, _strides ) );
    }

    void test_numpyToVec2( py::array_t<TScalar>& nparray )
    {
        auto _vec2 = numpyToVec2( nparray );
        TYSOC_CORE_TRACE( "test_numpyToVec2() >>> vec2: {0}", tysoc::TVec2::toString( _vec2 ) );
    }

    void test_numpyToVec3( py::array_t<TScalar>& nparray )
    {
        auto _vec3 = numpyToVec3( nparray );
        TYSOC_CORE_TRACE( "test_numpyToVec3() >>> vec3: {0}", tysoc::TVec3::toString( _vec3 ) );
    }

    void test_numpyToVec4( py::array_t<TScalar>& nparray )
    {
        auto _vec4 = numpyToVec4( nparray );
        TYSOC_CORE_TRACE( "test_numpyToVec4() >>> vec4: {0}", tysoc::TVec4::toString( _vec4 ) );
    }

    void test_numpyToMat3( py::array_t<TScalar>& nparray )
    {
        auto _mat3 = numpyToMat3( nparray );
        TYSOC_CORE_TRACE( "test_numpyToMat3() >>> mat3: {0}", tysoc::TMat3::toString( _mat3 ) );
    }

    void test_numpyToMat4( py::array_t<TScalar>& nparray )
    {
        auto _mat4 = numpyToMat4( nparray );
        TYSOC_CORE_TRACE( "test_numpyToMat4() >>> mat4: {0}", tysoc::TMat4::toString( _mat4 ) );
    }

    void test_numpyToVecArray( py::array_t<TScalar>& nparray )
    {
        auto _vecarray = numpyToVecArray( nparray );
        std::string _strres = " [ ";
        for ( size_t q = 0; q < _vecarray.size(); q++ )
            _strres += std::to_string( _vecarray[q] ) + " ";
        _strres += "]";
        TYSOC_CORE_TRACE( "test_numpyToVecArray() >>> std::vector: {0}", _strres );
    }

    py::array_t<TScalar> test_vecArrayToNumpy()
    {
        std::vector< TScalar > _vecarray = { 1.0f, 2.1f, 3.2f, 4.3f };
        return vecArrayToNumpy( _vecarray );
    }

    py::array_t<TScalar> test_vecArrayVec3ToNumpy()
    {
        std::vector< tysoc::TVec3 > _vecarrayvec3;
        _vecarrayvec3.push_back( tysoc::TVec3( 1.0f, 2.0f, 3.0f ) );
        _vecarrayvec3.push_back( tysoc::TVec3( 1.1f, 2.1f, 3.1f ) );
        _vecarrayvec3.push_back( tysoc::TVec3( 1.2f, 2.2f, 3.2f ) );
        _vecarrayvec3.push_back( tysoc::TVec3( 1.3f, 2.3f, 3.3f ) );
        _vecarrayvec3.push_back( tysoc::TVec3( 1.4f, 2.4f, 3.4f ) );
        _vecarrayvec3.push_back( tysoc::TVec3( 1.5f, 2.5f, 3.5f ) );
        _vecarrayvec3.push_back( tysoc::TVec3( 1.6f, 2.6f, 3.6f ) );
        _vecarrayvec3.push_back( tysoc::TVec3( 1.7f, 2.7f, 3.7f ) );
        _vecarrayvec3.push_back( tysoc::TVec3( 1.8f, 2.8f, 3.8f ) );
        return vecArrayVec3ToNumpy( _vecarrayvec3 );
    }

}