#pragma once

class CStringInt
{
public:
	CStringInt();
	CStringInt( int v );
	CStringInt( string str );
	~CStringInt(void);

	// 0: >=0
	// 1: < 0
	int			_sign;

	// 10, 100, 1000
	u32		HEX;
	
	//	123456789
	// [0]: 9, [1]: 8 ... [9]: 1
	vector< u32 >		_values;

public:
	string		toString( int bShowZero = 0 ) const;
	double		toDouble() const;

	CStringInt&	operator = ( string str );
	CStringInt& operator = ( int v );
	CStringInt& operator = ( const CStringInt &rhs );

	bool	operator != ( const CStringInt &a ) const;
	bool	operator == ( const CStringInt &a ) const;
	bool	operator > ( const CStringInt &a ) const;
	bool	operator < ( const CStringInt &a ) const;
	bool	operator >= ( const CStringInt &a ) const;
	bool	operator <= ( const CStringInt &a ) const;

	CStringInt	operator + ( CStringInt a );
	CStringInt	operator - ( CStringInt a );
	CStringInt	operator * ( CStringInt a );
	CStringInt	operator / ( CStringInt a );
	CStringInt	operator % ( CStringInt a );

	CStringInt	operator * ( int v );
	CStringInt	operator * ( int v ) const;


	bool		IsDoubleNumber();
	void		Half();

	bool		Is235Number();

	// prefix ++
	CStringInt&	operator ++();
	
	// postfix ++
	const CStringInt operator ++( int );

	CStringInt&	operator --();
	const CStringInt operator --( int );

	u32		GetValue( size_t i ) const;
	void		SetValue( size_t i, u32 v, bool bAutoFormat = false );
	void		AddValue( size_t i, u32 v, bool bAutoFormat = false );

	u32		GetValue_Highest() const;

	inline 
	size_t		GetSize() const { return _values.size(); }

	void		FormatValue();
	void		EraseHighZero();

	static void		FromString( CStringInt &c, string str );
	static void		FromInt( CStringInt &c, int v );

	void		Random( int nSize );
	bool		IsPrime();


	// return value
	//  1: a > b
	//  0: a = b
	// -1: a < b
	static int		Compare_Unsign( const CStringInt &a, const CStringInt &b );

	// +
	static void		Add_Unsign( const CStringInt &a, const CStringInt &b, CStringInt &c );
	// -
	static void		Sub_Unsign( const CStringInt &a, const CStringInt &b, CStringInt &c );
	// *
	static void		Mul_Unsign( const CStringInt &a, const CStringInt &b, CStringInt &c );
	// *
	static void		Mul_Unsign2( const CStringInt &a, const CStringInt &b, CStringInt &c );
	// /
	static void		Div_Unsign( const CStringInt &a, CStringInt &b, CStringInt &c );
	// %
	static void		Mod_Unsign( const CStringInt &a, const CStringInt &b, CStringInt &c );

	// a / b = c 余 d
	static void		DivMod( const CStringInt &a, CStringInt b, CStringInt &c, CStringInt &d );

	static void		Pow( const CStringInt &a, const CStringInt &b, CStringInt &c );

	static void		Factorial( int a, CStringInt &c );
	static void		Factorial2( int a, CStringInt &c );

	//	(d ^ e) % n;
	static CStringInt	Montgomery( CStringInt &d, CStringInt &e, CStringInt &n );

private:
	static void		CopyTo( const CStringInt &a, size_t nFrom, size_t nTo, CStringInt &c );
	static void		Append( CStringInt &a, const CStringInt &b );

	// 1  >
	// 0  =
	// -1 <
	// example:	
	// 1232424   1234:  -1
	// 3434267	 340:    1
	// 94834	 94:     0
	//static int		Compare_HighPart( const CStringInt &a, const CStringInt &b );
	//static void		Sub_HighPart( CStringInt &a, const CStringInt &b, CStringInt &c );
	//static void		Sub_HighPart2( CStringInt &a, const CStringInt &b );
	
	static bool		GetHighPart( const CStringInt &a, size_t nSize, CStringInt &b );
	static void		PlaceHighPart( CStringInt &a, const CStringInt &b, size_t nSize );

	static CStringInt	GetPart( const CStringInt &a, size_t nStart, size_t nSize );
	static CStringInt	Get10pow( size_t n );

	//	pow( 10, (len(a)+1 )*n ) % a; 
	static CStringInt	Get10powMod( const CStringInt &a, int n );

public:
	static void			GetFixSizePrime( CStringInt &a, size_t size );
	static CStringInt	GetFixSizePrime_Speed( size_t size );
	
	static void			NextPrime( CStringInt &a, const vector< CStringInt > &ap );
	static bool			TestPrime( CStringInt a, const vector< CStringInt > &ap, int n = -1 );
	static bool			TestPrime_Range( CStringInt a, const vector< CStringInt > &ap, int i, int n );

	static bool			TestPrime500( CStringInt a );

	static CStringInt	Sqrt( const CStringInt &a );

	static CStringInt	Sqrt_NT( CStringInt a, int n = 6 );


	static void			Get3Prime( CStringInt &a, CStringInt &b, CStringInt &c )
	{
		//a = 101;
		//b = 79;
		//c = 23;
		//a = 2083;
		//b = 3571;
		//c = 1571;

		//a = "1073195733138323";
		//b = "888897044557883";

		////           10        20        30     
		////   1234567890123456789012345678901
		//a = "1094575053967366365144802264571";
		//b = "874241434730398266616207700387";
		//c = "65537";

		a = GetFixSizePrime_Speed( 19 );
		b = GetFixSizePrime_Speed( 19 );
		c = GetFixSizePrime_Speed( 11 );
		//c = "65537";

		//vector< CStringInt > ap;
		//APreadFromTxt( ap );
		//cout << (TestPrime_Range( a, ap, 0, 2000 )?"": "no! ");
		//cout << (TestPrime_Range( b, ap, 0, 2000 )?"": "no! ");
	}

	// 辗转相除，求e
	// gcd( d*e, n ) = 1;
	// e*x - n*y = 1;

	// 求x
	// a*x - b*y = 1;
	static CStringInt		zzxc( CStringInt a, CStringInt b )
	{
		//if( b == 1 )
		//	return a-b;
		//
		//if( a > b )
		//	return ( a*zzxc( a%b, b ) - 1 ) / b;
		//else
		//	return ( b*zzxc( a, b%a ) + 1 ) / a;

		//cout << a << ' ' << b << endl;

		CStringInt		t = 0;
		if( b == 1 )
			t = a-b;
		else if( a == 1 )
		{
			t = b+1;
			//cout << "ERROR!" << endl;
		}
		else
		{
			if( a > b )
				t = ( a*zzxc( a%b, b ) - 1 ) / b;
			else
				t = ( b*zzxc( a, b%a ) + 1 ) / a;
		}

		////printf( "%s %s = %s\n", a.toString().c_str(), 
		////						b.toString().c_str(), 
		////						t.toString().c_str() );
		//cout << a << "zz" << b << " = " << t << endl;
		return t;
	}

	// ( n ^ p ) % m
	// 快速计算 (n ^ p) % m 的值
	//	蒙格马利”快速幂模算法
	static CStringInt		Montgomery2( CStringInt n, CStringInt p, CStringInt m )
	{
		CStringInt	k = 1;
		p = p % m;

		while( p != 1 )
		{
			//if( 0 != ( p&1 ) )
			if( !p.IsDoubleNumber() )
				k = ( n*k ) % m;

			n = (n*n) % m;
			//p = p/2;
			p.Half();
		}

		return ( n*k ) % m;
	}

	static void APreadFromTxt( vector< CStringInt > &ap )
	{
		if( !ap.empty() )
			return;

		ifstream		f( "1.txt" );

		for( int i = 0; i < 10000; i++ )
		{
			//if( i % 10 == 0 )
			//	cout << endl << (i/10) << '.';
		
			CStringInt		v;
			f >> v;
			//cout << v;
			ap.push_back( v );
		}
		
		//cout << "n = " << ap.size() << endl;
	}


	friend ostream& operator <<( ostream &f, CStringInt &a );
	friend istream& operator >>( istream &f, CStringInt &a );


	static vector< CStringInt > _sap;
};
