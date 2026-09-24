

// SDIAppDoc.h: интерфейс класса CSDIAppDoc 
//


#pragma once
#include "MyTreeView.h"


class CSDIAppView;


class CSDIAppDoc : public CDocument
{
protected: // создать только из сериализации
	CSDIAppDoc() noexcept;
	DECLARE_DYNCREATE(CSDIAppDoc)

	// Атрибуты
public:
	int iVersion = 1;
	int Px, Py, Pz;
	bool m_bLines = true;
	CMyTreeView* m_pTree;
	//data dat;

	// Операции
public:

	// Переопределение
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	CSDIAppView* m_pView;
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

	// Реализация
public:
	virtual ~CSDIAppDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Вспомогательная функция, задающая содержимое поиска для обработчика поиска
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
