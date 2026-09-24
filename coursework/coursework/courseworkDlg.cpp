
// courseworkDlg.cpp: файл реализации
//


#include "pch.h"
#include "framework.h"
#include "afxdialogex.h"
#include "coursework.h"
#include "courseworkDlg.h"
#include "math.h"
#include "cmath"

#include "C:\Program Files\ASCON\KOMPAS-3D v22 Study\SDK\Include\ksConstants.h"
#include "C:\Program Files\ASCON\KOMPAS-3D v22 Study\SDK\Include\ksConstants3D.h"
#include <atlsafe.h>

#include <comutil.h>

#define PI 4*atan(1)

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma once

#import "C:\Program Files\ASCON\KOMPAS-3D v22 Study\SDK\lib\kAPI5.tlb"

using namespace Kompas6API5;
//using namespace KompasAPI5;


KompasObjectPtr pKompasApp5;
//KompasObjectPtr pKompasApp5;

ksPartPtr pPart;// = PartDoc->GetTopPart();
ksDocument3DPtr pDoc;

//IModelContainerPtr pModelContainer;// (pPart);

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


// Диалоговое окно CcourseworkDlg



CcourseworkDlg::CcourseworkDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_COURSEWORK_DIALOG, pParent)
	, m_long(55)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CcourseworkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_FIRST, m_long);
}

BEGIN_MESSAGE_MAP(CcourseworkDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_FIRST, &CcourseworkDlg::OnBnClickedButtonFirst)
	ON_STN_CLICKED(IDC_STATIC_FIRST, &CcourseworkDlg::OnStnClickedStaticFirst)
	ON_EN_CHANGE(IDC_EDIT_FIRST, &CcourseworkDlg::OnEnChangeEditFirst)
	ON_STN_CLICKED(IDC_PIC2, &CcourseworkDlg::OnStnClickedPic2)
END_MESSAGE_MAP()


// Обработчики сообщений CcourseworkDlg

BOOL CcourseworkDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CcourseworkDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CcourseworkDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CcourseworkDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CcourseworkDlg::OnBnClickedButtonFirst()
{
	// TODO: добавьте свой код обработчика уведомлений
	BeginWaitCursor();

	CComPtr<IUnknown> pKompasAppUnk = nullptr;
	if (!pKompasApp5)
	{
		// Получаем CLSID для Компас
		CLSID InvAppClsid;

		HRESULT hRes = CLSIDFromProgID(L"Kompas.Application.5", &InvAppClsid);
		if (FAILED(hRes)) {
			pKompasApp5 = nullptr;
			return;
		}

		// Проверяем есть ли запущенный экземпляр Компас
		//если есть получаем IUnknown
		hRes = ::GetActiveObject(InvAppClsid, NULL, &pKompasAppUnk);
		if (FAILED(hRes)) {
			// Приходится запускать Компас самим так как работающего нет
			// Также получаем IUnknown для только что запущенного приложения Компас
			TRACE(L"Could not get hold of an active Inventor, will start a new session\n");
			hRes = CoCreateInstance(InvAppClsid, NULL, CLSCTX_LOCAL_SERVER, __uuidof(IUnknown), (void**)&pKompasAppUnk);
			if (FAILED(hRes)) {
				pKompasApp5 = nullptr;
				return;
			}
		}

		// Получаем интерфейс приложения Компас
		hRes = pKompasAppUnk->QueryInterface(__uuidof(KompasObject), (void**)&pKompasApp5);
		if (FAILED(hRes)) {
			return;
		}

		// делаем Компас видимым
		pKompasApp5->Visible = true;

		pDoc = pKompasApp5->Document3D();

		pDoc->Create(false, true);

		pPart = pDoc->GetPart(pTop_Part);

		// эскиз 1 прямоугольник

		ksEntityPtr pSketch = pPart->NewEntity(o3d_sketch);

		ksSketchDefinitionPtr pSketchDef = pSketch->GetDefinition();

		pSketchDef->SetPlane(pPart->GetDefaultEntity(o3d_planeXOY));

		pSketch->Create();

		ksDocument2DPtr p2DDoc = pSketchDef->BeginEdit();

		UpdateData();

		double point1[4][2];
		point1[0][0] = 0;
		point1[0][1] = 3.5;

		point1[1][0] = 0;
		point1[1][1] = -3.5;

		point1[2][0] = -m_long;
		point1[2][1] = -3.5;

		point1[3][0] = -m_long;
		point1[3][1] = 3.5;

		p2DDoc->ksLineSeg(point1[0][0], point1[0][1], point1[1][0], point1[1][1], 1);
		p2DDoc->ksLineSeg(point1[1][0], point1[1][1], point1[2][0], point1[2][1], 1);
		p2DDoc->ksLineSeg(point1[2][0], point1[2][1], point1[3][0], point1[3][1], 1);
		p2DDoc->ksLineSeg(point1[3][0], point1[3][1], point1[0][0], point1[0][1], 1);

		//p2DDoc->ksRectangle(param, 0);
		//ksRectangleParam param = (ksRectangleParam)kompas.GetParamStruct(91);

		pSketchDef->EndEdit();

		// выдавливание эскиза 1 

		ksEntityPtr pExtrude = pPart->NewEntity(o3d_bossExtrusion);
		ksBossExtrusionDefinitionPtr pExDef = pExtrude->GetDefinition();
		pExDef->directionType = dtNormal;
		pExDef->SetSketch(pSketch);
		pExDef->SetSideParam(true, etBlind, 1.5, 0, false);
		pExtrude->Create();

		// смещенная плоскость для эскиза 2

		ksEntityPtr pPlane = pPart->NewEntity(o3d_planeOffset);
		ksPlaneOffsetDefinitionPtr pPlaneDef = pPlane->GetDefinition();

		pPlaneDef->direction = true;
		pPlaneDef->offset = 3.5;
		pPlaneDef->SetPlane(pPart->GetDefaultEntity(o3d_planeXOZ));

		pPlane->Create();


		// эскиз 2 

		ksEntityPtr pSketch2 = pPart->NewEntity(o3d_sketch);

		pSketchDef = pSketch2->GetDefinition();

		pSketchDef->SetPlane(pPlane);

		pSketch2->Create();

		p2DDoc = pSketchDef->BeginEdit();

		UpdateData();

		double point2[12][2];
		point2[0][0] = 7;
		point2[0][1] = -1.5 - 2;

		point2[1][0] = 6.414214;
		point2[1][1] = -2.085786;

		point2[2][0] = 7 - 2;
		point2[2][1] = -1.5;

		point2[3][0] = -m_long;
		point2[3][1] = -1.5;

		point2[4][0] = -m_long;
		point2[4][1] = -1.5 - 3;

		point2[5][0] = -17;
		point2[5][1] = -1.5 - 3;

		point2[6][0] = -17;
		point2[6][1] = -1.5 - 23.5 + 2;

		point2[7][0] = -16.414214;
		point2[7][1] = -24.414214;

		point2[8][0] = -17 + 2;
		point2[8][1] = -1.5 - 23.5;

		point2[9][0] = 7 - 2;
		point2[9][1] = -1.5 - 23.5;

		point2[10][0] = 6.414214;
		point2[10][1] = -24.414214;

		point2[11][0] = 7;
		point2[11][1] = -1.5 - 23.5 + 2;


		p2DDoc->ksArcBy3Points(point2[0][0], point2[0][1], point2[1][0], point2[1][1], point2[2][0], point2[2][1], 1);
		p2DDoc->ksLineSeg(point2[2][0], point2[2][1], point2[3][0], point2[3][1], 1);
		p2DDoc->ksLineSeg(point2[3][0], point2[3][1], point2[4][0], point2[4][1], 1);
		p2DDoc->ksLineSeg(point2[4][0], point2[4][1], point2[5][0], point2[5][1], 1);
		p2DDoc->ksLineSeg(point2[5][0], point2[5][1], point2[6][0], point2[6][1], 1);
		p2DDoc->ksArcBy3Points(point2[6][0], point2[6][1], point2[7][0], point2[7][1], point2[8][0], point2[8][1], 1);
		p2DDoc->ksLineSeg(point2[8][0], point2[8][1], point2[9][0], point2[9][1], 1);
		p2DDoc->ksArcBy3Points(point2[9][0], point2[9][1], point2[10][0], point2[10][1], point2[11][0], point2[11][1], 1);
		p2DDoc->ksLineSeg(point2[11][0], point2[11][1], point2[0][0], point2[0][1], 1);

		p2DDoc->ksCircle(-5, -1.5 - 11.5, 11, 1);

		pSketchDef->EndEdit();

		// выдавливание эскиза 2 

		ksEntityPtr pExtrude2 = pPart->NewEntity(o3d_bossExtrusion);
		pExDef = pExtrude2->GetDefinition();
		pExDef->directionType = dtReverse;
		pExDef->SetSketch(pSketch2);
		pExDef->SetSideParam(false, etBlind, 1.5, 0, false);
		pExtrude2->Create();

		// вырез эскиз 3

		ksEntityPtr pSketch3 = pPart->NewEntity(o3d_sketch);

		pSketchDef = pSketch3->GetDefinition();

		pSketchDef->SetPlane(pPlane);

		pSketch3->Create();

		p2DDoc = pSketchDef->BeginEdit();

		p2DDoc->ksCircle(4.8, -1.5 - 2.3, 0.75, 1);

		pSketchDef->EndEdit();

		// вырез эскиза 3

		ksEntityPtr pExtrude3 = pPart->NewEntity(o3d_cutExtrusion);
		ksCutExtrusionDefinitionPtr pExDef1 = pExtrude3->GetDefinition();
		pExDef1->directionType = dtNormal;
		pExDef1->SetSketch(pSketch3);
		pExDef1->SetSideParam(true, etBlind, 1.5, 0, false);
		pExtrude3->Create();

		// смещенная плоскость для массива по сетке

		ksEntityPtr pPlane1 = pPart->NewEntity(o3d_planeOffset);
		pPlaneDef = pPlane1->GetDefinition();

		pPlaneDef->direction = true;
		pPlaneDef->offset = 13.25;
		pPlaneDef->SetPlane(pPart->GetDefaultEntity(o3d_planeXOY));

		pPlane1->Create();

		// массив по сетке 3 эскиза и выреза
		ksEntityCollectionPtr pCollection;//создаем коллекцию элементов
		ksEntityPtr pMirror = pPart->NewEntity(o3d_mirrorOperation);//создаем зеркальный массив
		ksMirrorCopyDefinitionPtr pMirrorDefPtr = pMirror->GetDefinition();
		pMirrorDefPtr->SetPlane(pPlane1);
		pCollection = pMirrorDefPtr->GetOperationArray();//коллекция теперь "обслуживает" операцию массива
		pCollection->Clear();
		pCollection->Add(pExDef1);
		pMirror->Create();

		// смещенная плоскость для массива по сетке 2 

		ksEntityPtr pPlane2 = pPart->NewEntity(o3d_planeOffset);
		pPlaneDef = pPlane2->GetDefinition();

		pPlaneDef->direction = true;
		pPlaneDef->offset = 5;
		pPlaneDef->SetPlane(pPart->GetDefaultEntity(o3d_planeYOZ));

		pPlane2->Create();

		// массив по сетке второй 3 эскиза и выреза
		ksEntityCollectionPtr pCollection1;//создаем коллекцию элементов
		ksEntityPtr pMirror1 = pPart->NewEntity(o3d_mirrorOperation);//создаем зеркальный массив
		pMirrorDefPtr = pMirror1->GetDefinition();
		pMirrorDefPtr->SetPlane(pPlane2);
		pCollection1 = pMirrorDefPtr->GetOperationArray();//коллекция теперь "обслуживает" операцию массива
		pCollection1->Clear();
		pCollection1->Add(pMirror);
		pMirror1->Create();

		// смещенная плоскость для эскиза 4

		ksEntityPtr pPlane3 = pPart->NewEntity(o3d_planeOffset);
		pPlaneDef = pPlane3->GetDefinition();

		pPlaneDef->direction = true;
		pPlaneDef->offset = -3.5;
		pPlaneDef->SetPlane(pPart->GetDefaultEntity(o3d_planeXOZ));

		pPlane3->Create();

		// эскиз 4

		ksEntityPtr pSketch4 = pPart->NewEntity(o3d_sketch);

		pSketchDef = pSketch4->GetDefinition();

		pSketchDef->SetPlane(pPlane3);

		pSketch4->Create();

		p2DDoc = pSketchDef->BeginEdit();

		p2DDoc->ksCircle(-5, -13, 11, 1);

		pSketchDef->EndEdit();

		// выдавливание эскиза 2 

		ksEntityPtr pExtrude4 = pPart->NewEntity(o3d_bossExtrusion);
		pExDef = pExtrude4->GetDefinition();
		pExDef->directionType = dtReverse;
		pExDef->SetSketch(pSketch4);
		pExDef->SetSideParam(false, etBlind, 1, 0, false);
		pExtrude4->Create();

		// смещенная плоскость для эскиза 5

		ksEntityPtr pPlane4 = pPart->NewEntity(o3d_planeOffset);
		pPlaneDef = pPlane4->GetDefinition();

		pPlaneDef->direction = true;
		pPlaneDef->offset = -4.5;
		pPlaneDef->SetPlane(pPart->GetDefaultEntity(o3d_planeXOZ));

		pPlane4->Create();

		// эскиз 5

		ksEntityPtr pSketch5 = pPart->NewEntity(o3d_sketch);

		pSketchDef = pSketch5->GetDefinition();

		pSketchDef->SetPlane(pPlane4);

		pSketch5->Create();

		p2DDoc = pSketchDef->BeginEdit();

		double point3[14][2];

		point3[0][0] = -15.070742;
		point3[0][1] = -8.575053;

		point3[1][0] = 5.162675;
		point3[1][1] = -8.790482;

		point3[2][0] = -8.992180;
		point3[2][1] = -23.25;

		point3[3][0] = -17.545616;
		point3[3][1] = -11.049927;

		point3[4][0] = -17.027978;
		point3[4][1] = -9.118075;

		point3[5][0] = -24.5;
		point3[5][1] = -16.590097;

		point3[6][0] = -24.5;
		point3[6][1] = -24.25;

		point3[7][0] = -10.760129;
		point3[7][1] = -24.25;

		point3[8][0] = -12.49218;
		point3[8][1] = -23.25;

		point3[9][0] = -13.308505;
		point3[9][1] = -4.691495;

		point3[10][0] = 5.855585;
		point3[10][1] = -8.503470;

		point3[11][0] = -5;
		point3[11][1] = -24.75;

		point3[12][0] = -25;
		point3[12][1] = -16.382991;

		point3[13][0] = -25;
		point3[13][1] = -24.75;

		p2DDoc->ksArcBy3Points(point3[0][0], point3[0][1], point3[1][0], point3[1][1], point3[2][0], point3[2][1], 1);
		p2DDoc->ksLineSeg(point3[0][0], point3[0][1], point3[3][0], point3[3][1], 1);
		p2DDoc->ksLineSeg(point3[3][0], point3[3][1], point3[4][0], point3[4][1], 1);
		p2DDoc->ksLineSeg(point3[4][0], point3[4][1], point3[5][0], point3[5][1], 1);
		p2DDoc->ksLineSeg(point3[5][0], point3[5][1], point3[6][0], point3[6][1], 1);
		p2DDoc->ksLineSeg(point3[6][0], point3[6][1], point3[7][0], point3[7][1], 1);
		p2DDoc->ksLineSeg(point3[7][0], point3[7][1], point3[8][0], point3[8][1], 1);
		p2DDoc->ksLineSeg(point3[8][0], point3[8][1], point3[2][0], point3[2][1], 1);
		p2DDoc->ksArcBy3Points(point3[9][0], point3[9][1], point3[10][0], point3[10][1], point3[11][0], point3[11][1], 1);
		p2DDoc->ksLineSeg(point3[9][0], point3[9][1], point3[12][0], point3[12][1], 1);
		p2DDoc->ksLineSeg(point3[12][0], point3[12][1], point3[13][0], point3[13][1], 1);
		p2DDoc->ksLineSeg(point3[13][0], point3[13][1], point3[11][0], point3[11][1], 1);

		pSketchDef->EndEdit();

		// выдавливание эскиза 5

		ksEntityPtr pExtrude5 = pPart->NewEntity(o3d_bossExtrusion);
		pExDef = pExtrude5->GetDefinition();
		pExDef->directionType = dtNormal;
		pExDef->SetSketch(pSketch5);
		pExDef->SetSideParam(true, etBlind, 6.504806, 0, false);
		pExtrude5->Create();

		// смещенная плоскость для эскиза 6

		ksEntityPtr pPlane5 = pPart->NewEntity(o3d_planeOffset);
		pPlaneDef = pPlane5->GetDefinition();

		pPlaneDef->direction = true;
		pPlaneDef->offset = 24.75;
		pPlaneDef->SetPlane(pPart->GetDefaultEntity(o3d_planeXOY));

		pPlane5->Create();

		// эскиз 6

		ksEntityPtr pSketch6 = pPart->NewEntity(o3d_sketch);

		pSketchDef = pSketch6->GetDefinition();

		pSketchDef->SetPlane(pPlane5);

		pSketch6->Create();

		p2DDoc = pSketchDef->BeginEdit();

		double point4[3][2];

		point4[0][0] = -16;
		point4[0][1] = 2 + 0.004806;

		point4[1][0] = -25;
		point4[1][1] = 2 + 0.004806;

		point4[2][0] = -25;
		point4[2][1] = 0;

		p2DDoc->ksLineSeg(point4[0][0], point4[0][1], point4[1][0], point4[1][1], 1);
		p2DDoc->ksLineSeg(point4[1][0], point4[1][1], point4[2][0], point4[2][1], 1);
		p2DDoc->ksLineSeg(point4[2][0], point4[2][1], point4[0][0], point4[0][1], 1);

		pSketchDef->EndEdit();

		// вырез эскиза 6

		ksEntityPtr pExtrude6 = pPart->NewEntity(o3d_cutExtrusion);
		pExDef1 = pExtrude6->GetDefinition();
		pExDef1->directionType = dtNormal;
		pExDef1->SetSketch(pSketch6);
		pExDef1->SetSideParam(true, etBlind, 23.217120, 0, false);
		pExtrude6->Create();

		ksEntityCollectionPtr pf = pPart->EntityCollection(o3d_edge);
		pf->SelectByPoint(-20.336439, 1.038837, 24.75);

		// смещенная плоскость для эскиза 7

		//ksEntityPtr pPlane6 = pPart->NewEntity(o3d_planeAngle);
		//ksPlaneAngleDefinitionPtr pan = pPlane6->GetDefinition();

		//pan->angle = 12.557961;
		//pan->SetPlane(pPart->GetDefaultEntity(o3d_planeXOZ));
		//pan->SetAxis(pf);

		//pPlane6->Create();

		// эскиз 7

		ksEntityPtr pSketch7 = pPart->NewEntity(o3d_sketch);

		pSketchDef = pSketch7->GetDefinition();

		pSketchDef->SetPlane(pPlane5);

		pSketch7->Create();

		p2DDoc = pSketchDef->BeginEdit();

		double point5[6][2];

		point5[0][0] = -16.019079;
		point5[0][1] = 2.524495;

		point5[1][0] = -16.019079;
		point5[1][1] = 0.724495;

		point5[2][0] = -25;
		point5[2][1] = -1.271265;

		point5[3][0] = -25;
		point5[3][1] = 0.528735;

		p2DDoc->ksLineSeg(point5[0][0], point5[0][1], point5[1][0], point5[1][1], 1);
		p2DDoc->ksLineSeg(point5[1][0], point5[1][1], point5[2][0], point5[2][1], 1);
		p2DDoc->ksLineSeg(point5[2][0], point5[2][1], point5[3][0], point5[3][1], 1);
		p2DDoc->ksLineSeg(point5[3][0], point5[3][1], point5[0][0], point5[0][1], 1);

		pSketchDef->EndEdit();


		//ksEntityCollectionPtr pf = pPart->EntityCollection(o3d_face);
		//bool res = pf->SelectByPoint(-20.304425, -1.784451, 11.687415);

		// выдавливание эскиза 7

		ksEntityPtr pExtrude7 = pPart->NewEntity(o3d_bossExtrusion);
		pExDef = pExtrude7->GetDefinition();
		pExDef->directionType = dtReverse;
		pExDef->SetSketch(pSketch7);
		pExDef->SetSideParam(false, etBlind, 8.367009, 0, false);
		pExtrude7->Create();

		//ksEntityPtr pExtrude7 = pPart->NewEntity(o3d_bossExtrusion);
		//pExDef = pExtrude7->GetDefinition();
		//pExDef->directionType = dtReverse;
		//pExDef->SetSketch(pSketch7);
		//pExDef->SetDepthObject(true, pf);
		//pExtrude7->Create();

		// скругления 

		ksEntityCollectionPtr pCollEdge = pPart->EntityCollection(o3d_edge);
		ksEntityPtr pFillet = pPart->NewEntity(o3d_fillet);
		ksFilletDefinitionPtr pFilletDef = pFillet->GetDefinition();
		pFilletDef->radius = 1;
		pFilletDef->tangent = false;
		ksEntityCollectionPtr pCollFillet = pFilletDef->array();
		pCollFillet->Clear();

		bool res = pCollEdge->SelectByPoint(-25.000000, 0.528735, 21.212881);
		pCollFillet->Add(pCollEdge->GetByIndex(0));

		pCollEdge = pPart->EntityCollection(o3d_edge);
		res = pCollEdge->SelectByPoint(-24.500000, -1.160154, 21.415557);
		pCollFillet->Add(pCollEdge->GetByIndex(0));
		pFillet->Create();

		pCollEdge = pPart->EntityCollection(o3d_edge);
		res = pCollEdge->SelectByPoint(-16.019079, 0.724495, 21.107395);
		pCollFillet->Add(pCollEdge->GetByIndex(0));
		pFillet->Create();

		// смещенная плоскость для зеркального массива 

		ksEntityPtr pPlane7= pPart->NewEntity(o3d_planeOffset);
		pPlaneDef = pPlane7->GetDefinition();

		UpdateData();

		pPlaneDef->direction = true;
		pPlaneDef->offset = m_long;
		pPlaneDef->SetPlane(pPart->GetDefaultEntity(o3d_planeYOZ));

		pPlane7->Create();

		// зеркальный массив

		ksEntityCollectionPtr pCollection2;//создаем коллекцию элементов
		ksEntityPtr pMirror2 = pPart->NewEntity(o3d_mirrorOperation);//создаем зеркальный массив
		pMirrorDefPtr = pMirror2->GetDefinition();
		pMirrorDefPtr->SetPlane(pPlane7);
		pCollection2 = pMirrorDefPtr->GetOperationArray();//коллекция теперь "обслуживает" операцию массива
		pCollection2->Clear();
		pCollection2->Add(pSketch);
		pCollection2->Add(pExtrude);
		pCollection2->Add(pPlane);
		pCollection2->Add(pSketch2);
		pCollection2->Add(pExtrude2);
		pCollection2->Add(pSketch3);
		pCollection2->Add(pExtrude3);
		pCollection2->Add(pPlane1);
		pCollection2->Add(pMirror);
		pCollection2->Add(pPlane2);
		pCollection2->Add(pMirror1);
		pCollection2->Add(pPlane3);
		pCollection2->Add(pSketch4);
		pCollection2->Add(pExtrude4);
		pCollection2->Add(pPlane4);
		pCollection2->Add(pSketch5);
		pCollection2->Add(pExtrude5);
		pCollection2->Add(pPlane5);
		pCollection2->Add(pSketch6);
		pCollection2->Add(pExtrude6);
		pCollection2->Add(pSketch7);
		pCollection2->Add(pExtrude7);
		pCollection2->Add(pFillet);
		pCollection2->Add(pPlane7);

		pMirror2->Create();

		pDoc->SaveAs("Крепление для кулеров.m3d");
		//pDoc->close();
	}


}

void CcourseworkDlg::OnStnClickedStaticFirst()
{
	// TODO: добавьте свой код обработчика уведомлений
}


void CcourseworkDlg::OnEnChangeEditFirst()
{
	// TODO:  Если это элемент управления RICHEDIT, то элемент управления не будет
	// send this notification unless you override the CDialog::OnInitDialog()
	// функция и вызов CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Добавьте код элемента управления
}


void CcourseworkDlg::OnStnClickedPic2()
{
	// TODO: добавьте свой код обработчика уведомлений
}
