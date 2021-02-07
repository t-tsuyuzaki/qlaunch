#pragma once
#include "afxwin.h"


// COption ダイアログ

class COption : public CDialog
{
	DECLARE_DYNAMIC(COption)

public:
	COption(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~COption();

// ダイアログ データ
	enum { IDD = IDD_OPTION };


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton1();
	CEdit m_editPrg;

	char currentDir[MAX_PATH];
private:
	void loadConfig();
	void saveConfig();
	void setPermission(int mode);
	int getPermission();

	void setCableSelect(int sel);
	int getCableSelect();

	void setPortSelect(int port);
	int getPortSelect();

	void setVerbose(int mode);
	int getVerbose();
};
