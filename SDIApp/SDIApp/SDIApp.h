
// SDIApp.h: основной файл заголовка для приложения SDIApp
//
#pragma once

#ifndef __AFXWIN_H__
#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"       // основные символы


// CSDIAppApp:
// Сведения о реализации этого класса: SDIApp.cpp
//

class CSDIAppApp : public CWinApp
{
public:
	CSDIAppApp() noexcept;


	// Переопределение
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	// Реализация
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CSDIAppApp theApp;
