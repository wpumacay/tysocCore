
import os
import sys
import subprocess

from setuptools import find_packages
from setuptools import setup 
from setuptools import Extension

from setuptools.command.build_ext import build_ext as BaseBuildExtCommand


def buildBindings( sourceDir, buildDir, cmakeArgs, buildArgs, env ):
    if not os.path.exists( buildDir ) :
        os.makedirs( buildDir )

    subprocess.call( ['cmake', sourceDir] + cmakeArgs, cwd=buildDir, env=env )
    subprocess.call( ['cmake', '--build', '.'] + buildArgs, cwd=buildDir )

class CMakeExtension( Extension ) :

    def __init__( self, name, sourceDir ) :
        super( CMakeExtension, self ).__init__( name, sources=[] )
        self.sourceDir = os.path.abspath( sourceDir )

class BuildCommand( BaseBuildExtCommand ) :

    def run( self ) :
        try:
            _ = subprocess.check_output( ['cmake', '--version'] )
        except OSError:
            raise RuntimeError( 'CMake must be installed to build the following extensions: ' +
                                ', '.join( e.name for e in self.extensions ) )

        for _extension in self.extensions :
            self.build_extension( _extension )

    def build_extension( self, extension ) :
        _extensionFullPath = self.get_ext_fullpath( extension.name )
        _extensionDirName = os.path.dirname( _extensionFullPath )
        _extensionDirPath = os.path.abspath( _extensionDirName )

        _cfg = 'Debug' if self.debug else 'Release'
        _buildArgs = ['--config', _cfg, '--', '-j4']
        _cmakeArgs = ['-DCMAKE_LIBRARY_OUTPUT_DIRECTORY=' + _extensionDirPath,
                      '-DPYTHON_EXECUTABLE=' + sys.executable,
                      '-DCMAKE_BUILD_TYPE=' + _cfg]

        _env = os.environ.copy()
        _env['CXXFLAGS'] = '{} -DVERSION_INFO=\\"{}\\"'.format( _env.get( 'CXXFLAGS', '' ),
                                                                self.distribution.get_version() )

        _sourceDir = extension.sourceDir
        _buildDir = self.build_temp

        buildBindings( _sourceDir, _buildDir, _cmakeArgs, _buildArgs, _env )

setup(
    name                    = 'pytysoc',
    description             = 'Core functionality for a backend-agnostic locomotion framework',
    author                  = 'Wilbert Santos Pumacay Huallpa',
    license                 = 'MIT License',
    author_email            = 'wpumacay@gmail.com',
    url                     = 'https://github.com/wpumacay/tysoc',
    keywords                = 'locomotion control simulation',
    packages                = find_packages(),
    zip_safe                = False,
    install_requires        = [
                                'numpy',
                                'setuptools'
                              ],
    package_data            = {
                                'pytysoc': [ '../res/templates/mjcf/*.xml',
                                             '../res/templates/urdf/*.urdf',
                                             '../res/templates/rlsim/*.json',
                                             '../res/xml/*.xml',
                                             '../res/xml/baxter_meshes/*.stl',
                                             '../res/xml/baxter_meshes/*.obj',
                                             '../res/xml/laikago_meshes/*.stl',
                                             '../res/xml/laikago_meshes/*.obj',
                                             '../res/xml/nao_meshes/*.stl',
                                             '../res/xml/nao_meshes/*.obj',
                                             '../res/xml/r2d2_meshes/*.stl',
                                             '../res/xml/r2d2_meshes/*.obj',
                                             '../res/xml/sawyer_meshes/*.stl',
                                             '../res/xml/sawyer_meshes/*.obj' ]
                              },
    ext_modules             = [
                                CMakeExtension( 'tysoc_bindings', '.' )
                              ],
    cmdclass                = {
                                'build_ext': BuildCommand
                              }
)