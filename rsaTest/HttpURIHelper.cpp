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

//HTTP URI�����
//	�ַ����� 
//	����RFC3986 2�淶��HTTP URI��������ֵ�US-ASCII�ַ����Ӽ������Էֳɱ�����δ������ת���⼸�࣬
//	ÿ���ȫ���ַ��б�����
//		����:  : / ? # [ ] @ ! $ & '( ) * + ,; =��18����һ������URI�����ָ�����
//		δ����:  a-z A-Z 0-9 - . _ ~��66����һ�����ڲ��������ݡ�
//		ת��:  %HEXHEX��HEX��ʾһ��ʮ����������[0-9A-F]��[0-9a-f]��ͨ�����ô�д��������HEX�ͱ�ʾһ��US-ASCII�ַ����룬ת��������URI�ڲ����뱣���ַ���ԭ����֧�ֵ��ַ���
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
