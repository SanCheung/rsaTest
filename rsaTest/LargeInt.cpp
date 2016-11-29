#include "StdAfx.h"
#include "LargeInt.h"

#define		HEX				10
#define		c2i( c )		( (c) - '0' )
#define		i2c( i )		(u8)( (i) + '0' )

CLargeInt::CLargeInt(void)
: _sign( 0 )
{
}

CLargeInt::CLargeInt( int v )
: _sign( 0 )
{
	*this = FromInt( v );
}

CLargeInt::CLargeInt( string str )
: _sign( 0 )
{
	*this = FromString( str );
}

CLargeInt::~CLargeInt(void)
{
}


void CLargeInt::FormatValue()
{
	size_t	i = 0;
	while( i < _values.size() )
	{
		int		v = GetValue( i );
		SetValue( i, v % HEX );
		if( v/HEX > 0 )
			AddValue( i+1, v/HEX );

		i++;
	}
}

void CLargeInt::EraseHighZero()
{
	size_t	i = _values.size();
	while( i-- )
	{
		if( _values[i] != 0 )
			break;

		_values.erase( _values.begin() + i );
	}

	if( _values.empty() )
		_values.push_back( 0 );
}


// FromInt / FromString
CLargeInt CLargeInt::FromString( string str )
{
	CLargeInt		c;
	if( str.empty() )
		return c;

	if( str[0] == '-' )
	{
		c._sign = 1;
		str.erase( 0, 1 );
	}

	int		n = (int)str.size();
	//if( 10 == c.HEX )
	//{
		while( n-- )
			c._values.push_back( c2i( str[n] ) );
	//}
	//else if( 100 == c.HEX )
	//{
	//	u32	v;
	//	while( n > 0 )
	//	{
	//		n--;
	//		if( n == 0 )
	//			v = c2i( str[n] );
	//		else
	//			v = 10*c2i(str[n-1]) + c2i(str[n]);

	//		c._values.push_back( v );

	//		n--;
	//	}
	//}
	//else if( 1000 == c.HEX )
	//{
	//	u32	v;
	//	while( n > 0 )
	//	{
	//		n--;
	//		if( n == 0 )
	//			v = c2i( str[n] );
	//		else if( n == 1 )
	//			v = 10*c2i(str[n-1]) + c2i(str[n]);
	//		else
	//			v = 100*c2i(str[n-2]) + 10*c2i(str[n-1]) + c2i(str[n]);

	//		c._values.push_back( v );
	//		n -= 2;
	//	}
	//}
	//else if( 10000 == c.HEX )
	//{
	//	u32	v;
	//	while( n > 0 )
	//	{
	//		n--;
	//		if( n == 0 )
	//			v = c2i( str[n] );
	//		else if( n == 1 )
	//			v = 10*c2i(str[n-1]) + c2i(str[n]);
	//		else if( n == 2 )
	//			v = 100*c2i(str[n-2]) + 10*c2i(str[n-1]) + c2i(str[n]);
	//		else
	//			v = 1000*c2i(str[n-3]) + 100*c2i(str[n-2]) + 10*c2i(str[n-1]) + c2i(str[n]);
	//		
	//		c._values.push_back( v );
	//		n -= 3;
	//	}
	//}
	c.EraseHighZero();
	return c;
}

CLargeInt CLargeInt::FromInt( int v )
{
	CLargeInt	c;

	if( v == 0 )
	{
		c._values.clear();
		c.SetValue( 0, 0 );
		return c;
	}

	if( v < 0 )
	{
		c._sign = 1;
		v = -v;
	}

	while( v > 0 )
	{
		c._values.push_back( v % HEX );
		v /= HEX;
	}

	return c;
}


// Get/Set/AddValue
u32 CLargeInt::GetValue( size_t i ) const
{
	size_t		n = _values.size();
	if( i >= n )
		return 0;

	return _values[i];
}

void CLargeInt::SetValue( size_t i, u32 v, bool bAutoFormat )
{
	size_t		n = _values.size();
	if( i >= n )
		_values.push_back( v );
	else
		_values[i] = v;

	if( !bAutoFormat )
		return;

	if( v >= HEX )
	{
		SetValue( i, v%HEX );
		if( v/HEX > 0 )
			AddValue( i+1, v/HEX, true );
	}
}

void CLargeInt::AddValue( size_t i, u32 v, bool bAutoFormat )
{
	int		v0 = GetValue( i );
	SetValue( i, v0 + v, bAutoFormat );
}


// All operator
CLargeInt& CLargeInt::operator = ( string str )
{
	*this = FromString( str );
	return *this;
}

CLargeInt& CLargeInt::operator = ( int v )
{
	*this = FromInt( v );
	return *this;
}

bool CLargeInt::operator != ( const CLargeInt &a ) const
{
	if( *this == a )
		return false;

	return true;
}

bool CLargeInt::operator == ( const CLargeInt &a ) const
{
	if( _sign == a._sign && Com_U( *this, a ) == 0 )
		return true;

	return false;
}

bool CLargeInt::operator > ( const CLargeInt &a ) const
{
	// 判断符号
	if( _sign != a._sign )
	{
		if( _sign == 0 )
			return true;
		else
			return false;
	}

	int		nRet = Com_U( *this, a );

	// 判断绝对值
	if( ( _sign == 0 && nRet == 1 )||( _sign == 1 && nRet == -1 ) )
		return true;
	return false;
}

bool CLargeInt::operator < ( const CLargeInt &a ) const
{
	// 判断符号
	if( _sign != a._sign )
	{
		if( _sign == 1 )
			return true;
		else
			return false;
	}

	int		nRet = Com_U( *this, a );

	// 判断绝对值
	if( ( _sign == 0 && nRet == -1 )||( _sign == 1 && nRet == 1 ) )
		return true;
	return false;	
}

bool CLargeInt::operator >= ( const CLargeInt &a ) const
{
	if( *this < a )
		return false;

	return true;
}

bool CLargeInt::operator <= ( const CLargeInt &a ) const
{
	if( *this > a )
		return false;

	return true;
}

CLargeInt CLargeInt::operator + ( CLargeInt a )
{
	CLargeInt		c;
	if( _sign == a._sign )
	{
		c._sign = _sign;
		c = Add_U( *this, a );
		return c;
	}

	int		nRet = Com_U( *this, a );
	if( nRet == 0 )
		return 0;

	if( nRet == 1 )
	{
		c = Sub_U( *this, a );
		return c;
	}

	c = Sub_U( a, *this );
	c._sign = a._sign;
	return c;
}

CLargeInt CLargeInt::operator - ( CLargeInt a )
{
	CLargeInt		c;
	
	int		nRet = Com_U( *this, a );
	if( _sign == a._sign )
	{
		if( nRet == 0 )
			return 0;
		
		if( nRet == 1 )
		{
			c = Sub_U( *this, a );
			c._sign = _sign;
		}
		else
		{
			c = Sub_U( a, *this );
			c._sign = !_sign;
		}
	}
	else
	{
		if( _sign == 0 && a._sign == 1 )
			c = Add_U( *this, a );

		if( _sign == 1 && a._sign == 0 )
		{
			c = Add_U( *this, a );
			c._sign = 1;
		}
	}
	
	return c;
}

CLargeInt CLargeInt::operator * ( CLargeInt a )
{
	CLargeInt	c = Mul_U( *this, a );
	if( c._sign != _sign )
		c._sign = 1;

	return c;
}

CLargeInt CLargeInt::operator / ( CLargeInt a )
{
	CLargeInt	c = Div_U( *this, a );
	if( c._sign != _sign )
		c._sign = 1;

	return c;
}

CLargeInt CLargeInt::operator % ( CLargeInt a )
{
	// 只有正数有效
	if( a._sign != 0 || _sign != 0 )
		return 0;
	
	return Mod_U( *this, a );
}

// prefix ++
CLargeInt& CLargeInt::operator ++()
{
	AddValue( 0, 1, true );
	return *this;
}

CLargeInt& CLargeInt::operator --()
{
	AddValue( 0, -1, true );
	return *this;
}

// postfix ++
const CLargeInt CLargeInt::operator ++( int )
{
	AddValue( 0, 1, true );
	return *this;
}

const CLargeInt CLargeInt::operator --( int )
{
	AddValue( 0, -1, true );
	return *this;
}


CLargeInt CLargeInt::operator += ( CLargeInt a )
{
	*this = *this + a;
	return *this;
}

CLargeInt CLargeInt::operator -= ( CLargeInt a )
{
	*this = *this - a;
	return *this;

}

CLargeInt CLargeInt::operator *= ( CLargeInt a )
{
	*this = *this * a;
	return *this;
}

CLargeInt CLargeInt::operator /= ( CLargeInt a )
{
	*this = *this / a;
	return *this;
}

CLargeInt CLargeInt::operator %= ( CLargeInt a )
{
	*this = *this % a;
	return *this;
}

int CLargeInt::Com_U( const CLargeInt &a, const CLargeInt &b )
{
	size_t n1 = a._values.size();
	size_t n2 = b._values.size();

	if( n1 > n2 )
		return 1;

	if( n1 < n2 )
		return -1;

	if( n1 == 0 )
		return 0;

	int		i = (int)n1;
	while( i-- )
	{
		u32 v1 = a._values[i];
		u32 v2 = b._values[i];

		if( v1 > v2 )
			return 1;

		if( v1 < v2 )
			return -1;
	}

	return 0;
}

CLargeInt CLargeInt::Add_U( const CLargeInt &a, const CLargeInt &b )
{
	CLargeInt	c = 0;

	size_t	nL = a._values.size();
	size_t  nR = b._values.size();

	size_t	i;
	size_t	n = MAX( nL, nR );

	int		temp = 0;
	for( i = 0; i < n; i++ )
	{
		u32  v = a.GetValue(i) + b.GetValue(i) + temp;

		if( v >= HEX )
		{
			temp = 1;
			v %= HEX;
		}
		else
			temp = 0;

		c.SetValue( i, v );
	}

	if( temp != 0 )
		c.SetValue( n, temp );

	return c;
}

CLargeInt CLargeInt::Sub_U( const CLargeInt &a, const CLargeInt &b )
{
	CLargeInt c = 0;

	size_t	nL = a._values.size();
	size_t  nR = b._values.size();

	size_t	i;
	size_t	n = MAX( nL, nR );

	int		nFlag = 0;
	for( i = 0; i < n; i++ )
	{
		int		v1 = a.GetValue(i);
		int		v2 = b.GetValue(i);

		if( nFlag )
			v1--;

		int		v = v1 - v2;
		if( v < 0 )
		{
			nFlag = 1;
			v += HEX;
		}
		else
			nFlag = 0;
		
		c.SetValue( i, v );
	}

	c.EraseHighZero();
	return c;
}

CLargeInt CLargeInt::Mul_U( const CLargeInt &a, const CLargeInt &b )
{
	CLargeInt	c = 0;

	size_t	nL = a._values.size();
	size_t  nR = b._values.size();

	size_t	i, j;

	for( i = 0; i < nL; i++ )
	{
		int		v1 = a.GetValue(i);
		for( j = 0; j < nR; j++ )
		{
			int		v2 = b.GetValue(j);	
			c.AddValue( i+j, v1*v2, true );
		}
	}

	//c.FormatValue();
	c.EraseHighZero();
	return c;
}

CLargeInt CLargeInt::Div_U( const CLargeInt &a, const CLargeInt &b )
{
	if( a < b )
		return 0;

	vector< u32 >	av;
	CLargeInt		t = 0;

	size_t		nL = a.size();
	size_t		n = b.size();

	int		i, j;
	for( i = (int)nL-1; i > -1 ; i-- )
	{
		t = t * HEX + a.GetValue( i );
		if( t == b )
		{
			av.push_back( 1 );
			t = 0;
		}
		else	
		{
			j = 0;
			while( j < (int)HEX )
			{
				if( t < b )
					break;

				t = t - b;
				j++;
			}

			av.push_back( j );
		}
	}
	
	CLargeInt		c;
	nL = av.size();
	for( i = (int)nL-1; i > -1 ; i-- )
		c._values.push_back( av[i] );

	c.EraseHighZero();
	return c;
}

CLargeInt CLargeInt::Mod_U( const CLargeInt &a, const CLargeInt &b )
{
	if( a < b )
		return a;

	CLargeInt	c = 0;
	size_t	nL = a.size();
	size_t	nR = b.size();

	if( nL <= nR+1 )
	{
		c = a;
		while ( c >= b )
			c = c - b;
	}
	else
	{
		size_t	n = nL / nR;
		if( nL % nR )
			n++;

		CLargeInt		nPart;
		CLargeInt		n10pow;

		CLargeInt		t = 1;

		size_t	i;
		for( i = 0; i < n; i++ )
		{
			nPart = GetPart( a, nR*i, nR );

			if( i == 0 )
				c = nPart % b;
			else
			{
				if( i == 1 )
					n10pow = Get10powMod( b, 1 );

				t = ( t * n10pow ) % b;
				c = ( c + (nPart % b) * t ) % b;
			}
		}
	}

	return c;
}

CLargeInt CLargeInt::Get10powMod( const CLargeInt &a, int n )
{
	if( n == 0 )
		return 1;

	CLargeInt	b = 0;	
	if( n == 1 )
	{
		size_t		size = a.size();
		for( size_t i = 0; i < size; i++ )
			b.SetValue( i, 0 );
		
		b.SetValue( size, 1 );		
	
		while( b >= a )
			b = b - a;

		return b;
	}

	b = Get10powMod( a, n-1 );
	return b*b % a;
}

CLargeInt CLargeInt::GetPart( const CLargeInt &a, size_t nStart, size_t nSize )
{
	CLargeInt	b = 0;
	size_t		n = a.size();
	if( nStart + nSize > n )
		nSize = n - nStart;

	for( size_t i = 0; i < nSize; i++ )
	{
		int v = a.GetValue( nStart+i );
		b.SetValue( i, v );
	}

	return b;
}

void CLargeInt::Random( int nSize, bool bFilter )
{
	_values.clear();
	for( int i = 0; i < nSize; i++ )
	{
		u32		v = rand() % HEX;

		if( bFilter )
		{
			if( i == 0 )
			{
				while( v % 2 == 0 || v % 5 == 0 )
					v = rand() % HEX;
			}
		}

		_values.push_back( v );
	}

	while( GetValue( nSize-1 ) == 0 )
		SetValue( nSize-1, rand() % HEX );
}


void CLargeInt::Half()
{
	size_t		n = _values.size();

	bool		bHasHigh = false;
	for( size_t i = 0; i < n; i++ )
	{
		u32		v = _values[n-1-i];
		if( bHasHigh )
			v += HEX;

		bHasHigh = (v % 2 == 1);
		_values[n-1-i] = v / 2;
	}

	EraseHighZero();
}

bool CLargeInt::IsEven()
{
	if( _values.empty() )
		return true;

	u32	v = GetValue( 0 );
	return 0 == v%2;
}

bool CLargeInt::Is235Time()
{
	u32	v = GetValue( 0 );
	if( 0 == v%2 || 0 == v%5 )
		return true;

	v = 0;
	size_t n = _values.size();
	for( size_t i = 0; i < n; i++ )
		v += _values[i];

	if( 0 == v%3 )
		return true;

	return false;
}


CLargeInt CLargeInt::GetFixSizePrime_Speed( size_t size, int nMethod )
{
	CLargeInt::APreadFromTxt( _sap );

	CLargeInt		a;
	while( 1 )
	{
		a.Random( (int)size, true );

		//if( nMethod == 0 )
		//{
		//	if( TestPrime_Range( a, _sap, 0, 500 ) )
		//		return a;
		//}
		//else if( 1 == nMethod )
		//{
		//	if( TestPrime_MillerRabin( a, _sap ) )
		//		return a;
		//}

		if( TestPrime_Range( a, _sap, 0, 1000 ) )
		{
			//if( TestPrime_MillerRabin( a, _sap ) )
				return a;
		}
	}

}

CLargeInt CLargeInt::Euclidean( CLargeInt a, CLargeInt b )
{
	CLargeInt		t = 0;
	if( b == 1 )
	{
		t = a-b;
	}
	else if( a == 1 )
	{
		t = b+1;
		cout << "*ERROR 1!" << endl;
	}
	else
	{
		if( a > b )
			t = ( a*Euclidean( a%b, b ) - 1 ) / b;
		else
			t = ( b*Euclidean( a, b%a ) + 1 ) / a;
	}

	////printf( "%s %s = %s\n", a.toString().c_str(), 
	////						b.toString().c_str(), 
	////						t.toString().c_str() );
	//cout << a << " # " << b << " = " << t << endl;
	return t;
}

CLargeInt CLargeInt::Montgomery( CLargeInt n, CLargeInt p, CLargeInt m )
{
	CLargeInt	k = 1;
	p %= m;

	while( p != 1 )
	{
		if( !p.IsEven() )
			k = ( n*k ) % m;

		n = (n*n) % m;
		p.Half();
	}

	return ( n*k ) % m;
}

u32 CLargeInt::bitSize()
{
	u32		k = 1;

	CLargeInt	a = *this;
	while( a != 1 )
	{
		a.Half();
		k++;
	}

	return k;
}



ostream& operator <<( ostream &f, CLargeInt &a )
{
	if( a._sign )
		f << '-';

	size_t	i = a._values.size();
	while( i-- )
	{
		int v = int( a._values[i] );
		f << v;
	}

	return f;
}

istream& operator >>( istream &f, CLargeInt &a )
{
	string	str;
	f >> str;

	a = str;
	return f;
}

vector< CLargeInt > CLargeInt::_sap;