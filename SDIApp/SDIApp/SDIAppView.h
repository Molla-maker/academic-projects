
// SDIAppView.h: интерфейс класса CSDIAppView
//

#pragma once
class CSDIAppDoc;

class CSDIAppView : public CView
{
protected: // создать только из сериализации
	CSDIAppView() noexcept;
	DECLARE_DYNCREATE(CSDIAppView)

	// Атрибуты
public:
	CSDIAppDoc* GetDocument() const;
	bool m_bShowSin;
	bool m_bShowSinArc1;
	bool m_bShowSinArc2;
	bool m_bShowOx;
	bool m_bShowOy;
	bool m_bShowBrush;
	bool m_bShowBrushVertical;
	bool m_bShowBrush45;
	bool m_bShowBrushTool;


	// Операции
public:

	// Переопределение
public:
	virtual void OnDraw(CDC* pDC);  // переопределено для отрисовки этого представления
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();


protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);


	// Реализация
public:
	virtual ~CSDIAppView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMymenuLine();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // версия отладки в SDIAppView.cpp
inline CSDIAppDoc* CSDIAppView::GetDocument() const
{
	return reinterpret_cast<CSDIAppDoc*>(m_pDocument);
}
#endif