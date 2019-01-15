
// CellularAutomatonDlg.h: 头文件
//

#pragma once
#include "OptionsDlg.h"
#include "BaseCA.h"
#include "CAFactory.h"
#include "Drawer.h"
#include "RunOptions.h"
#include "CASerializaer.h"

// CCellularAutomatonDlg 对话框
class CCellularAutomatonDlg : public CDialogEx
{
// 构造
public:
	CCellularAutomatonDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CELLULARAUTOMATON_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	void OnDrawCA();
	DECLARE_MESSAGE_MAP()
private:
	CMenu m_Menu_Main;
	Drawer* m_Drawer;
	BaseCA* m_CA;
	int m_Interval = 100;
private:
	void NextCAFrame();
	void SetMouseCell(int mX, int mY, bool status);
public:
	afx_msg void OnMenuMainNewCA();
	afx_msg void OnMenuMainStop();
	afx_msg void OnMenuMainRun();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
private:
	const int TIMER_DRAW = 1;
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMenuMainSavetobmp();
	afx_msg void OnMenuMainLoadStatus();
	afx_msg void OnMenuMainSaveStatus();
};
