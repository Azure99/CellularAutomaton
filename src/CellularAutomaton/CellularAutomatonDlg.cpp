
// CellularAutomatonDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "CellularAutomaton.h"
#include "CellularAutomatonDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCellularAutomatonDlg 对话框



CCellularAutomatonDlg::CCellularAutomatonDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CELLULARAUTOMATON_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCellularAutomatonDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCellularAutomatonDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_MENU_MAIN_NEWCA, &CCellularAutomatonDlg::OnMenuMainNewCA)
	ON_COMMAND(ID_MENU_MAIN_STOP, &CCellularAutomatonDlg::OnMenuMainStop)
	ON_COMMAND(ID_MENU_MAIN_RUN, &CCellularAutomatonDlg::OnMenuMainRun)
	ON_WM_TIMER()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_MENU_MAIN_SAVETOBMP, &CCellularAutomatonDlg::OnMenuMainSavetobmp)
	ON_COMMAND(ID_MENU_MAIN_LOADSTATUS, &CCellularAutomatonDlg::OnMenuMainLoadStatus)
	ON_COMMAND(ID_MENU_MAIN_SAVESTATUS, &CCellularAutomatonDlg::OnMenuMainSaveStatus)
END_MESSAGE_MAP()


// CCellularAutomatonDlg 消息处理程序

BOOL CCellularAutomatonDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	m_Menu_Main.LoadMenu(IDR_MENU_MAIN);
	SetMenu(&m_Menu_Main);
	
	RunOptions options;
	m_CA = CAFactory::Create(options);
	m_CA->FillArea();
	m_Drawer = new Drawer(GetDC());
	SkinH_Attach();
	SkinH_SetAero(1);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCellularAutomatonDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
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
		OnDrawCA();
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCellularAutomatonDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCellularAutomatonDlg::OnMenuMainNewCA()
{
	OnMenuMainStop();

	OptionsDlg dlg;
	INT_PTR res = dlg.DoModal();

	//取消
	if (res != 1)
	{
		return;
	}

	delete m_CA;

	RunOptions options = dlg.m_RunOptions;
	m_CA = CAFactory::Create(options);

	m_Interval = options.Interval;
	CRect clientRect;
	GetClientRect(&clientRect);
	m_Drawer->Clear(clientRect);


	OnDrawCA();

	// TODO: 在此添加命令处理程序代码
}

void CCellularAutomatonDlg::OnMenuMainRun()
{
	// TODO: 在此添加命令处理程序代码
	SetTimer(TIMER_DRAW, m_Interval, NULL);
}


void CCellularAutomatonDlg::OnMenuMainStop()
{
	// TODO: 在此添加命令处理程序代码
	KillTimer(TIMER_DRAW);
}


void CCellularAutomatonDlg::OnDrawCA()
{
	if (m_Drawer == nullptr)
	{
		return;
	}

	m_Drawer->DrawCell(m_CA->map, m_CA->Width, m_CA->Height);
}

void CCellularAutomatonDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent == TIMER_DRAW)
	{
		NextCAFrame();
	}
	CDialogEx::OnTimer(nIDEvent);
}

void CCellularAutomatonDlg::NextCAFrame()
{
	m_CA->NextFrame();
	//CString title;
	//title.Format(_T("CA - NowLive: %d - T: %d"), m_CA->NowLive, m_CA->Frame);
	//SetWindowText(title);
	OnDrawCA();
}

void CCellularAutomatonDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nFlags == MK_LBUTTON)
	{
		SetMouseCell(point.x, point.y, true);
	}
	else if (nFlags == MK_RBUTTON)
	{
		SetMouseCell(point.x, point.y, false);
	}
	CDialogEx::OnMouseMove(nFlags, point);
}

void CCellularAutomatonDlg::SetMouseCell(int mX, int mY, bool status)
{
	int x = mX / 4;
	int y = mY / 4;
	if (x >= 0 && x < m_CA->Width && y >= 0 && y < m_CA->Height)
	{
		m_CA->SetCell(x, y, status);
		m_Drawer->DrawOneCell(x, y, status);
	}
}

void CCellularAutomatonDlg::OnMenuMainSavetobmp()
{
	CString path;
	CString filter = _T("位图|*.bmp");
	CFileDialog dlg(FALSE, _T("bmp"), _T("image.bmp"), NULL, path);
	if (dlg.DoModal() != IDOK)
		return;

	KillTimer(TIMER_DRAW);

	path = dlg.m_ofn.lpstrFile;

	CRect cRect;
	GetClientRect(&cRect);
	int width = cRect.right - cRect.left;
	int height = cRect.bottom - cRect.top;

	CClientDC cDC(this);
	HDC hDC = CreateCompatibleDC(cDC);
	HBITMAP hbitmap = CreateCompatibleBitmap(cDC, width, height);
	HBITMAP hOldMap = (HBITMAP)SelectObject(hDC, hbitmap);
	BitBlt(hDC, 0, 0, width, height, cDC, 0, 0, SRCCOPY);
	CImage image;
	image.Attach(hbitmap);

	HRESULT hRe = image.Save(path);
	image.Detach();
	SelectObject(hDC, hOldMap);

	MessageBox(CString(_T("保存成功")));
	// TODO: 在此添加命令处理程序代码
}


void CCellularAutomatonDlg::OnMenuMainLoadStatus()
{
	KillTimer(TIMER_DRAW);
	m_CA = CASerializaer::DeSerialize();
	OnDrawCA();
	// TODO: 在此添加命令处理程序代码
}


void CCellularAutomatonDlg::OnMenuMainSaveStatus()
{
	KillTimer(TIMER_DRAW);
	CASerializaer::Serialize(m_CA);
	// TODO: 在此添加命令处理程序代码
}
