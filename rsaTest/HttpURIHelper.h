#pragma once
class CHttpURIHelper
{
public:
	CHttpURIHelper(void);
	~CHttpURIHelper(void);

	static string	ws2utf8( const wchar_t *ws );
	static string	utf82uri( const string &str, bool space_as_plus = false );

	static string	js_encodeURI( const wchar_t *ws );
};

