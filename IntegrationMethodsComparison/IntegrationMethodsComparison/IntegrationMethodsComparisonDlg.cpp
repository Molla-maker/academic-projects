
// IntegrationMethodsComparisonDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "IntegrationMethodsComparison.h"
#include "IntegrationMethodsComparisonDlg.h"
#include "afxdialogex.h"
#include <cmath>
#include <windows.h>


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


// Диалоговое окно CIntegrationMethodsComparisonDlg



CIntegrationMethodsComparisonDlg::CIntegrationMethodsComparisonDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_INTEGRATIONMETHODSCOMPARISON_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CIntegrationMethodsComparisonDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CIntegrationMethodsComparisonDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_INTEGRATE, &CIntegrationMethodsComparisonDlg::OnBnClickedButtonIntegrate)
	ON_BN_CLICKED(IDC_BUTTON_EVALUATE_ACCURACY, &CIntegrationMethodsComparisonDlg::OnBnClickedButtonEvaluateAccuracy)
END_MESSAGE_MAP()


// Обработчики сообщений CIntegrationMethodsComparisonDlg

BOOL CIntegrationMethodsComparisonDlg::OnInitDialog()
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

	CComboBox* pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_METHOD);
	if (pComboBox != NULL)
	{
		pComboBox->AddString(_T("Rectangle"));
		pComboBox->AddString(_T("Trapezoid"));
		pComboBox->AddString(_T("Simpson"));
	}

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CIntegrationMethodsComparisonDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CIntegrationMethodsComparisonDlg::OnPaint()
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
HCURSOR CIntegrationMethodsComparisonDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// Функция для вычисления интеграла методом прямоугольников
double RectangleMethod(double a, double b, int n) {
	double h = (b - a) / n;
	double sum = 0;
	for (int i = 0; i < n; ++i) {
		double x = a + i * h;
		sum += (4.5 - x) / tan(M_PI / x);
	}
	return sum * h;
}

// Функция для вычисления интеграла методом трапеций
double TrapezoidMethod(double a, double b, int n) {
	double h = (b - a) / n;
	double sum = 0.5 * ((4.5 - a) / tan(M_PI / a) + (4.5 - b) / tan(M_PI / b));
	for (int i = 1; i < n; ++i) {
		double x = a + i * h;
		sum += (4.5 - x) / tan(M_PI / x);
	}
	return sum * h;
}

// Функция для вычисления интеграла методом парабол
double SimpsonMethod(double a, double b, int n) {
	double h = (b - a) / n;
	double sum = (4.5 - a) / tan(M_PI / a) + (4.5 - b) / tan(M_PI / b);
	for (int i = 1; i < n; ++i) {
		double x = a + i * h;
		if (i % 2 == 0) {
			sum += 2 * (4.5 - x) / tan(M_PI / x);
		}
		else {
			sum += 4 * (4.5 - x) / tan(M_PI / x);
		}
	}
	return sum * h / 3;
}

const char* ConvertCStringToChar(const CString& str)
{
	int len = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);
	char* buffer = new char[len];
	WideCharToMultiByte(CP_ACP, 0, str, -1, buffer, len, NULL, NULL);
	return buffer;
}



void CIntegrationMethodsComparisonDlg::OnBnClickedButtonIntegrate()
{
	// Получение значений a и b из полей ввода
	double a, b;
	CString aStr, bStr;
	CEdit* pEditA = (CEdit*)GetDlgItem(IDC_EDIT_A);
	CEdit* pEditB = (CEdit*)GetDlgItem(IDC_EDIT_B);
	pEditA->GetWindowText(aStr);
	pEditB->GetWindowText(bStr);

	// Преобразование CString в const char*
	const char* aCStr = ConvertCStringToChar(aStr);
	const char* bCStr = ConvertCStringToChar(bStr);
	a = atof(aCStr);
	b = atof(bCStr);

	// Получение выбранного метода из выпадающего списка
	CComboBox* pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_METHOD);
	CString selectedMethod;
	pComboBox->GetWindowText(selectedMethod);

	// Вызов соответствующей функции интегрирования
	double result = 0.0;
	if (selectedMethod == "Rectangle") {
		result = RectangleMethod(a, b, 10000); // Пример вызова функции, предполагается, что n =   100
	}
	else if (selectedMethod == "Trapezoid") {
		result = TrapezoidMethod(a, b, 10000); // Пример вызова функции, предполагается, что n =   100
	}
	else if (selectedMethod == "Simpson") {
		result = SimpsonMethod(a, b, 10000); // Пример вызова функции, предполагается, что n =   100
	}

	// Вывод результата в статический текст
	CString resultStr;
	resultStr.Format(_T("%.5f"), result); // Форматирование результата с точностью до   5 знаков после запятой
	CStatic* pStaticResult = (CStatic*)GetDlgItem(IDC_STATIC_RESULT);
	pStaticResult->SetWindowText(resultStr);
}

struct IntegrationAccuracyResults {
	double rectangularAccuracy;
	double trapezoidalAccuracy;
	double simpsonAccuracy;
};

double GetMaxAccuracyFromResults(const IntegrationAccuracyResults& results) {
	double maxAccuracy = results.rectangularAccuracy;
	if (results.trapezoidalAccuracy > maxAccuracy) {
		maxAccuracy = results.trapezoidalAccuracy;
	}
	if (results.simpsonAccuracy > maxAccuracy) {
		maxAccuracy = results.simpsonAccuracy;
	}
	return maxAccuracy;
}

IntegrationAccuracyResults CalculateAccuracy(double a, double b, int N, double exactValue) {
	IntegrationAccuracyResults results;
	results.rectangularAccuracy = fabs((exactValue - RectangleMethod(a, b, N)) / exactValue);
	results.trapezoidalAccuracy = fabs((exactValue - TrapezoidMethod(a, b, N)) / exactValue);
	results.simpsonAccuracy = fabs((exactValue - SimpsonMethod(a, b, N)) / exactValue);

	// Возвращаем структуру с результатами
	return results;
}


int FindCriticalN(double a, double b, double exactValue) {
	IntegrationAccuracyResults results = CalculateAccuracy(a, b, 10000, 1.0);
	double maxAccuracy = GetMaxAccuracyFromResults(results);
	int N = 1; // Начальное число разбиений
	double accuracy = 1.0; // Начальная точность

	while (accuracy > 0.01) { // Пока точность больше  1%
		results = CalculateAccuracy(a, b, N, exactValue); // Получаем результаты для текущего N
		maxAccuracy = GetMaxAccuracyFromResults(results); // Извлекаем максимальную точность
		accuracy = maxAccuracy; // Обновляем значение точности
		N++; // Увеличиваем число разбиений
	}

	return N - 1; // Возвращаем предыдущее число разбиений, при котором точность была больше  1%
}





void CIntegrationMethodsComparisonDlg::OnBnClickedButtonEvaluateAccuracy() {

	// Получение значений a и b из полей ввода
	CString aStr, bStr;
	CEdit* pEditA = (CEdit*)GetDlgItem(IDC_EDIT_A);
	CEdit* pEditB = (CEdit*)GetDlgItem(IDC_EDIT_B);
	pEditA->GetWindowText(aStr);
	pEditB->GetWindowText(bStr);

	// Преобразование CString в double
	double a = atof(ConvertCStringToChar(aStr));
	double b = atof(ConvertCStringToChar(bStr));


	// Вызов функции CalculateAccuracy и получение результатов
	IntegrationAccuracyResults results = CalculateAccuracy(a, b, 10000, 1.0); // Предполагается, что N =   100 и точное значение интеграла равно   1.0

	// Отображение результатов в диалоговом окне или сохранение их в файл
	// Например, отображение в CStatic или CEdit
	CString resultStr;
	resultStr.Format(_T("Rectangular Accuracy: %.5f\nTrapezoidal Accuracy: %.5f\nSimpson Accuracy: %.5f"),
		results.rectangularAccuracy, results.trapezoidalAccuracy, results.simpsonAccuracy);
	CStatic* pStaticResult = (CStatic*)GetDlgItem(IDC_STATIC_ACCURACY);
	pStaticResult->SetWindowText(resultStr);
}