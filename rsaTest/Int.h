#pragma once

typedef		unsigned __int64	u64;

class CInt
{
public:
	CInt(void)		: _value( 0 ) {}
	CInt( u64 v)	: _value( v ) {}
	~CInt(void){}

	// 2^64 = 18,446,744,073,709,551,616
	u64		_value;

public:
	//string	toString( int bShowZero = 0 ) const;
	//CInt&		operator = ( string str );
	CInt&	operator = ( u64 v )				{ _value = v; return *this; }
	CInt&	operator = ( int v )				{ _value = v; return *this; }
	CInt&	operator = ( const CInt &rhs )		{ _value = rhs._value; return *this; }

	operator u64() const						{ return _value; }

	string	toString()
	{
		char buf[128] = {0};
		sprintf( buf, "%d", _value );

		return buf;
	}
	
public:
	static void		Get3Prime( CInt &a, CInt &b, CInt &c )
	{
		a = 101;
		b = 79;
		c = 23;
	}

	// 辗转相除，求e
	// gcd( d*e, n ) = 1;
	// e*x - n*y = 1;

	// 求x
	// a*x - b*y = 1;
	static CInt		zzxc( CInt a, CInt b )
	{
		if( b == 1 )
			return a-b;
		
		if( a > b )
			return ( a*zzxc( a%b, b ) - 1 ) / b;
		else
			return ( b*zzxc( a, b%a ) + 1 ) / a;
	}

	// ( n ^ p ) % m
	// 快速计算 (n ^ p) % m 的值
	//	蒙格马利”快速幂模算法
	static CInt		Montgomery2( CInt n, CInt p, CInt m )
	{
		CInt	k = 1;
		p = p % m;

		while( p != 1 )
		{
			if( 0 != ( p&1 ) )
				k = ( n*k ) % m;

			n = (n*n) % m;
			p = p/2;
		}

		return ( n*k ) % m;
	}

};
