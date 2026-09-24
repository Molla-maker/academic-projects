
// Задание 2Dlg.h: файл заголовка
//

#pragma once


// Диалоговое окно CЗадание2Dlg
class CЗадание2Dlg : public CDialogEx
{
// Создание
public:
	CЗадание2Dlg(CWnd* pParent = nullptr);	// стандартный конструктор
	int SWMD;

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD__2_DIALOG };
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
	CButton Radio_1;
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	CButton RCHK2;
	CButton RCHK3;
	CButton RCHK1;
	afx_msg void OnBnClickedButton1();
	int ZnA;
	int ZnB;
};
