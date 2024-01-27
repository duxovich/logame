#include "inputsystem.hpp"
#include "skc.hpp"
#include "vmpsdk.h"

void inputsystem::run( int *coords )
{
	VMProtectBeginMutation( __FUNCTION__ );
	using engine::PoolCoordinates;
	if ( GetForegroundWindow( ) == GetConsoleWindow( ) )
	{
		if ( GetAsyncKeyState( 'W' ) & TRUE )
		{
			if ( *coords!=PoolCoordinates::E_1_1&&*coords!=PoolCoordinates::E_1_2&&*coords!=PoolCoordinates::E_1_3&&*coords!=PoolCoordinates::E_1_4&&*coords!=PoolCoordinates::E_1_5&&*coords!=PoolCoordinates::SURBT&&*coords!=PoolCoordinates::REROL&&*coords!=PoolCoordinates::SHOWFC )
			{
				MOVE_UP( *coords );
				return;
			}
			if ( *coords==PoolCoordinates::SURBT )
			{
				*coords = PoolCoordinates::E_5_1;
				return;
			}
			if ( *coords==PoolCoordinates::REROL )
			{
				*coords = PoolCoordinates::E_5_2;
				return;
			}
			if ( *coords==PoolCoordinates::SHOWFC )
			{
				*coords = PoolCoordinates::E_5_3;
				return;
			}
		}
		if ( GetAsyncKeyState( 'S' ) & TRUE )
		{
			if ( *coords==PoolCoordinates::E_5_1||*coords==PoolCoordinates::E_5_2||*coords==PoolCoordinates::E_5_3||*coords==PoolCoordinates::E_5_4||*coords==PoolCoordinates::E_5_5 )
			{
				*coords = PoolCoordinates::SURBT;
				return;
			}
			if ( *coords!=PoolCoordinates::E_5_1&&*coords!=PoolCoordinates::E_5_2&&*coords!=PoolCoordinates::E_5_3&&*coords!=PoolCoordinates::E_5_4&&*coords!=PoolCoordinates::E_5_5&&*coords!=PoolCoordinates::SURBT&&*coords!=PoolCoordinates::REROL&&*coords!=PoolCoordinates::SHOWFC )
			{
				MOVE_DOWN( *coords );
				return;
			}
		}
		if ( GetAsyncKeyState( 'A' ) & TRUE )
		{
			if ( *coords!=PoolCoordinates::E_1_1&&*coords!=PoolCoordinates::E_2_1&&*coords!=PoolCoordinates::E_3_1&&*coords!=PoolCoordinates::E_4_1&&*coords!=PoolCoordinates::E_5_1&&*coords!=PoolCoordinates::SURBT&&*coords!=PoolCoordinates::REROL&&*coords!=PoolCoordinates::SHOWFC )
			{
				MOVE_LEFT( *coords );
				return;
			}
			if ( *coords==PoolCoordinates::SHOWFC )
			{
				*coords = PoolCoordinates::REROL;
				return;
			}
			if ( *coords==PoolCoordinates::REROL )
			{
				*coords = PoolCoordinates::SURBT;
				return;
			}
		}
		if ( GetAsyncKeyState( 'D' ) & TRUE )
		{
			if ( *coords!=PoolCoordinates::E_1_5&&*coords!=PoolCoordinates::E_2_5&&*coords!=PoolCoordinates::E_3_5&&*coords!=PoolCoordinates::E_4_5&&*coords!=PoolCoordinates::E_5_5&&*coords!=PoolCoordinates::SURBT&&*coords!=PoolCoordinates::REROL&&*coords!=PoolCoordinates::SHOWFC )
			{
				MOVE_RIGHT( *coords );
				return;
			}
			if ( *coords==PoolCoordinates::REROL )
			{
				*coords = PoolCoordinates::SHOWFC;
				return;
			}
			if ( *coords==PoolCoordinates::SURBT )
			{
				*coords = PoolCoordinates::REROL;
				return;
			}
		}
		if ( GetAsyncKeyState( VK_SPACE ) & TRUE )
		{
			if ( *coords==PoolCoordinates::SURBT )
			{
				MessageBox( GetConsoleWindow( ), _( "Defeat" ), _( "LOGame" ), MB_OK|MB_ICONERROR );
				engine::ResetEngine( );
				return;
			}
			if ( *coords==PoolCoordinates::REROL )
			{
				FILETIME ft;
				memset( &ft, 0, sizeof ft );
				GetSystemTimeAsFileTime( &ft );
				srand( ft.dwLowDateTime );
				engine::gamePool = 0;
				for ( auto m = 0; m < rand( ) % 100; m++ )
				{
					COORD _coordinates = { rand( ) % 4 + 1, rand( ) % 4 + 1 };
					for ( int j = 0; j < 5; j++ )
					{
						COORD m_coord = _coordinates;
						switch ( j )
						{
							case 0: {
								break;
							}
							case 1: {
								m_coord.X += 1;
								break;
							}
							case 2: {
								m_coord.X -= 1;
								break;
							}
							case 3: {
								m_coord.Y += 1;
								break;
							}
							case 4: {
								m_coord.Y -= 1;
								break;
							}
						}

						BOOL state = engine::GetState( m_coord );
						engine::SetState( m_coord, !state );
					}
				}
				return;
			}
			if ( *coords==PoolCoordinates::SHOWFC )
			{
				engine::debugMode = !engine::debugMode;
				return;
			}
			for ( int j = 0; j < 5; j++ )
			{
				COORD poolPos = engine::SceneToPoolPos( *coords );

				switch ( j )
				{
				case 0: {
					break;
				}
				case 1: {
					poolPos.X += 1;
					break;
				}
				case 2: {
					poolPos.X -= 1;
					break;
				}
				case 3: {
					poolPos.Y += 1;
					break;
				}
				case 4: {
					poolPos.Y -= 1;
					break;
				}
				}

				BOOL state = engine::GetState( poolPos );
				engine::SetState( poolPos, !state );
			}
		}
	}
	VMProtectEnd( );
}