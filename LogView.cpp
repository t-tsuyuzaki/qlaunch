// LogView.cpp : 実装ファイル
//

#include "stdafx.h"
#include "qlaunch.h"
#include "LogView.h"
#include ".\logview.h"


// CLogView ダイアログ

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

	// リングバッファ初期化
	m_logTop = 0;
	m_logTail = 0;
	m_logLength = 0;

	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
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


// CLogView メッセージ ハンドラ

BOOL CLogView::Create(void)
{
	return CDialog::Create( m_nID, m_pParent);
}

HBRUSH CLogView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO :  ここで DC の属性を変更してください。

	// TODO :  既定値を使用したくない場合は別のブラシを返します。
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



