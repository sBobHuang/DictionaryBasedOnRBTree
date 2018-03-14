
// dictionaryDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "dictionary.h"
#include "dictionaryDlg.h"
#include "afxdialogex.h"
#include <fstream>
#include "RBTree.h"
#include<windows.h>
RB_Tree<CString, CString> dic;
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}



// CdictionaryDlg 对话框



CdictionaryDlg::CdictionaryDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CdictionaryDlg::IDD, pParent)
	, m_mean(_T(""))
	, m_Edit_Word(_T(""))
	, m_Edit_Mean(_T(""))
	, m_time(0)
	, m_num(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON);
}

void CdictionaryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Edit, m_word);
	DDX_Text(pDX, IDC_Show, m_mean);
	DDX_Text(pDX, IDC_Edit_Word, m_Edit_Word);
	DDX_Text(pDX, IDC_EDIT_Mean, m_Edit_Mean);
	DDX_Text(pDX, IDC_EDIT1, m_time);
	DDX_Text(pDX, IDC_EDIT3, m_num);
}

BEGIN_MESSAGE_MAP(CdictionaryDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_Insert_OK, &CdictionaryDlg::OnBnClickedInsertOk)
	ON_EN_CHANGE(IDC_Show, &CdictionaryDlg::OnEnChangeShow)
	ON_BN_CLICKED(IDC_Delete_Word, &CdictionaryDlg::OnBnClickedDeleteWord)
	ON_BN_CLICKED(IDC_Insert, &CdictionaryDlg::OnBnClickedInsert)
	ON_EN_CHANGE(IDC_Edit, &CdictionaryDlg::OnEnChangeEdit)
	ON_COMMAND(ID_32771, &CdictionaryDlg::On32771)
	ON_COMMAND(ID_32772, &CdictionaryDlg::On32772)
	ON_EN_CHANGE(IDC_EDIT1, &CdictionaryDlg::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT3, &CdictionaryDlg::OnEnChangeEdit3)
END_MESSAGE_MAP()


// CdictionaryDlg 消息处理程序
BOOL CdictionaryDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	// TODO:  在此添加额外的初始化代码
	ifstream in(L".\\word.txt");
	char s[2][105];
	CString st[2];
	while (in >> s[0] >> s[1]){
		for (int i = 0; i<2; i++)
		{
			int charLen = strlen(s[i]);
			int len = MultiByteToWideChar(CP_ACP, 0, s[i], charLen, NULL, 0);
			TCHAR *buf = new TCHAR[len + 1];
			MultiByteToWideChar(CP_ACP, 0, s[i], charLen, buf, len);
			buf[len] = '\0';
			st[i] = buf;
		}
		dic.Insert(st[0],st[1]);
		m_num++;
	}
	UpdateData(FALSE);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CdictionaryDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CdictionaryDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CdictionaryDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CdictionaryDlg::OnBnClickedInsertOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString s1;
	m_word.GetWindowText(s1);
	LARGE_INTEGER  large_interger;
	double dff;
	__int64  c1, c2;
	QueryPerformanceFrequency(&large_interger);
	dff = large_interger.QuadPart;
	QueryPerformanceCounter(&large_interger);
	c1 = large_interger.QuadPart;
	CString s2 = dic.query(s1);
	QueryPerformanceCounter(&large_interger);
	c2 = large_interger.QuadPart;
	UpdateData(TRUE);
	m_time = (c2 - c1) * 1000 / dff;
	UpdateData(FALSE);
	if (s2.IsEmpty()==0){
		UpdateData(TRUE);
		m_mean = s1;
		m_mean += L"\r\n";
		m_mean += s2;
		GetDlgItem(IDC_Edit)->SetWindowText(_T(""));
		UpdateData(FALSE);
	}
	else{
		UpdateData(TRUE);
		int l =min(11, s1.GetLength());
		m_mean = L" ";
		for (int i = 3; i < l; i++){
			CString s2 = dic.query(s1.Left(i));
			if (s2.IsEmpty()==0)
			{
				m_mean += L"您可能要找的是    ";
				m_mean += s1.Left(i);
				m_mean += L"  ";
				m_mean += s2;
				m_mean += L"\r\n";
			}
		}
		m_mean += L"\r\n";
		m_mean += L"你要找的不会是BobHuang吧!";
		m_mean += L"\r\n\r\n\r\n\r\n\r\n";
		m_mean += L"欢迎加他的QQ：603921454";
		m_mean += L"\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n";
		m_mean += L"强行勾搭很不要脸啊";
		UpdateData(FALSE);
	MessageBox(L"你所要的单词我这没有，看看是不是打错了");
	}
}


void CdictionaryDlg::OnEnChangeShow()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void CdictionaryDlg::OnBnClickedDeleteWord()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_Edit_Word.GetLength()){
		dic.Delete(m_Edit_Word);
		MessageBox(m_Edit_Word, L"单词已删除");
		m_num--;
		m_Edit_Word = L"";
		UpdateData(FALSE);
	}
}


void CdictionaryDlg::OnBnClickedInsert()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_Edit_Word.GetLength()){
		if (dic.query(m_Edit_Word))
			dic.Delete(m_Edit_Word);
		dic.Insert(m_Edit_Word, m_Edit_Mean);
		m_num++;
		MessageBox(m_Edit_Word, L"新单词已插入");
		m_Edit_Word = L"";
		m_Edit_Mean = L"";
		UpdateData(FALSE);
	}
}


void CdictionaryDlg::OnEnChangeEdit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CdictionaryDlg::On32771()
{
	CFileDialog dlg(TRUE);///TRUE为OPEN对话框，FALSE为SAVE AS对话框
	if (dlg.DoModal() == IDOK)
	{
		ifstream in(dlg.GetPathName());
		char s[2][105];
		CString st[2];
		while (in >> s[0] >> s[1]){
			for (int i = 0; i<2; i++)
			{
				int charLen = strlen(s[i]);
				int len = MultiByteToWideChar(CP_ACP, 0, s[i], charLen, NULL, 0);
				TCHAR *buf = new TCHAR[len + 1];
				MultiByteToWideChar(CP_ACP, 0, s[i], charLen, buf, len);
				buf[len] = '\0';
				st[i] = buf;
			}
			dic.Insert(st[0], st[1]);
		}
		MessageBox(L"插入完成");
	}
}

void CdictionaryDlg::On32772()
{
	// TODO:  在此添加命令处理程序代码
	if(MessageBox(L"您正在修改字典源文件", L"warning", MB_OKCANCEL)==1)
		dic.InOrderTraverse();
}


void CdictionaryDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CdictionaryDlg::OnEnChangeEdit3()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
