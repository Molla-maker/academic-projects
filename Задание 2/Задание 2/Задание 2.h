
// Задание 2.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CЗадание2App:
// Сведения о реализации этого класса: Задание 2.cpp
//

class CЗадание2App : public CWinApp
{
public:
	CЗадание2App();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CЗадание2App theApp;
