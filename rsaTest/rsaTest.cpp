// rsaTest.cpp : Defines the entry point for the console application.
//

//RSA算法需要以下相关的数学概念：
//
//素数：素数是一个比1大，其因子只有1和它本身，没有其它数可以整除它的数。素数是无限的。例如，2，3，5，7……等。
//
//两个数互为素数：指的是它们除了1之外没有共同的因子。也可以说这两个数的最大公因子是1。例如，4和9，13和27等。
//
//模运算：如A模N运算，它给出了A的余数，余数是从0到N-1的某个整数，这种运算称为模运算。
//
//RSA加密算法的过程如下：
//
//（1）取两个随机大素数p和q（保密）
//（2）计算公开的模数r=pq(公开)
//（3）计算秘密的欧拉函数j (r) =（p-1）(q-1)（保密），两个素数p和q不再需要，应该丢弃，不要让任何人知道。
//（4）随机选取整数e，满足gcd(e, j (r))=1(公开e，加密密钥)
//（5）计算d，满足de≡1(mod j (r))(保密d，解密密钥，陷门信息)
//（6）将明文x（其值的范围在0到r-1之间）按模为r自乘e次幂以完成加密操作，从而产生密文y（其值也在0到r-1范围内）
//y=xe (mod r)
//（7）将密文y按模为r自乘d次幂，完成解密操作
//x=yd (mod r)
//下面用一个简单的例子来说明RSA公开密钥密码算法的工作原理。
//
//取两个素数p=11，q=13，p和q的乘积为r=p*q=143，算出秘密的欧拉函数j (r)=(p-1)*(q-1)=120，
//再选取一个与j (r)=120互质的数，例如e=7，作为公开密钥，e的选择不要求是素数，
//但不同的e的抗攻击性能力不一样，为安全起见要求选择为素数。
//对于这个e值，可以算出另一个值d=103，d是私有密钥，满足e*d=1 mod j (r)，其实7*103=721除以120确实余1。
// 欧几里德算法可以迅速地找出给定的两个整数a和b的最大公因数gcd（a，b），并可判断a与b是否互素，因此该算法可用来寻找解密密钥。
//
//120=7×17+1
//
//1=120-7×17 mod 120=120-7×(-120+17) mod 120==120+7×103 mod 120
//
//(n,e) 这组数公开，(n,d)这组数保密。
//
//设想需要发送信息x=85。利用(n,e)=(143,7)计算出加密值：
//
//y= xe (mod r)=857 mod 143=123
//
//收到密文y=123后，利用 (n,d)=(143,103)计算明文：
//
//x=yd (mod r) =123103mod 143=85



#include "stdafx.h"
//#include "LargeInt.h"
#include "StringInt.h"
#include "TimeCounter.h"
#include "RSAProcess.h"
#include "RSA.h"
#include "Int.h"

#include "LargeInt.h"
#include "HugeInt.h"


/*
// 500 = 16 x 31 + 4
static u32 prime500[] = 
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

int		zzxcE3( int a, int b );

double Factorial( int a )
{
	double	d = a;
	while( --a )
	{
		d *= a;
	}

	return d;
}
//  e < x
//  获得某个和x互质的数，最好是素数
int		gete( int x )
{
	return 23;
}

// (e * d) % x = 1;

int		getd( int e, int f )
{
	int		i = f/e;
	while( 1 )
	{
		if( (e*i) % f == 1 )
			return i;

		i++;
	}

	return 0;
}

int		pow( int a, int b )
{
	int		c = 1;
	while( b-- )
	{
		c *= a;
	}

	return c;
}

// ( n ^ p ) % m
// 快速计算 (n ^ p) % m 的值，与power算法极类似
u32 Montgomery( u32 n, u32 p, u32 m )
{
	u32	r = n % m;
	
	u32	k = 1;
	while( p > 1 )
	{
		if( (p&1) != 0 )
		{
			k = ( k * r ) % m;
		}

		r = ( r * r ) % m;
		p /= 2;
	}

	return ( r * k ) % m;
}

// http://blog.sina.com.cn/s/blog_64732e880100hzaq.html

//蒙格马利”快速幂模算法
//
//后面我们会用到这样一种运算：(X^Y)%Z
//
//问题是当X和Y很大时，只有32位的整型变量如何能够有效的计算出结果？
//考虑上面那份最终的优化代码和再上面提到过的积模分解公式。
//
// X^Y可以看作Y个X相乘，即然有积模分解公式，
//那么我们就可以把Y个X相乘再取模的过程分解开来，
// 比如：(17^25)%29则可分解为：( ( 17 * 17 ) % 29 * ( 17 * 17 ) % 29 * ……
//如果用上面的代码将这个过程优化，那么我们就得到了著名的“蒙格马利”快速幂模算法：

// ( n ^ p ) % m
__int64 Montgomery2( u32 n, u32 p, u32 m )
{
	u32	k = 1;
	p %= m;

	while( p != 1 )
	{
		if( 0 != ( p&1 ) )
			k = ( n*k ) % m;

		n = (n*n) % m;
		p >>= 1;
	}

	return ( n*k ) % m;
}

bool IsPrime( u32 n )
{
	if( n < 2 )
		return false;

	if( 2 == n )
		return true;
	
	int		max = (int)sqrt( (double)n );
	for( int i = 2; i <= max; i++ )
		if( n % i == 0 )
		{
			printf( "%d\n", i );
			return false;
		}
	
	return true;
}

bool IsPrime2( u32 n )
{
	if( n < 2 )
		return false;

	int		i;
	for( i = 0; i < 168; i++ )
	{
		if( n == prime500[i] )
			return true;
		
		if( 0 == n % prime500[i] )
		{
			printf( "%d\n", prime500[i] );
			return false;
		}
	}
	
	int		max = (int)sqrt( (double)n );
	for( i = 1009; i <= max; i++ )
		if( n % i == 0 )
		{
			printf( "%d\n", i );
			return false;
		}

	return true;
}

bool IsPrime3( u32 n )
{
	if( n < 2 )
		return false;

	int		i;
	for( i = 0; i < 5; i++ )
	{
		if( prime500[i] == n )
			return true;
	}

	for( i = 0; i < 5; i++ )
	{
		if( 1 != Montgomery2( prime500[i], n-1, n ) )
			return false;
	}

	return true;
}


//	Rabbin-Miller
bool IsPrime4( u32 n )
{
	if( n < 2 )
		return false;

	int		i;
	for( i = 0; i < 168; i++ )
	{
		if( prime500[i] == n )
			return true;

		if( 0 == n % prime500[i] )
			return false;
	}

	for( i = 0; i < 168; i++ )
	{
		if( 1 != Montgomery2( prime500[i], n-1, n ) )
			return false;
	}

	// 找到r和m，使得n = 2^r * m + 1;
    int r = 0, m = n - 1; // ( n - 1 ) 一定是合数
    while ( 0 == ( m & 1 ) )
    {
        m >>= 1; // 右移一位
        r++; // 统计右移的次数
    }

    const unsigned nTestCnt = 10; // 表示进行测试的次数
    for ( unsigned i = 0; i < nTestCnt; ++i )
    { // 利用随机数进行测试，
        int a = prime500[ rand() % 500 ];
        if ( 1 != Montgomery2( a, m, n ) )
        {
            int j = 0;
            int e = 1;
            for ( ; j < r; ++j )
            {
                if ( n - 1 == Montgomery( a, m * e, n ) )
                {
                    break;
                }
                e <<= 1;
            }
            if (j == r)
            {
                return false;
            }
        }
    }
    return true;
}

void Test()
{
	//CLargeInt::IsPrime();
}

//	return n ^ p
__int64	Power( u32 n, u32 p )
{
	__int64	odd = 1;
	while( p > 1 )
	{
		if( ( p&1 ) != 0 )
		{
			odd *= n;
		}

		n *= n;
		p /= 2;
	}

	return n*odd;
}


void TestPrime()
{
	//TestRSA();

	//DWORD	dwStart = timeGetTime();
	//int		nCounter = 1;
	//for( u32 n = 3; n < 1000000; n++ )
	//	if( IsPrime( n ) )
	//		nCounter++;
	//DWORD	dwEnd = timeGetTime();

	CTimeCounter		tc;

	//u32 n = 100000000;
	//while( 1 )
	//{
	//	n++;
	//	if( IsPrime( n ) )
	//		break;
	//}
	
	//vector< u32 >		an1, an2;

	u32	n;
	int		k;
	DWORD	time;

	for( k = 1, n = 1; n < 100000; n++ )
	{
		if( IsPrime( n ) )
		{
			//an1.push_back( n );
			k++;
		}
	}

	time = tc.GetTime();
	printf( "counter:%d\ntime:%dms\n", k, time );

	// 2
	tc.Reset();
	for( k = 1, n = 1; n < 100000; n++ )
	{
		if( IsPrime2( n ) )
		{
			//an2.push_back( n );
			k++;
		}
	}

	time = tc.GetTime();
	printf( "counter:%d\ntime:%dms\n", k, time );

	// 3
	tc.Reset();
	for( k = 1, n = 1; n < 100000; n++ )
	{
		if( IsPrime3( n ) )
		{
			//an2.push_back( n );
			k++;
		}
	}

	time = tc.GetTime();
	printf( "counter:%d\ntime:%dms\n", k, time );

	// 4
	tc.Reset();
	for( k = 1, n = 1; n < 100000; n++ )
	{
		if( IsPrime4( n ) )
		{
			//an2.push_back( n );
			k++;
		}
	}

	time = tc.GetTime();
	printf( "counter:%d\ntime:%dms\n", k, time );

	//int		i = 0;
	//while( 1 )
	//{
	//	if( i == an2.size() - 1 )
	//	{
	//		printf( "%4d [Last Value]\n", an2[i]  );
	//		break;
	//	}

	//	if( an1[i] != an2[i] )
	//	{
	//		printf( "%4d %4d\n", an1[i], an2[i] );
	//		break;
	//	}

	//	i++;
	//}

	//for( n = 0; n < 160; n++ )
	//{
	//	printf( "%4d = %4d \n", an1[n], an2[n] );
	//}
}

void TestPrime2()
{
	CTimeCounter		tc;

	u32	n = 0xFFFFFF1F;
	//int		k;
	DWORD	time;

	bool	b1 = false;
	//for( int i = 0; i < 10000; i++ )
	{
		if( IsPrime( n ) )
			b1 = true;
	}

	time = tc.GetTime();
	printf( "%s\ntime:%dms\n", b1?"true":"false", time );

	// 2
	tc.Reset();
	bool	b2 = false;
	//for( int i = 0; i < 10000; i++ )
	{
		if( IsPrime2( n ) )
			b2 = true;
	}

	time = tc.GetTime();
	printf( "%s\ntime:%dms\n", b2?"true":"false", time );


	printf( "%u = %d x %u\n", n, 65521, n/65521 );
}

void	PrintPrime500()
{
	int		i = 1;
	int		k = 0;
	while( k < 500 )
	{
		if( IsPrime( i ) )
		{
			printf( "%4d,", i );
			k++;
		}

		i++;
	}
	printf( "\n" );
}

void	TestStringInt()
{
	int		n = 2600;
	//printf( "%e\n", Factorial( n ) );
	
	while( 1 )
	{
		printf( "print input a Number:\n" );
		scanf_s( "%d", &n );
		if( n == 0 )
			break;

		CTimeCounter		tc;

		CStringInt		i1;
		CStringInt::Factorial( n, i1 );
		//printf( "%s\n", i1.toString().c_str() );
		printf( "%d time: %d\n", i1._values.size(), tc.GetTime() );
		tc.Reset();

		CStringInt		i2;
		CStringInt::Factorial2( n, i2 );
		//printf( "%s\n", i2.toString().c_str() );
		printf( "%d time: %d\n", i2._values.size(), tc.GetTime() );

		size_t		size = i1._values.size();
		printf( "%d.%d%d%d%d%d%d\n", i1.GetValue( size-1 ), 
			i1.GetValue( size-2 ), i1.GetValue( size-3 ), i1.GetValue( size-4 ),
			i1.GetValue( size-5 ), i1.GetValue( size-6 ), i1.GetValue( size-7 ));

		int nRet = CStringInt::Compare_Unsign( i1, i2 );
		printf( "compare result:%d\n\n", nRet );
	}
}

void TestStringInt2()
{
	//CStringInt		i;
	//i.HEX = 1000;
	//CStringInt::FromInt( i, 1394834 );
	//string		str = i.toString();

	//CStringInt		i2;
	//CStringInt::FromInt( i2, 23924834 );
	//string		str2 = i2.toString();

	//string		s1 = "22834912342134";
	//string		s2 = "19347";

	//CStringInt		i1( s1 );
	//CStringInt		i2( s2 );
	//CStringInt		c;
	//CStringInt::Mul_Unsign2( i1, i2, c );
	//
	//printf( "%s\n", c.toString().c_str() );

	//CStringInt		i3, i4;
	//CStringInt		cc;
	//i3.HEX = 10000;
	//i4.HEX = 10000;
	//cc.HEX = 10000;
	//
	//CStringInt::FromString( i3, s1 );
	//CStringInt::FromString( i4, s2 );
	//
	//CStringInt::Mul_Unsign2( i3, i4, cc );
	//
	//printf( "%s\n", cc.toString().c_str() );

	int		n = 2600;
	//printf( "%e\n", Factorial( n ) );
	
	while( 1 )
	{
		printf( "print input a Number:\n" );
		scanf_s( "%d", &n );
		if( n == 0 )
			break;

		CTimeCounter		tc;

		//CStringInt		i1;
		//CStringInt::Factorial2( n, i1 );
		////printf( "%s\n", i1.toString().c_str() );
		//printf( "%d time: %d\n", i1._values.size(), tc.GetTime() );
		//tc.Reset();

		CStringInt		i2;
		i2.HEX = 10000;
		CStringInt::Factorial2( n, i2 );
		//printf( "%s\n", i2.toString().c_str() );
		printf( "%d time: %d\n", i2._values.size()*4, tc.GetTime() );

		//size_t		n1 = i1._values.size();
		//printf( "%d%d%d%d%d%d%d%d ... %d%d%d%d\n", 
		//	i1.GetValue( n1-1 ), i1.GetValue( n1-2 ), i1.GetValue( n1-3 ), i1.GetValue( n1-4 ), 
		//	i1.GetValue( n1-5 ), i1.GetValue( n1-6 ), i1.GetValue( n1-7 ), i1.GetValue( n1-8 ),
		//	i1.GetValue(4), i1.GetValue(3), i1.GetValue(1), i1.GetValue(0) );

		size_t		n2 = i2._values.size();
		printf( "%04d%04d %04d%04d %04d%04d %04d%04d ...\n", 
			i2.GetValue( n2-1 ), i2.GetValue( n2-2 ), 
			i2.GetValue( n2-3 ), i2.GetValue( n2-4 ),
			i2.GetValue( n2-5 ), i2.GetValue( n2-6 ), 
			i2.GetValue( n2-7 ), i2.GetValue( n2-8 ) );

		//printf( "%s\n", i1.toString().c_str() );
		//printf( "%s\n", i2.toString().c_str() );

		//int nRet = CStringInt::Compare_Unsign( i1, i2 );
		//printf( "compare result:%d\n\n", nRet );
	}

	getchar();
}

void TestStringInt3()
{
	string		sa( "9384923482394934345" );
	string		sb( "1001439283492498459" );

	CStringInt	a( sa );
	CStringInt	b( sb );

	CStringInt	c;
	CStringInt	d;

	CStringInt::DivMod( a, b, c, d );

	printf( "%s\n", sa.c_str() );
	printf( "%s\n", sb.c_str() );

	printf( "%s\n", c.toString( 1 ).c_str() );
	printf( "%s\n", d.toString( 1 ).c_str() );

	getchar();
}

void TestStringInt4()
{
	CStringInt	a( 12996 );
	CStringInt	b( 143 );

	CStringInt	c, d;
	CStringInt::DivMod( a, b, c, d );	

	getchar();
}

void TestStringInt5()
{
	string		sa( "3162715073" );
	string		sb( "9834" );

	// 321,610
	// 2333

	CStringInt	a( sa );
	CStringInt	b( sb );

	CStringInt		c, d;

	printf( "%s\n", sa.c_str() );
	printf( "%s\n", sb.c_str() );

	c = a / b;
	d = a % b;
	//CStringInt::Mod_Unsign( a, b, c );

	printf( "%s\n", c.toString().c_str() );
	printf( "%s\n", d.toString().c_str() );

	getchar();
}

void	TestRSA()
{
	//int		p = 101;
	//int		q = 79;

	//int		_n = p * q;

	//int		_m = (p-1)*(q-1);
	//int		_e1 = 23;	//gete( m );

	//int		_e2 = zzxcE3( _e1, _m );//getd( _e1, _m );

	//int		data = 19;
	////int		s = ( pow(m,e) ) % r;
	////int		n = ( pow(s,d) ) % r;
	//int		data1 = Montgomery2( data, _e1, _n );
	//int		data2 = Montgomery2( data1, _e2, _n );

	//printf( "\nn = %d\n e1 = %d\n e2 = %d\n", _n, _e1, _e2 );
	//printf( "%d -> %d -> %d\n", data, data1, data2 );
}

void	TestRSAProcess()
{
	CRSAProcess		rp;
	CTimeCounter	tc;

	int		n = 5;
	while( n-- )
	{
		tc.Reset();
		CStringInt		p = rp.GetALargePrime( 10 );
		DWORD		 t = tc.GetTime();
		printf( "%d\n%s\n", t, p.toString().c_str() );
	}

	printf( "\n***ok!\n" );
	getchar();
}

void	TestRSAProcess2()
{
	CRSAProcess		rp;
	rp.Test();

	printf( "\n***ok!\n" );
	getchar();
}

int		gcd( int a, int b )
{
	if( 0 == a )
		return b;

	while( 0 != b )
	{
		if( a > b )
			a -= b;
		else
			b -= a;
	}

	return a;
}


// 获得一个数a的互质数b，即gcd( a, b ) = 1;
int		getHZ( int a, int base )
{
	while( gcd( a, base ) != 1 )
		base++;
	
	return base;
}

// 辗转相除，求e
// gcd( d*e, n ) = 1;
// e*x - n*y = 1;

// a*x - b*y = 1;

int		zzxcE( int a, int b )
{
	vector< int >	va;
	vector< int >	vb;

	va.push_back( a );
	vb.push_back( b );

	while( 1 != a && 1 != b )
	{
		if( a > b )
			a = a % b;
		else
			b = b % a;

		va.push_back( a );
		vb.push_back( b );
	}

	int		x = 1;
	int		y = 1;

	int		n = (int)va.size();
	for( int i = n-1; i >= 0; i-- )
	{
		int		t1 = va[i];
		int		t2 = vb[i];
		
		if( t1 > t2 )
			y = (t1*x - 1)/t2;
		else
			x = (t2*y + 1)/t1; 
		
		printf( "%4d %4d\t\t%4d %4d\n", va[i], vb[i], x, y );
	}

	return x;
}

// 性能优化版本
int		zzxcE2( int a, int b )
{
	vector< int >	v;
	v.push_back( b );
	v.push_back( a );

	int		t = a;
	while( 1 != t )
	{
		if( a > b )
		{
			a = a % b;
			t = a;
		}
		else
		{
			b = b % a;
			t = b;
		}

		v.push_back( t );
	}

	//int		x = 1;
	//int		y = 1;
	
	//int		flag = 1;
	//int		n = (int)v.size();
	//for( int i = n-1; i > 0; i-- )
	//{
	//	int		t1 = v[i];
	//	int		t2 = v[i-1];

	//	if( flag )
	//		y = (t2*x - 1)/t1;
	//	else
	//		x = (t2*y + 1)/t1; 
	//	
	//	printf( "%4d %4d\t\t%4d %4d\n", t1, t2, x, y );

	//	flag = !flag;
	//}

	int		value = 1;
	int		flag = 1;
	int		n = (int)v.size();
	for( int i = n-1; i > 0; i-- )
	{
		int		t1 = v[i];
		int		t2 = v[i-1];

		value = (t2*value - flag)/t1;

		printf( "%4d %4d\t\t%4d\n", t1, t2, value );

		flag = -flag;
	}

	return value;
}


// 递归版本
int		zzxcE3( int a, int b )
{
	//if( b == 1 )
	//	return a-b;
	//
	//if( a > b )
	//	return ( a*zzxcE3( a%b, b ) - 1 ) / b;
	//else
	//	return ( b*zzxcE3( a, b%a ) + 1 ) / a;

	int		t = 0;
	if( b == 1 )
		t = a-b;
	else
	{
		if( a > b )
			t = ( a*zzxcE3( a%b, b ) - 1 ) / b;
		else
			t = ( b*zzxcE3( a, b%a ) + 1 ) / a;
	}

	printf( "%d # %d = %d\n", a, b, t );
	return t;
}

unsigned long root1(unsigned long a)
{
	int		x = 20;

	for(int   i=0;i <20;i++) 
	{ 
		//x[i+1]=(x[i]+(a/x[i]))/2;
		x = ( x + a/x )/2;

		//printf( "%f\n", x );
	}

	return x;
}


unsigned long bigroot(unsigned long x)
{
	// unsigned long long x for 64bit and read with %I64u!
	// i < 16 -> i < 32 and x >> 30 -> x >> 62
	unsigned long rem = 0 , divisor = 0 , root = 0;

	for( int i = 0; i < 16 ; i++ )
	{
		rem = ( rem << 2 ) + ( x >> 30 );    // calculate the reminder
		divisor = ( root << 2 ) + 1;

		if( divisor <= rem )               // calculate the root
		{
			root = ( root << 1 ) + 1;          
			rem -= divisor;
		}
		else
			root <<= 1;

		x <<= 2;                             // delete top 2 bits
	}

	return root;
}

float InvSqrt(float x)
{
	float xhalf = 0.5f*x;
	int bx = *(int*)&x;        // get bits for floating value
	bx = 0x5f3759df-(bx>>1);   // gives initial guesss y0
	x = *(float*)&bx;          // convert bits back to float
	//x = x*(1.5f-xhalf*x*x);
	return x*(1.5f-xhalf*x*x); // Newton step, repeating increases accuracy
}

void TestRSA_T2()
{
	CRSA< CLargeInt >	rsa;

	CLargeInt		n = "18007976400253113172198203983513615405660046986655676045240868304902290861664213";
	CLargeInt		e1 = "85159";
	CLargeInt		e2 = "9856078301053292685951996729266267810118351983483664456787428641688723588467179";

	CLargeInt		data = "1234567890";
	cout << data << endl;

CTimeCounter		tc;
	CLargeInt		data1 = rsa.Enc( data, e1, n );
	cout << data1 << endl;
	tc.ShowTime();
	CLargeInt		data2 = rsa.Des( data1, e2, n );
	cout << data2 << endl;
	tc.ShowTime();
}

void TestRSA2014()
{
	CRSA< CLargeInt >	rsa;

	CLargeInt		n  = "18007976400253113172198203983513615405660046986655676045240868304902290861664213";
	CLargeInt		e1 = "15731475535125480233241449505678419569188461092269100637718450092894256493775359";
	CLargeInt		e2 = "3312247639";

	CLargeInt		data( 0x00FF0000 );
	cout << data << endl;

	CTimeCounter		tc;
	CLargeInt		data1 = rsa.Enc( data, e1, n );
	cout << data1 << endl;
	tc.ShowTime();
	CLargeInt		data2 = rsa.Des( data1, e2, n );
	cout << data2 << endl;
	tc.ShowTime();

	getchar();
}

void Test2014()
{
	CRSA< CHugeInt >	rsa;

	//CHugeInt		n  = "18007976400253113172198203983513615405660046986655676045240868304902290861664213";
	//CHugeInt		e1 = "15731475535125480233241449505678419569188461092269100637718450092894256493775359";
	//CHugeInt		e2 = "3312247639";

	CHugeInt		n  = "486831002429523673013777918735911266975559094894229971206230492135486522978402795723604710785330724974403638589567942113";
	CHugeInt		e1 = "421842199087085473992780890773343194166193743590882865394423926291244533922655403193289547268793250284425547544652352097";
	CHugeInt		e2 = "64122388541224036769";

	CHugeInt		data( 0x1234ABEF );
	cout << data << endl;

	CTimeCounter		tc;
	CHugeInt		data1 = rsa.Enc( data, e1, n );
	cout << data1 << endl;
	tc.ShowTime();
	CHugeInt		data2 = rsa.Des( data1, e2, n );
	cout << data2 << endl;
	tc.ShowTime();

	getchar();
}


void TestRSA_T()
{
	//CRSA< CInt >	rsa;
	//CRSA< CStringInt > rsa;
	CRSA< CLargeInt >	rsa;

	int		i = 0;

	int		nKeyCount = 10;

	while( 1 )
	{
		i++;
		if( rsa.Test() )
		{
			nKeyCount--;
			//cout << ">>> Key " << ( 10-nKeyCount ) << endl;
			if( nKeyCount < 0 )
				return;
		}

		cout << i << "\t";
		
		//cout << "Input q to quit: ";
	
		//char ch;
		//cin >> ch;
		//if( ch == 'q' )
		//	break;
	}
}

void writeToTxt()
{
	//FILE	*f = fopen( "primelist.txt", "rt" );
	
	ofstream		f( "1.txt" );

	for( int i = 0; i < 10; i++ )
	{
		CStringInt		v = i*i;
		f << v;
	}
}

void readFromTxt( )
{
	//FILE	*f = fopen( "primelist.txt", "rt" );
	
	ifstream		f( "1.txt" );

	for( int i = 0; i < 2000; i++ )
	{
		if( i % 10 == 0 )
			cout << endl << (i/10) << '.';
	
		CStringInt		v;
		f >> v;
		cout << v;
	}
}


void GetPrime_Test()
{
	CTimeCounter		tc;
	
	vector< CStringInt > ap;
	CStringInt::APreadFromTxt( ap );
	tc.ShowTime();

	for( int i = 0; i < 5; i++ )
	{
		cout << i << "...";

		CStringInt		a = CStringInt::GetFixSizePrime_Speed( 100 );

		cout << a << endl;
		tc.ShowTime();
		//CStringInt::GetFixSizePrime( a, 11 );
		cout << (CStringInt::TestPrime_Range( a, ap, 100, 1000 )?"": "no! ");
		tc.ShowTime();
		cout << (CStringInt::TestPrime_Range( a, ap, 1000, 2000 )?"": "no! ");
		tc.ShowTime();
		cout << (CStringInt::TestPrime_Range( a, ap, 2000, 5000 )?"": "no! ");
		tc.ShowTime();

		cout << endl;
	}
}


// montgomery快速幂模算法 (n ^ p) % m, 与power算法极类似
unsigned __int64 montgomery(unsigned __int64 n, unsigned __int64 p, unsigned __int64 m)
{ 
    unsigned __int64 r = n % m;
    unsigned __int64 tmp = 1;
    while (p > 1)
    {
        if ((p & 1)!=0)
        {
            tmp = (tmp * r) % m;
        }
        r = (r * r) % m;
        p >>= 1;
    }
    return (r * tmp) % m;
}

//返回true:n是合数, 返回false:n是素数
bool R_M_Help(unsigned __int64 a, unsigned __int64 k, unsigned __int64 q, unsigned __int64 n)
{
	if ( 1 != montgomery( a, q, n ) )
    {
        int e = 1;
        for ( int i = 0; i < k; ++i )
        {
            if ( n - 1 == montgomery( a, q * e, n ) ) 
                return false;
           
            e <<= 1;
        }
        
		return true;
    }

	return false;
}

//拉宾-米勒测试 返回true:n是合数, 返回false:n是素数  
bool R_M( unsigned __int64 n ) 
{
	if( n < 2 )
		throw 0;

	if ( n == 2 || n == 3 )
	{
		return false;
	}

	if( (n & 1) == 0 )
		return true;

    // 找到k和q, n = 2^k * q + 1;
    unsigned __int64 k = 0, q = n - 1;
    while( 0 == ( q & 1 ) )
    {
        q >>= 1;
        k++;
    }

	//if n < 1,373,653, it is enough to test a = 2 and 3. 
	//if n < 9,080,191, it is enough to test a = 31 and 73. 
	//if n < 4,759,123,141, it is enough to test a = 2, 7, and 61. 
	//if n < 2,152,302,898,747, it is enough to test a = 2, 3, 5, 7, and 11.
         
	if( n < 1373653 )
	{
		if( R_M_Help(2, k, q, n ) 
		 || R_M_Help(3, k, q, n ) )
			return true;
	}
	else if( n < 9080191 )
	{
		if( R_M_Help(31, k, q, n ) 
		 || R_M_Help(73, k, q, n ) )
			return true;
	}  
	else if( n < 4759123141 )
	{
		if( R_M_Help(2, k, q, n ) 
		 || R_M_Help(3, k, q, n )
		 || R_M_Help(5, k, q, n )
		 || R_M_Help(11, k, q, n ) )
			return true;
	}
	else if( n < 2152302898747 )
	{
		if( R_M_Help(2, k, q, n ) 
		 || R_M_Help(3, k, q, n )
		 || R_M_Help(5, k, q, n )
		 || R_M_Help(7, k, q, n )
		 || R_M_Help(11, k, q, n ) )
			return true;
	}
	else 
	{
		if( R_M_Help(2, k, q, n ) 
		 || R_M_Help(3, k, q, n )
		 || R_M_Help(5, k, q, n )
		 || R_M_Help(7, k, q, n )
		 || R_M_Help(11, k, q, n )
		 || R_M_Help(31, k, q, n )
		 || R_M_Help(61, k, q, n )
		 || R_M_Help(73, k, q, n ) )
			return true;
	}

    return false;
}



void RSABuild()
{
	CRSA< CHugeInt >	rsa;

	int		i = 0;
	int		nKeyCount = 10;

	while( 1 )
	{
		i++;
		cout << i << " ";

		CHugeInt	n, e1, e2;
		if( rsa.Build( n, e1, e2 ) )
		{
			nKeyCount--;
			if( nKeyCount < 0 )
				return;
		}
	}
}

void RSAProcess()
{

	CRSA< CHugeInt >	rsa;

	CHugeInt	n("486831002429523673013777918735911266975559094894229971206230492135486522978402795723604710785330724974403638589567942113");
	CHugeInt	e1("64122388541224036769");
	CHugeInt	e2("421842199087085473992780890773343194166193743590882865394423926291244533922655403193289547268793250284425547544652352097");
	rsa.Process( n, e1, e2 );
}
//*/


string codeGetter()
{
	int  v = rand()%10000 + 780000;

	CRSA< CHugeInt >	rsa;

	CHugeInt	data( v );
	CHugeInt	n("486831002429523673013777918735911266975559094894229971206230492135486522978402795723604710785330724974403638589567942113");
	CHugeInt	e("64122388541224036769");
	CHugeInt	d2 = rsa.Des( data, e, n );

	return d2.toString();
}

bool IsValidCode( string code )
{
	CRSA< CHugeInt >	rsa;

	CHugeInt	data( code );
	CHugeInt	n("486831002429523673013777918735911266975559094894229971206230492135486522978402795723604710785330724974403638589567942113");
	CHugeInt	e("421842199087085473992780890773343194166193743590882865394423926291244533922655403193289547268793250284425547544652352097");
	CHugeInt	d2 = rsa.Enc( data, e, n );

	string		str = d2.toString();
	int v = atoi( str.c_str() );
	if( v / 10000 == 78 )
		return true;
	return false;
}

void removeIndex()
{
	FILE	*f = fopen( "code1000.txt", "rt" );
	FILE	*f2 = fopen( "code1000noindex.txt", "wt+" );
	
	int		index;
	char	str[128] = {0};
	while( !feof( f ) )
	{
		memset( str, 0, 128 );
		fscanf( f, "%d %s", &index, str );

		printf( "%d\t", index );

		fprintf( f2, "%s\n", str );

		if( index == 999 )
			break;
	}

	fclose( f );
	fclose( f2 );
}

void testHEX()
{
	wchar_t ws[20] = {0x308b, 0x2c81, 0xfcb0, 0xc122, 0x6cf8 };

	char s[10] = {0x4a,0x9b,0xd1,0x8c,0x59,0x98,0xd0,0xad,0xa7,0x8b};

	//wchar_t ws[20] = {0};
	//int n = ::MultiByteToWideChar( CP_MACCP, MB_COMPOSITE, s, 10, NULL, 0 );
	//::MultiByteToWideChar( CP_MACCP, MB_COMPOSITE, s, 10, ws, n );
}


int _tmain(int argc, _TCHAR* argv[])
{
	//srand((int)time(0));

	//FILE	*f = fopen( "code1000.txt", "wt+" );

	//for( int i = 0; i < 1000; i++ )
	//{
	//	string code = codeGetter();
	//	//if( IsValidCode( code ) )
	//	//	cout << i << " ok! " << code << endl;
	//	//else
	//	//	cout << i << " error!" << endl;

	//	//cout << i << "  " << code << endl;
	//	if( i % 100 == 0 )
	//		printf( "%d ok!", i/100 );

	//	fprintf( f, "%d %s\n", i, code.c_str() );
	//}

	//fclose( f );

	//printf( "1000 ok!" );

	//removeIndex();
	testHEX();
	getchar();

	//RSABuild();
	//RSAProcess();

	//TestRSAProcess2();

	//CHugeInt	h1 = CHugeInt::FromInt( 123456 );
	//CHugeInt	h2 = CHugeInt::FromString( "3498320045" );

	//CHugeInt	x = h2 / h1;

	//printf( "%s\n%s\n%s\n", h1.toString().c_str(), h2.toString().c_str(), x.toString().c_str() );

	//CHugeInt	x = "100000000000000000000000000000000000002";
	//cout << x  << endl;

	//getchar();

	//Test2014();

	//TestRSA2014();

	return 0;
}