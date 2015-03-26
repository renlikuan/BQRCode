
// BQRCodeDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CBQRCodeDlg �Ի���
class CBQRCodeDlg : public CDialogEx
{
// ����
public:
	CBQRCodeDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_BQRCODE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	CString picturePath;// ͼƬ·��
	CString qrcodePath;// ��ά��ı���·��
	
	// ���ɵ���Ϣӳ�亯��
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
