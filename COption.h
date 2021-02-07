#pragma once
#include "afxwin.h"


// CCOption ダイアログ

class CCOption : public CDHtmlDialog
{
	DECLARE_DYNCREATE(CCOption)

public:
	CCOption(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CCOption();
// オーバーライド
	HRESULT OnButtonOK(IHTMLElement *pElement);
	HRESULT OnButtonCancel(IHTMLElement *pElement);

// ダイアログ データ
	enum { IDD = IDD_OPTION, IDH = IDR_HTML_COPTION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
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
