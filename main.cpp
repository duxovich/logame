#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include "engine.hpp"
#include "rendersystem.hpp"

int main( )
{
	SetConsoleTitleA( "LO Game" );

	render::create( 50, 20 );

	for ( ; ; )
	{
		render::run( );
	}

	return 0;
}