// test_librsa.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <string>
using namespace std;

#include "..\librsa\librsa.h"
#pragma comment( lib, "librsa.lib" )


int _tmain(int argc, _TCHAR* argv[])
{
	string		n("486831002429523673013777918735911266975559094894229971206230492135486522978402795723604710785330724974403638589567942113");
	string		e("64122388541224036769");
	string		e2("421842199087085473992780890773343194166193743590882865394423926291244533922655403193289547268793250284425547544652352097");

	for( int i = 0; i < 100; i++ )
	{
		string		code = rsaCryp::getCode( n, e );
		bool		b = rsaCryp::isValidCode( n, e2, code );

		printf( "[%d] %s\n%s\n", code.size(), code.c_str(), b?"OK!":"Error!" );
	}

	getchar();
	return 0;
}

