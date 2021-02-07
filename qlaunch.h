// qlaunch.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです。
//

#pragma once

#ifndef __AFXWIN_H__
	#error このファイルを PCH に含める前に、'stdafx.h' を含めてください。
#endif

#include "resource.h"		// メイン シンボル


// CqlaunchApp:
// このクラスの実装については、qlaunch.cpp を参照してください。
//

class CqlaunchApp : public CWinApp
{
public:
	CqlaunchApp();

// オーバーライド
	public:
	virtual BOOL InitInstance();

// 実装

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
#define LOG_LENGTH 100		// ログバッファの長さ


