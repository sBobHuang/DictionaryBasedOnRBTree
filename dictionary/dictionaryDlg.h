
// dictionaryDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
// CdictionaryDlg 对话框
class CdictionaryDlg : public CDialogEx
{
// 构造
public:
	CdictionaryDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_DICTIONARY_DIALOG };

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
	CEdit m_word;
	afx_msg void OnBnClickedInsertOk();
	afx_msg void OnEnChangeShow();
	CString m_mean;
	CString m_Edit_Word;
	afx_msg void OnBnClickedDeleteWord();
	CString m_Edit_Mean;
	afx_msg void OnBnClickedInsert();
	afx_msg void OnEnChangeEdit();
	afx_msg void On32771();
	afx_msg void On32772();
	afx_msg void OnEnChangeEdit1();
	double m_time;
	int m_num;
	afx_msg void OnEnChangeEdit3();
};
