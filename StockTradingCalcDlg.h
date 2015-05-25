// StockTradingCalcDlg.h : ͷ�ļ�
//

#pragma once


// CStockTradingCalcDlg �Ի���
class CStockTradingCalcDlg : public CDialog
{
// ����
public:
	CStockTradingCalcDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_STOCKTRADINGCALC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
    int m_nSockType;    // ֤ȯ���� 0����A  1����A
public:
    afx_msg void OnCbnSelchangeCombo1();
};
