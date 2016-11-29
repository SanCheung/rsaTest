#pragma once

// RSA���㷨�漰����������n��e1��e2�� ����
// ���У�n������������p��q�Ļ���n�Ķ����Ʊ�ʾʱ��ռ�õ�λ����������ν����Կ����
// e1��e2��һ����ص�ֵ��e1��������ȡ����Ҫ��e1��(p-1)*(q-1)���ʣ�
// ��ѡ��e2��Ҫ��(e2*e1)mod((p-1)*(q-1))=1�� ����
// (n��e1),(n��e2)������Կ�ԡ� ����

// RSA�ӽ��ܵ��㷨��ȫ��ͬ,
// ��AΪ���ģ�BΪ���ģ���	A=B^e1 mod n��B=A^e2 mod n�� ����
//  e1��e2���Ի���ʹ�ã����� A=B^e2 mod n��B=A^e1 mod n;
#include "StringInt.h"

class CRSAProcess
{
public:
	CRSAProcess(void);
	virtual ~CRSAProcess(void);

	void	Test();

//protected:
	CStringInt	GetALargePrime( int nLength );
	CStringInt	GetCoPrime( CStringInt p );
	CStringInt	GetD( CStringInt e, CStringInt m );
	CStringInt	GetD2( CStringInt e, CStringInt m );

	CStringInt	Cryp( CStringInt d, CStringInt n, CStringInt e );
};
