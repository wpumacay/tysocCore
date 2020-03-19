
#include <loco_common_py.h>
#include <loco_scenario.h>

namespace py = pybind11;

namespace loco
{
    void bindings_scenario( py::module& m )
    {
        // Bindings for TScenario class
        {
            py::class_<TScenario>( m, "Scenario" )
                .def( py::init<>() )
                .def( "Initialize", &TScenario::Initialize )
                .def( "PreStep", &TScenario::PreStep )
                .def( "PostStep", &TScenario::PostStep )
                .def( "Reset", &TScenario::Reset )
                .def( "AddDrawable", &TScenario::AddDrawable, py::arg( "drawable" ),
                      py::return_value_policy::reference,
                      py::keep_alive<1, 2>() )
                .def( "AddSingleBody", &TScenario::AddSingleBody, py::arg( "single_body" ),
                      py::return_value_policy::reference,
                      py::keep_alive<1, 2>() )
                //// .def( "AddCompound", &TScenario::AddCompound, py::arg( "compound" ),
                ////       py::return_value_policy::reference,
                ////       py::keep_alive<1, 2>() )
                //// .def( "AddKinematicTree", &TScenario::AddKinematicTree, py::arg( "kinematic_tree" ),
                ////       py::return_value_policy::reference,
                ////       py::keep_alive<1, 2>() )
                //// .def( "AddKinematicTreeSensor", &TScenario::AddKinematicTreeSensor, py::arg( "kinematic_tree_sensor" ),
                ////       py::return_value_policy::reference,
                ////       py::keep_alive<1, 2>() )
                //// .def( "AddTerrainGenerator", &TScenario::AddTerrainGenerator, py::arg( "terrain_generator" ),
                ////       py::return_value_policy::reference,
                ////       py::keep_alive<1, 2>() )
                .def( "GetDrawableByName", []( TScenario* self, const std::string& name ) -> TDrawable*
                    {
                        return self->GetDrawableByName( name );
                    },
                    py::arg( "name" ), py::return_value_policy::reference )
                .def( "GetSingleBodyByName", []( TScenario* self, const std::string& name ) -> TSingleBody*
                    {
                        return self->GetSingleBodyByName( name );
                    },
                    py::arg( "name" ), py::return_value_policy::reference )
                //// .def( "GetCompoundByName", []( TScenario* self, const std::string& name ) -> TCompound*
                ////     {
                ////         return self->GetCompoundByName( name );
                ////     },
                ////     py::arg( "name" ), py::return_value_policy::reference )
                //// .def( "GetKinematicTreeByName", []( TScenario* self, const std::string& name ) -> TKinematicTree*
                ////     {
                ////         return self->GetKinematicTreeByName( name );
                ////     },
                ////     py::arg( "name" ), py::return_value_policy::reference )
                //// .def( "GetKinematicTreeSensorByName", []( TScenario* self, const std::string& name ) -> TKinematicTree*
                ////     {
                ////         return self->GetKinematicTreeSensorByName( name );
                ////     },
                ////     py::arg( "name" ), py::return_value_policy::reference )
                //// .def( "GetTerrainGeneratorByName", []( TScenario* self, const std::string& name ) -> TITerrainGenerator*
                ////     {
                ////         return self->GetTerrainGeneratorByName( name );
                ////     },
                ////     py::arg( "name" ), py::return_value_policy::reference )
                .def( "GetNumDrawables", &TScenario::GetNumDrawables )
                .def( "GetNumSingleBodies", &TScenario::GetNumSingleBodies )
                //// .def( "GetNumCompounds", &TScenario::GetNumCompounds )
                //// .def( "GetNumKinematicTrees", &TScenario::GetNumKinematicTrees )
                //// .def( "GetNumKinematicTreeSensors", &TScenario::GetNumKinematicTreeSensors )
                //// .def( "GetNumTerrainGenerators", &TScenario::GetNumTerrainGenerators )
                .def( "HasDrawableNamed", &TScenario::HasDrawableNamed, py::arg( "name" ) )
                .def( "HasSingleBodyNamed", &TScenario::HasSingleBodyNamed, py::arg( "name" ) )
                //// .def( "HasCompoundNamed", &TScenario::HasCompoundNamed, py::arg( "name" ) )
                //// .def( "HasKinematicTreeNamed", &TScenario::HasKinematicTreeNamed, py::arg( "name" ) )
                //// .def( "HasKinematicTreeSensorNamed", &TScenario::HasKinematicTreeSensorNamed, py::arg( "name" ) )
                //// .def( "HasTerrainGeneratorNamed", &TScenario::HasTerrainGeneratorNamed, py::arg( "name" ) )
                .def( "GetDrawablesList", []( TScenario* self ) -> std::vector<TDrawable*>
                    {
                        return self->GetDrawablesList();
                    },
                    py::return_value_policy::reference )
                .def( "GetSingleBodiesList", []( TScenario* self ) -> std::vector<TSingleBody*>
                    {
                        return self->GetSingleBodiesList();
                    },
                    py::return_value_policy::reference )
                //// .def( "GetCompoundsList", []( TScenario* self ) -> std::vector<TCompound*>
                ////     {
                ////         return self->GetCompoundsList();
                ////     },
                ////     py::return_value_policy::reference )
                //// .def( "GetKinematicTreesList", []( TScenario* self ) -> std::vector<TKinematicTree*>
                ////     {
                ////         return self->GetKinematicTreesList();
                ////     },
                ////     py::return_value_policy::reference )
                //// .def( "GetKinematicTreeSensorsList", []( TScenario* self ) -> std::vector<TKinematicTreeSensor*>
                ////     {
                ////         return self->GetKinematicTreeSensorsList();
                ////     },
                ////     py::return_value_policy::reference )
                //// .def( "GetTerrainGeneratorsList", []( TScenario* self ) -> std::vector<TITerrainGenerator*>
                ////     {
                ////         return self->GetTerrainGeneratorsList();
                ////     },
                ////     py::return_value_policy::reference )
                .def( "__repr__", []( const TScenario* self )
                    {
                        auto _strrep = std::string( "Scenario(\n" );
                        _strrep += "cpp-address         : " + loco::PointerToHexAddress( self ) + "\n";
                        _strrep += "num-drawables       : " + std::to_string( self->GetNumDrawables() ) + "\n";
                        _strrep += "num-single-bodies   : " + std::to_string( self->GetNumSingleBodies() ) + "\n";
                        //// _strrep += "num-compounds       : " + std::to_string( self->GetNumCompounds() ) + "\n";
                        //// _strrep += "num-kintrees        : " + std::to_string( self->GetNumKinematicTrees() ) + "\n";
                        //// _strrep += "num-kintree-sensors : " + std::to_string( self->GetNumKinematicTreeSensors() ) + "\n";
                        //// _strrep += "num-terrain-gens.   : " + std::to_string( self->GetNumTerrainGenerator() ) + "\n";
                        _strrep += "drawables           :\n";
                        auto drawablesList = self->GetDrawablesList();
                        for ( auto drawable : drawablesList )
                            _strrep += "\t(name=" + drawable->name() + ", pos=" + loco::ToString( drawable->pos() ) + ")\n";
                        _strrep += "single-bodies       :\n";
                        auto singleBodiesList = self->GetSingleBodiesList();
                        for ( auto singleBody : singleBodiesList )
                            _strrep += "\t(name=" + singleBody->name() + ", pos=" + loco::ToString( singleBody->pos() ) + ")\n";
                        _strrep += ")";
                        return _strrep;
                    } );
        }
    }
}