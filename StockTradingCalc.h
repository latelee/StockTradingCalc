// StockTradingCalc.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "resource.h"		// ������


// CStockTradingCalcApp:
// �йش����ʵ�֣������ StockTradingCalc.cpp
//

class CStockTradingCalcApp : public CWinApp
{
public:
	CStockTradingCalcApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CStockTradingCalcApp theApp;
