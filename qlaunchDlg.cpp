// qlaunchDlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "qlaunch.h"
#include "qlaunchDlg.h"
#include ".\qlaunchdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// アプリケーションのバージョン情報に使われる CAboutDlg ダイアログ

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// ダイアログ データ
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

// 実装
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


// CqlaunchDlg ダイアログ



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


// CqlaunchDlg メッセージ ハンドラ

BOOL CqlaunchDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// "バージョン情報..." メニューをシステム メニューに追加します。

	// IDM_ABOUTBOX は、システム コマンドの範囲内になければなりません。
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
			pSysMenu->AppendMenu(MF_STRING, IDM_OPTION, "設定");
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
//	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
//	SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定

	// TODO: 初期化をここに追加します。
	initApplication();
	
	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
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

// ダイアログに最小化ボタンを追加する場合、アイコンを描画するための
//  下のコードが必要です。ドキュメント/ビュー モデルを使う MFC アプリケーションの場合、
//  これは、Framework によって自動的に設定されます。

void CqlaunchDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// クライアントの四角形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンの描画
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


//ユーザーが最小化したウィンドウをドラッグしているときに表示するカーソルを取得するために、
//  システムがこの関数を呼び出します。
HCURSOR CqlaunchDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



//
// アプリケーション初期化関連
//
void CqlaunchDlg::initApplication()
{
	m_font.CreatePointFont(360, _T("ＭＳ Ｐゴシック"));
	m_editTargetDevice.SetFont(&m_font);
	m_editTargetFile.SetFont(&m_font);

	readDefFile();
	loadConfig();

	m_btnExec.EnableWindow(FALSE);

	m_indColor = COLOR_GREEN;
}

//
// アプリケーション終了処理
//
void CqlaunchDlg::releaseApplication()
{
	int count;
	int i;
	PVOID ptr;
	
	saveConfig();

	// あとしまつ．
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

	// quartusプログラマ
	GetPrivateProfileString("Config", "Program", "", programmer, MAX_PATH, cFileName);

	// プログラミングケーブル
	selcable = GetPrivateProfileInt("Config", "Cable", BYTEBLASTERII, cFileName);
	selport = GetPrivateProfileInt("Config", "Port", PORT_LPT1, cFileName);
	sprintf(cable, "%s[%s]",
		!selcable ? "ByteBlasterII" : "ByteBlasterMV",
		!selport ? "LPT1" : "LPT2"
		);
	m_editCable.SetWindowText(cable);

	// verbose
	verbose = GetPrivateProfileInt("Config", "Verbose", YES, cFileName);


	// 非推奨デバイス書き込みフラグ
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

	//初期リスト構築
	devcount = 0;

	GetCurrentDirectory(MAX_PATH, path);
	strcpy(currentDir, path);
	strcpy(m_DlgOption.currentDir, path);
	strcat(path, "\\devices.def" );

	if ( strFile.Open(path, CFile::modeRead) ) {
		// 1行毎ループ
		while (strFile.ReadString(buf)) {

			// "*"より左で作業する
			if ( (pt = buf.Find(ast)) != -1 ) {
				wkbuf = buf.Mid(0, pt);
			} else {
				wkbuf = buf;
			}

			// 有効な行か
			if ( (pt = wkbuf.Find(sep)) != -1 ) {
				//とりあえず最初の","発見．この時点でこの行は有効と判断する．エラーチェックなし．
				wkdl = new DEVLIST;

				// 正式型番
				wkdl->Type = wkbuf.Mid(0, pt);
				wkbuf.Delete(0, wkdl->Type.GetLength() + sep.GetLength());
				m_comboDevice.InsertString(devcount, wkdl->Type);
				m_comboDevice.SetItemDataPtr(devcount, wkdl);

				// 次はMODE
				if ( (pt = wkbuf.Find(sep)) != -1 ) {
					wkdl->Mode = wkbuf.Mid(0, pt);
					wkbuf.Delete(0, wkdl->Mode.GetLength() + sep.GetLength());

					// 次は表示名称
					if ( (pt = wkbuf.Find(sep)) != -1 ) {
						wkdl->Name = wkbuf.Mid(0, pt);
						wkbuf.Delete(0, wkdl->Name.GetLength() + sep.GetLength());

						// 次はパッケージ形状
						if ( (pt = wkbuf.Find(sep)) != -1 ) {
							wkdl->Package = wkbuf.Mid(0, pt);
							wkbuf.Delete(0, wkdl->Package.GetLength() + sep.GetLength());

							// お次は使用許可/不許可フラグ
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
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	DEVLIST *dl;

	selectedNumber = m_comboDevice.GetCurSel();
	dl = (DEVLIST*)m_comboDevice.GetItemDataPtr(selectedNumber);
	if ( dl != NULL ) {
		m_editTargetDevice.SetWindowText(dl->Name);
		m_editMode.SetWindowText(dl->Mode);

		// 使用許可かどうか
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


// ファイル選択
void CqlaunchDlg::OnBnClickedButton1()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
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


// ダウンロード実行
void CqlaunchDlg::OnBnClickedButton2()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
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

	// 情報取得
	m_editFilename.GetWindowText(filename, MAX_PATH);
	m_editMode.GetWindowText(mode,16);
	m_editTargetDevice.GetWindowText(device,100);


	if ( strcmp(device,"") == 0 ) {
		MessageBox("デバイスが設定されていません", "エラー",
					MB_OK | MB_ICONHAND );
		return;
	}

	if ( strcmp(filename,"") == 0 ) {
		MessageBox("ダウンロードファイルが設定されていません", "エラー",
					MB_OK | MB_ICONHAND );
		return;
	}

	if ( strcmp(programmer,"") == 0 ) {
		MessageBox("プログラマが設定されていません", "エラー",
					MB_OK | MB_ICONHAND );
		return;
	}

	if ( strcmp(cable,"") == 0 ) {
		MessageBox("ダウンロードケーブルが設定されていません", "エラー",
					MB_OK | MB_ICONHAND );
		return;
	}

	// コマンドライン構築
	sprintf(comline, "%s -c %s -m %s -o pl;%s", programmer, cable, mode, filename);
/*
	{
		MessageBox(comline, "コマンドライン", MB_OK | MB_ICONINFORMATION);
	}
*/

	GetStartupInfo(&sinfo);

	// verboseモード
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
		// 実行できた場合
		m_indColor = COLOR_BLUE;
		m_indStr = "ダウンロード実行中";
		changePict();

		m_btnExec.EnableWindow(FALSE);
		WaitForSingleObject(pinfo.hProcess, INFINITE);
		m_btnExec.EnableWindow(TRUE);

		GetExitCodeProcess(pinfo.hProcess, &exitcode);

		CloseHandle(pinfo.hThread);
		CloseHandle(pinfo.hProcess);

		if ( exitcode != 0 ) {
			m_indColor = COLOR_RED;
			m_indStr = "エラーが発生しています";
			changePict();

			sprintf(exit, "エラーが発生しました code = %d", exitcode);
			MessageBox(exit, "エラー", MB_OK | MB_ICONINFORMATION);
		} else {
			m_indColor = COLOR_GREEN;
			m_indStr = "";
			changePict();
		}
	} else {
		m_indColor = COLOR_RED;
		m_indStr = "エラーが発生しています";
		changePict();

		MessageBox("プログラムツールの起動に失敗しました","エラー",MB_OK | MB_ICONHAND);
	}
}


// ベリファイ
void CqlaunchDlg::OnBnClickedButton3()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。

	// TODO : ここにコントロール通知ハンドラ コードを追加します。
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

	// 情報取得
	m_editFilename.GetWindowText(filename, MAX_PATH);
	m_editMode.GetWindowText(mode,16);
	m_editTargetDevice.GetWindowText(device,100);


	if ( strcmp(device,"") == 0 ) {
		MessageBox("デバイスが設定されていません", "エラー",
					MB_OK | MB_ICONHAND );
		return;
	}

	if ( strcmp(filename,"") == 0 ) {
		MessageBox("ダウンロードファイルが設定されていません", "エラー",
					MB_OK | MB_ICONHAND );
		return;
	}

	if ( strcmp(programmer,"") == 0 ) {
		MessageBox("プログラマが設定されていません", "エラー",
					MB_OK | MB_ICONHAND );
		return;
	}

	if ( strcmp(cable,"") == 0 ) {
		MessageBox("ダウンロードケーブルが設定されていません", "エラー",
					MB_OK | MB_ICONHAND );
		return;
	}

	// コマンドライン構築
	sprintf(comline, "%s -c %s -m %s -o v;%s", programmer, cable, mode, filename);
/*
	{
		MessageBox(comline, "コマンドライン", MB_OK | MB_ICONINFORMATION);
	}
*/
	GetStartupInfo(&sinfo);

	// verboseモード
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
		// 実行できた場合
		m_indColor = COLOR_BLUE;
		m_indStr = "ベリファイ実行中";
		changePict();

		m_btnVerify.EnableWindow(FALSE);
		WaitForSingleObject(pinfo.hProcess, INFINITE);
		m_btnVerify.EnableWindow(TRUE);

		GetExitCodeProcess(pinfo.hProcess, &exitcode);

		CloseHandle(pinfo.hThread);
		CloseHandle(pinfo.hProcess);

		if ( exitcode != 0 ) {
			m_indColor = COLOR_RED;
			m_indStr = "エラーが発生しています";
			changePict();

			sprintf(exit, "エラーが発生しました code = %d", exitcode);
			MessageBox(exit, "エラー", MB_OK | MB_ICONINFORMATION);
		} else {
			m_indColor = COLOR_GREEN;
			m_indStr = "";
			changePict();
		}
	} else {
		m_indColor = COLOR_RED;
		m_indStr = "エラーが発生しています";
		changePict();

		MessageBox("プログラムツールの起動に失敗しました","エラー",MB_OK | MB_ICONHAND);
	}
}

HBRUSH CqlaunchDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO :  ここで DC の属性を変更してください。

	// TODO :  既定値を使用したくない場合は別のブラシを返します。

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