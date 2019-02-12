
#pragma once

#include <tysoc_common.h>

namespace tysoc{
namespace agent{

    const std::string AGENT_TYPE_SIMPLE     = "simple";
    const std::string AGENT_TYPE_KINTREE    = "kintree";


    /**
    * This is the base interface for the agents in the library.
    */
    class TIAgent
    {

        protected : 

        std::vector< TGeometry >    m_geometries;
        std::string                 m_name;
        std::string                 m_type;
        TVec3                       m_position;

        // agent specific functionality
        virtual void _updateAgentInternal( float dt ) = 0;

        public :

        TIAgent( const std::string& name,
                 const TVec3& position );
        virtual ~TIAgent();

        void setPosition( const TVec3& position );
        TVec3 getPosition();
        void update( float dt );

        std::string name();
        std::string type();
        const std::vector< TGeometry >& getGeometries() const;
    };



}}