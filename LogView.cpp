// LogView.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "qlaunch.h"
#include "LogView.h"
#include ".\logview.h"


// CLogView �_�C�A���O

IMPLEMENT_DYNAMIC(CLogView, CDialog)
CLogView::CLogView(CWnd* pParent /*=NULL*/)
	: CDialog(CLogView::IDD, pParent)
{
	m_pParent = pParent;
	m_nID = CLogView::IDD;
}

CLogView::~CLogView()
{
}

void CLogView::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_LOGVIEW, m_editLogView);
}


BEGIN_MESSAGE_MAP(CLogView, CDialog)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


BOOL CLogView::OnInitDialog()
{
	CDialog::OnInitDialog();

	// �����O�o�b�t�@������
	m_logTop = 0;
	m_logTail = 0;
	m_logLength = 0;

	return TRUE;  // �t�H�[�J�X���R���g���[���ɐݒ肵���ꍇ�������ATRUE ��Ԃ��܂��B
}


BOOL CLogView::PreTranslateMessage(MSG* pMsg) 
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


// CLogView ���b�Z�[�W �n���h��

BOOL CLogView::Create(void)
{
	return CDialog::Create( m_nID, m_pParent);
}

HBRUSH CLogView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO :  ������ DC �̑�����ύX���Ă��������B

	// TODO :  ����l���g�p�������Ȃ��ꍇ�͕ʂ̃u���V��Ԃ��܂��B
	if(pWnd->GetDlgCtrlID()==IDC_EDIT_LOGVIEW){
		if(nCtlColor==CTLCOLOR_EDIT||nCtlColor==CTLCOLOR_STATIC){
			pDC->SetBkColor(RGB(255,255,255));
			hbr = CreateSolidBrush(RGB(255,255,255));
		}
		return (HBRUSH)GetStockObject(WHITE_BRUSH);
	}
	return hbr;
}



void CLogView::setMessage(LPCSTR str)
{
	m_strLog[m_logTop].Format("%s",str);
	m_logTop++;

	if ( m_logTop > LOG_LENGTH ) {
		m_logTop = 0;
	}
}



