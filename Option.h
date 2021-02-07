#pragma once
#include "afxwin.h"


// COption �_�C�A���O

class COption : public CDialog
{
	DECLARE_DYNAMIC(COption)

public:
	COption(CWnd* pParent = NULL);   // �W���R���X�g���N�^
	virtual ~COption();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_OPTION };


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
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
