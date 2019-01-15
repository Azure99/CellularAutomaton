#pragma once
#include "RunOptions.h"

// OptionsDlg 对话框

class OptionsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(OptionsDlg)

public:
	OptionsDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~OptionsDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OPTIONS_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
private:
	void SetTips(CString tips);
public:
	
	CEdit m_Edit_UpperLine;
	CEdit m_Edit_LowerLine;
	CEdit m_Edit_LiveRate;
	CEdit m_Edit_DeadRate;
	CEdit m_Edit_Height;
	CEdit m_Edit_Width;
	afx_msg void OnBnClickedOk();
	CButton m_Check_Fill;
public:
	RunOptions m_RunOptions;
	CButton m_Radio_Classical;
	CButton m_Radio_Custom;
	
	CButton m_Radio_Custom2;
	CEdit m_Edit_Interval;
	CStatic m_Static_Tips;
	afx_msg void OnEnSetfocusEditWidth();
	afx_msg void OnEnSetfocusEditHeight();
	afx_msg void OnBnSetfocusCheckFill();
	afx_msg void OnBnSetfocusRadioClassical();
	afx_msg void OnBnSetfocusRadioCustom();
	afx_msg void OnBnSetfocusRadioCustom2();
	afx_msg void OnEnSetfocusEditUpperline();
	afx_msg void OnEnSetfocusEditLowerline();
	afx_msg void OnEnSetfocusEditLiverate();
	afx_msg void OnEnSetfocusEditDeadrate();
	afx_msg void OnEnSetfocusEditInterval();
	afx_msg void OnBnClickedRadioCustom();
	afx_msg void OnBnClickedRadioClassical();
	afx_msg void OnBnClickedRadioCustom2();
};
