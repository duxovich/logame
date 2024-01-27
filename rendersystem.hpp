#include < windows.h >
#include < iostream >

#include "engine.hpp"
#include "inputsystem.hpp"
#include "runtime.hpp"

#include "vmpsdk.h"

namespace render
{
	extern void create( int w, int h );
	extern void CALLBACK run( );

	extern HANDLE hConsole;
	extern char scene[ 50 * 20 ];
	extern unsigned frames;
}