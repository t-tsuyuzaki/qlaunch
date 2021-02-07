// qlaunchDlg.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "qlaunch.h"
#include "qlaunchDlg.h"
#include ".\qlaunchdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// �A�v���P�[�V�����̃o�[�W�������Ɏg���� CAboutDlg �_�C�A���O

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

// ����
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CqlaunchDlg �_�C�A���O



CqlaunchDlg::CqlaunchDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CqlaunchDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CqlaunchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_comboDevice);
	DDX_Control(pDX, IDC_EDIT1, m_editFilename);
	DDX_Control(pDX, IDC_EDIT2, m_editMode);
	DDX_Control(pDX, IDC_EDIT3, m_editCable);
	DDX_Control(pDX, IDC_EDIT4, m_editTargetDevice);
	DDX_Control(pDX, IDC_EDIT5, m_editTargetFile);
	DDX_Control(pDX, IDC_BUTTON2, m_btnExec);
	DDX_Control(pDX, IDC_BUTTON3, m_btnVerify);
	DDX_Control(pDX, IDC_PICT, m_pict);
}

BEGIN_MESSAGE_MAP(CqlaunchDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_CBN_SELCHANGE(IDC_COMBO1, OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnBnClickedButton3)
	ON_WM_CTLCOLOR()
//	ON_EN_UPDATE(IDC_EDIT_IND, OnEnUpdateEditInd)
END_MESSAGE_MAP()


// CqlaunchDlg ���b�Z�[�W �n���h��

BOOL CqlaunchDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// "�o�[�W�������..." ���j���[���V�X�e�� ���j���[�ɒǉ����܂��B

	// IDM_ABOUTBOX �́A�V�X�e�� �R�}���h�͈͓̔��ɂȂ���΂Ȃ�܂���B
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_OPTION, "�ݒ�");
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���̃_�C�A���O�̃A�C�R����ݒ肵�܂��B�A�v���P�[�V�����̃��C�� �E�B���h�E���_�C�A���O�łȂ��ꍇ�A
	//  Framework �́A���̐ݒ�������I�ɍs���܂��B
//	SetIcon(m_hIcon, TRUE);			// �傫���A�C�R���̐ݒ�
//	SetIcon(m_hIcon, FALSE);		// �������A�C�R���̐ݒ�

	// TODO: �������������ɒǉ����܂��B
	initApplication();
	
	return TRUE;  // �t�H�[�J�X���R���g���[���ɐݒ肵���ꍇ�������ATRUE ��Ԃ��܂��B
}

void CqlaunchDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
/*
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
*/
	CAboutDlg dlgAbout;

	switch (nID & 0xFFF0) {
		case IDM_ABOUTBOX:
			dlgAbout.DoModal();
			break;
		case IDM_OPTION:
			m_DlgOption.DoModal();
			loadConfig();
			break;
		default:
			CDialog::OnSysCommand(nID, lParam);
			break;
	}
}

// �_�C�A���O�ɍŏ����{�^����ǉ�����ꍇ�A�A�C�R����`�悷�邽�߂�
//  ���̃R�[�h���K�v�ł��B�h�L�������g/�r���[ ���f�����g�� MFC �A�v���P�[�V�����̏ꍇ�A
//  ����́AFramework �ɂ���Ď����I�ɐݒ肳��܂��B

void CqlaunchDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �`��̃f�o�C�X �R���e�L�X�g

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// �N���C�A���g�̎l�p�`�̈���̒���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �A�C�R���̕`��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
		changePict();
	}
}

BOOL CqlaunchDlg::PreTranslateMessage(MSG* pMsg) 
{
    switch(pMsg->message){
        case WM_KEYDOWN:
            switch(pMsg->wParam){
                case VK_RETURN:return TRUE;
                case VK_ESCAPE:return TRUE;
            }
    }
    return CDialog::PreTranslateMessage(pMsg);
}


//���[�U�[���ŏ��������E�B���h�E���h���b�O���Ă���Ƃ��ɕ\������J�[�\�����擾���邽�߂ɁA
//  �V�X�e�������̊֐����Ăяo���܂��B
HCURSOR CqlaunchDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



//
// �A�v���P�[�V�����������֘A
//
void CqlaunchDlg::initApplication()
{
	m_font.CreatePointFont(360, _T("�l�r �o�S�V�b�N"));
	m_editTargetDevice.SetFont(&m_font);
	m_editTargetFile.SetFont(&m_font);

	readDefFile();
	loadConfig();

	m_btnExec.EnableWindow(FALSE);

	m_indColor = COLOR_GREEN;
}

//
// �A�v���P�[�V�����I������
//
void CqlaunchDlg::releaseApplication()
{
	int count;
	int i;
	PVOID ptr;
	
	saveConfig();

	// ���Ƃ��܂D
	count = m_comboDevice.GetCount();
	for ( i=0 ; i<count ; i++) {
		ptr = m_comboDevice.GetItemDataPtr(i);
		if ( ptr != NULL ) {
			delete ptr;
		}
	}
}

void CqlaunchDlg::saveConfig()
{
}

void CqlaunchDlg::loadConfig()
{
	char cFileName[MAX_PATH];
	int selcable,selport;

	sprintf(cFileName, "%s\\"INIFILE, currentDir);

	// quartus�v���O���}
	GetPrivateProfileString("Config", "Program", "", programmer, MAX_PATH, cFileName);

	// �v���O���~���O�P�[�u��
	selcable = GetPrivateProfileInt("Config", "Cable", BYTEBLASTERII, cFileName);
	selport = GetPrivateProfileInt("Config", "Port", PORT_LPT1, cFileName);
	sprintf(cable, "%s[%s]",
		!selcable ? "ByteBlasterII" : "ByteBlasterMV",
		!selport ? "LPT1" : "LPT2"
		);
	m_editCable.SetWindowText(cable);

	// verbose
	verbose = GetPrivateProfileInt("Config", "Verbose", YES, cFileName);


	// �񐄏��f�o�C�X�������݃t���O
	permission = GetPrivateProfileInt("Config", "Permission", NO, cFileName);
}



bool CqlaunchDlg::readDefFile()
{
	bool ret = true;
	char path[MAX_PATH+1];
	CStdioFile strFile;
	CString buf,wkbuf;
	CString sep=",";
	CString ast="*";

	DEVLIST *wkdl;

	int pt;

	//�������X�g�\�z
	devcount = 0;

	GetCurrentDirectory(MAX_PATH, path);
	strcpy(currentDir, path);
	strcpy(m_DlgOption.currentDir, path);
	strcat(path, "\\devices.def" );

	if ( strFile.Open(path, CFile::modeRead) ) {
		// 1�s�����[�v
		while (strFile.ReadString(buf)) {

			// "*"��荶�ō�Ƃ���
			if ( (pt = buf.Find(ast)) != -1 ) {
				wkbuf = buf.Mid(0, pt);
			} else {
				wkbuf = buf;
			}

			// �L���ȍs��
			if ( (pt = wkbuf.Find(sep)) != -1 ) {
				//�Ƃ肠�����ŏ���","�����D���̎��_�ł��̍s�͗L���Ɣ��f����D�G���[�`�F�b�N�Ȃ��D
				wkdl = new DEVLIST;

				// �����^��
				wkdl->Type = wkbuf.Mid(0, pt);
				wkbuf.Delete(0, wkdl->Type.GetLength() + sep.GetLength());
				m_comboDevice.InsertString(devcount, wkdl->Type);
				m_comboDevice.SetItemDataPtr(devcount, wkdl);

				// ����MODE
				if ( (pt = wkbuf.Find(sep)) != -1 ) {
					wkdl->Mode = wkbuf.Mid(0, pt);
					wkbuf.Delete(0, wkdl->Mode.GetLength() + sep.GetLength());

					// ���͕\������
					if ( (pt = wkbuf.Find(sep)) != -1 ) {
						wkdl->Name = wkbuf.Mid(0, pt);
						wkbuf.Delete(0, wkdl->Name.GetLength() + sep.GetLength());

						// ���̓p�b�P�[�W�`��
						if ( (pt = wkbuf.Find(sep)) != -1 ) {
							wkdl->Package = wkbuf.Mid(0, pt);
							wkbuf.Delete(0, wkdl->Package.GetLength() + sep.GetLength());

							// �����͎g�p����/�s���t���O
							wkbuf.Trim();
							if ( !wkbuf.Compare("1") ) {
								wkdl->Permission = true;
							} else {
								wkdl->Permission = false;
							}
						}
					}
				}
				devcount++;
			}
			buf.Empty();
		}
		if (strFile.m_hFile!=CFile::hFileNull) {
			strFile.Close();
		}
	} else {
		return false;
	}
	return ret;
}






void CqlaunchDlg::OnCbnSelchangeCombo1()
{
	// TODO : �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
	DEVLIST *dl;

	selectedNumber = m_comboDevice.GetCurSel();
	dl = (DEVLIST*)m_comboDevice.GetItemDataPtr(selectedNumber);
	if ( dl != NULL ) {
		m_editTargetDevice.SetWindowText(dl->Name);
		m_editMode.SetWindowText(dl->Mode);

		// �g�p�����ǂ���
		if ( dl->Permission ) {
			m_btnExec.EnableWindow(TRUE);
		} else {
			if ( !permission ) {
				m_btnExec.EnableWindow(FALSE);
			} else {
				m_btnExec.EnableWindow(TRUE);
			}
		}
	}
}


// �t�@�C���I��
void CqlaunchDlg::OnBnClickedButton1()
{
	// TODO : �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
	OPENFILENAME ofn;
	char	cFileName[MAX_PATH];
	int		result;

	cFileName[0] = '\0';
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.Flags = 0;
	ofn.lpstrFile = cFileName;
	ofn.nMaxFile = sizeof(cFileName);

	ofn.lpstrFilter = "pof\0" "*.pof\0";
	ofn.nFilterIndex = 2;
	result = GetOpenFileName(&ofn);

	if ( result ) {
		m_editFilename.SetWindowText(cFileName);

		{
			char cDrive[_MAX_DRIVE+1];
			char cPath[_MAX_PATH+1];
			char cName[_MAX_FNAME+1];
			char cExt[_MAX_EXT+1];
			char cFile[_MAX_PATH+1];

			_splitpath(cFileName, cDrive, cPath, cName, cExt);
			sprintf(cFile,"%s%s", cName,cExt);
			m_editTargetFile.SetWindowText(cFile);
		}
	}
}


// �_�E�����[�h���s
void CqlaunchDlg::OnBnClickedButton2()
{
	// TODO : �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
	PROCESS_INFORMATION pinfo;
	STARTUPINFO sinfo;
	DWORD	exitcode;
	BOOL	ret;
	char comline[MAX_PATH+MAX_PATH];
	char exit[256];
	char filename[MAX_PATH];
	char mode[16];
	char device[100];

    ZeroMemory(&sinfo, sizeof(sinfo));
    ZeroMemory(&pinfo, sizeof(pinfo));
    sinfo.cb = sizeof(sinfo);

	// ���擾
	m_editFilename.GetWindowText(filename, MAX_PATH);
	m_editMode.GetWindowText(mode,16);
	m_editTargetDevice.GetWindowText(device,100);


	if ( strcmp(device,"") == 0 ) {
		MessageBox("�f�o�C�X���ݒ肳��Ă��܂���", "�G���[",
					MB_OK | MB_ICONHAND );
		return;
	}

	if ( strcmp(filename,"") == 0 ) {
		MessageBox("�_�E�����[�h�t�@�C�����ݒ肳��Ă��܂���", "�G���[",
					MB_OK | MB_ICONHAND );
		return;
	}

	if ( strcmp(programmer,"") == 0 ) {
		MessageBox("�v���O���}���ݒ肳��Ă��܂���", "�G���[",
					MB_OK | MB_ICONHAND );
		return;
	}

	if ( strcmp(cable,"") == 0 ) {
		MessageBox("�_�E�����[�h�P�[�u�����ݒ肳��Ă��܂���", "�G���[",
					MB_OK | MB_ICONHAND );
		return;
	}

	// �R�}���h���C���\�z
	sprintf(comline, "%s -c %s -m %s -o pl;%s", programmer, cable, mode, filename);
/*
	{
		MessageBox(comline, "�R�}���h���C��", MB_OK | MB_ICONINFORMATION);
	}
*/

	GetStartupInfo(&sinfo);

	// verbose���[�h
	if ( verbose == NO ) {
		sinfo.dwFlags = STARTF_USESHOWWINDOW;
		sinfo.wShowWindow = SW_HIDE;
	}


	ret = CreateProcess(NULL, comline,
						0,0,
						FALSE,
						CREATE_NEW_CONSOLE,
						0,0,
						&sinfo,
						&pinfo);
	if ( ret ) {
		// ���s�ł����ꍇ
		m_indColor = COLOR_BLUE;
		m_indStr = "�_�E�����[�h���s��";
		changePict();

		m_btnExec.EnableWindow(FALSE);
		WaitForSingleObject(pinfo.hProcess, INFINITE);
		m_btnExec.EnableWindow(TRUE);

		GetExitCodeProcess(pinfo.hProcess, &exitcode);

		CloseHandle(pinfo.hThread);
		CloseHandle(pinfo.hProcess);

		if ( exitcode != 0 ) {
			m_indColor = COLOR_RED;
			m_indStr = "�G���[���������Ă��܂�";
			changePict();

			sprintf(exit, "�G���[���������܂��� code = %d", exitcode);
			MessageBox(exit, "�G���[", MB_OK | MB_ICONINFORMATION);
		} else {
			m_indColor = COLOR_GREEN;
			m_indStr = "";
			changePict();
		}
	} else {
		m_indColor = COLOR_RED;
		m_indStr = "�G���[���������Ă��܂�";
		changePict();

		MessageBox("�v���O�����c�[���̋N���Ɏ��s���܂���","�G���[",MB_OK | MB_ICONHAND);
	}
}


// �x���t�@�C
void CqlaunchDlg::OnBnClickedButton3()
{
	// TODO : �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B

	// TODO : �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
	PROCESS_INFORMATION pinfo;
	STARTUPINFO sinfo;
	DWORD	exitcode;
	BOOL	ret;
	char comline[MAX_PATH+MAX_PATH];
	char exit[256];
	char filename[MAX_PATH];
	char mode[16];
	char device[100];

    ZeroMemory(&sinfo, sizeof(sinfo));
    ZeroMemory(&pinfo, sizeof(pinfo));
    sinfo.cb = sizeof(sinfo);

	// ���擾
	m_editFilename.GetWindowText(filename, MAX_PATH);
	m_editMode.GetWindowText(mode,16);
	m_editTargetDevice.GetWindowText(device,100);


	if ( strcmp(device,"") == 0 ) {
		MessageBox("�f�o�C�X���ݒ肳��Ă��܂���", "�G���[",
					MB_OK | MB_ICONHAND );
		return;
	}

	if ( strcmp(filename,"") == 0 ) {
		MessageBox("�_�E�����[�h�t�@�C�����ݒ肳��Ă��܂���", "�G���[",
					MB_OK | MB_ICONHAND );
		return;
	}

	if ( strcmp(programmer,"") == 0 ) {
		MessageBox("�v���O���}���ݒ肳��Ă��܂���", "�G���[",
					MB_OK | MB_ICONHAND );
		return;
	}

	if ( strcmp(cable,"") == 0 ) {
		MessageBox("�_�E�����[�h�P�[�u�����ݒ肳��Ă��܂���", "�G���[",
					MB_OK | MB_ICONHAND );
		return;
	}

	// �R�}���h���C���\�z
	sprintf(comline, "%s -c %s -m %s -o v;%s", programmer, cable, mode, filename);
/*
	{
		MessageBox(comline, "�R�}���h���C��", MB_OK | MB_ICONINFORMATION);
	}
*/
	GetStartupInfo(&sinfo);

	// verbose���[�h
	if ( verbose == NO ) {
		sinfo.dwFlags = STARTF_USESHOWWINDOW;
		sinfo.wShowWindow = SW_HIDE;
	}

	ret = CreateProcess(NULL, comline,
						0,0,
						FALSE,
						CREATE_NEW_CONSOLE,
						0,0,
						&sinfo,
						&pinfo);
	if ( ret ) {
		// ���s�ł����ꍇ
		m_indColor = COLOR_BLUE;
		m_indStr = "�x���t�@�C���s��";
		changePict();

		m_btnVerify.EnableWindow(FALSE);
		WaitForSingleObject(pinfo.hProcess, INFINITE);
		m_btnVerify.EnableWindow(TRUE);

		GetExitCodeProcess(pinfo.hProcess, &exitcode);

		CloseHandle(pinfo.hThread);
		CloseHandle(pinfo.hProcess);

		if ( exitcode != 0 ) {
			m_indColor = COLOR_RED;
			m_indStr = "�G���[���������Ă��܂�";
			changePict();

			sprintf(exit, "�G���[���������܂��� code = %d", exitcode);
			MessageBox(exit, "�G���[", MB_OK | MB_ICONINFORMATION);
		} else {
			m_indColor = COLOR_GREEN;
			m_indStr = "";
			changePict();
		}
	} else {
		m_indColor = COLOR_RED;
		m_indStr = "�G���[���������Ă��܂�";
		changePict();

		MessageBox("�v���O�����c�[���̋N���Ɏ��s���܂���","�G���[",MB_OK | MB_ICONHAND);
	}
}

HBRUSH CqlaunchDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO :  ������ DC �̑�����ύX���Ă��������B

	// TODO :  ����l���g�p�������Ȃ��ꍇ�͕ʂ̃u���V��Ԃ��܂��B

/*
	if(pWnd->GetDlgCtrlID()==IDC_EDIT_IND){
		if(nCtlColor==CTLCOLOR_EDIT||nCtlColor==CTLCOLOR_STATIC){
			pDC->SetBkColor(indColor);
		}
		return (HBRUSH)GetStockObject(WHITE_BRUSH);
	}
*/
	return hbr;
}

void CqlaunchDlg::changePict()
{
	
	CRect rect;
	CClientDC pictDC(&m_pict);
	m_pict.GetClientRect(rect);
	int color;

	switch ( m_indColor ) {
		case COLOR_RED:
			color = RGB(255,50,50);
			break;
		case COLOR_GREEN:
			color = RGB(50,255,50);
			break;
		case COLOR_BLUE:
			color = RGB(50,50,255);
			break;
	}

	pictDC.SelectObject(m_font);
	pictDC.SetTextColor(RGB(255,255,255));
	pictDC.FillSolidRect(rect, color);
	pictDC.TextOut(0,0,m_indStr);
}