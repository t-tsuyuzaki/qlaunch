#pragma once
#include "afxwin.h"


// CLogView �_�C�A���O

class CLogView : public CDialog
{
	DECLARE_DYNAMIC(CLogView)

public:
	CLogView(CWnd* pParent = NULL);   // �W���R���X�g���N�^
	virtual ~CLogView();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_LOGVIEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
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
