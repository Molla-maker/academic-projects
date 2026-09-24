
// MyMFCAppDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "MyMFCApp.h"
#include "MyMFCAppDlg.h"
#include "afxdialogex.h"

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


// Диалоговое окно CMyMFCAppDlg



CMyMFCAppDlg::CMyMFCAppDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MYMFCAPP_DIALOG, pParent)
	, MyVar(0)
	, m_StrItemSelected(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyMFCAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, MyVar);
	DDX_Control(pDX, ID_SLYDER_VALUE, m_Slyder);
	DDX_Control(pDX, IDC_STATIC_TXT, m_TextControl);
	DDX_Text(pDX, IDC_STATIC_TXT, m_StrItemSelected);
	DDX_Control(pDX, IDC_STATIC_TXT, m_TextControl);
	DDX_Control(pDX, IDC_TREE1, m_TreeCtrl);
	DDX_Control(pDX, IDC_SCROLLBAR1, m_ScrollBar);
	DDX_Control(pDX, IDC_PROGRESS1, m_Progress);
	DDX_Control(pDX, IDC_CHECKBOX1, m_Checkbox);
	DDX_Control(pDX, IDC_LIST3, m_ListCtrl);
}

BEGIN_MESSAGE_MAP(CMyMFCAppDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMyMFCAppDlg::OnBnClickedButton1)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BUTTON2, &CMyMFCAppDlg::OnBnClickedButton2)
	ON_LBN_SELCHANGE(IDC_LIST2, &CMyMFCAppDlg::OnLbnSelchangeList2)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &CMyMFCAppDlg::OnTvnSelchangedTree1)
	ON_BN_CLICKED(IDC_RADIO, &CMyMFCAppDlg::OnBnClickedRadio)
END_MESSAGE_MAP()


// Обработчики сообщений CMyMFCAppDlg

BOOL CMyMFCAppDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	((CButton*)GetDlgItem(IDC_CHECKBOX1))->SetCheck(BST_UNCHECKED); // Установите флажок в неотмеченное состояние

	// Добавление пункта "О программе..." в системное меню.
	CWnd* pWnd = GetDlgItem(IDC_COMBO_VALUE);

	int num = ((CComboBox*)pWnd)->AddString(L"Первая строка");
	((CComboBox*)pWnd)->SetItemData(num, 1);

	num = ((CComboBox*)pWnd)->AddString(L"Вторая строка");
	((CComboBox*)pWnd)->SetItemData(num, 2);

	num = ((CComboBox*)pWnd)->AddString(L"Третья строка");
	((CComboBox*)pWnd)->SetItemData(num, 3);

	// Добавляем корневой элемент в контрол дерева
	HTREEITEM hRoot = m_TreeCtrl.InsertItem(_T("Корневой элемент"));

	// Добавляем дочерние элементы в контрол дерева
	HTREEITEM hChild1 = m_TreeCtrl.InsertItem(_T("Дочерний элемент  1"), hRoot);
	HTREEITEM hChild2 = m_TreeCtrl.InsertItem(_T("Дочерний элемент  2"), hRoot);

	// Добавляем вложенные элементы в дочерний элемент  1
	HTREEITEM hGrandChild1 = m_TreeCtrl.InsertItem(_T("Внук  1"), hChild1);
	HTREEITEM hGrandChild2 = m_TreeCtrl.InsertItem(_T("Внук  2"), hChild1);

	HTREEITEM hGrandChild3 = m_TreeCtrl.InsertItem(_T("Внук   3"), hChild2);
HTREEITEM hGrandChild4 = m_TreeCtrl.InsertItem(_T("Внук   4"), hChild2);


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

	m_ListCtrl.InsertColumn(0, _T("Заголовок  1"), LVCFMT_LEFT, 100);
	m_ListCtrl.InsertColumn(1, _T("Заголовок  2"), LVCFMT_LEFT, 100);
	m_ListCtrl.InsertColumn(2, _T("Заголовок  3"), LVCFMT_LEFT, 100);

	// Добавление элементов
	m_ListCtrl.InsertItem(0, _T("Элемент  1"));
	m_ListCtrl.SetItemText(0, 1, _T("Текст  2"));
	m_ListCtrl.SetItemText(0, 2, _T("Текст  3"));

	m_ListCtrl.InsertItem(1, _T("Элемент  2"));
	m_ListCtrl.SetItemText(1, 1, _T("Текст  4"));
	m_ListCtrl.SetItemText(1, 2, _T("Текст  5"));

	// Добавление еще одного элемента
	m_ListCtrl.InsertItem(2, _T("Элемент  3"));
	m_ListCtrl.SetItemText(2, 1, _T("Текст  6"));
	m_ListCtrl.SetItemText(2, 2, _T("Текст  7"));

	m_Progress.SetRange(0, 500); // Установите диапазон от  0 до  500
	m_Progress.SetPos(0); // Установите начальное положение в  0

	m_Slyder.SetRange(0, 500);
	m_Slyder.SetPos((m_Slyder.GetRangeMax() + m_Slyder.GetRangeMin())/2);
	// TODO: добавьте дополнительную инициализацию
	m_ListBox.Create(WS_CHILD | WS_VISIBLE | LBS_NOTIFY,
		CRect(10, 10, 100, 100), // Задайте нужные координаты
		this,
		IDC_LIST2); // Используйте уникальный идентификатор

	// Добавляем строки в ListBox
	m_ListBox.AddString(_T("Item  1"));
	m_ListBox.AddString(_T("Item  2"));
	m_ListBox.AddString(_T("Item  3"));


	// Центрирование ListBox
	CRect rect;
	GetClientRect(&rect);
	m_ListBox.MoveWindow(rect.left + (rect.Width() - 120) / 2,
		rect.top + (rect.Height() - 120) / 2,
		120, 120); // Увеличенные размеры ListBox до  200x200



	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CMyMFCAppDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMyMFCAppDlg::OnPaint()
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
HCURSOR CMyMFCAppDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMyMFCAppDlg::OnBnClickedButton1()
{
	// TODO: добавьте свой код обработчика уведомлений
	UpdateData();
	CString str;
	str.Format(L"%i", MyVar);
	MessageBox(str);
}

void CMyMFCAppDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// Проверяем, является ли прокрутка от CScrollBar или CSliderCtrl
	if (pScrollBar == (CScrollBar*)&m_ScrollBar || pScrollBar == (CScrollBar*)&m_Slyder)
	{
		// Определяем новое положение ползунка CSliderCtrl
		int newSliderPos = m_Slyder.GetPos();

		// Изменяем положение ползунка CSliderCtrl в зависимости от кода прокрутки
		switch (nSBCode)
		{
		case SB_LINELEFT: // Пользователь переместил ползунок влево
			newSliderPos -= 10;
			break;
		case SB_LINERIGHT: // Пользователь переместил ползунок вправо
			newSliderPos += 10;
			break;
		case SB_THUMBTRACK: // Пользователь перемещает ползунок
			newSliderPos = nPos;
			break;
		}

		// Ограничиваем положение ползунка CSliderCtrl от   0 до   500
		newSliderPos = max(0, min(500, newSliderPos));

		// Обновляем положение ползунка CSliderCtrl
		m_Slyder.SetPos(newSliderPos);

		// Обновляем поле ввода с новым значением
		CString str;
		str.Format(_T("%d"), newSliderPos);
		SetDlgItemText(IDC_EDIT1, str);

		// Обновляем прогресс-бар
		m_Progress.SetPos(newSliderPos);

		// Получаем максимальное значение диапазона прогресс-бара
		int nLower, nUpper;
		m_Progress.GetRange(nLower, nUpper);

		// Проверяем, заполнен ли прогресс-бар
		if (newSliderPos == nUpper)
		{
			// Прогресс-бар заполнен, устанавливаем флажок в отмеченное состояние
			m_Checkbox.SetCheck(BST_CHECKED);
		}
		else
		{
			// Прогресс-бар не заполнен, устанавливаем флажок в неотмеченное состояние
			m_Checkbox.SetCheck(BST_UNCHECKED);
		}
	}

	// Вызываем базовый обработчик, чтобы сохранить стандартное поведение
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CMyMFCAppDlg::OnBnClickedButton2()
{
	// TODO: добавьте свой код обработчика уведомлений
	CWnd* pWnd = GetDlgItem(IDC_COMBO_VALUE);
	int selection = ((CComboBox*)pWnd)->GetCurSel();
	int res = ((CComboBox*)pWnd)->GetItemData(selection);
	CString str;
	str.Format(L"%i", res);
	MessageBox(str);
}


void CMyMFCAppDlg::OnLbnSelchangeList2()
{
	int nIndex = m_ListBox.GetCurSel();
	if (nIndex != LB_ERR)
	{
		m_ListBox.GetText(nIndex, m_StrItemSelected);
		// Обновляем данные, если это необходимо
		// Обновляем CStatic с выбранным текстом
		m_TextControl.SetWindowText(m_StrItemSelected);
		// UpdateData(FALSE);
	}
}



void CMyMFCAppDlg::OnTvnSelchangedTree1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: добавьте свой код обработчика уведомлений
	*pResult = 0;
}



void CMyMFCAppDlg::OnBnClickedRadio()
{
	// TODO: добавьте свой код обработчика уведомлений
	UpdateListBox();
} 
