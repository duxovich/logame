#pragma once

#include < windows.h >
#include < iostream >

#include "skc.hpp"

namespace engine
{
	enum PoolCoordinates : int
	{
		E_1_1 = 4 * 50 + 14,
		E_1_2 = 4 * 50 + 18,
		E_1_3 = 4 * 50 + 22,
		E_1_4 = 4 * 50 + 26,
		E_1_5 = 4 * 50 + 30,
		E_2_1 = 6 * 50 + 14,
		E_2_2 = 6 * 50 + 18,
		E_2_3 = 6 * 50 + 22,
		E_2_4 = 6 * 50 + 26,
		E_2_5 = 6 * 50 + 30,
		E_3_1 = 8 * 50 + 14,
		E_3_2 = 8 * 50 + 18,
		E_3_3 = 8 * 50 + 22,
		E_3_4 = 8 * 50 + 26,
		E_3_5 = 8 * 50 + 30,
		E_4_1 = 10 * 50 + 14,
		E_4_2 = 10 * 50 + 18,
		E_4_3 = 10 * 50 + 22,
		E_4_4 = 10 * 50 + 26,
		E_4_5 = 10 * 50 + 30,
		E_5_1 = 12 * 50 + 14,
		E_5_2 = 12 * 50 + 18,
		E_5_3 = 12 * 50 + 22,
		E_5_4 = 12 * 50 + 26,
		E_5_5 = 12 * 50 + 30,
		SURBT = 20 * 49 - 30,
		REROL = 20 * 49 - 16,
		SHOWFC =  20 * 49 - 5
	};

	extern COORD PoolToScreenPos( COORD pool );
	extern COORD SceneToPoolPos( int scenePos );
	extern __forceinline BOOL CheckWin( );
	extern __forceinline BOOL GetState( COORD coord );
	extern __forceinline void SetState( COORD coord, BOOL state );
	extern __forceinline void ResetEngine( );

	extern BOOL debugMode;
	extern int gamePool;

	extern int selectedField;
}