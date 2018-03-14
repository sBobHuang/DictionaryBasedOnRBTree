
// dictionaryDlg.cpp : ʵ���ļ�
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}



// CdictionaryDlg �Ի���



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


// CdictionaryDlg ��Ϣ�������
BOOL CdictionaryDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
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
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CdictionaryDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
		// ʹͼ���ڹ����������о���
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
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CdictionaryDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CdictionaryDlg::OnBnClickedInsertOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
				m_mean += L"������Ҫ�ҵ���    ";
				m_mean += s1.Left(i);
				m_mean += L"  ";
				m_mean += s2;
				m_mean += L"\r\n";
			}
		}
		m_mean += L"\r\n";
		m_mean += L"��Ҫ�ҵĲ�����BobHuang��!";
		m_mean += L"\r\n\r\n\r\n\r\n\r\n";
		m_mean += L"��ӭ������QQ��603921454";
		m_mean += L"\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n";
		m_mean += L"ǿ�й���ܲ�Ҫ����";
		UpdateData(FALSE);
	MessageBox(L"����Ҫ�ĵ�������û�У������ǲ��Ǵ����");
	}
}


void CdictionaryDlg::OnEnChangeShow()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

void CdictionaryDlg::OnBnClickedDeleteWord()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (m_Edit_Word.GetLength()){
		dic.Delete(m_Edit_Word);
		MessageBox(m_Edit_Word, L"������ɾ��");
		m_num--;
		m_Edit_Word = L"";
		UpdateData(FALSE);
	}
}


void CdictionaryDlg::OnBnClickedInsert()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (m_Edit_Word.GetLength()){
		if (dic.query(m_Edit_Word))
			dic.Delete(m_Edit_Word);
		dic.Insert(m_Edit_Word, m_Edit_Mean);
		m_num++;
		MessageBox(m_Edit_Word, L"�µ����Ѳ���");
		m_Edit_Word = L"";
		m_Edit_Mean = L"";
		UpdateData(FALSE);
	}
}


void CdictionaryDlg::OnEnChangeEdit()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CdictionaryDlg::On32771()
{
	CFileDialog dlg(TRUE);///TRUEΪOPEN�Ի���FALSEΪSAVE AS�Ի���
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
		MessageBox(L"�������");
	}
}

void CdictionaryDlg::On32772()
{
	// TODO:  �ڴ���������������
	if(MessageBox(L"�������޸��ֵ�Դ�ļ�", L"warning", MB_OKCANCEL)==1)
		dic.InOrderTraverse();
}


void CdictionaryDlg::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CdictionaryDlg::OnEnChangeEdit3()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
