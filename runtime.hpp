#pragma once

namespace vcruntime
{
	__declspec( selectany ) unsigned next = 0;

	int rand( );
	void srand( unsigned _seed );

	void memset( void *_dst, int _val, unsigned __int64 _sz );
	void strcpy( char *_dst, const char *_src );
}