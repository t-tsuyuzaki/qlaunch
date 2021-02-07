// qlaunch.h : PROJECT_NAME �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C���ł��B
//

#pragma once

#ifndef __AFXWIN_H__
	#error ���̃t�@�C���� PCH �Ɋ܂߂�O�ɁA'stdafx.h' ���܂߂Ă��������B
#endif

#include "resource.h"		// ���C�� �V���{��


// CqlaunchApp:
// ���̃N���X�̎����ɂ��ẮAqlaunch.cpp ���Q�Ƃ��Ă��������B
//

class CqlaunchApp : public CWinApp
{
public:
	CqlaunchApp();

// �I�[�o�[���C�h
	public:
	virtual BOOL InitInstance();

// ����

	DECLARE_MESSAGE_MAP()
};

extern CqlaunchApp theApp;

// permission
// verbose
enum {
	NO,
	YES
};

// cable
enum {
	BYTEBLASTERII,
	BYTEBLASTERMV
};

// port
enum {
	PORT_LPT1,
	PORT_LPT2
};

// color
enum {
	COLOR_RED,
	COLOR_GREEN,
	COLOR_BLUE
};

typedef struct _DEVLIST
{
	CString		Type;
	CString		Mode;
	CString		Name;
	CString		Package;
	bool		Permission;
} DEVLIST, *PDEVLIST;

#define INIFILE "qlaunch.ini"
#define LOG_LENGTH 100		// ���O�o�b�t�@�̒���


