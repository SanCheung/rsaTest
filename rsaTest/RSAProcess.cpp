#include "StdAfx.h"
#include "RSAProcess.h"

CRSAProcess::CRSAProcess(void)
{
}

CRSAProcess::~CRSAProcess(void)
{
}


void CRSAProcess::Test()
{
/*
p = 9254169600320915904625194129360560316823
q = 2514204350707295938137154806979185290801
n = 2326687347131004473253216936069843819700512861606077421374815536734662994744
5223
m = 2326687347131004473253216936069843819699336024210974600190539301841029020183
7600
e = 8763495995706312878196462760337233455413
//*/
	//              0        1         2         3         4
	//              1234567890123456789012345678901234567890
	//CStringInt p = "9254169600320915904625194129360560316823";
	//CStringInt q = "2514204350707295938137154806979185290801";
	//CStringInt n = "23266873471310044732532169360698438197005128616060774213748155367346629947445223";
	//CStringInt m = "23266873471310044732532169360698438196993360242109746001905393018410290201837600";
	//CStringInt e = "8763495995706312878196462760337233455413";

	CStringInt	p, q;
	//p = 11;
	//q = 13;
	p = GetALargePrime(3);
	q = GetALargePrime(3);
	printf( "p = %s\n", p.toString().c_str() );
	printf( "q = %s\n", q.toString().c_str() );

	CStringInt	n = p * q;
	printf( "n = %s\n", n.toString().c_str() );

	// 120
	CStringInt	m = (p-1)*(q-1);
	printf( "m = %s\n", m.toString().c_str() );


	//	e, m互质
	CStringInt		e;
	//e = 7;
	//CStringInt	e = GetCoPrime( m );
	e = GetALargePrime( 3 );
	printf( "e = %s\n", e.toString().c_str() );
	
	//	d*e % m = 1
	CStringInt	d = GetD( e, m );
	printf( "d = %s\n", d.toString().c_str() );

	CStringInt	data = 0x13;
	CStringInt	data1;
	CStringInt	data2;
	printf( "data = %s\n", data.toString().c_str() );
	
	// 加密 (n, e) = ( 143, 7 )
	data1 = CRSAProcess::Cryp( data, n, e );
	printf( "data1 = %s\n", data1.toString().c_str() );

	// 解密 (n, d) = ( 143, 103 )
	data2 = CRSAProcess::Cryp( data1, n, d );
	printf( "data2 = %s\n", data2.toString().c_str() );
}

CStringInt CRSAProcess::GetALargePrime( int nLength )
{
	CStringInt		i;
	i.Random( nLength );

	if( i.GetValue( 0 ) % 2 == 0 )
		i++;

	while( !i.IsPrime() )
	{
		//i = i + 2;
		i.Random( nLength );
	}

	return i;
}

// 互质
CStringInt CRSAProcess::GetCoPrime( CStringInt p )
{
	return 7;
}

//	d*e % m = 1
CStringInt CRSAProcess::GetD( CStringInt e, CStringInt m )
{
	// d * e % m = 1;
	// d * e = m*x + 1

	// d = ( m*x + 1 ) / e
	
	CStringInt		x = 1;
	CStringInt		d;
	while( 1 )
	{
		CStringInt		t;
		CStringInt		tt = m*x + 1;
		CStringInt::DivMod( tt, e, d, t );

		if( t == 0 )
			break;

		x++;
	}

	// m = e*a + b;
	// d * e = e*a*x + b*x + 1
	// d = a*x + ( b*x + 1 ) / e
	//CStringInt	a, b;
	//CStringInt::DivMod( m, e, a, b );

	//CStringInt		x = 1;
	//CStringInt		c;
	//while( 1 )
	//{
	//	c = b * x + 1;
	//	CStringInt	t1 = c % e;
	//	if( t1 == 0 )
	//		break;

	//	x++;
	//}
	//
	//CStringInt		d = a * x + c / e;

	return d;
}

//  e*x % m = 1 求 x
//	即 e*x - m*y = 1;

//  11x - 49y = 1 求x
//	49%11 = 5; 11x - 5y = 1;
//	11%5 = 1;	x - 5y = 1;
// y = 0, x = 1;
// x = 1, y = 2;
// y = 2, x = 9;

// e = 29, m = 120
// 29x - 120y = 1;	求x
// 120 % 29 = 4; 29x - 4y = 1;
// 29 % 4 = 1;	 x - 4y = 1;
// y = 0, x = 1;
// x=1, y=7
// 29
CStringInt CRSAProcess::GetD2( CStringInt e, CStringInt m )
{
	return 0;
}


// (d ^ e) % n;
CStringInt CRSAProcess::Cryp( CStringInt d, CStringInt n, CStringInt e )
{
	return CStringInt::Montgomery( d, e, n );
}
