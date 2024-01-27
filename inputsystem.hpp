#include < windows.h >
#include < iostream >

#include "engine.hpp"

#define MOVE_UP( var ) var -= 100
#define MOVE_DOWN( var ) var += 100
#define MOVE_LEFT( var ) var -= 4
#define MOVE_RIGHT( var ) var += 4

namespace inputsystem
{
	extern void run( int *coordinates );
}