#pragma once

template< typename T >
class CRSA
{
public:

	static T	Process( T data, T e1, T n )
	{
		return Montgomery( data, e1, n );
	}

	// return n^p mod m
	static T	Montgomery( T n, T p, T m )
	{
		T	k = 1;
		p %= m;

		while( p != 1 )
		{
			if( !p.IsEven() )
				k = ( n*k ) % m;

			n = (n*n) % m;
			p /= 2;
		}

		return ( n*k ) % m;
	}

};