
// modifyNameDlg.h: 头文件
//

#pragma once
#include "afxwin.h"
#include "afxeditbrowsectrl.h"


// CmodifyNameDlg 对话框
class CmodifyNameDlg : public CDialogEx
{
// 构造
public:
	CmodifyNameDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MODIFYNAME_DIALOG };
#endif

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
	afx_msg void OnBnClickedOk();
	CString prefix_;    //前缀
	CString extension_; //扩展名
	CString dir_;

	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();

	std::vector<CString> pageVector_;
	void GetExtFiles();

	CString GetFiles();

	afx_msg void OnCbnSelchangeCombo1();


	CComboBox extCom_;
	CMFCEditBrowseCtrl browserCtrl_;
	afx_msg void OnEnChangeMfceditbrowse2();
	afx_msg void OnUpdateMfceditbrowse2();
};
