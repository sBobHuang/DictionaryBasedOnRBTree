
// dictionaryDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
// CdictionaryDlg �Ի���
class CdictionaryDlg : public CDialogEx
{
// ����
public:
	CdictionaryDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DICTIONARY_DIALOG };

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
