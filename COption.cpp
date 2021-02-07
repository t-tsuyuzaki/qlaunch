// COption.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "qlaunch.h"
#include "COption.h"
#include ".\coption.h"


// CCOption �_�C�A���O

IMPLEMENT_DYNCREATE(CCOption, CDHtmlDialog)

CCOption::CCOption(CWnd* pParent /*=NULL*/)
	: CDHtmlDialog(CCOption::IDD, CCOption::IDH, pParent)
{
}

CCOption::~CCOption()
{
}

void CCOption::DoDataExchange(CDataExchange* pDX)
{
	CDHtmlDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_editPrg);
	DDX_Control(pDX, IDC_EDIT2, m_editCable);
}

BOOL CCOption::OnInitDialog()
{
	CDialog::OnInitDialog();
	loadConfig();
	return TRUE;  // �t�H�[�J�X���R���g���[���ɐݒ肵���ꍇ�������ATRUE ��Ԃ��܂��B
}

BEGIN_MESSAGE_MAP(CCOption, CDHtmlDialog)
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnBnClickedButton3)
END_MESSAGE_MAP()

BEGIN_DHTML_EVENT_MAP(CCOption)
	DHTML_EVENT_ONCLICK(_T("ButtonOK"), OnButtonOK)
	DHTML_EVENT_ONCLICK(_T("ButtonCancel"), OnButtonCancel)
END_DHTML_EVENT_MAP()


BOOL CCOption::PreTranslateMessage(MSG* pMsg) 
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



// CCOption ���b�Z�[�W �n���h��
HRESULT CCOption::OnButtonOK(IHTMLElement* /*pElement*/)
{
	OnOK();
	return S_OK;  // �t�H�[�J�X���R���g���[���ɐݒ肵���ꍇ�������ATRUE ��Ԃ��܂��B
}

HRESULT CCOption::OnButtonCancel(IHTMLElement* /*pElement*/)
{
	OnCancel();
	return S_OK;  // �t�H�[�J�X���R���g���[���ɐݒ肵���ꍇ�������ATRUE ��Ԃ��܂��B
}


void CCOption::setPermission(int mode)
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


int CCOption::getPermission()
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


void CCOption::loadConfig()
{
	char cFileName[MAX_PATH];
	char cData[MAX_PATH];

	sprintf(cFileName, "%s\\"inifile, currentDir);

	// quartus�v���O���}
	GetPrivateProfileString("Config", "Program", "", cData, MAX_PATH, cFileName);
	m_editPrg.SetWindowText(cData);

	// �P�[�u��
	GetPrivateProfileString("Config", "Cable", "", cData, MAX_PATH, cFileName);
	m_editCable.SetWindowText(cData);

	// �񐄏��f�o�C�X�������݃t���O
	setPermission(GetPrivateProfileInt("Config", "Permission", NO, cFileName));
}


void CCOption::saveConfig()
{
	char cFileName[MAX_PATH];
	char cData[MAX_PATH];
	int mode;

	sprintf(cFileName, "%s\\"inifile, currentDir);

	// quartus�v���O���}
	m_editPrg.GetWindowText(cData, MAX_PATH);
	WritePrivateProfileString("Config", "Program", cData, cFileName);

	// �v���O���~���O�P�[�u��
	m_editCable.GetWindowText(cData, MAX_PATH);
	WritePrivateProfileString("Config", "Cable", cData, cFileName);

	// �񐄏��f�o�C�X�������݃t���O
	mode = getPermission();
	sprintf(cData, "%d", mode);
	WritePrivateProfileString("Config", "Permission", cData, cFileName);

	WriteProfileString(NULL, NULL, NULL);//���܂��Ȃ�
}






// �v���O�����Q�ƃ{�^��
void CCOption::OnBnClickedButton1()
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

	ofn.lpstrFilter = "exe\0" "*.exe\0";
	ofn.nFilterIndex = 2;
	result = GetOpenFileName(&ofn);

	if ( result ) {
		m_editPrg.SetWindowText(cFileName);
	}
}

// OK
void CCOption::OnBnClickedButton2()
{
	// TODO : �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
	saveConfig();
	OnOK();
}

// �L�����Z��
void CCOption::OnBnClickedButton3()
{
	// TODO : �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
	OnCancel();
}




