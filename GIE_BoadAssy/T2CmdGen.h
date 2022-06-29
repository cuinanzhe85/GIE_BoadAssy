// T4CmdGen.h: interface for the T4CmdGen class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_T2CMDGEN_H__24771AD0_8948_4ECA_BA02_31987AF319BD__INCLUDED_)
#define AFX_T2CMDGEN_H__24771AD0_8948_4ECA_BA02_31987AF319BD__INCLUDED_

//#include "MLT2.h" // Test

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CT2CmdGen  
{
public:
	CT2CmdGen();
	CT2CmdGen(int h, int v);
	virtual ~CT2CmdGen();

public:
	static CString makeT2dataStrFromFile(CString pbdFilePath);
	static CString makeT2PatternStr(int nPixelType, CString dataStr, int width, int height);
	static CString makeT2FileStr(CString dataStr);

private:
	CString makeObjStr(int nPixelType, CString dataStr);
	CString makeSubStr(int nPixelType, CString dataStr, int idx);
	int makeStringArray(CString dataStr);
	double String2Float(LPCTSTR pStrNum,int base);


	CString Chess2AsciiHex(CString& szBits,int x, int y);
	CString makeFieldStr(CString dataStr);

private:
//	CMLT2App* m_pApp; // Test
//	LPFUSINGINFO lpFusingInfo; // Test

	int hResol;
	int vResol;
	CStringArray pbdData;
};

#endif // !defined(AFX_T2CMDGEN_H__24771AD0_8948_4ECA_BA02_31987AF319BD__INCLUDED_)
