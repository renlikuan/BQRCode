
// BQRCodeDlg.cpp : ʵ���ļ�
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


// CBQRCodeDlg �Ի���



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


// CBQRCodeDlg ��Ϣ�������

BOOL CBQRCodeDlg::OnInitDialog()
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
	// ������
	m_progress.SetRange(0,100);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CBQRCodeDlg::OnPaint()
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
HCURSOR CBQRCodeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


/*ѡ���ļ���ť*/
void CBQRCodeDlg::OnBnClickedSelectfile()
{

	// ������
	static TCHAR BASED_CODE szFilter[] = _T("λͼ(*.bmp)|*.bmp|ͼƬ(*.png)|*.png|");
	CFileDialog dlgFile(TRUE,NULL,NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter,NULL,0,TRUE);

	if (dlgFile.DoModal())
	{
		picturePath = dlgFile.GetPathName();
		m_filePath.SetWindowTextA(picturePath);
	}
	//MessageBox(_T("ѡ���ļ���ť"));
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CBQRCodeDlg::OnBnClickedGenerate()
{
	// ���ɶ�ά�밴ť
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	MessageBox(_T("���ɸ��Ի���ά��"));
	m_progress.SetPos(30);
	
	IplImage *iplImg = cvLoadImage(picturePath.GetBuffer(0),0);//��ȡΪ��ͨ��ͼƬ�����Ҷ�ͼ
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
	// �����ά�밴ť
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	MessageBox(_T("�������ɵĶ�ά��"));
}



void CBQRCodeDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}

void CBQRCodeDlg::OnBnClickedSelectsave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	static TCHAR BASED_CODE szFilter[] = _T("λͼ(*.bmp)|*.bmp|");
	CFileDialog dlgFile(FALSE,NULL,_T("BQRCode"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter,NULL,0,TRUE);

	if (dlgFile.DoModal())
	{
		qrcodePath = dlgFile.GetPathName();
		m_savePath.SetWindowTextA(qrcodePath);
	}
}
void CBQRCodeDlg::ShowImage(Mat img,UINT ID){
	/*��ʾͼƬ��ͼƬ�ؼ���*/
	
	if(img.empty()){
		MessageBox("�ļ�Ϊ��");
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