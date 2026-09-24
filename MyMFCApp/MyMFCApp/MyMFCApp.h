
// MyMFCApp.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CMyMFCAppApp:
// Сведения о реализации этого класса: MyMFCApp.cpp
//

class CMyMFCAppApp : public CWinApp
{
public:
	CMyMFCAppApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CMyMFCAppApp theApp;
