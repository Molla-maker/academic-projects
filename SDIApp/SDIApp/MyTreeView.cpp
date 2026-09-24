// MyTreeView.cpp: файл реализации
//

#include "pch.h"
#include "SDIApp.h"
#include "MyTreeView.h"
#include "SDIAppDoc.h"
#include "SDIAppView.h"	




// CMyTreeView

IMPLEMENT_DYNCREATE(CMyTreeView, CTreeView)

CMyTreeView::CMyTreeView()
{

}

void CMyTreeView::UpdateView()
{
	CTreeCtrl& tree = GetTreeCtrl();
	CSDIAppDoc* pDoc = (CSDIAppDoc*)GetDocument();
	if (!pDoc || !pDoc->m_pView)
		return;

	CSDIAppView* pView = pDoc->m_pView;

	pView->m_bShowSin = tree.GetCheck(m_hSin);
	pView->m_bShowSinArc1 = tree.GetCheck(m_hSinArc1);
	pView->m_bShowSinArc2 = tree.GetCheck(m_hSinArc2);
	pView->m_bShowOx = tree.GetCheck(m_hOx);
	pView->m_bShowOy = tree.GetCheck(m_hOy);
	pView->m_bShowBrush = tree.GetCheck(m_hBrush);
	pView->m_bShowBrushVertical = tree.GetCheck(m_hBrushVertical);
	pView->m_bShowBrush45 = tree.GetCheck(m_hBrush45);
	pView->m_bShowBrushTool = tree.GetCheck(m_hBrushTool);

	pView->Invalidate();
}

void CMyTreeView::OnTvnItemChanged(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMTVITEMCHANGE* pNMTVItemChange = reinterpret_cast<NMTVITEMCHANGE*>(pNMHDR);
	*pResult = 0;
	if ((pNMTVItemChange->uStateNew & TVIS_STATEIMAGEMASK) !=
		(pNMTVItemChange->uStateOld & TVIS_STATEIMAGEMASK))
	{
		CTreeCtrl& treeCtrl = GetTreeCtrl();
		HTREEITEM hItem = pNMTVItemChange->hItem;
		BOOL bChecked = treeCtrl.GetCheck(hItem);
		if (treeCtrl.ItemHasChildren(hItem))
		{
			SetChildrenChecked(hItem, bChecked);
		}
		UpdateParentState(treeCtrl.GetParentItem(hItem));
		UpdateView();
	}
}
void CMyTreeView::SetChildrenChecked(HTREEITEM hItem, BOOL bCheck)
{
	CTreeCtrl& treeCtrl = GetTreeCtrl();
	treeCtrl.SetRedraw(FALSE);
	HTREEITEM hChildItem = treeCtrl.GetChildItem(hItem);
	while (hChildItem != NULL)
	{
		treeCtrl.SetCheck(hChildItem, bCheck);
		if (treeCtrl.ItemHasChildren(hChildItem))
		{
			SetChildrenChecked(hChildItem, bCheck);
		}
		hChildItem = treeCtrl.GetNextSiblingItem(hChildItem);
	}
	treeCtrl.SetRedraw(TRUE);
}

void CMyTreeView::UpdateParentState(HTREEITEM hItem)
{
	if (hItem == NULL)
		return;
	CTreeCtrl& treeCtrl = GetTreeCtrl();
	BOOL AllChecked = TRUE;
	BOOL AllUnchecked = TRUE;
	HTREEITEM hChildItem = treeCtrl.GetChildItem(hItem);
	while (hChildItem != NULL)
	{
		if (treeCtrl.GetCheck(hChildItem))
			AllUnchecked = FALSE;
		else
			AllChecked = FALSE;

		hChildItem = treeCtrl.GetNextSiblingItem(hChildItem);
	}
	if (AllChecked)
		treeCtrl.SetCheck(hItem, TRUE);
	else if (AllUnchecked)
		treeCtrl.SetCheck(hItem, FALSE);
	else
		treeCtrl.SetCheck(hItem, FALSE);
	UpdateParentState(treeCtrl.GetParentItem(hItem));
}
void CMyTreeView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CTreeCtrl& treeCtrl = GetTreeCtrl();
	UINT uFlags;
	HTREEITEM hItem = treeCtrl.HitTest(point, &uFlags);
	if ((uFlags & TVHT_ONITEMSTATEICON) && hItem != NULL)
	{
		BOOL bChecked = !treeCtrl.GetCheck(hItem);
		treeCtrl.SetCheck(hItem, bChecked);
		if (treeCtrl.ItemHasChildren(hItem))
		{
			SetChildrenChecked(hItem, bChecked);
		}
		UpdateParentState(treeCtrl.GetParentItem(hItem));
		UpdateView();
		return;
	}
}

void CMyTreeView::FillTree() {
	CTreeCtrl& tree = GetTreeCtrl();
	tree.DeleteAllItems();

	m_hSin = tree.InsertItem(L"Синус", -1, -1, NULL, TVI_ROOT);
	tree.SetCheck(m_hSin, TRUE);

	m_hSinArc1 = tree.InsertItem(L"Дуга синуса 1", -1, -1, m_hSin, TVI_FIRST);
	tree.SetCheck(m_hSinArc1, TRUE);

	m_hSinArc2 = tree.InsertItem(L"Дуга синуса 2", -1, -1, m_hSin, TVI_FIRST);
	tree.SetCheck(m_hSinArc2, TRUE);

	m_hCoord = tree.InsertItem(L"Система координат", -1, -1, NULL, TVI_ROOT);
	tree.SetCheck(m_hCoord, TRUE);

	m_hOx = tree.InsertItem(L"Ось Ox", -1, -1, m_hCoord, TVI_FIRST);
	tree.SetCheck(m_hOx, TRUE);

	m_hOy = tree.InsertItem(L"Ось Oy", -1, -1, m_hCoord, TVI_FIRST);
	tree.SetCheck(m_hOy, TRUE);

	m_hBrush = tree.InsertItem(L"Штриховка", -1, -1, NULL, TVI_ROOT);
	tree.SetCheck(m_hBrush, TRUE);

	m_hBrushVertical = tree.InsertItem(L"Вертикальная штриховка", -1, -1, m_hBrush, TVI_FIRST);
	m_hBrush45 = tree.InsertItem(L"Косая штриховка", -1, -1, m_hBrush, TVI_FIRST);
	m_hBrushTool = tree.InsertItem(L"Штриховка CBrush", -1, -1, m_hBrush, TVI_FIRST);

	tree.SetCheck(m_hSinArc1, TRUE);

	tree.SetCheck(m_hSin, TRUE);

	tree.Expand(m_hSin, TVE_EXPAND);
	tree.Expand(m_hCoord, TVE_EXPAND);
	tree.Expand(m_hBrush, TVE_EXPAND);
	

	UpdateView();
}


CMyTreeView::~CMyTreeView()
{
}

BEGIN_MESSAGE_MAP(CMyTreeView, CTreeView)
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(TVN_ITEMCHANGED, &CMyTreeView::OnTvnItemChanged)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// Диагностика CMyTreeView

#ifdef _DEBUG
void CMyTreeView::AssertValid() const
{
	CTreeView::AssertValid();
}

#ifndef _WIN32_WCE
void CMyTreeView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
#endif //_DEBUG


// Обработчики сообщений CMyTreeView




int CMyTreeView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	lpCreateStruct->style |= TVS_HASLINES | TVS_HASBUTTONS | TVS_LINESATROOT | TVS_SHOWSELALWAYS | TVS_CHECKBOXES;
	if (CTreeView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Добавьте специализированный код создания

	return 0;
}