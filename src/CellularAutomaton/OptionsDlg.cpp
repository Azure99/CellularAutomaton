// OptionsDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "CellularAutomaton.h"
#include "OptionsDlg.h"
#include "afxdialogex.h"


// OptionsDlg 对话框

IMPLEMENT_DYNAMIC(OptionsDlg, CDialogEx)

OptionsDlg::OptionsDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_OPTIONS_DIALOG, pParent)
{

}

OptionsDlg::~OptionsDlg()
{
}

BOOL OptionsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_Radio_Classical.SetCheck(1);
	m_Edit_UpperLine.SetWindowTextW(_T("6"));
	m_Edit_LowerLine.SetWindowTextW(_T("2"));
	m_Edit_LiveRate.SetWindowTextW(_T("100"));
	m_Edit_DeadRate.SetWindowTextW(_T("100"));
	m_Edit_Height.SetWindowTextW(_T("200"));
	m_Edit_Width.SetWindowTextW(_T("200"));
	m_Edit_Interval.SetWindowTextW(_T("100"));
	m_Check_Fill.SetCheck(0);

	return TRUE;
}

void OptionsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RADIO_CUSTOM, m_Radio_Custom);
	DDX_Control(pDX, IDC_EDIT_UPPERLINE, m_Edit_UpperLine);
	DDX_Control(pDX, IDC_EDIT_LOWERLINE, m_Edit_LowerLine);
	DDX_Control(pDX, IDC_EDIT_LIVERATE, m_Edit_LiveRate);
	DDX_Control(pDX, IDC_EDIT_DEADRATE, m_Edit_DeadRate);
	DDX_Control(pDX, IDC_EDIT_HEIGHT, m_Edit_Height);
	DDX_Control(pDX, IDC_EDIT_WIDTH, m_Edit_Width);
	DDX_Control(pDX, IDC_CHECK_FILL, m_Check_Fill);
	DDX_Control(pDX, IDC_RADIO_CLASSICAL, m_Radio_Classical);
	DDX_Control(pDX, IDC_RADIO_CUSTOM2, m_Radio_Custom2);
	DDX_Control(pDX, IDC_EDIT_INTERVAL, m_Edit_Interval);
	DDX_Control(pDX, IDC_STATIC_TIPS, m_Static_Tips);
}


BEGIN_MESSAGE_MAP(OptionsDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &OptionsDlg::OnBnClickedOk)
	ON_EN_SETFOCUS(IDC_EDIT_WIDTH, &OptionsDlg::OnEnSetfocusEditWidth)
	ON_EN_SETFOCUS(IDC_EDIT_HEIGHT, &OptionsDlg::OnEnSetfocusEditHeight)
	ON_BN_SETFOCUS(IDC_CHECK_FILL, &OptionsDlg::OnBnSetfocusCheckFill)
	ON_BN_SETFOCUS(IDC_RADIO_CLASSICAL, &OptionsDlg::OnBnSetfocusRadioClassical)
	ON_BN_SETFOCUS(IDC_RADIO_CUSTOM, &OptionsDlg::OnBnSetfocusRadioCustom)
	ON_BN_SETFOCUS(IDC_RADIO_CUSTOM2, &OptionsDlg::OnBnSetfocusRadioCustom2)
	ON_EN_SETFOCUS(IDC_EDIT_UPPERLINE, &OptionsDlg::OnEnSetfocusEditUpperline)
	ON_EN_SETFOCUS(IDC_EDIT_LOWERLINE, &OptionsDlg::OnEnSetfocusEditLowerline)
	ON_EN_SETFOCUS(IDC_EDIT_LIVERATE, &OptionsDlg::OnEnSetfocusEditLiverate)
	ON_EN_SETFOCUS(IDC_EDIT_DEADRATE, &OptionsDlg::OnEnSetfocusEditDeadrate)
	ON_EN_SETFOCUS(IDC_EDIT_INTERVAL, &OptionsDlg::OnEnSetfocusEditInterval)
	ON_BN_CLICKED(IDC_RADIO_CUSTOM, &OptionsDlg::OnBnClickedRadioCustom)
	ON_BN_CLICKED(IDC_RADIO_CLASSICAL, &OptionsDlg::OnBnClickedRadioClassical)
	ON_BN_CLICKED(IDC_RADIO_CUSTOM2, &OptionsDlg::OnBnClickedRadioCustom2)
END_MESSAGE_MAP()


// OptionsDlg 消息处理程序


void OptionsDlg::OnBnClickedOk()
{
	CString str;

	m_Edit_DeadRate.GetWindowTextW(str);
	int deadRate = _ttoi(str);

	bool fillMap = m_Check_Fill.GetCheck();

	m_Edit_Height.GetWindowTextW(str);
	int height = _ttoi(str);

	m_Edit_LiveRate.GetWindowTextW(str);
	int liveRate = _ttoi(str);

	m_Edit_LowerLine.GetWindowTextW(str);
	int lowerLine = _ttoi(str);

	m_Edit_UpperLine.GetWindowTextW(str);
	int upperLine = _ttoi(str);

	m_Edit_Width.GetWindowTextW(str);
	int width = _ttoi(str);

	m_Edit_Interval.GetWindowTextW(str);
	int interval = _ttoi(str);

	int rule = CA_CLASSICAL;
	if (m_Radio_Custom.GetCheck())
	{
		rule = CA_CUSTOM;
	}
	else if (m_Radio_Classical.GetCheck())
	{
		rule = CA_CLASSICAL;
	}
	else if (m_Radio_Custom2.GetCheck())
	{
		rule = CA_CUSTOM2;
	}

	m_RunOptions.DeadRate = deadRate;
	m_RunOptions.FillMap = fillMap;
	m_RunOptions.Height = height;
	m_RunOptions.LiveRate = liveRate;
	m_RunOptions.LowerLine = lowerLine;
	m_RunOptions.Rule = rule;
	m_RunOptions.UpperLine = upperLine;
	m_RunOptions.Width = width;
	m_RunOptions.Interval = interval;

	if (deadRate < 0 || deadRate > 100)
	{
		MessageBox(_T("死亡率必须大于等于0且小于等于100"));
		return;
	}

	if (height < 1 || height > 400)
	{
		MessageBox(_T("高度必须大于0且小于400"));
		return;
	}

	if (liveRate < 0 || liveRate > 100)
	{
		MessageBox(_T("出生率必须大于等于0且小于等于100"));
		return;
	}

	if (lowerLine < 0 || lowerLine > 8)
	{
		MessageBox(_T("下限必须大于等于0且小于等于8"));
		return;
	}

	if (upperLine < 0 || upperLine > 8)
	{
		MessageBox(_T("上限必须大于等于0且小于等于8"));
		return;
	}

	if (lowerLine > upperLine)
	{
		MessageBox(_T("下限不能大于上限"));
		return;
	}

	if (width < 0 || width > 400)
	{
		MessageBox(_T("宽度必须大于0且小于400"));
		return;
	}

	if (interval <= 0 || interval > 10000)
	{
		MessageBox(_T("帧间隔必须大于0且小于10000"));
		return;
	}

	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void OptionsDlg::OnEnSetfocusEditWidth()
{
	SetTips(_T("地图宽度"));
	// TODO: 在此添加控件通知处理程序代码
}


void OptionsDlg::OnEnSetfocusEditHeight()
{
	SetTips(_T("地图高度"));
	// TODO: 在此添加控件通知处理程序代码
}


void OptionsDlg::OnBnSetfocusCheckFill()
{
	SetTips(_T("是否填满地图"));
	// TODO: 在此添加控件通知处理程序代码
}


void OptionsDlg::OnBnSetfocusRadioClassical()
{
	SetTips(_T("最经典的规则"));
	// TODO: 在此添加控件通知处理程序代码
}


void OptionsDlg::OnBnSetfocusRadioCustom()
{
	SetTips(_T("低于下限活, 高于上线死, 中间不变"));
	// TODO: 在此添加控件通知处理程序代码
}


void OptionsDlg::OnBnSetfocusRadioCustom2()
{
	SetTips(_T("低于下限死, 高于上限死, 中间活"));
	// TODO: 在此添加控件通知处理程序代码
}


void OptionsDlg::OnEnSetfocusEditUpperline()
{
	SetTips(_T("死亡条件上限(细胞数)"));
	// TODO: 在此添加控件通知处理程序代码
}


void OptionsDlg::OnEnSetfocusEditLowerline()
{
	SetTips(_T("出生/死亡条件下限(细胞数)"));
	// TODO: 在此添加控件通知处理程序代码
}


void OptionsDlg::OnEnSetfocusEditLiverate()
{
	SetTips(_T("出生率: 当触发出生条件时可以出生的概率"));
	// TODO: 在此添加控件通知处理程序代码
}


void OptionsDlg::OnEnSetfocusEditDeadrate()
{
	SetTips(_T("死亡率: 当触发死亡条件时会死亡的概率"));
	// TODO: 在此添加控件通知处理程序代码
}


void OptionsDlg::OnEnSetfocusEditInterval()
{
	SetTips(_T("每帧的间隔, 越小越快"));
	// TODO: 在此添加控件通知处理程序代码
}

void OptionsDlg::SetTips(CString tips)
{
	m_Static_Tips.SetWindowTextW(tips);
}

void OptionsDlg::OnBnClickedRadioCustom()
{
	SetTips(_T("低于下限活, 高于上线死, 中间不变"));
	m_Radio_Classical.SetCheck(0);
	m_Radio_Custom2.SetCheck(0);
	// TODO: 在此添加控件通知处理程序代码
}


void OptionsDlg::OnBnClickedRadioClassical()
{
	SetTips(_T("最经典的规则"));
	m_Radio_Custom.SetCheck(0);
	m_Radio_Custom2.SetCheck(0);
	// TODO: 在此添加控件通知处理程序代码
}


void OptionsDlg::OnBnClickedRadioCustom2()
{
	SetTips(_T("低于下限死, 高于上限死, 中间活"));
	m_Radio_Classical.SetCheck(0);
	m_Radio_Custom.SetCheck(0);
	// TODO: 在此添加控件通知处理程序代码
}
