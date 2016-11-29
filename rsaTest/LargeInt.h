#pragma once

class CLargeInt
{
public:
	CLargeInt(void);
	CLargeInt( int v );
	CLargeInt( string str );

	~CLargeInt(void);


	// 0: >=0
	// 1: < 0
	int			_sign;

	//	123456789
	// [0]: 9, [1]: 8 ... [9]: 1
	vector< u32 >		_values;


public:
	inline size_t size() const { return _values.size(); }
	u32		bitSize();

	u32		GetValue( size_t i ) const;
	void		SetValue( size_t i, u32 v, bool bAutoFormat = false );
	void		AddValue( size_t i, u32 v, bool bAutoFormat = false );

	void		Random( int nSize, bool bFilter = false );
	void		Half();
	bool		IsEven();
	bool		Is235Time();

	static CLargeInt	GetFixSizePrime_Speed( size_t size, int nMethod = 0 );


	// 欧几里德 辗转相除法
	// a*x - b*y = 1;
	// 求x
	static CLargeInt	Euclidean( CLargeInt a, CLargeInt b );

	// 蒙格马利 快速幂模算法
	// 快速计算 (n ^ p) % m
	static CLargeInt	Montgomery( CLargeInt n, CLargeInt p, CLargeInt m );

private:
	void		FormatValue();
	void		EraseHighZero();

public:
	//	operator
	CLargeInt& operator = ( string str );
	CLargeInt& operator = ( int v );

	bool	operator != ( const CLargeInt &a ) const;
	bool	operator == ( const CLargeInt &a ) const;
	bool	operator > ( const CLargeInt &a ) const;
	bool	operator < ( const CLargeInt &a ) const;
	bool	operator >= ( const CLargeInt &a ) const;
	bool	operator <= ( const CLargeInt &a ) const;

	CLargeInt	operator + ( CLargeInt a );
	CLargeInt	operator - ( CLargeInt a );
	CLargeInt	operator * ( CLargeInt a );
	CLargeInt	operator / ( CLargeInt a );
	CLargeInt	operator % ( CLargeInt a );

	CLargeInt	operator += ( CLargeInt a );
	CLargeInt	operator -= ( CLargeInt a );
	CLargeInt	operator *= ( CLargeInt a );
	CLargeInt	operator /= ( CLargeInt a );
	CLargeInt	operator %= ( CLargeInt a );

	// prefix ++
	CLargeInt&	operator ++();
	CLargeInt&	operator --();

	// postfix ++
	const CLargeInt operator ++( int );
	const CLargeInt operator --( int );

public:
	static CLargeInt	FromString( string str );
	static CLargeInt	FromInt( int v );

	// a > b return 1
	// a = b return 0
	// a < b return -1
	static int			Com_U( const CLargeInt &a, const CLargeInt &b );

	// + - * / %
	static CLargeInt	Add_U( const CLargeInt &a, const CLargeInt &b );
	static CLargeInt 	Sub_U( const CLargeInt &a, const CLargeInt &b );
	static CLargeInt 	Mul_U( const CLargeInt &a, const CLargeInt &b );
	static CLargeInt 	Div_U( const CLargeInt &a, const CLargeInt &b );
	static CLargeInt 	Mod_U( const CLargeInt &a, const CLargeInt &b );

private:
	//	pow( 10, (len(a)+1 )*n ) % a; 
	static CLargeInt	Get10powMod( const CLargeInt &a, int n );	
	static CLargeInt	GetPart( const CLargeInt &a, size_t nStart, size_t nSize );


friend ostream& operator <<( ostream &f, CLargeInt &a );
friend istream& operator >>( istream &f, CLargeInt &a );

	static bool TestPrime_Range( CLargeInt a, const vector< CLargeInt > &ap, int i, int n )
	{
		// 2/3/5倍数
		if( a.Is235Time() )
			return false;
		
		for( int j = 1; j < n; j++ )
		{
			CLargeInt b = ap[i+j];
			if( a % b == 0 )
				return false;
		}
		
		return true;	
	}

public:
	static CLargeInt	gcd( CLargeInt a, CLargeInt b )
	{
		if( a == 0 )
			return b;

		while( b != 0 )
		{
			if( a > b )
				a %= b;
			else
				b %= a;
		}

		return a;
	}

	static bool TestPrime_MillerRabin( CLargeInt n, const vector< CLargeInt > &ap )
	{
		// 2/3/5倍数
		if( n.Is235Time() )
			return false;

		// 找到k和q, n = 2^k * q + 1;
	    int			k = 0;
		CLargeInt	q = n - 1;
		//while( 0 == ( q & 1 ) )
		while( q.IsEven() )
		{
			//q >>= 1;
			q.Half();
			k++;
		}

		for( int i = 0; i < 5; i++ )
		{
			CLargeInt	d = ap[i];
		
			//R_M_Help( d, k, q, n )
			if ( Montgomery( d, q, n ) != 1 )
			{
				int e = 1;
				for ( int j = 0; j < k; j++ )
				{
					if ( n - 1 == Montgomery( d, q * e, n ) ) 
						return false;
		           
					e <<= 1;
				}
			}
		}

		return true;
	}

	static void APreadFromTxt( vector< CLargeInt > &ap )
	{
		if( !ap.empty() )
			return;

		ifstream		f( "1.txt" );

		for( int i = 0; i < 10000; i++ )
		{		
			CLargeInt		v;
			f >> v;
			ap.push_back( v );
		}
	}

	//static bool MillerRabin( CLargeInt a, int k )
	//{
	//	// 2/3/5倍数
	//	if( a.Is235Time() )
	//		return false;

	//	while( k-- > 0 )
	//		if( Witness( random( n-3 ) + 2, n ) )
	//			return false;

	//	return true;
	//}

	static vector< CLargeInt > _sap;
};
