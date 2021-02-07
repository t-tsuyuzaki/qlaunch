// qlaunchDlg.h : ヘッダー ファイル
//

#pragma once
#include "afxwin.h"
#include "Option.h"
#include "LogView.h"

// CqlaunchDlg ダイアログ
class CqlaunchDlg : public CDialog
{
// コンストラクション
public:
	CqlaunchDlg(CWnd* pParent = NULL);	// 標準コンストラクタ

// ダイアログ データ
	enum { IDD = IDD_QLAUNCH_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート


// 実装
protected:
	HICON m_hIcon;

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	void initApplication();
	void releaseApplication();
	bool readDefFile();
	DEVLIST devlist;
	int devcount;
	CFont m_font;
	void saveConfig();
	void loadConfig();
	void changePict();

	char currentDir[MAX_PATH];
	char programmer[MAX_PATH];
	char cable[MAX_PATH];
	int permission;
	int selectedNumber;
	int verbose;
	int m_indColor;
	CString m_indStr;

	COption m_DlgOption;
	CLogView m_DlgLogView;
public:
	afx_msg void OnCbnSelchangeCombo1();
	CComboBox m_comboDevice;
	CEdit m_editFilename;
	CEdit m_editMode;
	CEdit m_editCable;
	CEdit m_editTargetDevice;
	CEdit m_editTargetFile;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	CButton m_btnExec;
	CButton m_btnVerify;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CStatic m_pict;
};
