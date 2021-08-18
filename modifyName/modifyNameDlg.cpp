
// modifyNameDlg.cpp: 实现文件
//喜欢古典小说的
//欢迎关注 头条号： 古典小说
//        公众号： 古典小说网
//        喜马拉雅号：古典小说网
//        个人网站 www.gudianxiaoshuo.com
//
//csdn博客 ：           https://gudianxiaoshuo.blog.csdn.net/
//本文CSDN博客          

#include "pch.h"
#include "framework.h"
#include "modifyName.h"
#include "modifyNameDlg.h"
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
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CmodifyNameDlg 对话框



CmodifyNameDlg::CmodifyNameDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MODIFYNAME_DIALOG, pParent)
	, prefix_(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CmodifyNameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, prefix_);
	DDX_Control(pDX, IDC_COMBO1, extCom_);
	DDX_Control(pDX, IDC_MFCEDITBROWSE2, browserCtrl_);
}

BEGIN_MESSAGE_MAP(CmodifyNameDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CmodifyNameDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON2, &CmodifyNameDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CmodifyNameDlg::OnBnClickedButton1)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CmodifyNameDlg::OnCbnSelchangeCombo1)
	ON_EN_CHANGE(IDC_MFCEDITBROWSE2, &CmodifyNameDlg::OnEnChangeMfceditbrowse2)
	ON_EN_UPDATE(IDC_MFCEDITBROWSE2, &CmodifyNameDlg::OnUpdateMfceditbrowse2)
END_MESSAGE_MAP()

//-----------------------------------------------------------
//     
//  函数名称：FindFileInDir
//     
//  参    数：
//    - BOOL bSize                          是否判断文件大小
//     
//    - CString fileExtention               文件扩展名，不包括‘.’
//     
//    - CString filePath                    文件所在的父目录
//     
//    - std::vector<CString> &pageVector    保存指定文件的容器
//     
//  返    回：void
//     
//  函数作用：查找目录filePath下，扩展名为FindFileInDir的所有文件
//     
//  修改日期：2012年9月17日  By YuJian
// 
//-----------------------------------------------------------
void FindFileInDir(BOOL bSize, CString fileExtention, CString filePath, std::vector<CString>& pageVector)
{

	std::vector <CString> directoryPath;

	CString subfilePathtemp;
	CString subFilePath;

	WIN32_FIND_DATA fd;
	ZeroMemory(&fd, sizeof(WIN32_FIND_DATA));

	HANDLE hSearch;

	if (filePath.Right(1) != _T("\\"))
	{
		filePath += _T("\\");
	}

	filePath += _T("*");
	hSearch = ::FindFirstFile(filePath, &fd);

	if (INVALID_HANDLE_VALUE == hSearch)
	{
		AfxMessageBox(L"请正确选择文件夹");
		return;
	}

	subFilePath = filePath.Left(filePath.GetLength() - 1);
	if ((fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && !(fd.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM) && !(fd.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) && _tcscmp((const TCHAR*)&fd.cFileName, L".") && _tcscmp((const TCHAR*)&fd.cFileName, L"..") && _tcscmp((const TCHAR*)&fd.cFileName, L"RECYCLER") && _tcscmp((const TCHAR*)&fd.cFileName, L"System Volume Information"))   //文件夹
	{

		subfilePathtemp = subFilePath + fd.cFileName;;
		directoryPath.push_back(subfilePathtemp);//  将目录放大局部容器变量中

	}
	else {



		subfilePathtemp = fd.cFileName;
		int dotPosition = subfilePathtemp.ReverseFind(L'.');
		subfilePathtemp = subfilePathtemp.Right(subfilePathtemp.GetLength() - dotPosition - 1);

		if (subfilePathtemp.Compare(fileExtention) == 0)
		{
			//subfilePathtemp=subFilePath+fd.cFileName;
			//pageVector.push_back(subfilePathtemp); // 将所查到文件放入全局容器变量中， 这样遍历完所有文件夹后，所有的文件路径都存放在了全局容器中

			if (!bSize)
				pageVector.push_back(subFilePath+fd.cFileName);
			else
				if (fd.nFileSizeLow == 466 || fd.nFileSizeLow == 226)
					pageVector.push_back(fd.cFileName);
		}
	}



	BOOL bFinished = FALSE;


	while (!bFinished)
	{
		if (FindNextFile(hSearch, &fd))
		{
			if ((fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && !(fd.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM) && !(fd.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) && _tcscmp((const TCHAR*)&fd.cFileName, L".") && _tcscmp((const TCHAR*)&fd.cFileName, L"..") && _tcscmp((const TCHAR*)&fd.cFileName, L"RECYCLER") && _tcscmp((const TCHAR*)&fd.cFileName, L"System Volume Information"))   //文件夹
			{
				subfilePathtemp = subFilePath + fd.cFileName;;
				directoryPath.push_back(subfilePathtemp);

			}
			else {

				subfilePathtemp = fd.cFileName;
				int dotPosition = subfilePathtemp.ReverseFind(L'.');
				subfilePathtemp = subfilePathtemp.Right(subfilePathtemp.GetLength() - dotPosition - 1);

				if (subfilePathtemp.Compare(fileExtention) == 0)
				{
					pageVector.push_back(subFilePath + fd.cFileName);
					//if (!bSize)
					//	pageVector.push_back(fd.cFileName);
					//else
					//	if (fd.nFileSizeLow == 466 || fd.nFileSizeLow == 226)	 //闪电图的大小			
					//		pageVector.push_back(fd.cFileName);
				}
			}
		}
		else {

			if (GetLastError() == ERROR_NO_MORE_FILES) //正常结束
			{
				bFinished = TRUE;
			}
			else {

				bFinished = TRUE;
			}


		}
	}

	FindClose(hSearch); //关闭查找

	//for (int i = 0; i < directoryPath.size(); i++) //对每一个路径，递归调用
	//{
	//	FindFileInDir(bSize, fileExtention, directoryPath.at(i), pageVector);
	//}
}

// CmodifyNameDlg 消息处理程序

BOOL CmodifyNameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// TODO: 在此添加额外的初始化代码



	//browserCtrl_.
	TCHAR szPath[255];
	GetModuleFileName(NULL, szPath, 255);
	*(_tcsrchr(szPath, _T('\\')) + 1) = 0;
	dir_ = szPath;

	browserCtrl_.SetWindowTextW(dir_);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}


void CmodifyNameDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CmodifyNameDlg::OnPaint()
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
HCURSOR CmodifyNameDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CmodifyNameDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}
void CmodifyNameDlg::GetExtFiles(){
	if (pageVector_.empty())
	{

		FindFileInDir(false, extension_, dir_, pageVector_);
	}

}

void CmodifyNameDlg::OnBnClickedButton2()
{
	SetDlgItemText(IDC_RES, L"正在修改");
	UpdateData(true);
	// TODO: Add your control notification handler code here
	GetExtFiles();

	for (auto& it : pageVector_)
	{


		TCHAR drive[MAX_PATH] = L"";
		TCHAR dir[MAX_PATH] = L"";
		TCHAR fileName[MAX_PATH] = L"";
		TCHAR ext[MAX_PATH] = L"";
		_wsplitpath_s(it.GetBuffer(), drive, dir, fileName, ext);

		CString fileNameS = fileName;

		if (fileNameS.Find(prefix_) == -1)
		{
		
			auto temp = fileNameS;
			fileNameS = prefix_ +L" "+ temp;

			CString modified = drive + CString(dir) + fileNameS + ext;

			_wrename(it.GetBuffer(), modified.GetBuffer());
			it = modified;
		}
	}
	
	SetDlgItemText(IDC_RES, L"修改完毕");
}


void CmodifyNameDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	SetDlgItemText(IDC_RES, L"正在修改");
	GetExtFiles();

	for (auto& it : pageVector_)
	{
		auto itModified = it;
		bool bChanged = false;
		if (itModified.Find(L",") != -1)
		{
			itModified.Replace(L',', L' ');
			bChanged = true;
		}
		if (itModified.Find(L"○") != -1)
		{
			itModified.Replace(L'○', L' ');
			bChanged = true;
		}

		if (bChanged)
		{
			_wrename(it.GetBuffer(), itModified.GetBuffer());
			it = itModified;
		}

	}

	SetDlgItemText(IDC_RES, L"完成修改");
}


void CmodifyNameDlg::OnCbnSelchangeCombo1()
{
	// TODO: Add your control notification handler code here

	extCom_.GetLBText(extCom_.GetCurSel(), extension_);
	pageVector_.clear();
}


void CmodifyNameDlg::OnEnChangeMfceditbrowse2()
{
	 browserCtrl_.GetWindowTextW(dir_);

	 pageVector_.clear();
}


void CmodifyNameDlg::OnUpdateMfceditbrowse2()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.

	// TODO:  Add your control notification handler code here

	pageVector_.clear();
}
