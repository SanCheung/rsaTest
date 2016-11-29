#pragma once

// RSA的算法涉及三个参数，n、e1、e2。 　　
// 其中，n是两个大质数p、q的积，n的二进制表示时所占用的位数，就是所谓的密钥长度
// e1和e2是一对相关的值，e1可以任意取，但要求e1与(p-1)*(q-1)互质；
// 再选择e2，要求(e2*e1)mod((p-1)*(q-1))=1。 　　
// (n及e1),(n及e2)就是密钥对。 　　

// RSA加解密的算法完全相同,
// 设A为明文，B为密文，则：	A=B^e1 mod n；B=A^e2 mod n； 　　
//  e1和e2可以互换使用，即： A=B^e2 mod n；B=A^e1 mod n;
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
