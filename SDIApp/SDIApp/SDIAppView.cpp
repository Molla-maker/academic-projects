
// SDIAppView.cpp: реализация класса CSDIAppView
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "SDIApp.h"
#include <windows.h>
#include <vector>
#endif

#include "SDIAppDoc.h"
#include "SDIAppView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// CSDIAppView

IMPLEMENT_DYNCREATE(CSDIAppView, CView)

BEGIN_MESSAGE_MAP(CSDIAppView, CView)
    // Стандартные команды печати
    ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
    ON_WM_CREATE()
    ON_COMMAND(ID_MYMENU_LINE, &CSDIAppView::OnMymenuLine)
    ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// Создание или уничтожение CSDIAppView
class CSDIAppDoc;

CSDIAppView::CSDIAppView() noexcept
{
    // TODO: добавьте код создания
    m_bShowSin = true;
    m_bShowSinArc1 = true;
    m_bShowSinArc2 = true;
    m_bShowOx = true;
    m_bShowOy = true;
    m_bShowBrush = true;
    m_bShowBrushVertical = true;
    m_bShowBrush45 = true;
    m_bShowBrushTool = true;

}

CSDIAppView::~CSDIAppView()
{
}

BOOL CSDIAppView::PreCreateWindow(CREATESTRUCT& cs)
{
    // TODO: изменить класс Window или стили посредством изменения
    //  CREATESTRUCT cs

    return CView::PreCreateWindow(cs);
}

void CSDIAppView::OnInitialUpdate()
{
    CView::OnInitialUpdate();

    CSDIAppDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (pDoc)
        pDoc->m_pView = this;
}

void CSDIAppView::OnDraw(CDC* pDC)
{
    CSDIAppDoc* pDoc = GetDocument();
    ASSERT_VALID(pDC);
    if (!pDoc)
        return;

    CRect rt;
    GetClientRect(&rt);
    int centerY = rt.Height() / 2;
    int centerX = rt.Width() / 2;

    double scaleX = rt.Width() / (2 * M_PI);
    double scaleY = rt.Height() / 2;
    double step = 2 * M_PI / rt.Width();

    CPen penSin(PS_SOLID, 1, RGB(0, 0, 255));  // Синий для волн синуса
    CPen penAxis(PS_SOLID, 1, RGB(0, 0, 0));   // Черный для осей координат
    CPen* oldPen = pDC->SelectObject(&penSin);

    // Отрисовка крестовой штриховки для всего окна, если активна
    if (m_bShowBrushTool)
    {
        CBrush brushCross(HS_CROSS, RGB(200, 200, 200));
        pDC->FillRect(&rt, &brushCross);
    }

    // Отрисовка осей OX и OY
    if (m_bShowOx) {
        pDC->SelectObject(&penAxis);
        pDC->MoveTo(0, centerY);
        pDC->LineTo(rt.Width(), centerY);
    }
    if (m_bShowOy) {
        pDC->SelectObject(&penAxis);
        pDC->MoveTo(centerX, 0);
        pDC->LineTo(centerX, rt.Height());
    }

    // Отрисовка первой полуволны с выбором штриховки
    if (m_bShowSinArc1) {
        pDC->SelectObject(&penSin);
        pDC->MoveTo(0, centerY);

        // Кисть для первой полуволны
        CBrush hatchBrush1;
        if (m_bShowBrushVertical) {
            hatchBrush1.CreateHatchBrush(HS_VERTICAL, RGB(0, 0, 255));
        }
        else if (m_bShowBrush45) {
            hatchBrush1.CreateHatchBrush(HS_FDIAGONAL, RGB(0, 0, 255));
        }

        // Массив точек для первой синусоиды
        std::vector<POINT> points1 = { {0, centerY} };
        for (double x = 0; x <= M_PI; x += step) {
            int pixelX = static_cast<int>(x * scaleX);
            int pixelY = static_cast<int>(centerY - sin(x) * scaleY);
            points1.push_back({ pixelX, pixelY });
            pDC->LineTo(pixelX, pixelY); // Отрисовка синусоиды
        }
        points1.push_back({ int(M_PI * scaleX), centerY });

        // Применение кисти штриховки
        if (hatchBrush1.GetSafeHandle()) {
            CBrush* oldBrush = pDC->SelectObject(&hatchBrush1);
            pDC->Polygon(points1.data(), points1.size());
            pDC->SelectObject(oldBrush);
        }
    }

    // Отрисовка второй полуволны с выбором штриховки
    if (m_bShowSinArc2) {
        pDC->SelectObject(&penSin);
        pDC->MoveTo(centerX, centerY);

        // Кисть для второй полуволны
        CBrush hatchBrush2;
        if (m_bShowBrushVertical) {
            hatchBrush2.CreateHatchBrush(HS_VERTICAL, RGB(0, 255, 0));
        }
        else if (m_bShowBrush45) {
            hatchBrush2.CreateHatchBrush(HS_FDIAGONAL, RGB(0, 255, 0));
        }

        // Массив точек для второй синусоиды
        std::vector<POINT> points2 = { {centerX, centerY} };
        for (double x = M_PI; x <= 2 * M_PI; x += step) {
            int pixelX = static_cast<int>(x * scaleX);
            int pixelY = static_cast<int>(centerY - sin(x) * scaleY);
            points2.push_back({ pixelX, pixelY });
            pDC->LineTo(pixelX, pixelY); // Отрисовка синусоиды
        }
        points2.push_back({ int(2 * M_PI * scaleX), centerY });

        // Применение кисти штриховки
        if (hatchBrush2.GetSafeHandle()) {
            CBrush* oldBrush = pDC->SelectObject(&hatchBrush2);
            pDC->Polygon(points2.data(), points2.size());
            pDC->SelectObject(oldBrush);
        }
    }

    // Восстанавливаем исходные перо и кисть
    pDC->SelectObject(oldPen);
}


// Печать CSDIAppView

BOOL CSDIAppView::OnPreparePrinting(CPrintInfo* pInfo)
{
    // подготовка по умолчанию
    return DoPreparePrinting(pInfo);
}

void CSDIAppView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
    // TODO: добавьте дополнительную инициализацию перед печатью
}

void CSDIAppView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
    // TODO: добавьте очистку после печати
}


// Диагностика CSDIAppView

#ifdef _DEBUG
void CSDIAppView::AssertValid() const
{
    CView::AssertValid();
}

void CSDIAppView::Dump(CDumpContext& dc) const
{
    CView::Dump(dc);
}

CSDIAppDoc* CSDIAppView::GetDocument() const // встроена неотлаженная версия
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSDIAppDoc)));
    return (CSDIAppDoc*)m_pDocument;
}
#endif //_DEBUG



// Обработчики сообщений CMFCApplicationView


void CSDIAppView::OnMymenuLine()
{
	// TODO: добавьте свой код обработчика команд
	CSDIAppDoc* pDoc = GetDocument();
	pDoc->m_bLines = !pDoc->m_bLines;

	Invalidate();
}


void CSDIAppView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	CMenu MainMenu;
	MainMenu.LoadMenuW(IDR_MAINFRAME);

	CMenu* SubMenu = MainMenu.GetSubMenu(3);
	ClientToScreen(&point);
	//if (pDoc->m_bLine1)
	//	SubMenu->CheckMenuItem(ID_LINES_LINE1, MF_CHECKED);
	SubMenu->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);

	CView::OnRButtonUp(nFlags, point);
}