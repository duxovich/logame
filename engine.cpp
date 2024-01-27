#include "engine.hpp"
#include "vmpsdk.h"

BOOL engine::debugMode = FALSE;
int engine::gamePool = 0;
int engine::selectedField = engine::E_3_3;

#pragma warning( disable : 4838 )
#pragma warning( disable : 4554 )

COORD engine::PoolToScreenPos( COORD pool )
{
	COORD screenPos = { 10 + 4 * pool.X, 2 + 2 * pool.Y };
	return screenPos;
}

COORD engine::SceneToPoolPos( int scenePos )
{
	char sceneRaw[ 4 ];
	sprintf( sceneRaw, _( "%zi" ), scenePos );

	char _y[ 2 ] = { sceneRaw[ 0 ], '\0' };
	int y = atoi( _y ) - 1;

	char _x[ 3 ] = { sceneRaw[ 1 ], sceneRaw[ 2 ], '\0' };
	int x = atoi( _x );

	x = ( x - 14 ) / 4 + 1;

	COORD poolPos = { x, y };
	return poolPos;
}

BOOL engine::CheckWin( )
{
	return gamePool == 0b1111111111111111111111111;
}

BOOL engine::GetState( COORD coord )
{
	return ( gamePool & ( 1 << ( ( coord.Y - 1 ) * 5 ) + ( coord.X - 1 ) ) ) > 0;
}

void engine::SetState( COORD coord, BOOL state )
{
	if ( ( coord.X > 0 && coord.X <= 5 ) && ( coord.Y > 0 && coord.Y <= 5 ) )
	{
		if ( state )
		{
			gamePool |= ( TRUE << ( ( coord.Y - 1 ) * 5 ) + ( coord.X - 1 ) );
		}
		else
		{
			gamePool &= ~( TRUE << ( ( coord.Y - 1 ) * 5 ) + ( coord.X - 1 ) );
		}
	}
}

void engine::ResetEngine( )
{
	gamePool ^= gamePool;
	selectedField = E_3_3;
	debugMode = FALSE;
}