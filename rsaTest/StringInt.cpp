#include "StdAfx.h"
#include "StringInt.h"

// 500 = 16 x 31 + 4
static u32 sau_prime500[] = 
{
	   2,   3,   5,   7,  11,  13,  17,  19,  23,  29,  31,  37,  41,  43,  47,  53,
	  59,  61,  67,  71,  73,  79,  83,  89,  97, 101, 103, 107, 109, 113, 127, 131,
	 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223,
	 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311,
	 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409,
	 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503,
	 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613,
	 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719,
	 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827,
	 829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 941,
	 947, 953, 967, 971, 977, 983, 991, 997,1009,1013,1019,1021,1031,1033,1039,1049,
	1051,1061,1063,1069,1087,1091,1093,1097,1103,1109,1117,1123,1129,1151,1153,1163,
	1171,1181,1187,1193,1201,1213,1217,1223,1229,1231,1237,1249,1259,1277,1279,1283,
	1289,1291,1297,1301,1303,1307,1319,1321,1327,1361,1367,1373,1381,1399,1409,1423,
	1427,1429,1433,1439,1447,1451,1453,1459,1471,1481,1483,1487,1489,1493,1499,1511,
	1523,1531,1543,1549,1553,1559,1567,1571,1579,1583,1597,1601,1607,1609,1613,1619,
	1621,1627,1637,1657,1663,1667,1669,1693,1697,1699,1709,1721,1723,1733,1741,1747,
	1753,1759,1777,1783,1787,1789,1801,1811,1823,1831,1847,1861,1867,1871,1873,1877,
	1879,1889,1901,1907,1913,1931,1933,1949,1951,1973,1979,1987,1993,1997,1999,2003,
	2011,2017,2027,2029,2039,2053,2063,2069,2081,2083,2087,2089,2099,2111,2113,2129,
	2131,2137,2141,2143,2153,2161,2179,2203,2207,2213,2221,2237,2239,2243,2251,2267,
	2269,2273,2281,2287,2293,2297,2309,2311,2333,2339,2341,2347,2351,2357,2371,2377,
	2381,2383,2389,2393,2399,2411,2417,2423,2437,2441,2447,2459,2467,2473,2477,2503,
	2521,2531,2539,2543,2549,2551,2557,2579,2591,2593,2609,2617,2621,2633,2647,2657,
	2659,2663,2671,2677,2683,2687,2689,2693,2699,2707,2711,2713,2719,2729,2731,2741,
	2749,2753,2767,2777,2789,2791,2797,2801,2803,2819,2833,2837,2843,2851,2857,2861,
	2879,2887,2897,2903,2909,2917,2927,2939,2953,2957,2963,2969,2971,2999,3001,3011,
	3019,3023,3037,3041,3049,3061,3067,3079,3083,3089,3109,3119,3121,3137,3163,3167,
	3169,3181,3187,3191,3203,3209,3217,3221,3229,3251,3253,3257,3259,3271,3299,3301,
	3307,3313,3319,3323,3329,3331,3343,3347,3359,3361,3371,3373,3389,3391,3407,3413,
	3433,3449,3457,3461,3463,3467,3469,3491,3499,3511,3517,3527,3529,3533,3539,3541,
	3547,3557,3559,3571
};

//static void rev( const string &s, string &d, bool toChar )
//{
//	size_t		n = s.size();
//	while( n-- )
//		if( toChar )
//			d.push_back( s[n]+'0' );
//		else
//			d.push_back( s[n]-'0' );
//}


//#define		HEX		10

#define		c2i( c )		( (c) - '0' )
#define		i2c( i )		(u8)( (i) + '0' )
#define		SHEX			10

//inline	u32  c2i( char c )
//{
//	return c - '0';
//}
//
//inline	char  i2c( u32 u )
//{
//	return u + '0';
//}


ostream& operator <<( ostream &f, CStringInt &a )
{
	size_t	i = a._values.size();
	while( i-- )
	{
		int v = int( a._values[i] );
		f << v;
	}

	f << ' ';
	return f;
}

istream& operator >>( istream &f, CStringInt &a )
{
	string	str;
	f >> str;

	CStringInt::FromString( a, str );
	return f;
}


vector< CStringInt > CStringInt::_sap;



CStringInt::CStringInt()
	: _sign( 0 )
	, HEX( SHEX )
{

}

CStringInt::CStringInt( int v )
	: _sign( 0 )
	, HEX( SHEX )
{
	FromInt( *this, v );
}

CStringInt::CStringInt( string str )
	: _sign( 0 )
	, HEX( SHEX )
{
	FromString( *this, str );
}

CStringInt::~CStringInt(void)
{
	_values.clear();
}

// static 
void CStringInt::FromString( CStringInt &c, string str )
{
	if( str.empty() )
		return;

	if( str[0] == '-' )
	{
		c._sign = 1;
		str.erase( 0 );
	}

	int		n = (int)str.size();

	if( 10 == c.HEX )
	{
		while( n-- )
			c._values.push_back( c2i( str[n] ) );
		//rev( str, c._values, false );	
	}
	else if( 100 == c.HEX )
	{
		u32	v;
		while( n > 0 )
		{
			n--;
			if( n == 0 )
				v = c2i( str[n] );
			else
				v = 10*c2i(str[n-1]) + c2i(str[n]);

			c._values.push_back( v );

			n--;
		}
	}
	else if( 1000 == c.HEX )
	{
		u32	v;
		while( n > 0 )
		{
			n--;
			if( n == 0 )
				v = c2i( str[n] );
			else if( n == 1 )
				v = 10*c2i(str[n-1]) + c2i(str[n]);
			else
				v = 100*c2i(str[n-2]) + 10*c2i(str[n-1]) + c2i(str[n]);

			c._values.push_back( v );
			n -= 2;
		}
	}
	else if( 10000 == c.HEX )
	{
		u32	v;
		while( n > 0 )
		{
			n--;
			if( n == 0 )
				v = c2i( str[n] );
			else if( n == 1 )
				v = 10*c2i(str[n-1]) + c2i(str[n]);
			else if( n == 2 )
				v = 100*c2i(str[n-2]) + 10*c2i(str[n-1]) + c2i(str[n]);
			else
				v = 1000*c2i(str[n-3]) + 100*c2i(str[n-2]) + 10*c2i(str[n-1]) + c2i(str[n]);
			
			c._values.push_back( v );
			n -= 3;
		}
	}

	c.EraseHighZero();
}

void CStringInt::FromInt( CStringInt &c, int v )
{
	c._values.clear();

	if( v == 0 )
	{
		c._values.clear();
		c.SetValue( 0, 0 );
		return;
	}

	if( v < 0 )
	{
		c._sign = 1;
		v = -v;
	}

	while( v > 0 )
	{
		c._values.push_back( v % c.HEX );
		v /= c.HEX;
	}
}

void CStringInt::Random( int nSize )
{
	_values.clear();
	for( int i = 0; i < nSize; i++ )
	{
		u32		v = rand() % HEX;

		if( i == 0 )
		{
			while( v % 2 == 0 || v % 5 == 0 )
				v = rand() % HEX;
		}

		_values.push_back( v );
	}

	EraseHighZero();
}

void CStringInt::FormatValue()
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

void CStringInt::EraseHighZero()
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

CStringInt& CStringInt::operator = ( int i )
{
	FromInt( *this, i );
	return *this;
}

CStringInt& CStringInt::operator = ( string str )
{
	if( str.empty() )
		return *this;

	if( str[0] == '-' )
	{
		_sign = 1;
		str.erase( 0 );
	}

	////rev( str, _values, false );
	//size_t		n = str.size();
	//while( n-- )
	//	_values.push_back( str[n] - '0' );
	FromString( *this, str );
	return *this;
}

CStringInt& CStringInt::operator = ( const CStringInt &rhs )
{
	_values.clear();

	_sign = rhs._sign;
	HEX = rhs.HEX;
	
	size_t		n = rhs._values.size();
	for( size_t i = 0; i < n; i++ )
		_values.push_back( rhs._values[i] );

	return *this;
}

double CStringInt::toDouble() const
{
	int		n = (int)GetSize();
	if( n > 307 )
		return 0;

	string	str;
	for( int i = 0; i < 10; i++ )
	{
		int		v = GetValue( n-1-i );
		str.push_back( i2c( v ) );

		if( i == 0 )
			str.push_back( '.' );
	}

	str += "e";

	char buf[8] = {0};
	sprintf( buf, "%d", n-1 );
	
	str += buf;
	return atof( str.c_str() );
}


string CStringInt::toString( int bShowZero ) const
{
	string		str;
	//rev( _values, str, true );
	size_t		n = _values.size();
//	while( n-- )
//		str.push_back( (u8)(_values[n]&0xff) + '0' );

	if( 0 == n )
		return "0";

	if( 1 == n && _values[0] == 0 )
		return "0";
	
	while( n-- )
	{
		int		v = _values[n];
		if( 10 == HEX )
			str.push_back( i2c(v) );
		else if( 100 == HEX )
		{
			str.push_back( i2c(v/10) );
			str.push_back( i2c(v%10) );
		}
		else if( 1000 == HEX )
		{
			str.push_back( i2c(v/100) );
			str.push_back( i2c(v/10%10) );
			str.push_back( i2c(v%10) );
		}
		else if( 10000 == HEX )
		{
			str.push_back( i2c(v/1000) );
			str.push_back( i2c(v/100%10) );
			str.push_back( i2c(v/10%10) );
			str.push_back( i2c(v%10) );			
		}
	}

	if( !bShowZero )
	{
		while( str[0] == '0' )
			str.erase( 0, 1 );
	}

	if( _sign )
		str.insert( str.begin(), '-' );

	return str;
}

u32 CStringInt::GetValue( size_t i ) const
{
	size_t		n = _values.size();
	if( i >= n )
		return 0;

	return _values[i];
}

u32 CStringInt::GetValue_Highest() const
{
	size_t		n = _values.size();
	if( 0 == n )
		return 0;

	return _values[n-1];
}

void CStringInt::SetValue( size_t i, u32 v, bool bAutoFormat )
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

void CStringInt::AddValue( size_t i, u32 v, bool bAutoFormat )
{
	int		v0 = GetValue( i );
	SetValue( i, v0 + v, bAutoFormat );
}

CStringInt CStringInt::operator + ( CStringInt a )
{
	CStringInt		c;
	Add_Unsign( *this, a, c );
	return c;
}

CStringInt CStringInt::operator - ( CStringInt a )
{
	CStringInt		c;
	Sub_Unsign( *this, a, c );
	return c;
}

CStringInt CStringInt::operator * ( CStringInt a )
{
	CStringInt		c;
	Mul_Unsign( *this, a, c );
	return c;
}

CStringInt CStringInt::operator * ( int v )
{
	CStringInt		b = v;

	CStringInt		c;
	Mul_Unsign( *this, b, c );
	return c;
}

CStringInt CStringInt::operator * ( int v ) const
{
	CStringInt		b = v;

	CStringInt		c;
	Mul_Unsign( *this, b, c );
	return c;
}

CStringInt CStringInt::operator / ( CStringInt b )
{
//	string		sa( "3162715073" );
//	string		sb( "9834" );
	CStringInt	a = *this;

	if( a < b )
		return 0;

	vector< u32 >		av;
	CStringInt		t = 0;

	size_t		nL = a.GetSize();
	size_t		n = b.GetSize();

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
	
	CStringInt		c;
	nL = av.size();
	for( i = (int)nL-1; i > -1 ; i-- )
		c._values.push_back( av[i] );

	c.EraseHighZero();

	//cout << a.toString() << " / " << b.toString() << " = " << c.toString() << endl;


	////CStringInt		c, d;
	////DivMod( *this, a, c, d );
	////return c;

	//CStringInt		c = 0;
	//CStringInt		t = *this;

	//while( t >= b )
	//{
	//	c++;
	//	t = t - b;
	//}

	//CStringInt	a = *this;

	////CStringInt	tmp, mod, res;
	//CStringInt	mod, res;

	//int		i;
	//int		lf, rg, mid;

	//mod = 0;
	//for( i = a.GetSize() - 1; i >= 0; i--) 
	//{
	//	//mod = mod * base + a.GetValue( i );
	//	mod = mod * HEX + a.GetValue( i );
	//	for (lf = 0, rg = HEX -1; lf < rg; ) 
	//	{
	//		mid = (lf + rg + 1) / 2;
	//		if( b * mid <= mod ) 
	//			lf = mid;
	//		else 
	//			rg = mid - 1;
	//	}
	//	
	//	//res.v[i] = lf;
	//	res.SetValue( i, lf );
	//	mod = mod - b * lf;
	//}

	////res.ln = a.ln;
	////while (res.ln > 0 && res.v[res.ln - 1] == 0) 
	////	res.ln--;
	//res.EraseHighZero();
	//return res; // return mod 就是%运算

	return c;
}

CStringInt CStringInt::operator % ( CStringInt a )
{
	CStringInt		c;
	//CStringInt		c, d;
	//DivMod( *this, a, c, d );
	Mod_Unsign( *this, a, c );
	return c;
}


CStringInt& CStringInt::operator ++()
{
	AddValue( 0, 1, true );
	return *this;
}

const CStringInt CStringInt::operator ++( int )
{
	AddValue( 0, 1, true );
	return *this;
}

CStringInt& CStringInt::operator --()
{
	AddValue( 0, -1, true );
	return *this;
}

const CStringInt CStringInt::operator --( int )
{
	AddValue( 0, -1, true );
	return *this;
}

// static 
int CStringInt::Compare_Unsign( const CStringInt &a, const CStringInt &b )
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

bool CStringInt::operator > ( const CStringInt &a ) const
{
	if( Compare_Unsign( *this, a ) == 1 )
		return true;

	return false;
}

bool CStringInt::operator < ( const CStringInt &a ) const
{
	if( Compare_Unsign( *this, a ) == -1 )
		return true;

	return false;
}

bool CStringInt::operator != ( const CStringInt &a ) const
{
	if( Compare_Unsign( *this, a ) != 0 )
		return true;

	return false;
}

bool CStringInt::operator == ( const CStringInt &a ) const
{
	if( Compare_Unsign( *this, a ) == 0 )
		return true;

	return false;
}

bool CStringInt::operator >= ( const CStringInt &a ) const
{
	if( Compare_Unsign( *this, a ) >= 0 )
		return true;

	return false;
}

bool CStringInt::operator <= ( const CStringInt &a ) const
{
	if( Compare_Unsign( *this, a ) <= 0 )
		return true;

	return false;

}

// +
// static 
void CStringInt::Add_Unsign( const CStringInt &a, const CStringInt &b, CStringInt &c )
{
	c = 0;

	size_t	nL = a._values.size();
	size_t  nR = b._values.size();

	size_t	i;
	size_t	n = MAX( nL, nR );

	int		temp = 0;
	for( i = 0; i < n; i++ )
	{
		u32  v = a.GetValue(i) + b.GetValue(i) + temp;

		if( v >= c.HEX )
		{
			temp = 1;
			v %= c.HEX;
		}
		else
			temp = 0;

		c.SetValue( i, v );
	}

	if( temp != 0 )
		c.SetValue( n, temp );
}

// -
// static 
void CStringInt::Sub_Unsign( const CStringInt &a, const CStringInt &b, CStringInt &c )
{
	c = 0;

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
			v += c.HEX;
		}
		else
			nFlag = 0;
		
		c.SetValue( i, v );
	}

	c.EraseHighZero();
}

// *
// static 
void CStringInt::Mul_Unsign( const CStringInt &a, const CStringInt &b, CStringInt &c )
{
	c = 0;

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
}

// *
// static 
// 提速
void CStringInt::Mul_Unsign2( const CStringInt &a, const CStringInt &b, CStringInt &c )
{
	c = 0;

	size_t	nL = a._values.size();
	size_t  nR = b._values.size();

	size_t	i, j;

	for( i = 0; i < nL; i++ )
	{
		int		v1 = a.GetValue(i);
		for( j = 0; j < nR; j++ )
		{
			int		v2 = b.GetValue(j);	
			c.AddValue( i+j, v1*v2, false );
		}
	}

	c.FormatValue();
}

void CStringInt::CopyTo( const CStringInt &a, size_t nFrom, size_t nTo, CStringInt &c )
{
	c = 0;

	size_t		i;
	for( i = nFrom; i < nTo; i++ )
	{
		c._values.push_back( a._values[i] );
	}
}

void CStringInt::Append( CStringInt &a, const CStringInt &b )
{
	size_t		n = b._values.size();
	for( size_t i = 0; i < n; i++ )
		a._values.push_back( b._values[i] );
}

//int CStringInt::Compare_HighPart( const CStringInt &a, const CStringInt &b )
//{
//	size_t		n1 = a._values.size();
//	size_t		n2 = b._values.size();
//	if( n1 < n2 )
//		return -1;
//
//	for( size_t i = 0; i < n2; i++ )
//	{
//		u32	v1 = a.GetValue( n1-1 - i );
//		u32	v2 = b.GetValue( n2-1 - i );
//		if( v1 > v2 )
//			return 1;
//		
//		if( v1 < v2 )
//			return -1;
//	}
//
//	return 0;
//}

//void CStringInt::Sub_HighPart( CStringInt &a, const CStringInt &b, CStringInt &c )
//{
//	c = 0;
//
//	size_t	nL = a._values.size();
//	size_t  nR = b._values.size();
//
//	size_t	n = min( nL, nR );
//
//	size_t	i;
//
//	int		nFlag = 0;
//	for( i = 0; i < n; i++ )
//	{
//		int		v1 = a.GetValue(nL-n+i);
//		int		v2 = b.GetValue(nR-n+i);
//
//		if( nFlag )
//			v1--;
//
//		int		v = v1 - v2;
//		if( v < 0 )
//		{
//			nFlag = 1;
//			v += c.HEX;
//		}
//		else
//			nFlag = 0;
//		
//		c.SetValue( i, v );
//	}
//
//	c.EraseHighZero();
//}
//
//void CStringInt::Sub_HighPart2( CStringInt &a, const CStringInt &b )
//{
//	size_t	nL = a._values.size();
//	size_t  nR = b._values.size();
//
//	size_t	i;
//
//	int		nFlag = 0;
//	for( i = 0; i < nR; i++ )
//	{
//		int		v1 = a.GetValue(nL-nR+i);
//		int		v2 = b.GetValue(i);
//
//		if( nFlag )
//			v1--;
//
//		int		v = v1 - v2;
//		if( v < 0 )
//		{
//			nFlag = 1;
//			v += a.HEX;
//		}
//		else
//			nFlag = 0;
//
//		a.SetValue( nL-nR+i, v );
//	}
//
//	a.EraseHighZero();
//}

bool CStringInt::GetHighPart( const CStringInt &a, size_t nSize, CStringInt &b )
{
	b = 0;
	
	size_t	n = a.GetSize();
	if( n < nSize )
		return false;

	for( size_t i = 0; i < nSize; i++ )
	{
		u32	v = a.GetValue( n - nSize + i );
		b.SetValue( i, v );
	}

	return true;
}

CStringInt CStringInt::GetPart( const CStringInt &a, size_t nStart, size_t nSize )
{
	CStringInt b = 0;

	size_t		n = a.GetSize();
	if( nStart + nSize > n )
		nSize = n - nStart;

	for( size_t i = 0; i < nSize; i++ )
	{
		int v = a.GetValue( nStart+i );
		b.SetValue( i, v );
	}

	return b;
}

CStringInt CStringInt::Get10pow( size_t n )
{
	CStringInt	b = 0;

	for( size_t i = 0; i < n; i++ )
		b.SetValue( i, 0 );
	
	b.SetValue( n, 1 );
	return b;
}

CStringInt CStringInt::Get10powMod( const CStringInt &a, int n )
{
	if( n == 0 )
		return 1;

	CStringInt	b = 0;	
	if( n == 1 )
	{
		size_t		size = a.GetSize();
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


// a / b = c mod d
void CStringInt::DivMod( const CStringInt &a, CStringInt b, CStringInt &c, CStringInt &d )
{
	// 0除
	if( b == 0 )
		return;

	if( a < b )
	{
		c = 0;
		d = a;
		return;
	}

	vector< u32 >	av;

	CStringInt		aa = a;
	CStringInt		t = 0;
	CStringInt		t2 = 0;
	u32			v = -1;
	
	size_t		nn = b.GetSize();
	u32		v2 = b.GetValue_Highest();		

	while( aa > b )
	{
		size_t	nBak = nn;
		t = 0;
		
		size_t	n1 = aa.GetSize();
		if( n1 < nn )
		{
			av.push_back( 0 );
			t = aa;
			break;
		}

		if( !GetHighPart( aa, nn, t ) )
		{
			av.push_back( 0 );
			t = aa;
			break;
		}

		int		nRet = Compare_Unsign( t, b );
		if( 0 == nRet )
		{
			v = 1;
			t2 = b;
			t = 0;
		}
		else if( -1 == nRet )
		{
			v = 0;
			t2 = 0;
			nn++;
		}
		else
		{
			u32 v1 = t.GetValue_Highest();
			if( nn > b.GetSize() && nn >= 2 )
				v1 = t.GetValue( nn-1 ) * t.HEX + t.GetValue( nn-2 );

			if( v1 < v2 )
			{
				v = 0;
				t2 = 0;
				nn++;
			}
			else
			{
				v = v1 / v2;
				
				t2 = b * v;
				while( t2 > t )
				{
					v--;
					t2 = t2 - b;
				}

				t = t - t2;
				nn = t.GetSize()+1;
			}
		}

		av.push_back( v );
		PlaceHighPart( aa, t, nBak );
	}

	if( aa.GetSize() == b.GetSize() )
	{
		av.push_back( 0 );
		d = aa;
	}
	else
		d = t;

	size_t	n = av.size();
	for( size_t i = 0; i < n; i++ )
		c.SetValue( i, av[n-1-i] );

	c.EraseHighZero();
}

void CStringInt::PlaceHighPart( CStringInt &a, const CStringInt &b, size_t nSize )
{
	size_t	n1 = a.GetSize();
	size_t	n2 = b.GetSize();
	
	for( size_t i = 0; i < nSize; i++ )
	{
		u32	v = b.GetValue( i );
		a.SetValue( n1- nSize + i, v );
	}

	a.EraseHighZero();
}


// /
// static 
void CStringInt::Div_Unsign( const CStringInt &a, CStringInt &b, CStringInt &c )
{
	//if( a < b )
	//{
	//	c = 0;
	//	return;
	//}

	//vector< u32 >	v;
	//
	//size_t n1 = a._values.size();
	//size_t n2 = b._values.size();

	//CStringInt		t;
	//CStringInt		d;

	//size_t	i;
	//size_t	n = n1 - n2;
	//for( i = 0; i < n; i++ )
	//{
	//	CopyTo( a, n1-i-n2, n1-i, t );
	//	Append( t, d );

	//	u32		vv;
	//	DivMod_SameLength( t, b, vv, d );

	//	v.push_back( vv );
	//}
	
	//c = vv;
}

// static
void CStringInt::Mod_Unsign( const CStringInt &a, const CStringInt &b, CStringInt &c )
{
	c = 0;
	if( a < b )
	{
		c = a;
		return;
	}

	size_t	nL = a.GetSize();
	size_t	nR = b.GetSize();

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

		CStringInt		nPart;
		CStringInt		n10pow;

		CStringInt		t = 1;

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

	//cout << a.toString() << " % " << b.toString() << " = " << c.toString() << endl;
}

void CStringInt::Pow( const CStringInt &a, const CStringInt &b, CStringInt &c )
{

}

void CStringInt::Factorial( int a, CStringInt &c )
{
	c = a;
	while( --a )
	{
		CStringInt	t = c;

		string		str = t.toString();
		Mul_Unsign( t, a, c );
	}
}

void CStringInt::Factorial2( int a, CStringInt &c )
{
	c = a;
	while( --a )
	{
		CStringInt	t = c;

		//string		str = t.toString();
		CStringInt	t2;
		t2.HEX = t.HEX;
		FromInt( t2, a );

		Mul_Unsign2( t, t2, c );
	}
}

// X^Y可以看作Y个X相乘，即然有积模分解公式，
//那么我们就可以把Y个X相乘再取模的过程分解开来，
// 比如：(17^25)%29则可分解为：( ( 17 * 17 ) % 29 * ( 17 * 17 ) % 29 * ……
// 如果用上面的代码将这个过程优化，那么我们就得到了著名的“蒙格马利”快速幂模算法：
CStringInt CStringInt::Montgomery( CStringInt &n, CStringInt &p, CStringInt &m )
{
	// ( n ^ p ) % m
	CStringInt	k = 1;
	p = p % m;

	while( p != 1 )
	{
		if( !p.IsDoubleNumber() )
			k = ( n*k ) % m;

		CStringInt	t = (n*n) % m;
		//printf( "p = %s, k = %s, t = %s\n", p.toString().c_str(), k.toString().c_str(), t.toString().c_str() );

		n = t;
		p.Half();
	}

	return ( n*k ) % m;
}

bool CStringInt::IsPrime()
{
	int		i;
	//for( i = 0; i < 500; i++ )
	//{
	//	if( *this == i )
	//		return true;
	//}

	for( i = 0; i < 500; i++ )
	{
		int		v = sau_prime500[i];
		if( *this % v == 0 )
			return false;
	}
	
	//int		max = (int)sqrt( (double)n );
	//for( i = 1009; i <= max; i++ )
	//	if( n % i == 0 )
	//		return false;

	return true;
}

bool CStringInt::Is235Number()
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

bool CStringInt::IsDoubleNumber()
{
	if( _values.empty() )
		return true;

	u32	v = GetValue( 0 );
	return 0 == v%2;
}

void CStringInt::Half()
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

bool CStringInt::TestPrime500( CStringInt a )
{
	// 2/3/5倍数
	if( a.Is235Number() )
		return false;

	int		N = 500;

	int		i;
	for( i = 3; i < N; i++ )
	{
		CStringInt		t = sau_prime500[i];
	
		//if( t == a )
		//	return true;

		if( a % t == 0 )
			return false;
	}

	return true;
}

bool CStringInt::TestPrime( CStringInt a, const vector< CStringInt > &ap, int n )
{
	// 2/3/5倍数
	if( a.Is235Number() )
		return false;

	int		nRootSize = (int)sqrt( float(a.GetSize()) ) + 1; 
	if( n == -1 )
		n = (int)ap.size();
	
	for( int i = 1; i < n; i++ )
	{
		CStringInt b = ap[i];
		
		if( (int)b.GetSize() > nRootSize )
			return true;

		if( a % b == 0 )
			return false;
	}
	
	return true;
}

bool CStringInt::TestPrime_Range( CStringInt a, const vector< CStringInt > &ap, int i, int n )
{
	// 2/3/5倍数
	if( a.Is235Number() )
		return false;
	
	for( int j = 1; j < n; j++ )
	{
		CStringInt b = ap[i+j];
		if( a % b == 0 )
			return false;
	}
	
	return true;
}

void CStringInt::NextPrime( CStringInt &a, const vector< CStringInt > &ap )
{
	if( a.IsDoubleNumber() )
	{
		a++;
		if( TestPrime( a, ap ) )
			return;
	}


	while( 1 )
	{
		a = a + 2;
		if( TestPrime( a, ap ) )
			return;
	}
}

CStringInt CStringInt::GetFixSizePrime_Speed( size_t size )
{
	//vector< CStringInt > ap;
	CStringInt::APreadFromTxt( _sap );
	//tc.ShowTime();

	CStringInt		a;
	while( 1 )
	{
		a.Random( (int)size );
		//if( TestPrime500( a ) )
			//return a;

		if( TestPrime_Range( a, _sap, 0, 10000 ) )
			return a;
	}
}

void CStringInt::GetFixSizePrime( CStringInt &a, size_t size )
{
	ofstream		f( "1.txt" );

	vector< CStringInt > ap;

	int		N = 500;

	int		i;
	for( i = 0; i < N; i++ )
	{
		ap.push_back( (CStringInt)sau_prime500[i] );
		//fprintf( f, "%s,", ap[i].toString().c_str() );
		f << ap[i];
	}

	CStringInt		t = ap[N-1];

	a.Random( (int)size );
	//getchar();
	cout << "500 ok!"<<endl;

	i = 0;
	while( t * t  < a )
	{
		NextPrime( t, ap );
		ap.push_back( t );
		
		i++;
		if( i % 20 == 0 )
			printf( "%s ", t.toString().c_str() );
		f << t;
	}

	//fclose( f );

	printf( "\n%d\n", ap.size() );
	printf( "\n***%s\n", a.toString().c_str() );
	NextPrime( a, ap );
	printf( "--->%s\n", a.toString().c_str() );
}

CStringInt CStringInt::Sqrt( const CStringInt &a )
{
	double	d = a.toDouble();
	d = sqrt( d );

	char	buf[32] = {0};
	sprintf( buf, "%e", d );

	string	str = buf;
	int		npos = (int)str.find( 'e' );

	if( -1 == npos )
		return 0;

	CStringInt	b;
	for( int i = 0; i < npos; i++ )
	{
		char  c = str[i];
		if( c != '.' )
			b._values.insert( b._values.begin(), c2i(c) );
			//b._values.push_back( c2i(c) );
	}

	string		strSize = str.substr( npos+1, str.size() - npos-1 );
	int		nSize = atoi( strSize.c_str() );

	int		i = (int)b.GetSize();
	//b.AddValue( 0, 1, true );

	for( ; i < nSize+1; i++ )
		b._values.insert( b._values.begin(), 0 );

	return b;
}

CStringInt CStringInt::Sqrt_NT( CStringInt a, int n )
{
	CStringInt		x = Sqrt( a );
	while( n-- > 0 )
	{
		x = x + a / x;
		x.Half();

		cout << n << ": "<< x*x - a << endl;
	}

	return x;
}
