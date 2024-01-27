#include "rendersystem.hpp"

HANDLE render::hConsole;
char render::scene[ 50 * 20 ];
unsigned render::frames = 0;

#pragma warning ( disable : 4838 )

void render::create( int w, int h )
{
	VMProtectBeginMutation( __FUNCTION__ );
	COORD coord;
	coord.X = w;
	coord.Y = h;
	SMALL_RECT Rect;
	Rect.Top = 0;
	Rect.Left = 0;
	Rect.Bottom = h-1;
	Rect.Right = w-1;
	HANDLE Handle = GetStdHandle( STD_OUTPUT_HANDLE );
	SetConsoleScreenBufferSize( Handle, coord );
	SetConsoleWindowInfo( Handle, TRUE, &Rect );
	hConsole = CreateConsoleScreenBuffer(
		GENERIC_READ|GENERIC_WRITE, 0, 0, CONSOLE_TEXTMODE_BUFFER, 0
	);
	SetConsoleActiveScreenBuffer( render::hConsole );
	VMProtectEnd( );
}

void CALLBACK render::run( )
{
	VMProtectBeginMutation( __FUNCTION__ );
	if ( GetForegroundWindow( ) == GetConsoleWindow( ) )
	{
		WORD buttonCol = 0;

		if ( engine::CheckWin( ) )
		{
			MessageBox( 0, _( "Win" ), _( "LOGame" ), MB_OK|MB_ICONINFORMATION );
			engine::ResetEngine( );
		}

		inputsystem::run( &engine::selectedField );

		COORD coord = { 0, 0 };
		DWORD total = 0;

		if ( engine::debugMode )
		{
			sprintf( &scene[ 0*0 ], _( "Total frames: %u" ), frames );
		}
		else
		{
			vcruntime::memset( &scene[ 0*0 ], '\0', 50 );
		}

		vcruntime::strcpy( &scene[ engine::E_1_1 ], _( "[ ] [ ] [ ] [ ] [ ]" ) );
		vcruntime::strcpy( &scene[ engine::E_2_1 ], _( "[ ] [ ] [ ] [ ] [ ]" ) );
		vcruntime::strcpy( &scene[ engine::E_3_1 ], _( "[ ] [ ] [ ] [ ] [ ]" ) );
		vcruntime::strcpy( &scene[ engine::E_4_1 ], _( "[ ] [ ] [ ] [ ] [ ]" ) );
		vcruntime::strcpy( &scene[ engine::E_5_1 ], _( "[ ] [ ] [ ] [ ] [ ]" ) );

		vcruntime::strcpy( &scene[ engine::SURBT ], _( "[ SURRENDER ]" ) );
		vcruntime::strcpy( &scene[ engine::REROL ], _( "[ REROLL ]" ) );
		vcruntime::strcpy( &scene[ engine::SHOWFC ], _( "[ SHOW FRAME COUNT ]" ) );

		if ( engine::selectedField != engine::SURBT && engine::selectedField != engine::REROL && engine::selectedField != engine::SHOWFC )
		{
			vcruntime::memset( &scene[ engine::selectedField + 1 ], 'x', 1 );
		}

		for ( int x = 1; x < 6; x++ )
		{
			for ( int y = 1; y < 6; y++ )
			{
				COORD coordinate = { x, y };
				WORD color = engine::GetState( coordinate ) ? ( ( ( 6 << 4 ) | 0 ) ) : ( ( ( 0 << 4 ) | 7 ) );
				DWORD dwAttrWritten = 0;
				for ( int j = 0; j < 3; j++ )
				{
					COORD screenPos = engine::PoolToScreenPos( coordinate );
					screenPos.X += j;
					WriteConsoleOutputAttribute( hConsole, &color, 1, screenPos, &dwAttrWritten );
				}
			}
		}

		for ( int m = 0; m < 13; m++ )
		{
			COORD buttonCoord = { m, 19 };
			buttonCol = engine::selectedField != engine::SURBT ? ( ( ( 0 << 4 ) | 0xC ) ) : ( ( ( 0xC << 4 ) | 0 ) );
			WriteConsoleOutputAttribute( hConsole, &buttonCol, 1, buttonCoord, &total );
		}
		for ( int r = 14; r < 24; r++ )
		{
			COORD buttonCoord = { r, 19 };
			buttonCol = engine::selectedField !=engine::REROL ? ( ( ( 0 << 4 ) | 7 ) ) : ( ( ( 7 << 4 ) | 0 ) );
			WriteConsoleOutputAttribute( hConsole, &buttonCol, 1, buttonCoord, &total );
		}
		for ( int f = 25; f < 45; f++ )
		{
			COORD buttonCoord = { f, 19 };
			buttonCol = engine::debugMode ? 0xA : 0xC;
			buttonCol |= engine::selectedField == engine::SHOWFC ? ( 8 << 4 ) : ( 0 << 4 );
			WriteConsoleOutputAttribute( hConsole, &buttonCol, 1, buttonCoord, &total );
		}

		WriteConsoleOutputCharacter( hConsole, scene, sizeof scene, coord, &total );
		++frames;
	}
	Sleep( 10 );
	VMProtectEnd( );
}