
// BQRCodeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BQRCode.h"
#include "BQRCodeDlg.h"
#include "afxdialogex.h"
#include "RSCoder.h"
#include "CvvImage.h"
#include "Img2Code.h"
#include "QRCodeProcess.h"

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


// CBQRCodeDlg 对话框



CBQRCodeDlg::CBQRCodeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBQRCodeDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBQRCodeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FILEPATH, m_filePath);
	DDX_Control(pDX, IDC_SAVEPATH, m_savePath);
	DDX_Control(pDX, IDC_PROGRESS, m_progress);
}

BEGIN_MESSAGE_MAP(CBQRCodeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDCANCEL, &CBQRCodeDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_SELECTFILE, &CBQRCodeDlg::OnBnClickedSelectfile)
	ON_BN_CLICKED(IDC_GENERATE, &CBQRCodeDlg::OnBnClickedGenerate)
	ON_BN_CLICKED(IDC_SAVE, &CBQRCodeDlg::OnBnClickedSave)
	ON_BN_CLICKED(IDC_SELECTSAVE, &CBQRCodeDlg::OnBnClickedSelectsave)
END_MESSAGE_MAP()


// CBQRCodeDlg 消息处理程序

BOOL CBQRCodeDlg::OnInitDialog()
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
	// 进度条
	m_progress.SetRange(0,100);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CBQRCodeDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CBQRCodeDlg::OnPaint()
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
HCURSOR CBQRCodeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


/*选择文件按钮*/
void CBQRCodeDlg::OnBnClickedSelectfile()
{

	// 过滤器
	static TCHAR BASED_CODE szFilter[] = _T("位图(*.bmp)|*.bmp|图片(*.png)|*.png|");
	CFileDialog dlgFile(TRUE,NULL,NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter,NULL,0,TRUE);

	if (dlgFile.DoModal())
	{
		picturePath = dlgFile.GetPathName();
		m_filePath.SetWindowTextA(picturePath);
	}
	//MessageBox(_T("选择文件按钮"));
	// TODO: 在此添加控件通知处理程序代码
}


void CBQRCodeDlg::OnBnClickedGenerate()
{
	// 生成二维码按钮
	// TODO: 在此添加控件通知处理程序代码
	MessageBox(_T("生成个性化二维码"));
	m_progress.SetPos(30);
	
	IplImage *iplImg = cvLoadImage(picturePath.GetBuffer(0),0);//读取为单通道图片，即灰度图
	Mat input_image(iplImg,0);
	
	CImg2Code img2code;

	img2code.Img2bit(input_image,imgBits);
	
	/*
	ShowImage(input_image,IDC_QRCODE);

	unsigned char msg[223];
	unsigned char codeword[256];
	for(int i=0;i<223;i++){
		msg[i]=i;
	}
	initialize_ecc ();
	encode_data(msg,223, codeword);
	*/
}

void CBQRCodeDlg::OnBnClickedSave()
{
	// 保存二维码按钮
	// TODO: 在此添加控件通知处理程序代码
	MessageBox(_T("保存生成的二维码"));
}



void CBQRCodeDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}

void CBQRCodeDlg::OnBnClickedSelectsave()
{
	// TODO: 在此添加控件通知处理程序代码
	static TCHAR BASED_CODE szFilter[] = _T("位图(*.bmp)|*.bmp|");
	CFileDialog dlgFile(FALSE,NULL,_T("BQRCode"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter,NULL,0,TRUE);

	if (dlgFile.DoModal())
	{
		qrcodePath = dlgFile.GetPathName();
		m_savePath.SetWindowTextA(qrcodePath);
	}
}
void CBQRCodeDlg::ShowImage(Mat img,UINT ID){
	/*显示图片到图片控件中*/
	
	if(img.empty()){
		MessageBox("文件为空");
		return;
	}
	IplImage iplImg = IplImage(img);
	CDC *pDC=GetDlgItem(ID)->GetDC();
	HDC hDC=pDC->GetSafeHdc();
	CRect rect;
	GetDlgItem(ID)->GetClientRect(&rect);
	/*
	CString debugInfo;
	debugInfo.Format("%d  %d",rect.Width(),rect.Height());
	MessageBox(debugInfo);
	*/
	CvvImage cvvImg;  
    cvvImg.CopyOf(&iplImg);  
    cvvImg.DrawToHDC(hDC,&rect);  
    ReleaseDC(pDC);
}