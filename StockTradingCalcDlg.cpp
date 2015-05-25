// StockTradingCalcDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "StockTradingCalc.h"
#include "StockTradingCalcDlg.h"
#include ".\stocktradingcalcdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CStockTradingCalcDlg �Ի���



CStockTradingCalcDlg::CStockTradingCalcDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStockTradingCalcDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CStockTradingCalcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CStockTradingCalcDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
    ON_CBN_SELCHANGE(IDC_COMBO1, OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// CStockTradingCalcDlg ��Ϣ�������

BOOL CStockTradingCalcDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��\������...\���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
    ((CComboBox *)GetDlgItem(IDC_COMBO1))->SetCurSel(0);
    m_nSockType = 0;

    CString strTemp;

    strTemp.Format("0.3");
    GetDlgItem(IDC_EDIT3)->SetWindowText(strTemp.GetBuffer());

    strTemp.Format("0.1");
    GetDlgItem(IDC_EDIT6)->SetWindowText(strTemp.GetBuffer());

	return TRUE;  // ���������˿ؼ��Ľ��㣬���򷵻� TRUE
}

void CStockTradingCalcDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CStockTradingCalcDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
HCURSOR CStockTradingCalcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CStockTradingCalcDlg::Calc(float fltPrice, int iCount,
                                float& fltTotalMoney, float& fltBrokerage,
                                float& fltTransferFee, float& fltStampFee)
{
    // Ӷ���ʡ�ӡ��˰��
    float fltBrokerageRate = 0.0;
    float fltStampRate = 0.0;

    CString strTemp;

    GetDlgItem(IDC_EDIT3)->GetWindowText(strTemp);
    fltBrokerageRate = (float)atof(strTemp.GetBuffer());

    GetDlgItem(IDC_EDIT6)->GetWindowText(strTemp);
    fltStampRate = (float)atof(strTemp.GetBuffer());

    fltTotalMoney = fltPrice * iCount;  // �ɽ����

    // Ӷ��
    fltBrokerage = (float)(fltTotalMoney * fltBrokerageRate / 100.0);

    // Ӷ�����Ϊ5Ԫ
    if (fltBrokerage > -0.0000001 && fltBrokerage < 0.0000001)
        fltBrokerage = 0.0;
    else if (fltBrokerage < 5.0)
        fltBrokerage = 5.0;

    // ������
    // ע�����в���Ҫ
    if (m_nSockType == 0)
        fltTransferFee = (float)(iCount * 0.0006);
    else if (m_nSockType == 1)
        fltTransferFee = 0.00;
    else
        // will not go here
        ;

    // ӡ��˰
    // ���벻��Ҫ
    fltStampFee = (float)(fltTotalMoney * fltStampRate / 100.0);
}

void CStockTradingCalcDlg::OnBnClickedButton1()
{
    // TODO: Add your control notification handler code here

    // ���������۸�����
    float fltPriceBuy = 0.0;
    float fltPriceSell = 0.0;
    int iCountBuy = 0;
    int iCountSell = 0;

    // �ɽ����
    float fltTotalMoneyBuy = 0.0;
    float fltTotalMoneySell = 0.0;

    // Ӷ��
    float fltBrokerageBuy = 0.0;
    float fltBrokerageSell = 0.0;

    // ������
    float fltTransferFeesBuy = 0.0;
    float fltTransferFeesSell = 0.0;

    // ӡ��˰
    float fltStampMoneySell = 0.0;

    // ˰�Ѻϼ�
    float fltCostMoneyBuy = 0.0;
    float fltCostMoneySell = 0.0;

    // ӯ�����
    float fltLastMoney = 0.0;
    float fltLastRate = 0.0;

    // �ɱ���
    float fltCostPrice = 0.0;

    CString strTemp;

    // ����
    GetDlgItem(IDC_EDIT1)->GetWindowText(strTemp);
    fltPriceBuy = (float)atof(strTemp.GetBuffer());
    GetDlgItem(IDC_EDIT4)->GetWindowText(strTemp);
    iCountBuy = atoi(strTemp.GetBuffer());

    GetDlgItem(IDC_EDIT2)->GetWindowText(strTemp);
    fltPriceSell = (float)atof(strTemp.GetBuffer());
    GetDlgItem(IDC_EDIT5)->GetWindowText(strTemp);
    iCountSell = atoi(strTemp.GetBuffer());

    // �������
    float fltNotUsed;
    Calc(fltPriceBuy, iCountBuy, fltTotalMoneyBuy, fltBrokerageBuy, fltTransferFeesBuy, fltNotUsed);
    
    fltCostMoneyBuy = fltBrokerageBuy + fltTransferFeesBuy;

    // �ɱ���
    if (iCountBuy == 0)
        fltCostPrice = 0.0;
    else
        fltCostPrice = (fltTotalMoneyBuy + fltCostMoneyBuy) / iCountBuy;

    // ��ʾ
    strTemp.Format("%.3f", fltCostPrice);
    GetDlgItem(IDC_EDIT7)->SetWindowText(strTemp);
    strTemp.Format("%.2f", fltTotalMoneyBuy);
    GetDlgItem(IDC_EDIT8)->SetWindowText(strTemp);
    strTemp.Format("%.2f", fltBrokerageBuy);
    GetDlgItem(IDC_EDIT9)->SetWindowText(strTemp);
    strTemp.Format("%.2f", fltTransferFeesBuy);
    GetDlgItem(IDC_EDIT10)->SetWindowText(strTemp);
    strTemp.Format("%.2f", fltCostMoneyBuy);
    GetDlgItem(IDC_EDIT11)->SetWindowText(strTemp);
    strTemp.Format("%.2f", fltTotalMoneyBuy + fltCostMoneyBuy);
    GetDlgItem(IDC_EDIT17)->SetWindowText(strTemp);
    
    /////////////////////////////////////////////////
    // ��������
    Calc(fltPriceSell, iCountSell, fltTotalMoneySell, fltBrokerageSell, fltTransferFeesSell, fltStampMoneySell);
    
    fltCostMoneySell = fltBrokerageSell + fltTransferFeesSell + fltStampMoneySell;

    // ��ʾ
    strTemp.Format("%.2f", fltTotalMoneySell);
    GetDlgItem(IDC_EDIT12)->SetWindowText(strTemp);
    strTemp.Format("%.2f", fltBrokerageSell);
    GetDlgItem(IDC_EDIT13)->SetWindowText(strTemp);
    strTemp.Format("%.2f", fltTransferFeesSell);
    GetDlgItem(IDC_EDIT14)->SetWindowText(strTemp);
    strTemp.Format("%.2f", fltStampMoneySell);
    GetDlgItem(IDC_EDIT15)->SetWindowText(strTemp);
    strTemp.Format("%.2f", fltCostMoneySell);
    GetDlgItem(IDC_EDIT16)->SetWindowText(strTemp);
    strTemp.Format("%.2f", fltTotalMoneySell - fltCostMoneySell);
    GetDlgItem(IDC_EDIT18)->SetWindowText(strTemp);

    // ӯ��
    // �����������ټ���һ�γɱ�
    Calc(fltPriceBuy, iCountSell, fltTotalMoneyBuy, fltBrokerageBuy, fltTransferFeesBuy, fltNotUsed);
    fltCostMoneyBuy = fltBrokerageBuy + fltTransferFeesBuy;

    fltLastMoney = (fltTotalMoneySell - fltCostMoneySell) - (fltTotalMoneyBuy + fltCostMoneyBuy);

    if (fltTotalMoneyBuy > -0.0000001 && fltTotalMoneyBuy < 0.0000001)
        fltLastRate = 0;
    else
        fltLastRate = (float)(fltLastMoney / fltTotalMoneyBuy * 100.0);

    strTemp.Format("%.2f", fltLastMoney);
    GetDlgItem(IDC_EDIT19)->SetWindowText(strTemp);

    strTemp.Format("%.2f", fltLastRate);
    GetDlgItem(IDC_EDIT20)->SetWindowText(strTemp);
}

void CStockTradingCalcDlg::OnCbnSelchangeCombo1()
{
    // TODO: Add your control notification handler code here
    m_nSockType =((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();
}
