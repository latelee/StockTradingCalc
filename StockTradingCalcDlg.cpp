// StockTradingCalcDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "StockTradingCalc.h"
#include "StockTradingCalcDlg.h"
#include ".\stocktradingcalcdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CStockTradingCalcDlg 对话框



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


// CStockTradingCalcDlg 消息处理程序

BOOL CStockTradingCalcDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将\“关于...\”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
    ((CComboBox *)GetDlgItem(IDC_COMBO1))->SetCurSel(0);
    m_nSockType = 0;

    CString strTemp;

    strTemp.Format("0.3");
    GetDlgItem(IDC_EDIT3)->SetWindowText(strTemp.GetBuffer());

    strTemp.Format("0.1");
    GetDlgItem(IDC_EDIT6)->SetWindowText(strTemp.GetBuffer());

	return TRUE;  // 除非设置了控件的焦点，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CStockTradingCalcDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
HCURSOR CStockTradingCalcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CStockTradingCalcDlg::Calc(float fltPrice, int iCount,
                                float& fltTotalMoney, float& fltBrokerage,
                                float& fltTransferFee, float& fltStampFee)
{
    // 佣金率、印花税率
    float fltBrokerageRate = 0.0;
    float fltStampRate = 0.0;

    CString strTemp;

    GetDlgItem(IDC_EDIT3)->GetWindowText(strTemp);
    fltBrokerageRate = (float)atof(strTemp.GetBuffer());

    GetDlgItem(IDC_EDIT6)->GetWindowText(strTemp);
    fltStampRate = (float)atof(strTemp.GetBuffer());

    fltTotalMoney = fltPrice * iCount;  // 成交金额

    // 佣金
    fltBrokerage = (float)(fltTotalMoney * fltBrokerageRate / 100.0);

    // 佣金最低为5元
    if (fltBrokerage > -0.0000001 && fltBrokerage < 0.0000001)
        fltBrokerage = 0.0;
    else if (fltBrokerage < 5.0)
        fltBrokerage = 5.0;

    // 过户费
    // 注：深市不需要
    if (m_nSockType == 0)
        fltTransferFee = (float)(iCount * 0.0006);
    else if (m_nSockType == 1)
        fltTransferFee = 0.00;
    else
        // will not go here
        ;

    // 印花税
    // 买入不需要
    fltStampFee = (float)(fltTotalMoney * fltStampRate / 100.0);
}

void CStockTradingCalcDlg::OnBnClickedButton1()
{
    // TODO: Add your control notification handler code here

    // 买入卖出价格、数量
    float fltPriceBuy = 0.0;
    float fltPriceSell = 0.0;
    int iCountBuy = 0;
    int iCountSell = 0;

    // 成交金额
    float fltTotalMoneyBuy = 0.0;
    float fltTotalMoneySell = 0.0;

    // 佣金
    float fltBrokerageBuy = 0.0;
    float fltBrokerageSell = 0.0;

    // 过户费
    float fltTransferFeesBuy = 0.0;
    float fltTransferFeesSell = 0.0;

    // 印花税
    float fltStampMoneySell = 0.0;

    // 税费合计
    float fltCostMoneyBuy = 0.0;
    float fltCostMoneySell = 0.0;

    // 盈亏金额
    float fltLastMoney = 0.0;
    float fltLastRate = 0.0;

    // 成本价
    float fltCostPrice = 0.0;

    CString strTemp;

    // 输入
    GetDlgItem(IDC_EDIT1)->GetWindowText(strTemp);
    fltPriceBuy = (float)atof(strTemp.GetBuffer());
    GetDlgItem(IDC_EDIT4)->GetWindowText(strTemp);
    iCountBuy = atoi(strTemp.GetBuffer());

    GetDlgItem(IDC_EDIT2)->GetWindowText(strTemp);
    fltPriceSell = (float)atof(strTemp.GetBuffer());
    GetDlgItem(IDC_EDIT5)->GetWindowText(strTemp);
    iCountSell = atoi(strTemp.GetBuffer());

    // 买入计算
    float fltNotUsed;
    Calc(fltPriceBuy, iCountBuy, fltTotalMoneyBuy, fltBrokerageBuy, fltTransferFeesBuy, fltNotUsed);
    
    fltCostMoneyBuy = fltBrokerageBuy + fltTransferFeesBuy;

    // 成本价
    if (iCountBuy == 0)
        fltCostPrice = 0.0;
    else
        fltCostPrice = (fltTotalMoneyBuy + fltCostMoneyBuy) / iCountBuy;

    // 显示
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
    // 卖出计算
    Calc(fltPriceSell, iCountSell, fltTotalMoneySell, fltBrokerageSell, fltTransferFeesSell, fltStampMoneySell);
    
    fltCostMoneySell = fltBrokerageSell + fltTransferFeesSell + fltStampMoneySell;

    // 显示
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

    // 盈亏
    // 以卖出数量再计算一次成本
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
