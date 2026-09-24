// Задание 2Dlg.cpp: файл реализации

#include "pch.h"
#include "framework.h"
#include "Задание 2.h"
#include "Задание 2Dlg.h"
#include "afxdialogex.h"

#define M_PI 3.14159265358979323846


#ifdef _DEBUG
#define new DEBUG_NEW
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

// Диалоговое окно CЗадание2Dlg

CЗадание2Dlg::CЗадание2Dlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD__2_DIALOG, pParent)

    , ZnA(2.4)
    , ZnB(4.08)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CЗадание2Dlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_RADIO2, RCHK2);
    DDX_Control(pDX, IDC_RADIO3, RCHK3);
    DDX_Control(pDX, IDC_RADIO1, RCHK1);
    DDX_Text(pDX, IDC_EDIT1, ZnA);
    DDX_Text(pDX, IDC_EDIT2, ZnB);
}

BEGIN_MESSAGE_MAP(CЗадание2Dlg, CDialogEx)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_RADIO1, &CЗадание2Dlg::OnBnClickedRadio1)
    ON_BN_CLICKED(IDC_RADIO2, &CЗадание2Dlg::OnBnClickedRadio2)
    ON_BN_CLICKED(IDC_RADIO3, &CЗадание2Dlg::OnBnClickedRadio3)
    ON_BN_CLICKED(IDC_BUTTON1, &CЗадание2Dlg::OnBnClickedButton1)
END_MESSAGE_MAP()

// Обработчики сообщений CЗадание2Dlg

BOOL CЗадание2Dlg::OnInitDialog()
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
    // если главное окно приложения не является диалоговым
    SetIcon(m_hIcon, TRUE);            // Крупный значок
    SetIcon(m_hIcon, FALSE);           // Мелкий значок

    // TODO: добавьте дополнительную инициализацию

    RCHK1.SetCheck(0);
    RCHK2.SetCheck(0);
    RCHK3.SetCheck(0);

    double str1 = 2.4;
    double str2 = 4.08;
    CString str1Text, str2Text;
    str1Text.Format(L"%.3f", str1);
    str2Text.Format(L"%.3f", str2);
    SetDlgItemText(IDC_EDIT1, str1Text);
    SetDlgItemText(IDC_EDIT2, str2Text);
    return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CЗадание2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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
// чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
// это автоматически выполняется рабочей областью.

void CЗадание2Dlg::OnPaint()
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
// свернутого окна.
HCURSOR CЗадание2Dlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}

double f(double x)
{
    return (4.5 - x) * (1.0 / tan(M_PI / x)); // Используем ctg(pi/x) вместо ctg(pi/x)
}

void CЗадание2Dlg::OnBnClickedRadio1()
{
    SWMD = 1;
}

void CЗадание2Dlg::OnBnClickedRadio2()
{
    SWMD = 2;
}

void CЗадание2Dlg::OnBnClickedRadio3()
{
    SWMD = 3;
}

void CЗадание2Dlg::OnBnClickedButton1()
{
    UpdateData(TRUE);
    int a = 2.4;
    int b = 4.08;
    double h = 0.00001;
    double x = a;
    int shag = (b - a) / h;
    double sum = 0;
    double sumX = 0;

    if (SWMD == 1)
    {
        for (int i = 0; i <= shag; i++)
        {
            double xi = a + (h * i);
            sum += f(xi + h / 2);
        }
        sumX = sum * h;
    }
    else if (SWMD == 2)
    {
        sum += (f(a) + f(b)) / 2;

        for (int i = 1; i < shag; i += 1)
        {
            double xi = a + h * i;
            sum += f(xi);
        }

        sumX = sum * h;
    }
    else if (SWMD == 3)
    {
        sum = f(x) + f(x + h * (shag - 1));
        for (int i = 1; i < shag - 1; i += 2)
            sum += f(x + h * i);
        sumX += 4 * sum;
        sum = 0;
        for (int i = 2; i < shag - 1; i += 2)
            sum += f(x + h * i);
        sumX = (sumX + 2 * sum) * h / 3;
    }

    CString textT;
    textT.Format(_T("%f"), sumX);
    GetDlgItem(IDC_STATIC4)->SetWindowText(textT);
}