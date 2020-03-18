
#include <loco_scenario.h>

namespace loco
{
    TScenario::TScenario()
    {
    #if defined( LOCO_CORE_USE_TRACK_ALLOCS )
        if ( TLogger::IsActive() )
            LOCO_CORE_TRACE( "Loco::Allocs: Created TScenario @ {0}", loco::PointerToHexAddress( this ) );
        else
            std::cout << "Loco::Allocs: Created TScenario @ " << loco::PointerToHexAddress( this ) << std::endl;
    #endif
    }

    TScenario::~TScenario()
    {
        m_singleBodies.clear();
        //// m_compounds.clear();
        //// m_kinTreeAgents.clear();
        //// m_kinTreeSensors.clear();
        //// m_terrainGenerators.clear();

    #if defined( LOCO_CORE_USE_TRACK_ALLOCS )
        if ( TLogger::IsActive() )
            LOCO_CORE_TRACE( "Loco::Allocs: Destroyed TScenario @ {0}", loco::PointerToHexAddress( this ) );
        else
            std::cout << "Loco::Allocs: Destroyed TScenario @ " << loco::PointerToHexAddress( this ) << std::endl;
    #endif
    }

    TDrawable* TScenario::AddDrawable( std::unique_ptr< TDrawable > drawable )
    {
        LOCO_CORE_ASSERT( drawable, "TScenario::AddDrawable >>> tried adding nullptr" );

        if ( HasDrawableNamed( drawable->name() ) )
        {
            LOCO_CORE_WARN( "TScenario::AddDrawable >>> drawable with name {0} already exists. \
                             New one won't be added, returning nullptr instead.", drawable->name() );
            return nullptr;
        }

        m_drawablesMap[drawable->name()] = m_drawables.size();
        m_drawables.push_back( std::move( drawable ) );
        return m_drawables.back().get();
    }

    TSingleBody* TScenario::AddSingleBody( std::unique_ptr< TSingleBody > singleBody )
    {
        LOCO_CORE_ASSERT( singleBody, "TScenario::AddSingleBody >>> tried adding nullptr" );

        if ( HasSingleBodyNamed( singleBody->name() ) )
        {
            LOCO_CORE_WARN( "TScenario::AddSingleBody >>> single-body with name {0} already exists. \
                             New one won't be added, returning nullptr instead.", singleBody->name() );
            return nullptr;
        }

        m_singleBodiesMap[singleBody->name()] = m_singleBodies.size();
        m_singleBodies.push_back( std::move( singleBody ) );
        return m_singleBodies.back().get();
    }

////     TCompound* TScenario::AddCompound( std::unique_ptr< TCompound > compound )
////     {
////         LOCO_CORE_ASSERT( compound, "TScenario::AddCompound >>> tried adding nullptr" );
//// 
////         if ( HasCompoundNamed( compound->name() ) )
////         {
////             LOCO_CORE_WARN( "TScenario::AddCompound >>> compound with name {0} already exists. \
////                              New one won't be added, returning nullptr instead.", compound->name() );
////             return nullptr;
////         }
//// 
////         m_compoundsMap[compound->name()] = m_compounds.size();
////         m_compounds.push_back( std::move( compound ) );
////         return m_compounds.back().get();
////     }
//// 
////     TKinTreeAgent* TScenario::AddKinTreeAgent( std::unique_ptr< TKinTreeAgent > kinTreeAgent )
////     {
////         LOCO_CORE_ASSERT( kinTreeAgent, "TScenario::AddKinTreeAgent >>> tried adding nullptr" );
//// 
////         if ( HasKinTreeAgentNamed( kinTreeAgent->name() ) )
////         {
////             LOCO_CORE_WARN( "TScenario::AddKinTreeAgent >>> kinTreeAgent with name {0} already exists. \
////                              New one won't be added, returning nullptr instead.", kinTreeAgent->name() );
////             return nullptr;
////         }
//// 
////         m_kinTreeAgentsMap[kinTreeAgent->name()] = m_kinTreeAgents.size();
////         m_kinTreeAgents.push_back( std::move( kinTreeAgent ) );
////         return m_kinTreeAgents.back().get();
////     }
//// 
////     TKinTreeSensor* TScenario::AddKinTreeSensor( std::unique_ptr< TKinTreeSensor > kinTreeSensor )
////     {
////         LOCO_CORE_ASSERT( kinTreeSensor, "TScenario::AddKinTreeSensor >>> tried adding nullptr" );
//// 
////         if ( HasKinTreeSensorNamed( kinTreeSensor->name() ) )
////         {
////             LOCO_CORE_WARN( "TScenario::AddKinTreeSensor >>> kinTreeSensor with name {0} already exists. \
////                              New one won't be added, returning nullptr instead.", kinTreeSensor->name() );
////             return nullptr;
////         }
//// 
////         m_kinTreeSensorsMap[kinTreeSensor->name()] = m_kinTreeSensors.size();
////         m_kinTreeSensors.push_back( std::move( kinTreeSensor ) );
////         return m_kinTreeSensors.back().get();
////     }
//// 
////     TTerrainGenerator* TScenario::AddTerrainGenerator( std::unique_ptr< TTerrainGenerator > terrainGenerator )
////     {
////         LOCO_CORE_ASSERT( terrainGenerator, "TScenario::AddTerrainGenerator >>> tried adding nullptr" );
//// 
////         if ( HasTerrainGeneratorNamed( terrainGenerator->name() ) )
////         {
////             LOCO_CORE_WARN( "TScenario::AddTerrainGenerator >>> terrainGenerator with name {0} already exists. \
////                              New one won't be added, returning nullptr instead.", terrainGenerator->name() );
////             return nullptr;
////         }
//// 
////         m_terrainGeneratorsMap[terrainGenerator->name()] = m_terrainGenerators.size();
////         m_terrainGenerators.push_back( std::move( terrainGenerator ) );
////         return m_terrainGenerators.back().get();
////     }

    void TScenario::Initialize()
    {
        for ( auto& drawable : m_drawables )
            drawable->Initialize();

        for ( auto& singleBody : m_singleBodies )
            singleBody->Initialize();

////         for ( auto& compound : m_compounds )
////             compound->Initialize();
//// 
////         for ( auto& kinTreeAgent : m_kinTreeAgents )
////             kinTreeAgent->Initialize();
//// 
////         for ( auto& kinTreeSensor : m_kinTreeSensors )
////             kinTreeSensor->Initialize();
//// 
////         for ( auto& terrainGenerator : m_terrainGenerators )
////             terrainGenerator->Initialize();
    }

    void TScenario::PreStep()
    {
        for ( auto& drawable : m_drawables )
            drawable->PreStep();

        for ( auto& singleBody : m_singleBodies )
            singleBody->PreStep();

////         for ( auto& compound : m_compounds )
////             compound->PreStep();
//// 
////         for ( auto& kinTreeAgent : m_kinTreeAgents )
////             kinTreeAgent->PreStep();
//// 
////         for ( auto& kinTreeSensor : m_kinTreeSensors )
////             kinTreeSensor->PreStep();
//// 
////         for ( auto& terrainGenerator : m_terrainGenerators )
////             terrainGenerator->PreStep();
    }

    void TScenario::PostStep()
    {
        for ( auto& drawable : m_drawables )
            drawable->PostStep();

        for ( auto& singleBody : m_singleBodies )
            singleBody->PostStep();

////         for ( auto& compound : m_compounds )
////             compound->PostStep();
//// 
////         for ( auto& kinTreeAgent : m_kinTreeAgents )
////             kinTreeAgent->PostStep();
//// 
////         for ( auto& kinTreeSensor : m_kinTreeSensors )
////             kinTreeSensor->PostStep();
//// 
////         for ( auto& terrainGenerator : m_terrainGenerators )
////             terrainGenerator->PostStep();
}

    void TScenario::Reset()
    {
        for ( auto& drawable : m_drawables )
            drawable->Reset();

        for ( auto& singleBody : m_singleBodies )
            singleBody->Reset();

////         for ( auto& compound : m_compounds )
////             compound->Reset();
//// 
////         for ( auto& kinTreeAgent : m_kinTreeAgents )
////             kinTreeAgent->Reset();
//// 
////         for ( auto& kinTreeSensor : m_kinTreeSensors )
////             kinTreeSensor->Reset();
//// 
////         for ( auto& terrainGenerator : m_terrainGenerators )
////             terrainGenerator->Reset();
    }

    void TScenario::DetachSim()
    {
        for ( auto& drawable : m_drawables )
            drawable->DetachSim();

        for ( auto& singleBody : m_singleBodies )
            singleBody->DetachSim();

////         for ( auto& compound : m_compounds )
////             compound->DetachSim();
//// 
////         for ( auto& kinTreeAgent : m_kinTreeAgents )
////             kinTreeAgent->DetachSim();
//// 
////         for ( auto& kinTreeSensor : m_kinTreeSensors )
////             kinTreeSensor->DetachSim();
//// 
////         for ( auto& terrainGenerator : m_terrainGenerators )
////             terrainGenerator->DetachSim();
    }

    void TScenario::DetachViz()
    {
        for ( auto& drawable : m_drawables )
            drawable->DetachViz();

        for ( auto& singleBody : m_singleBodies )
            singleBody->DetachViz();

////         for ( auto& compound : m_compounds )
////             compound->DetachViz();
//// 
////         for ( auto& kinTreeAgent : m_kinTreeAgents )
////             kinTreeAgent->DetachViz();
//// 
////         for ( auto& kinTreeSensor : m_kinTreeSensors )
////             kinTreeSensor->DetachViz();
//// 
////         for ( auto& terrainGenerator : m_terrainGenerators )
////             terrainGenerator->DetachViz();
    }

    const TDrawable* TScenario::GetDrawableByName( const std::string& name ) const
    {
        if ( !HasDrawableNamed( name ) )
        {
            LOCO_CORE_ERROR( "TScenario::GetDrawableByName >>> drawable with name {0} not found in the scenario", name );
            return nullptr;
        }

        return _get_drawable( m_drawablesMap.at( name ) );
    }

    const TSingleBody* TScenario::GetSingleBodyByName( const std::string& name ) const
    {
        if( !HasSingleBodyNamed( name ) )
        {
            LOCO_CORE_ERROR( "TScenario::GetSingleBodyByName >>> single-body with name {0} not found in the scenario", name );
            return nullptr;
        }

        return _get_singleBody( m_singleBodiesMap.at( name ) );
    }

////     const TCompound* TScenario::GetCompoundBodyByName( const std::string& name ) const
////     {
////         if( !HasCompoundBodyNamed( name ) )
////         {
////             LOCO_CORE_ERROR( "TScenario::GetTerrainGeneratorByName >>> terrainGenerator with name {0} not found", name );
////             return nullptr;
////         }
//// 
////         return _get_compound( m_compoundsMap.at( name ) );
////     }
//// 
////     const TKinTreeAgent* TScenario::GetKinTreeAgentByName( const std::string& name ) const
////     {
////         if( !HasKinTreeAgentNamed( name ) )
////         {
////             LOCO_CORE_ERROR( "TScenario::GetKinTreeAgentByName >>> kintreeAgent with name {0} not found", name );
////             return nullptr;
////         }
//// 
////         return _get_kintreeAgent( m_kintreeAgentsMap.at( name ) );
////     }
//// 
////     const TKinTreeSensor* TScenario::GetKinTreeSensorByName( const std::string& name ) const
////     {
////         if( !HasKinTreeSensorNamed( name ) )
////         {
////             LOCO_CORE_ERROR( "TScenario::GetKinTreeSensorByName >>> kintreeSensor with name {0} not found", name );
////             return nullptr;
////         }
//// 
////         return _get_kintreeSensor( m_kintreeSensorsMap.at( name ) );
////     }
//// 
////     const TTerrainGenerator* TScenario::GetTerrainGeneratorByName( const std::string& name ) const
////     {
////         if( !HasTerrainGeneratorNamed( name ) )
////         {
////             LOCO_CORE_ERROR( "TScenario::GetTerrainGeneratorByName >>> terrainGenerator with name {0} not found", name );
////             return nullptr;
////         }
//// 
////         return _get_terrainGenerator( m_terrainGeneratorsMap.at( name ) );
////     }

    TDrawable* TScenario::GetDrawableByName( const std::string& name )
    {
        if( !HasSingleBodyNamed( name ) )
        {
            LOCO_CORE_ERROR( "TScenario::GetSingleBodyByName >>> single-body with name {0} not found in the scenario", name );
            return nullptr;
        }

        return _get_mutable_drawable( m_drawablesMap.at( name ) );
    }

    TSingleBody* TScenario::GetSingleBodyByName( const std::string& name )
    {
        if( !HasSingleBodyNamed( name ) )
        {
            LOCO_CORE_ERROR( "TScenario::GetSingleBodyByName >>> single-body with name {0} not found", name );
            return nullptr;
        }

        return _get_mutable_singleBody( m_singleBodiesMap.at( name ) );
    }

////     TCompound* TScenario::GetCompoundBodyByName( const std::string& name )
////     {
////         if( !HasCompoundBodyNamed( name ) )
////         {
////             LOCO_CORE_ERROR( "TScenario::GetCompoundBodyByName >>> compound with name {0} not found", name );
////             return nullptr;
////         }
//// 
////         return _get_mutable_compound( m_compoundsMap.at( name ) );
////     }
//// 
////     TKinTreeAgent* TScenario::GetKinTreeAgentByName( const std::string& name )
////     {
////         if( !HasKinTreeAgentNamed( name ) )
////         {
////             LOCO_CORE_ERROR( "TScenario::GetKinTreeAgentByName >>> kintreeAgent with name {0} not found", name );
////             return nullptr;
////         }
//// 
////         return _get_mutable_kintreeAgent( m_kintreeAgentsMap.at( name ) );
////     }
//// 
////     TKinTreeSensor* TScenario::GetKinTreeSensorByName( const std::string& name )
////     {
////         if( !HasKinTreeSensorNamed( name ) )
////         {
////             LOCO_CORE_ERROR( "TScenario::GetKinTreeSensorByName >>> kintreeSensor with name {0} not found", name );
////             return nullptr;
////         }
//// 
////         return _get_mutable_kintreeSensor( m_kintreeSensorsMap.at( name ) );
////     }
//// 
////     TTerrainGenerator* TScenario::GetTerrainGeneratorByName( const std::string& name )
////     {
////         if( !HasTerrainGeneratorNamed( name ) )
////         {
////             LOCO_CORE_ERROR( "TScenario::GetTerrainGeneratorByName >>> terrainGenerator with name {0} not found", name );
////             return nullptr;
////         }
//// 
////         return _get_mutable_terrainGenerator( m_terrainGeneratorsMap.at( name ) );
////     }

    size_t TScenario::GetNumDrawables() const
    {
        return m_drawables.size();
    }

    size_t TScenario::GetNumSingleBodies() const
    {
        return m_singleBodies.size();
    }

////     size_t TScenario::GetNumCompounds() const
////     {
////         return m_compounds.size();
////     }
//// 
////     size_t TScenario::GetNumKinTreeAgents() const
////     {
////         return m_kinTreeAgents.size();
////     }
//// 
////     size_t TScenario::GetNumKinTreeSensors() const
////     {
////         return m_kinTreeSensors.size();
////     }
//// 
////     size_t TScenario::GetNumTerrainGenerators() const
////     {
////         return m_terrainGenerators.size();
////     }

    bool TScenario::HasDrawableNamed( const std::string& name ) const
    {
        return m_drawablesMap.find( name ) != m_drawablesMap.end();
    }

    bool TScenario::HasSingleBodyNamed( const std::string& name ) const
    {
        return m_singleBodiesMap.find( name ) != m_singleBodiesMap.end();
    }

////     bool TScenario::HasCompoundNamed( const std::string& name ) const
////     {
////         return m_compoundsMap.find( name ) != m_compoundsMap.end();
////     }
//// 
////     bool TScenario::HasKinTreeAgentNamed( const std::string& name ) const
////     {
////         return m_kinTreeAgentsMap.find( name ) != m_kinTreeAgentsMap.end();
////     }
//// 
////     bool TScenario::HasKinTreeSensorNamed( const std::string& name ) const
////     {
////         return m_kinTreeSensorsMap.find( name ) != m_kinTreeSensorsMap.end();
////     }
//// 
////     bool TScenario::HasTerrainGeneratorNamed( const std::string& name ) const
////     {
////         return m_terrainGeneratorsMap.find( name ) != m_terrainGeneratorsMap.end();
////     }

    std::vector<const TDrawable*> TScenario::GetDrawablesList() const
    {
        std::vector<const TDrawable*> _drawablesList;
        for ( auto& drawable : m_drawables )
            _drawablesList.push_back( drawable.get() );
        return _drawablesList;
    }

    std::vector<const TSingleBody*> TScenario::GetSingleBodiesList() const
    {
        std::vector<const TSingleBody*> _singleBodiesList;
        for ( auto& singleBody : m_singleBodies )
            _singleBodiesList.push_back( singleBody.get() );
        return _singleBodiesList;
    }

////     std::vector<const TCompound*> TScenario::GetCompoundsList() const
////     {
////         std::vector<const TCompound*> _compoundsList;
////         for ( auto& compound : m_compounds )
////             _compoundsList.push_back( compound.get() );
////         return _compoundsList;
////     }
//// 
////     std::vector<const TKinTreeAgent*> TScenario::GetKinTreeAgentsList() const
////     {
////         std::vector<const TKinTreeAgent*> _kintreeAgentsList;
////         for ( auto& kintreeAgent : m_kinTreeAgents )
////             _kintreeAgentsList.push_back( kinTreeAgent.get() );
////         return _kintreeAgentsList;
////     }
//// 
////     std::vector<const TKinTreeSensor*> TScenario::GetKinTreeSensorsList() const
////     {
////         std::vector<const TKinTreeSensor*> _kintreeSensorsList;
////         for ( auto& kintreeSensor : m_kinTreeSensors )
////             _kintreeSensorsList.push_back( kinTreeSensor.get() );
////         return _kintreeSensorsList;
////     }
//// 
////     std::vector<const TTerrainGenerator*> TScenario::GetTerrainGeneratorsList() const
////     {
////         std::vector<const TTerrainGenerator*> _terrainGeneratorsList;
////         for ( auto& terrainGenerator : m_terrainGenerators )
////             _terrainGeneratorsList.push_back( terrainGenerator.get() );
////         return _terrainGeneratorsList;
////     }

    std::vector< TDrawable* > TScenario::GetDrawablesList()
    {
        std::vector<TDrawable*> _drawablesList;
        for ( auto& drawable : m_drawables )
            _drawablesList.push_back( drawable.get() );
        return _drawablesList;
    }

    std::vector< TSingleBody* > TScenario::GetSingleBodiesList()
    {
        std::vector<TSingleBody*> _singleBodiesList;
        for ( auto& singleBody : m_singleBodies )
            _singleBodiesList.push_back( singleBody.get() );
        return _singleBodiesList;
    }

////     std::vector<TCompound*> TScenario::GetCompoundsList()
////     {
////         std::vector<TCompound*> _compoundsList;
////         for ( auto& compound : m_compounds )
////             _compoundsList.push_back( compound.get() );
////         return _compoundsList;
////     }
//// 
////     std::vector<TKinTreeAgent*> TScenario::GetKinTreeAgentsList()
////     {
////         std::vector<TKinTreeAgent*> _kintreeAgentsList;
////         for ( auto& kintreeAgent : m_kinTreeAgents )
////             _kintreeAgentsList.push_back( kinTreeAgent.get() );
////         return _kintreeAgentsList;
////     }
//// 
////     std::vector<TKinTreeSensor*> TScenario::GetKinTreeSensorsList()
////     {
////         std::vector<TKinTreeSensor*> _kintreeSensorsList;
////         for ( auto& kintreeSensor : m_kinTreeSensors )
////             _kintreeSensorsList.push_back( kinTreeSensor.get() );
////         return _kintreeSensorsList;
////     }
//// 
////     std::vector<TTerrainGenerator*> TScenario::GetTerrainGeneratorsList()
////     {
////         std::vector<TTerrainGenerator*> _terrainGeneratorsList;
////         for ( auto& terrainGenerator : m_terrainGenerators )
////             _terrainGeneratorsList.push_back( terrainGenerator.get() );
////         return _terrainGeneratorsList;
////     }

    const TDrawable* TScenario::_get_drawable( ssize_t index ) const
    {
        LOCO_CORE_ASSERT( ( index >= 0 && index < m_drawables.size() ), "TScenario::_get_drawable >>> \
                          index {0} out of range [0,{1}]", index, m_drawables.size() );
        return m_drawables[index].get();
    }

    const TSingleBody* TScenario::_get_singleBody( ssize_t index ) const
    {
        LOCO_CORE_ASSERT( ( index >= 0 && index < m_singleBodies.size() ), "TScenario::_get_singleBody >>> \
                          index {0} out of range [0,{1}]", index, m_singleBodies.size() );
        return m_singleBodies[index].get();
    }

////     const TCompound* TScenario::_get_compound( ssize_t index ) const
////     {
////         LOCO_CORE_ASSERT( ( index >= 0 && index < m_compounds.size() ), "TScenario::_get_compound >>> \
////                           index {0} out of range [0,{1}]", index, m_compounds.size() );
////         return m_compounds[index].get();
////     }
//// 
////     const TKinTreeAgent* TScenario::_get_kintreeAgent( ssize_t index ) const
////     {
////         LOCO_CORE_ASSERT( ( index >= 0 && index < m_kinTreeAgents.size() ), "TScenario::_get_kintreeAgent >>> \
////                           index {0} out of range [0,{1}]", index, m_kinTreeAgents.size() );
////         return m_kinTreeAgents[index].get();
////     }
//// 
////     const TKinTreeSensor* TScenario::_get_kintreeSensor( ssize_t index ) const
////     {
////         LOCO_CORE_ASSERT( ( index >= 0 && index < m_kinTreeSensors.size() ), "TScenario::_get_kintreeSensor >>> \
////                           index {0} out of range [0,{1}]", index, m_kinTreeSensors.size() );
////         return m_kinTreeSensors[index].get();
////     }
//// 
////     const TTerrainGenerator* TScenario::_get_terrainGenerator( ssize_t index ) const
////     {
////         LOCO_CORE_ASSERT( ( index >= 0 && index < m_terrainGenerators.size() ), "TScenario::_get_terrainGenerator >>> \
////                           index {0} out of range [0,{1}]", index, m_terrainGenerators.size() );
////         return m_terrainGenerators[index].get();
////     }

    TDrawable* TScenario::_get_mutable_drawable( ssize_t index )
    {
        LOCO_CORE_ASSERT( ( index >= 0 && index < m_drawables.size() ), "TScenario::_get_mutable_drawable >>> \
                          index {0} our of range [0,...,{1}]", index, m_drawables.size() );
        return m_drawables[index].get();
    }

    TSingleBody* TScenario::_get_mutable_singleBody( ssize_t index )
    {
        LOCO_CORE_ASSERT( ( index >= 0 && index < m_singleBodies.size() ), "TScenario::_get_mutable_singleBody >>> \
                          index {0} out of range [0,...,{1}]", index, m_singleBodies.size() );
        return m_singleBodies[index].get();
    }

////     TCompound* TScenario::_get_mutable_compound( ssize_t index )
////     {
////         LOCO_CORE_ASSERT( ( index >= 0 && index < m_compounds.size() ), "TScenario::_get_mutable_compound >>> \
////                           index {0} out of range [0,...,{1}]", index, m_compounds.size() );
////         return m_compounds[index].get();
////     }
//// 
////     TKinTreeAgent* TScenario::_get_mutable_kintreeAgent( ssize_t index )
////     {
////         LOCO_CORE_ASSERT( ( index >= 0 && index < m_kinTreeAgents.size() ), "TScenario::_get_mutable_kintreeAgent >>> \
////                           index {0} out of range [0,...,{1}]", index, m_kinTreeAgents.size() );
////         return m_kinTreeAgents[index].get();
////     }
//// 
////     TKinTreeSensor* TScenario::_get_mutable_kintreeSensor( ssize_t index )
////     {
////         LOCO_CORE_ASSERT( ( index >= 0 && index < m_kinTreeSensors.size() ), "TScenario::_get_mutable_kintreeSensor >>> \
////                           index {0} out of range [0,...,{1}]", index, m_kinTreeSensors.size() );
////         return m_kinTreeSensors[index].get();
////     }
//// 
////     TTerrainGenerator* TScenario::_get_mutable_terrainGenerator( ssize_t index )
////     {
////         LOCO_CORE_ASSERT( ( index >= 0 && index < m_terrainGenerators.size() ), "TScenario::_get_mutable_terrainGenerator >>> \
////                           index {0} out of range [0,...,{1}]", index, m_terrainGenerators.size() );
////         return m_terrainGenerators[index].get();
////     }
}