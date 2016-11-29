#include "StdAfx.h"
#include "HugeInt.h"

CHugeInt::CHugeInt(void)
	: _sign( 0 )
{
}

CHugeInt::CHugeInt( int v )
{
	*this = FromInt( v );
}

CHugeInt::CHugeInt( string str )
{
	*this = FromString( str );
}


CHugeInt::~CHugeInt(void)
{
}

u32 CHugeInt::str2Number( char *c, int n )
{
	u32 v = 0;
	for( int i = 0; i < n; i++ )
		v = v*10 + c[i] - '0';

	return v;
}

void CHugeInt::num2String( u32 v, char* c )
{
	if( v >= CARRY )
		return;

	char p[4] = {0};

	int i = 0;
	while( v > 0 )
	{
		p[3-i] = char( '0' + v%10 );
		v /= 10;
		i++;
	}

	while( i < 4 )
	{
		p[3-i] = '0';
		i++;
	}

	memcpy( c, p, i );
}



void CHugeInt::EraseHighZero()
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

CHugeInt CHugeInt::FromString( string str )
{
	CHugeInt		_this;
	if( str.empty() )
		return _this;

	char *s = (char *)str.c_str();
	int	 n = (int)str.size();

	if( *s == '-' )
	{
		_this._sign = 0;
		s++;
		n--;
	}

	int x = n % 4;

	u32		v;
	while( n > 0 )
	{
		if( x > 0 )
		{
			v = str2Number( s, x );
			_this._values.insert( _this._values.begin(), v );

			s += x;
			n -= x;
		}

		x = 4;
	}

	return _this;
}

string CHugeInt::toString()
{
	size_t	i;
	size_t	n = size();

	string	str;

	char p[8] = {0};
	for( i = 0; i < n; i++ )
	{
		num2String( _values[n-1-i], p );
		str += p;
		//str += ",";
	}

	while( str[0] == '0' )
		str.erase( 0, 1 );

	return str;
}


CHugeInt CHugeInt::FromInt( int v )
{
	CHugeInt		_this;

	if( v < 0 )
	{
		_this._sign = 0;
		v = -v;
	}

	while( v > 0 )
	{
		_this._values.push_back( v%CARRY );
		v /= CARRY;
	}
		
	return _this;
}

// Get/Set/AddValue
u32 CHugeInt::GetValue( size_t i ) const
{
	size_t		n = _values.size();
	if( i >= n )
		return 0;

	return _values[i];
}

void CHugeInt::SetValue( size_t i, u32 v, bool bAutoFormat )
{
	size_t		n = _values.size();
	if( i >= n )
		_values.push_back( v );
	else
		_values[i] = v;

	if( !bAutoFormat )
		return;

	if( v >= CARRY )
	{
		SetValue( i, v%CARRY );
		if( v/CARRY > 0 )
			AddValue( i+1, v/CARRY, true );
	}
}

void CHugeInt::AddValue( size_t i, u32 v, bool bAutoFormat )
{
	int		v0 = GetValue( i );
	SetValue( i, v0 + v, bAutoFormat );
}




// All operator
CHugeInt& CHugeInt::operator = ( string str )
{
	*this = FromString( str );
	return *this;
}

CHugeInt& CHugeInt::operator = ( int v )
{
	*this = FromInt( v );
	return *this;
}

bool CHugeInt::operator != ( const CHugeInt &a ) const
{
	if( *this == a )
		return false;

	return true;
}

bool CHugeInt::operator == ( const CHugeInt &a ) const
{
	if( _sign == a._sign && Com_U( *this, a ) == 0 )
		return true;

	return false;
}

bool CHugeInt::operator > ( const CHugeInt &a ) const
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

bool CHugeInt::operator < ( const CHugeInt &a ) const
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

bool CHugeInt::operator >= ( const CHugeInt &a ) const
{
	if( *this < a )
		return false;

	return true;
}

bool CHugeInt::operator <= ( const CHugeInt &a ) const
{
	if( *this > a )
		return false;

	return true;
}

CHugeInt CHugeInt::operator + ( CHugeInt a )
{
	CHugeInt		c;
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

CHugeInt CHugeInt::operator - ( CHugeInt a )
{
	CHugeInt		c;

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

CHugeInt CHugeInt::operator * ( CHugeInt a )
{
	CHugeInt	c = Mul_U( *this, a );
	if( c._sign != _sign )
		c._sign = 1;

	return c;
}

//CHugeInt CHugeInt::operator * ( int a )
//{
//	CHugeInt	aa( a );
//	CHugeInt	c = Mul_U( *this, aa );
//	if( c._sign != _sign )
//		c._sign = 1;
//
//	return c;
//}

CHugeInt CHugeInt::operator / ( CHugeInt a )
{
	CHugeInt	m;
	CHugeInt	c = Div_U( *this, a, m );
	if( c._sign != _sign )
		c._sign = 1;

	return c;
}

CHugeInt CHugeInt::operator % ( CHugeInt a )
{
	// 只有正数有效
	if( a._sign != 0 || _sign != 0 )
		return 0;

	//return Mod_U( *this, a );
	CHugeInt	m;
	Div_U( *this, a, m );

	return m;
}

// prefix ++
CHugeInt& CHugeInt::operator ++()
{
	AddValue( 0, 1, true );
	return *this;
}

CHugeInt& CHugeInt::operator --()
{
	AddValue( 0, -1, true );
	return *this;
}

// postfix ++
const CHugeInt CHugeInt::operator ++( int )
{
	AddValue( 0, 1, true );
	return *this;
}

const CHugeInt CHugeInt::operator --( int )
{
	AddValue( 0, -1, true );
	return *this;
}


CHugeInt CHugeInt::operator += ( CHugeInt a )
{
	*this = *this + a;
	return *this;
}

CHugeInt CHugeInt::operator -= ( CHugeInt a )
{
	*this = *this - a;
	return *this;

}

CHugeInt CHugeInt::operator *= ( CHugeInt a )
{
	*this = *this * a;
	return *this;
}

CHugeInt CHugeInt::operator /= ( CHugeInt a )
{
	*this = *this / a;
	return *this;
}

CHugeInt CHugeInt::operator %= ( CHugeInt a )
{
	*this = *this % a;
	return *this;
}







// private
int CHugeInt::Com_U( const CHugeInt &a, const CHugeInt &b )
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

CHugeInt CHugeInt::Add_U( const CHugeInt &a, const CHugeInt &b )
{
	CHugeInt	c = 0;

	size_t	nL = a._values.size();
	size_t  nR = b._values.size();

	size_t	i;
	size_t	n = MAX( nL, nR );

	int		temp = 0;
	for( i = 0; i < n; i++ )
	{
		u32  v = a.GetValue(i) + b.GetValue(i) + temp;

		if( v >= CARRY )
		{
			temp = 1;
			v %= CARRY;
		}
		else
			temp = 0;

		c.SetValue( i, v );
	}

	if( temp != 0 )
		c.SetValue( n, temp );

	return c;
}

CHugeInt CHugeInt::Sub_U( const CHugeInt &a, const CHugeInt &b )
{
	CHugeInt c = 0;

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
			v += CARRY;
		}
		else
			nFlag = 0;

		c.SetValue( i, v );
	}

	c.EraseHighZero();
	return c;
}

CHugeInt CHugeInt::Mul_U( const CHugeInt &a, const CHugeInt &b )
{
	CHugeInt	c = 0;

	size_t	nL = a._values.size();
	size_t  nR = b._values.size();

	if( nL == 0 || nR == 0 )
		return c;

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

	c.EraseHighZero();
	return c;
}

CHugeInt CHugeInt::Div_U( const CHugeInt &a, const CHugeInt &b, CHugeInt &m )
{
	if( a < b )
	{
		m = a;
		return 0;
	}

	vector< u32 >	av;
	CHugeInt		t = 0;

	size_t		nL = a.size();
	size_t		n = b.size();
	int			i;
	for( i = (int)nL-1; i > -1 ; i-- )
	{
		t = baseUp( t ) + a.GetValue( i );

		CHugeInt	tt;
		int		lf, rg, mid;
		for (lf = 0, rg = CARRY -1; lf < rg; ) {
			mid = (lf + rg + 1) / 2;

			tt = mid;
			if ( tt * b > t )
				rg = mid - 1;
			else
				lf = mid;	
		}

		tt = lf;
		tt *= b;
		t -= tt;
		av.push_back( lf );
	}

	m = t;

	CHugeInt		c;
	nL = av.size();
	for( i = (int)nL-1; i > -1 ; i-- )
		c._values.push_back( av[i] );

	c.EraseHighZero();
	return c;
}


CHugeInt CHugeInt::Div_U2( const CHugeInt &a, const CHugeInt &b, CHugeInt &m )
{
	if( a < b )
	{
		m = a;
		return 0;
	}

	vector< u32 >	av;
	CHugeInt		t = 0;

	size_t		nL = a.size();
	size_t		n = b.size();

	//int		l, r, mid;

	int		i, j;
	for( i = (int)nL-1; i > -1 ; i-- )
	{
		t = baseUp( t ) + a.GetValue( i );
		j = 0;
		while( j < (int)CARRY )
		{
			if( t < b )
				break;

			t = t - b;
			j++;
		}

		av.push_back( j );
	}

	m = t;

	CHugeInt		c;
	nL = av.size();
	for( i = (int)nL-1; i > -1 ; i-- )
		c._values.push_back( av[i] );

	c.EraseHighZero();
	return c;
}


/*
CHugeInt CHugeInt::Mod_U( const CHugeInt &a, const CHugeInt &b )
{
	if( a < b )
		return a;

	CHugeInt	c = 0;
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

		CHugeInt		nPart;
		CHugeInt		n10pow;

		CHugeInt		t = 1;

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


CHugeInt CHugeInt::Get10powMod( const CHugeInt &a, int n )
{
	if( n == 0 )
		return 1;

	CHugeInt	b = 0;	
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

CHugeInt CHugeInt::GetPart( const CHugeInt &a, size_t nStart, size_t nSize )
{
	CHugeInt	b = 0;
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

//*/

CHugeInt CHugeInt::baseUp( CHugeInt t )
{
	CHugeInt r = t * CARRY;
	return r;
}


ostream& operator <<( ostream &f, CHugeInt &a )
{
	//if( a._sign )
	//	f << '-';

	//size_t	i = a._values.size();
	//while( i-- )
	//{
	//	int v = int( a._values[i] );
	//	f << v;
	//}

	//return f;
	string	str = a.toString();
	f << str.c_str();
	return f;
}

istream& operator >>( istream &f, CHugeInt &a )
{
	string	str;
	f >> str;

	a = str;
	return f;
}

bool CHugeInt::IsEven()
{
	if( _values.empty() )
		return true;

	u32	v = GetValue( 0 );
	return 0 == v%2;
}

CHugeInt CHugeInt::Montgomery( CHugeInt n, CHugeInt p, CHugeInt m )
{
	CHugeInt	k = 1;
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

void CHugeInt::Random( int nSize, bool bFilter25 )
{
	_values.clear();
	for( int i = 0; i < nSize; i++ )
	{
		u32		v = rand() % CARRY;

		if( bFilter25 && i == 0 )
		{
			while( v % 2 == 0 || v % 5 == 0 )
				v = rand() % CARRY;
		}

		_values.push_back( v );
	}

	while( GetValue( nSize-1 ) == 0 )
		SetValue( nSize-1, rand() % CARRY );
}

u32 CHugeInt::bitSize()
{
	u32		k = 1;

	CHugeInt	a = *this;
	while( a != 1 )
	{
		a /= 2;
		k++;
	}

	return k;
}