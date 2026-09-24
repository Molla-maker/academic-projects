
// TranscendentalEquationSolverDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "TranscendentalEquationSolver.h"
#include "TranscendentalEquationSolverDlg.h"
#include "afxdialogex.h"
#include <cmath>
#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#define M_PI  3.14159265358979323846
#endif


// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Диалоговое окно CTranscendentalEquationSolverDlg



CTranscendentalEquationSolverDlg::CTranscendentalEquationSolverDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TRANSCENDENTALEQUATIONSOLVER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTranscendentalEquationSolverDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTranscendentalEquationSolverDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SOLVE, &CTranscendentalEquationSolverDlg::OnBnClickedButtonSolve)
END_MESSAGE_MAP()


// Обработчики сообщений CTranscendentalEquationSolverDlg

BOOL CTranscendentalEquationSolverDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	CComboBox* pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_METHOD);
	if (pComboBox != NULL)
	{
		pComboBox->AddString(_T("Newton"));
		pComboBox->AddString(_T("Bisection"));
		pComboBox->AddString(_T("Chord"));
		pComboBox->SetCurSel(0); // Установите выбранный элемент по умолчанию
	}

	// TODO: добавьте дополнительную инициализацию

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CTranscendentalEquationSolverDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CTranscendentalEquationSolverDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CTranscendentalEquationSolverDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

double NewtonMethod(double x0, double epsilon, int maxIterations) {
	double x = x0;
	bool foundPositiveRoot = false;
	for (int i = 0; i < maxIterations; ++i) {
		double f = sin(M_PI * x) + x * x - 2;
		double df = M_PI * cos(M_PI * x) + 2 * x;
		double xNew = x - f / df;
		if (fabs(xNew - x) < epsilon) {
			// Если мы находимся в положительной части корня, возвращаем результат
			if (f > 0) {
				return xNew;
			}
			// Если мы находимся в отрицательной части корня, переходим к следующему корню
			else {
				foundPositiveRoot = true;
				x0 = xNew + 1.5; // Увеличиваем начальное приближение
				x = x0;
			}
		}
		else {
			x = xNew;
		}
	}
	// Если после всех итераций не найден положительный корень, возвращаем последнее значение
	return x;
}

double func(double x) {
	return sin(M_PI * x) + x * x - 2;
}

// Метод дихотомии
double BisectionMethod(double a, double b, double epsilon, int maxIterations) {
	// Убедимся, что a < b
	if (a > b) {
		std::swap(a, b);
	}

	double c = a;
	for (int i = 0; i < maxIterations; ++i) {
		// Вычисляем середину интервала [a, b]
		c = (a + b) / 2;

		// Проверяем, находится ли корень в интервале [a, c] или [c, b]
		if (func(c) < 0) {
			b = c;
		}
		else {
			a = c;
		}

		// Проверяем условие остановки
		if (fabs(b - a) < epsilon) {
			return c;
		}
	}

	// Если метод не сходится, возвращаем последнее значение c
	return c;
}

// Метод хорд
double ChordMethod(double a, double b, double epsilon, int maxIterations) {
	// Убедимся, что a < b
	if (a > b) {
		std::swap(a, b);
	}

	double c = a;
	for (int i = 0; i < maxIterations; ++i) {
		// Вычисляем середину интервала [a, b]
		c = (a + b) / 2;

		// Вычисляем значения функции в точках a и c
		double f_a = func(a);
		double f_c = func(c);

		// Вычисляем значение функции в точке, где она пересекает ось x
		double x_chord = a - f_a * (c - a) / (f_c - f_a);

		// Проверяем, находится ли корень в интервале [a, x_chord] или [x_chord, b]
		if (func(x_chord) < 0) {
			b = x_chord;
		}
		else {
			a = x_chord;
		}

		// Проверяем условие остановки
		if (fabs(b - a) < epsilon) {
			return x_chord;
		}
	}

	// Если метод не сходится, возвращаем последнее значение x_chord
	return c;
}



void CTranscendentalEquationSolverDlg::OnBnClickedButtonSolve()
{
	CString method;
	CComboBox* pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_METHOD);
	if (pComboBox != NULL)
	{
		int nSel = pComboBox->GetCurSel();
		if (nSel != CB_ERR)
		{
			pComboBox->GetLBText(nSel, method);
		}
	}

	double precision = 0.0001; // Пример точности
	CString precisionStr;
	GetDlgItemText(IDC_EDIT_PRECISION, precisionStr);
	precisionStr.Trim();
	if (!precisionStr.IsEmpty()) {
		precision = wcstod(precisionStr.GetString(), NULL);
	}

	double result = 0.0;
	if (method == _T("Newton")) {
		result = NewtonMethod(0.0, precision, 100); // Пример начальной точки, итераций и точности
	}
	else if (method == _T("Bisection")) {
		result = BisectionMethod(1.68, 1.69, precision, 100); // Пример начальных границ, итераций и точности
	}
	else if (method == _T("Chord")) {
		result = ChordMethod(1.68, 1.69, precision, 100); // Пример начальных границ, итераций и точности
	}

	double trueValue = 1.68; // Пример точного значения
	double error = fabs(result - trueValue); // Расчет абсолютной ошибки
	double relativeError = error / trueValue; // Расчет относительной ошибки

	// Отображение результата в текстовом поле
	CString resultStr;
	resultStr.Format(_T("Результат: %f"), result);
	SetDlgItemText(IDC_EDIT_RESULT, resultStr);

	CString errorStr;
	errorStr.Format(_T("Точность: %f"), precision);
	SetDlgItemText(IDC_EDIT_ERROR, errorStr); // Предполагается, что IDC_EDIT_ERROR - идентификатор текстового поля для отображения точности

}
