
// MyMFCAppDlg.h: файл заголовка
//

#pragma once


// Диалоговое окно CMyMFCAppDlg
class CMyMFCAppDlg : public CDialogEx
{
// Создание
public:
	CMyMFCAppDlg(CWnd* pParent = nullptr);	// стандартный конструктор

	void UpdateListBox()
	{
		// Пример кода для добавления элемента в CListBox
		m_ListBox.AddString(L"Item 4");
		m_ListBox.AddString(L"Item 5");
		m_ListBox.AddString(L"Item 6");
}

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYMFCAPP_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	int MyVar;
	CSliderCtrl m_Slyder;
	afx_msg void OnBnClickedButton2();
	CStatic m_TextControl;
	CString m_StrItemSelected;
	CListBox m_ListBox;
	afx_msg void OnLbnSelchangeList2();
	CTreeCtrl m_TreeCtrl;
	CScrollBar m_ScrollBar;
	CProgressCtrl m_Progress;
	CButton m_Checkbox;
	CListCtrl m_ListCtrl;
	afx_msg void OnTvnSelchangedTree1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedRadio();
};
