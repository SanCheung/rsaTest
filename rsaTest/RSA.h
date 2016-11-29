#pragma once
#include "TimeCounter.h"

template< typename T >
class CRSA
{
public:
	CRSA(void)
	{
	}

	~CRSA(void)
	{
	}

	void	Process( T _n, T _e1, T _e2 )
	{
		CTimeCounter		tc;

		T		data, data1, data2;
		data.Random( 2, false );
		cout << tc.GetTime() << "  " << data << endl;

		data1 = Montgomery( data, _e1, _n );
		cout << tc.GetTime() << "  " << data1 << endl;

		data2 = Montgomery( data1, _e2, _n );
		cout << tc.GetTime() << "  " << data2 << endl;

		if( data == data2 )
		{
			//cout << "\nn = " << _n << "  [" << _n.bitSize() << "bits]" 
			//	<< "\ne1 = " << _e1 << "  [" << _e1.bitSize() << "bits]" 
			//	<< "\ne2 = " << _e2 << "  [" << _e2.bitSize() << "bits]"
			//	<< endl;
			cout << "ok!" << endl;
		}
		else
		{
			cout << "error!" << endl;
		}

		getchar();
	}


	bool	Build( T &_n, T &_e1, T &_e2 )
	{
//#define		OUTC   cout << '<'
#define		OUTC   

		T	p, q;

		OUTC;
		p = GetFixSizePrime_Speed( 10 );

		OUTC;
		q = GetFixSizePrime_Speed( 10 );

		OUTC;
		_e1 = GetFixSizePrime_Speed( 5 );

		_n = p*q;

		T	m = (p-1)*(q-1);

		OUTC;
		_e2 = Euclidean( _e1, m );

		T		data, data1, data2;
		data.Random( 2, false );

		OUTC;
		data1 = Montgomery( data, _e1, _n );

		OUTC;
		data2 = Montgomery( data1, _e2, _n );

		OUTC;
		if( data == data2 )
		{
			cout << "\nn = " << _n << "  [" << _n.bitSize() << "bits]" 
				<< "\n " << p
				<< " x " << q
				<< "\ne1 = " << _e1 << "  [" << _e1.bitSize() << "bits]" 
				<< "\ne2 = " << _e2 << "  [" << _e2.bitSize() << "bits]"
				<< endl;
			return true;
		}
		else
		{
			//cout << "[Prime ERROR]" << endl;
			cout << "   ";
			return false;
		}
	}


	bool	Test()
	{
		char	c = '<';

		//	Get _n
		T	_n;
		T	p, q, _e1;
		//T::Get3Prime( p, q, _e1 );

//n = 8416058881495454970823363494684270758353  [133bits]
// 95280897558596557531 * 88328921086408576963
//e1 = 5869561123
//e2 = 4959400550198471211360647885494031404327

		//a = 101;
		//b = 79;
		//c = 23;
		cout << c;
		p = T::GetFixSizePrime_Speed( 20 );
		cout << c;
		q = T::GetFixSizePrime_Speed( 20 );
		cout << c;
		_e1 = T::GetFixSizePrime_Speed( 10 );
		cout << c;

		_n = p*q;

		T	_m = (p-1)*(q-1);
		//cout << "m = (p-1)*(q-1) = " << _m << endl;
		//cout << "gcd( e1, (p-1)(q-1) ) = " << T::gcd( _e1, _m ) << endl;

//CTimeCounter		tc;

		//while( _m % _e1 != 1 )
		//{
		//	_e1 = T::GetFixSizePrime_Speed( 20 );
		//}

		//cout << "p = " << p << endl;
		//cout << "q = " << q << endl;
		//cout << "e1 = " << _e1 << endl;

		//// gcd( e1*e2, m ) = 1;
		////T	_e2 = T::zzxc( _e1, _m);
		//cout << _m % _e1 << endl;		

		//cout << _e1 << "*x - " << _m << "*y = 1 " <<endl; 
		T	_e2 = T::Euclidean( _e1, _m );
		cout << c;

		//cout << "*********";
		//cout << _e1*_e2 % _m << endl;

		if( _e2 > _m )
		{
			//cout << "error 2!" << endl;
			return false;
		}
		
		//while( _e2 > _m )
		//{
		//	cout << "Try other " << endl;
		//	_e1 = T::GetFixSizePrime_Speed( 5 );
		//	_e2 = T::Euclidean( _e1, _m );
		//}

		T		data;
		data.Random( 10 );

//tc.ShowTime();

		cout << c;
		T		data1 = Montgomery( data, _e1, _n );

		cout << c;
//tc.ShowTime();

		T		data2 = Montgomery( data1, _e2, _n );
		cout << c;
//tc.ShowTime();

		if( data == data2 )
		{
			//printf( "n = %s\ne1 = %s\ne2 = %s\n\n%s -> %s -> %s\n",
			//					_n.toString().c_str(),
			//					_e1.toString().c_str(),
			//					_e2.toString().c_str(),
			//					data.toString().c_str(), 
			//					data1.toString().c_str(),
			//					data2.toString().c_str() );
			cout << "\nn = " << _n << "  [" << _n.bitSize() << "bits]" 
				 << "\n " << p
				 << " x " << q
				 << "\ne1 = " << _e1 << "  [" << _e1.bitSize() << "bits]" 
				 << "\ne2 = " << _e2 << "  [" << _e2.bitSize() << "bits]" 
				 << "\n\n" ;//<< data << " -> " << data1 << " -> " << data2 << endl;

			//for( int i = 0; i < 4; i++ )
			//{
			//	data.Random( 10 );
			//	data1 = T::Montgomery( data, _e1, _n );
			//	data2 = T::Montgomery( data1, _e2, _n );

			//	if( data == data2 )
			//		//printf( "ok! %s -> %s -> %s\n", 
			//		//			data.toString().c_str(),
			//		//			data1.toString().c_str(), 
			//		//			data2.toString().c_str() );
			//		//cout << "ok! " << data << " -> " << data1 << " -> " << data2 << endl;
			//		cout << data << " -> " << data1 << " -> " << data2 << endl;
			//}

			return true;
		}
		else
			cout << "[Prime ERROR]" << endl;
		//	cout << "[ERROR!]e1 = " << _e1 << endl << "e2 = " << _e2 << endl;
		
		//p = "1094575053967366365144802264571";
		//q = "874241434730398266616207700387";
		//n = 956922865600533482366665940019692096578141187603125873088977
		//e1 = 65537
		//e2 = 535939298134909768074041737161458916271465291974975163662773
		//53624688834865518740012075893086949917912142143488693110397

		return false;
	}

	
	T	Enc( T data, T e1, T n )
	{
		return Montgomery( data, e1, n );
	}

	T	Des( T data, T e2, T n )
	{
		return Montgomery( data, e2, n );
	}

	// 蒙哥马利
	// return n^p mod m
	T	Montgomery( T n, T p, T m )
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

	// 辗转相除法
	// m = (p-1)*(q-1)
	// (e2*e1) mod m = 1
	// T	_e2 = T::Euclidean( _e1, _m );

	T	Euclidean( T a, T b )
	{
		T		t = 0;
		if( b == 1 )
		{
			t = a-b;
		}
		else if( a == 1 )
		{
			t = b+1;
		}
		else
		{
			if( a > b )
				t = ( a*Euclidean( a%b, b ) - 1 ) / b;
			else
				t = ( b*Euclidean( a, b%a ) + 1 ) / a;
		}

		return t;
	}

	private:
		static void APreadFromTxt( vector< T > &ap )
		{
			if( !ap.empty() )
				return;

			ifstream		f( "1.txt" );

			for( int i = 0; i < 10000; i++ )
			{		
				T		v;
				f >> v;
				ap.push_back( v );
			}
		}

		vector< T > _sap;


		T GetFixSizePrime_Speed( size_t size )
		{
			APreadFromTxt( _sap );

			T		a;
			while( 1 )
			{
				a.Random( (int)size, true );
				if( TestPrime_Range( a, _sap, 0, 600 ) )
					return a;
			}
		}

		bool TestPrime_Range( T a, const vector< T > &ap, int i, int n )
		{
			for( int j = 1; j < n; j++ )
			{
				if( a % ap[j] == 0 )
					return false;
			}

			return true;	
		}

};
