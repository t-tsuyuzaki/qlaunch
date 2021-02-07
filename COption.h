#pragma once
#include "afxwin.h"


// CCOption �_�C�A���O

class CCOption : public CDHtmlDialog
{
	DECLARE_DYNCREATE(CCOption)

public:
	CCOption(CWnd* pParent = NULL);   // �W���R���X�g���N�^
	virtual ~CCOption();
// �I�[�o�[���C�h
	HRESULT OnButtonOK(IHTMLElement *pElement);
	HRESULT OnButtonCancel(IHTMLElement *pElement);

// �_�C�A���O �f�[�^
	enum { IDD = IDD_OPTION, IDH = IDR_HTML_COPTION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	DECLARE_MESSAGE_MAP()
	DECLARE_DHTML_EVENT_MAP()
public:
	CEdit m_editPrg;
	CEdit m_editCable;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();

	char currentDir[MAX_PATH];

private:
	void loadConfig();
	void saveConfig();
	void setPermission(int mode);
	int getPermission();

};
