#pragma once

namespace rsaCryp
{
	string		getCode( string n, string e );
	bool		isValidCode( string n, string k, string code );
};

