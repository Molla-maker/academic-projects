
// courseworkDlg.h: файл заголовка
//

#pragma once


// Диалоговое окно CcourseworkDlg
class CcourseworkDlg : public CDialog
{
// Создание
public:
	CcourseworkDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COURSEWORK_DIALOG };
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
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonFirst();
	afx_msg void OnStnClickedStaticFirst();
	afx_msg void OnEnChangeEditFirst();
	double m_long;
	afx_msg void OnStnClickedPic2();
};
