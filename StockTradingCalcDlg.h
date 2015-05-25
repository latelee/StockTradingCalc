// StockTradingCalcDlg.h : 头文件
//

#pragma once


// CStockTradingCalcDlg 对话框
class CStockTradingCalcDlg : public CDialog
{
// 构造
public:
	CStockTradingCalcDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_STOCKTRADINGCALC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedButton1();

public:
    void Calc(float fltPrice, int iCount, float& fltTotalMoney, float& fltBrokerage, float& fltTransferFee, float& fltStampFee);
private:
    int m_nSockType;    // 证券类型 0：沪A  1：深A
public:
    afx_msg void OnCbnSelchangeCombo1();
};
