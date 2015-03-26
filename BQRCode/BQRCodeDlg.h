
// BQRCodeDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CBQRCodeDlg 对话框
class CBQRCodeDlg : public CDialogEx
{
// 构造
public:
	CBQRCodeDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_BQRCODE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	CString picturePath;// 图片路径
	CString qrcodePath;// 二维码的保存路径
	
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSelectfile();
	afx_msg void OnBnClickedGenerate();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedCancel();
	CEdit m_filePath;
};
