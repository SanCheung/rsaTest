#include "StdAfx.h"
#include "librsa.h"
#include "HugeInt.h"
#include "rsa.h"


namespace rsaCryp
{

string getCode( string n, string e )
{
	int  v = rand()%10000 + 780000;
	CHugeInt	data( v );
	CHugeInt	hin(n);
	CHugeInt	hie(e);
	CHugeInt	d2 = CRSA<CHugeInt>::Process( data, hie, hin );

	return d2.toString();
}
	

bool isValidCode( string n, string k, string code )
{
	CHugeInt	data( code );
	CHugeInt	hin(n);
	CHugeInt	hie(k);
	CHugeInt	d2 = CRSA<CHugeInt>::Process( data, hie, hin );

	string		str = d2.toString();
	int v = atoi( str.c_str() );
	if( v / 10000 == 78 )
		return true;
	return false;
}


};
