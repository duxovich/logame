#include "runtime.hpp"

int vcruntime::rand( )
{
	next = next * 1103515245 + 12345;
	return ( next / 65535 ) % 32768;
}

void vcruntime::srand( unsigned _seed )
{
	next = _seed;
}

void vcruntime::memset( void *_dst, int _val, unsigned __int64 _sz )
{
	for ( auto j = 0; j < _sz; j++ )
	{
		reinterpret_cast< char * >( _dst )[ j ] = static_cast< unsigned char >( _val );
	}
}

void vcruntime::strcpy( char *_dst, const char *_src )
{
	for ( auto j = 0; _src[ j ]; j++ )
	{
		_dst[ j ] = _src[ j ];
	}
}