// Option.cpp : 実装ファイル
//

#include "stdafx.h"
#include "qlaunch.h"
#include "Option.h"
#include ".\option.h"


// COption ダイアログ

IMPLEMENT_DYNAMIC(COption, CDialog)
COption::COption(CWnd* pParent /*=NULL*/)
	: CDialog(COption::IDD, pParent)
{
}

COption::~COption()
{
}

void COption::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_editPrg);
}


BEGIN_MESSAGE_MAP(COption, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
END_MESSAGE_MAP()


BOOL COption::OnInitDialog()
{
	CDialog::OnInitDialog();
	loadConfig();
	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}

BOOL COption::PreTranslateMessage(MSG* pMsg) 
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

//------------------------------------------------------------------------------------
// ダウンロードケーブル
void COption::setCableSelect(int sel)
{
	int sw;

	switch(sel) {
		case BYTEBLASTERII:
			sw = IDC_RADIO_BLASTERII;
			break;
		case BYTEBLASTERMV:
			sw = IDC_RADIO_BLASTERMV;
			break;
		default:
			return;
	}
	CheckRadioButton(IDC_RADIO_BLASTERII, IDC_RADIO_BLASTERMV, sw);
}

int COption::getCableSelect()
{
	int ret;

	switch ( GetCheckedRadioButton(IDC_RADIO_BLASTERII, IDC_RADIO_BLASTERMV) ) {
		case IDC_RADIO_BLASTERII:
			ret = BYTEBLASTERII;
			break;
		case IDC_RADIO_BLASTERMV:
			ret = BYTEBLASTERMV;
			break;
	}

	return ret;
}

//------------------------------------------------------------------------------------
// ケーブルポート
void COption::setPortSelect(int port)
{
	int sw;

	switch(port) {
		case PORT_LPT1:
			sw = IDC_RADIO_LPT1;
			break;
		case PORT_LPT2:
			sw = IDC_RADIO_LPT2;
			break;
		default:
			return;
	}
	CheckRadioButton(IDC_RADIO_LPT1, IDC_RADIO_LPT2, sw);
}

int COption::getPortSelect()
{
	int ret;

	switch ( GetCheckedRadioButton(IDC_RADIO_LPT1, IDC_RADIO_LPT2) ) {
		case IDC_RADIO_LPT1:
			ret = PORT_LPT1;
			break;
		case IDC_RADIO_LPT2:
			ret = PORT_LPT2;
			break;
	}

	return ret;
}

//------------------------------------------------------------------------------------
// 表示関係
void COption::setVerbose(int mode)
{
	int sw;

	switch(mode) {
		case YES:
			sw = IDC_RADIO_VERBOSE_ON;
			break;
		case NO:
			sw = IDC_RADIO_VERBOSE_OFF;
			break;
		default:
			return;
	}
	CheckRadioButton(IDC_RADIO_VERBOSE_ON, IDC_RADIO_VERBOSE_OFF, sw);
}


int COption::getVerbose()
{
	int ret;

	switch ( GetCheckedRadioButton(IDC_RADIO_VERBOSE_ON, IDC_RADIO_VERBOSE_OFF) ) {
		case IDC_RADIO_VERBOSE_ON:
			ret = YES;
			break;
		case IDC_RADIO_VERBOSE_OFF:
			ret = NO;
			break;
	}

	return ret;
}

//------------------------------------------------------------------------------------
// 許可関係
void COption::setPermission(int mode)
{
	int sw;

	switch (mode) {
		case YES:
			sw = IDC_RADIO_YES;
			break;
		case NO:
			sw = IDC_RADIO_NO;
			break;
		default:
			return;
	}
	CheckRadioButton(IDC_RADIO_YES, IDC_RADIO_NO, sw);
}


int COption::getPermission()
{
	int ret;

	switch ( GetCheckedRadioButton(IDC_RADIO_YES, IDC_RADIO_NO) ) {
		case IDC_RADIO_YES:
			ret = YES;
			break;
		case IDC_RADIO_NO:
			ret = NO;
			break;
	}

	return ret;
}


//------------------------------------------------------------------------------------
void COption::loadConfig()
{
	char cFileName[MAX_PATH];
	char cData[MAX_PATH];

	sprintf(cFileName, "%s\\"INIFILE, currentDir);

	// quartusプログラマ
	GetPrivateProfileString("Config", "Program", "", cData, MAX_PATH, cFileName);
	m_editPrg.SetWindowText(cData);

	// ケーブル
	setCableSelect(GetPrivateProfileInt("Config", "Cable", BYTEBLASTERII, cFileName));

	// ポート
	setPortSelect(GetPrivateProfileInt("Config", "Port", PORT_LPT1, cFileName));

	// verbose
	setVerbose(GetPrivateProfileInt("Config", "Verbose", NO, cFileName));

	// 非推奨デバイス書き込みフラグ
	setPermission(GetPrivateProfileInt("Config", "Permission", NO, cFileName));
}


void COption::saveConfig()
{
	char cFileName[MAX_PATH];
	char cData[MAX_PATH];

	sprintf(cFileName, "%s\\"INIFILE, currentDir);

	// quartusプログラマ
	m_editPrg.GetWindowText(cData, MAX_PATH);
	WritePrivateProfileString("Config", "Program", cData, cFileName);

	// プログラミングケーブル
	sprintf(cData, "%d", getCableSelect());
	WritePrivateProfileString("Config", "Cable", cData, cFileName);

	// ポート
	sprintf(cData, "%d", getPortSelect());
	WritePrivateProfileString("Config", "Port", cData, cFileName);

	// verbose
	sprintf(cData, "%d", getVerbose());
	WritePrivateProfileString("Config", "Verbose", cData, cFileName);

	// 非推奨デバイス書き込みフラグ
	sprintf(cData, "%d", getPermission());
	WritePrivateProfileString("Config", "Permission", cData, cFileName);

	WriteProfileString(NULL, NULL, NULL);//おまじない
}


// COption メッセージ ハンドラ

void COption::OnBnClickedOk()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	saveConfig();
	OnOK();
}

void COption::OnBnClickedCancel()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	OnCancel();
}

void COption::OnBnClickedButton1()
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

	ofn.lpstrFilter = "quartus_pgm\0" "quartus_pgm.exe\0";
	ofn.nFilterIndex = 2;
	result = GetOpenFileName(&ofn);

	if ( result ) {
		m_editPrg.SetWindowText(cFileName);
	}
}
