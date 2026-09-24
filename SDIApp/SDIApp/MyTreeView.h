#pragma once
#include "afxcview.h"

// Просмотр CMyTreeView

class CMyTreeView : public CTreeView
{
	DECLARE_DYNCREATE(CMyTreeView)

protected:
	CMyTreeView();           // защищенный конструктор, используемый при динамическом создании
	virtual ~CMyTreeView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	void UpdateView();
	void SetChildrenChecked(HTREEITEM hItem, BOOL bCheck);
	void UpdateParentState(HTREEITEM hItem);
	HTREEITEM m_hSin, m_hCoord, m_hBrush, m_hLine;
	HTREEITEM m_hSinArc1, m_hSinArc2, m_hOx, m_hOy, m_hBrushVertical, m_hBrush45, m_hBrushTool, m_hLine1;
	BOOL m_SinCheck;
	void FillTree();

#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMyCommand();
	afx_msg void OnUpdateMyCommand(CCmdUI* pCmdUI);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTvnItemChanged(NMHDR* pNMHDR, LRESULT* pResult);
};



