#include "stdAfx.h"
#include "HttpURIHelper.h"


CHttpURIHelper::CHttpURIHelper(void)
{
}


CHttpURIHelper::~CHttpURIHelper(void)
{
}

string CHttpURIHelper::ws2utf8( const wchar_t *ws )
{
	int len = ::WideCharToMultiByte(CP_UTF8, 0, ws, -1, NULL, 0, NULL, NULL);  
	if (len == 0) return "";

	string	str;
	str.reserve( len );
	::WideCharToMultiByte(CP_UTF8, 0, ws, -1, (char *)str.data(), len, NULL, NULL);
	return str;
}

//HTTP URI编解码
//	字符集合 
//	依据RFC3986 2规范，HTTP URI中允许出现的US-ASCII字符的子集，可以分成保留、未保留及转义这几类，
//	每类的全部字符列表如下
//		保留:  : / ? # [ ] @ ! $ & '( ) * + ,; =共18个，一般用于URI部件分隔符。
//		未保留:  a-z A-Z 0-9 - . _ ~共66个，一般用于部件内数据。
//		转义:  %HEXHEX，HEX表示一个十六进制数字[0-9A-F]或[0-9a-f]，通常采用大写，这两个HEX就表示一个US-ASCII字符代码，转义用于在URI内部插入保留字符及原本不支持的字符。
std::string CHttpURIHelper::utf82uri( const string &str, bool space_as_plus )
{
	static const char safe[]={
		/* 0 */
		0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 1, 1, 1, //-./
		1, 1, 1, 1, 1, 1, 1, 1,   1, 1, 1, 1, 0, 1, 0, 1, //01234567 89:;<=>?
		/* 64 */
		0, 1, 1, 1, 1, 1, 1, 1,   1, 1, 1, 1, 1, 1, 1, 1, //A..Z
		1, 1, 1, 1, 1, 1, 1, 1,   1, 1, 1, 0, 0, 0, 0, 1, //_
		0, 1, 1, 1, 1, 1, 1, 1,   1, 1, 1, 1, 1, 1, 1, 1, //a..z
		1, 1, 1, 1, 1, 1, 1, 1,   1, 1, 1, 0, 0, 0, 1, 0, //~
		/* 128 */
		0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0,
		/* 192 */
		0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0
	};

	string	out;

	char buf[8];
	unsigned char *ptr = (unsigned char *)str.c_str();

	out.reserve( strlen( (char *)ptr) );
	for( ; *ptr; ++ptr )
	{
		if ( !safe[*ptr] ) 
		{
			memset(buf, 0, 5);
			_snprintf_s(buf, 5, "%%%X", (*ptr));
			out.append(buf);  
		}
		else if( space_as_plus && *ptr == ' ' )
			out += '+';
		else
			out += *ptr;
	}

	return out;
}

std::string CHttpURIHelper::js_encodeURI( const wchar_t *ws )
{
	return utf82uri( ws2utf8(ws) );
}
