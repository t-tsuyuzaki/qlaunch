#pragma once
#include "afxwin.h"


// CLogView ダイアログ

class CLogView : public CDialog
{
	DECLARE_DYNAMIC(CLogView)

public:
	CLogView(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CLogView();

// ダイアログ データ
	enum { IDD = IDD_LOGVIEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	DECLARE_MESSAGE_MAP()

	CWnd *m_pParent;
	int m_nID;

public:
	BOOL Create(void);
	CEdit m_editLogView;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	void setMessage(LPCSTR str);

private:
	CString m_strLog[LOG_LENGTH];
	int m_logTop;
	int m_logTail;
	int m_logLength;
};
