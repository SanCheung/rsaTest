#pragma once

/*

	u32 a = 0xffff;
	u32 b = 0xffff;
	u32 c = a * b;
	printf( "%u * %u = %u\n", a, b, c );

	u64 x = 0xffffFFFF;
	u64 y = 0xffffFFFF;
	u64 z = x * y;
	printf( "%I64u * %I64u = %I64u\n", x, y, z );

	
	输出结果：
	65535 * 65535 = 4294836225
	4294967295 * 4294967295 = 18446744065119617025
//*/

// 如果使用 2^32进制的话，__int64涉及到的n条指令
// int32仅需要1行指令即可实现运算

// 使用 10000 进制的超大数存储方式
// 如果使用 2^16 (65536） 进制的话，转换成字符串会非常麻烦。

class CHugeInt
{
public:
	CHugeInt(void);
	CHugeInt( int v );
	CHugeInt( string str );

	virtual ~CHugeInt(void);

public:
	static CHugeInt	FromString( string str );
	static CHugeInt	FromInt( int v );

	string toString();

	inline 
	size_t	size() const { return _values.size(); }
	u32		GetValue( size_t i ) const;
	void	SetValue( size_t i, u32 v, bool bAutoFormat = false );
	void	AddValue( size_t i, u32 v, bool bAutoFormat = false );

public:
	//	operator
	CHugeInt& operator = ( string str );
	CHugeInt& operator = ( int v );

	bool	operator != ( const CHugeInt &a ) const;
	bool	operator == ( const CHugeInt &a ) const;
	bool	operator >  ( const CHugeInt &a ) const;
	bool	operator <  ( const CHugeInt &a ) const;
	bool	operator >= ( const CHugeInt &a ) const;
	bool	operator <= ( const CHugeInt &a ) const;

	CHugeInt	operator + ( CHugeInt a );
	CHugeInt	operator - ( CHugeInt a );
	CHugeInt	operator * ( CHugeInt a );
	CHugeInt	operator / ( CHugeInt a );
	CHugeInt	operator % ( CHugeInt a );

	CHugeInt	operator += ( CHugeInt a );
	CHugeInt	operator -= ( CHugeInt a );
	CHugeInt	operator *= ( CHugeInt a );
	CHugeInt	operator /= ( CHugeInt a );
	CHugeInt	operator %= ( CHugeInt a );

	// prefix ++
	CHugeInt&	operator ++();
	CHugeInt&	operator --();

	// postfix ++
	const CHugeInt operator ++( int );
	const CHugeInt operator --( int );

	static CHugeInt Montgomery( CHugeInt n, CHugeInt p, CHugeInt m );
	bool	IsEven();

	void	Random( int nSize, bool bFilter25 );
	u32		bitSize();

private:
	static const u32  CARRY = 10000;

	// 0: >=0
	// 1: < 0
	int		_sign;

	// 如： 112,2345,6778,8003,4023,9420,3423,4214,1234
	//         8,   7,   6,   5,   4,   3,   2,   1,   0
	vector< u32 >	_values;

	static u32	str2Number( char *c, int n );
	static void num2String( u32 v, char* c );

	// a > b return 1
	// a = b return 0
	// a < b return -1
	static int			Com_U( const CHugeInt &a, const CHugeInt &b );

	// + - * / %
	static CHugeInt		Add_U( const CHugeInt &a, const CHugeInt &b );
	static CHugeInt 	Sub_U( const CHugeInt &a, const CHugeInt &b );
	static CHugeInt 	Mul_U( const CHugeInt &a, const CHugeInt &b );
	static CHugeInt 	Div_U( const CHugeInt &a, const CHugeInt &b, CHugeInt &m );
	static CHugeInt 	Div_U2( const CHugeInt &a, const CHugeInt &b, CHugeInt &m );
	//static CHugeInt 	Mod_U( const CHugeInt &a, const CHugeInt &b );

	void	EraseHighZero();

	// 加CARRY倍
	static CHugeInt		baseUp( CHugeInt t );

	friend ostream& operator <<( ostream &f, CHugeInt &a );
	friend istream& operator >>( istream &f, CHugeInt &a );
	
};
