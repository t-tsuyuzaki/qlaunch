// qlaunchDlg.h : �w�b�_�[ �t�@�C��
//

#pragma once
#include "afxwin.h"
#include "Option.h"
#include "LogView.h"

// CqlaunchDlg �_�C�A���O
class CqlaunchDlg : public CDialog
{
// �R���X�g���N�V����
public:
	CqlaunchDlg(CWnd* pParent = NULL);	// �W���R���X�g���N�^

// �_�C�A���O �f�[�^
	enum { IDD = IDD_QLAUNCH_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �T�|�[�g


// ����
protected:
	HICON m_hIcon;

	// �������ꂽ�A���b�Z�[�W���蓖�Ċ֐�
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
