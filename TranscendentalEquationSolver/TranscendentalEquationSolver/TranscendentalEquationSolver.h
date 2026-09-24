
// TranscendentalEquationSolver.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CTranscendentalEquationSolverApp:
// Сведения о реализации этого класса: TranscendentalEquationSolver.cpp
//

class CTranscendentalEquationSolverApp : public CWinApp
{
public:
	CTranscendentalEquationSolverApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CTranscendentalEquationSolverApp theApp;
