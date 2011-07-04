
#include <spl.h>

#if SPL_PLATFORM == SPL_PLATFORM_WIN32
	// Include windows.h - Needed for Windows projects.
	#include <windows.h>
#endif

#include <PluginParameters.h>

//
// Define standard export symbols for Win32.
// Note: You don't have to remove this macro for other platforms.
//
SPL_DEFINE_PLUGIN_EXPORTS();

SPL_DEFINE_PLUGIN_INFO( 
1,	///< The build number. 
1,	///< The major version (e.g. 1.xx).
0,	///< The minor version (e.g. 0.10).
true,	///< Does this plugin show its arguments to the public?
"VoronoiDiagram",	///< The plugin's name.
"Douglas Uba",	///< The plugin's vendor.
"Generate Voronoi Diagrams",	///< The plugin's general description.
PLUGINPARAMETERS_VERSION,	///< The expected plugin parameters version.
"www.dpi.inpe.br/ ~douglas",	///< The plugin vendor's homepage.
"douglas@dpi.inpe.br",	///< The plugin vendor's email address.
"TerraViewPlugin" );	///< The plugin's UUID, must be "TerraViewPlugin".

//
// Define a standard DllMain() function for Win32 plugin DLLs.
// Note: You haven't to delete or comment out this function for other platforms.
// SPL automatically detects the current platform and removes unused/unwanted code
// behind the macros.
//
SPL_DEFINE_PLUGIN_DLLMAIN();

//
// We don't want to change the default get information method, so simply
// use the default implementation.
//
SPL_IMPLEMENT_PLUGIN_GETINFO();
