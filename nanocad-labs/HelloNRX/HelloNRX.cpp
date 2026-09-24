//
// Копирайт (С) 2019, ООО «Нанософт разработка». Все права защищены.
// 
// Данное программное обеспечение, все исключительные права на него, его
// документация и сопроводительные материалы принадлежат ООО «Нанософт разработка».
// Данное программное обеспечение может использоваться при разработке и входить
// в состав разработанных программных продуктов при соблюдении условий
// использования, оговоренных в «Лицензионном договоре присоединения
// на использование программы для ЭВМ «Платформа nanoCAD»».
// 
// Данное программное обеспечение защищено в соответствии с законодательством
// Российской Федерации об интеллектуальной собственности и международными
// правовыми актами.
// 
// Используя данное программное обеспечение,  его документацию и
// сопроводительные материалы вы соглашаетесь с условиями использования,
// указанными выше. 
//

#include "stdafx.h"
#include <cmath>
#include <vector>


using namespace std;

struct LineS;
struct LineS
{
    AcGePoint3d StartPoint, EndPoint;
    
};

struct ArcPar;
struct ArcPar 
{
    AcGePoint3d CentPoint;
    double Rad, sAngle, fAngle;
    
};

vector<ArcPar> arcList; 
vector<AcDbObjectId> ID;
vector<AcDbObjectId> IDArc;
vector<LineS> lineList;



class MyReactor :public NcDbObjectReactor
{
public:
    void modified(const NcDbObject* object)
    {
        
            NcDbArc* pArc = NcDbArc::cast(object); 
            NcDbLine* pLine = NcDbLine::cast(object); 

            
            if (pArc != nullptr)
            {

                for (int a = 0; a < IDArc.size(); a++)
                {
                    if (object->objectId() == IDArc[a])
                    {
                        pArc->setCenter(arcList[a].CentPoint); 
                        pArc->setRadius(arcList[a].Rad); 
                        pArc->setStartAngle(arcList[a].sAngle); 
                        pArc->setEndAngle(arcList[a].fAngle); 
                    }
                    
                }




            }
      
            if (pLine != nullptr) 
            {
                for (int s = 0; s < ID.size(); s++)
                {
                    if (object->objectId() == ID[s])
                    {
                        pLine->setStartPoint(lineList[s].StartPoint); 
                        pLine->setEndPoint(lineList[s].EndPoint); 
                    }
                    

                }
            }

    }
};

void addToModelSpace(AcDbObjectId& objId, AcDbEntity* pEntity);

MyReactor* react;

void helloNrxCmd()
{
  //acutPrintf(L"\oh no, NRX!\n");

    AcDbObjectId lineId;
    AcDbLine* pline = new AcDbLine(AcGePoint3d(10, 10, 0), AcGePoint3d(110, 10, 0));
    LineS line1;  
    line1.StartPoint = AcGePoint3d(10, 10, 0);
    line1.EndPoint = AcGePoint3d(110, 10, 0);
    addToModelSpace(lineId, pline);
    pline->addReactor(react); 
    pline->close();
    ID.push_back(lineId);
    lineList.push_back(line1); 

    AcDbObjectId line2Id;
    AcDbLine* pline2 = new AcDbLine(AcGePoint3d(10, 10, 0), AcGePoint3d(10, 110, 0));
    LineS line2;
    line2.StartPoint = AcGePoint3d(10, 10, 0);
    line2.EndPoint = AcGePoint3d(10, 110, 0); 
    addToModelSpace(line2Id, pline2); 
    pline2->addReactor(react);
    pline2->close();
    ID.push_back(line2Id);
    lineList.push_back(line2); 

    AcDbObjectId line3Id;
    AcDbLine* pline3 = new AcDbLine(AcGePoint3d(150, 50, 0), AcGePoint3d(150, 150, 0));
    LineS line3;
    line3.StartPoint = AcGePoint3d(150, 50, 0);
    line3.EndPoint = AcGePoint3d(150, 150, 0);
    addToModelSpace(line3Id, pline3);
    pline3->addReactor(react);
    pline3->close();
    ID.push_back(line3Id);
    lineList.push_back(line3); 

    AcDbObjectId line4Id;
    AcDbLine* pline4 = new AcDbLine(AcGePoint3d(50, 150, 0), AcGePoint3d(150, 150, 0));
    LineS line4;
    line4.StartPoint = AcGePoint3d(50, 150, 0);
    line4.EndPoint = AcGePoint3d(150, 150, 0);
    addToModelSpace(line4Id, pline4); 
    pline4->addReactor(react);
    pline4->close();
    lineList.push_back(line4);
    ID.push_back(line4Id); 

    AcDbObjectId arcId;
    double rad = 40.0;
    double stAngle = PI/2;
    double enAngle = PI;
    AcDbArc* pArc = new AcDbArc(AcGePoint3d(150, 10, 0), rad, stAngle, enAngle);
    ArcPar arc1;
    arc1.CentPoint = AcGePoint3d(150, 10, 0);
    arc1.Rad = rad;
    arc1.sAngle = stAngle;
    arc1.fAngle = enAngle;
    addToModelSpace(arcId, pArc); 
    pArc->addReactor(react); 
    pArc->close();
    IDArc.push_back(arcId);
    arcList.push_back(arc1); 

    AcDbObjectId arc2Id;
    double rad2 = 40.0;
    double stAngle2 = -(PI / 2); 
    double enAngle2 = 0; 
    AcDbArc* pArc2 = new AcDbArc(AcGePoint3d(10, 150, 0), rad2, stAngle2, enAngle2);
    ArcPar arc2;
    arc2.CentPoint = AcGePoint3d(10, 150, 0);
    arc2.Rad = rad2;
    arc2.sAngle = stAngle2;
    arc2.fAngle = enAngle2;
    addToModelSpace(arc2Id, pArc2); 
    pArc2->addReactor(react);
    pArc2->close();
    IDArc.push_back(arc2Id);
    arcList.push_back(arc2); 

    AcDbObjectId arc3Id;
    double rad3 = 12.5;
    double stAngle3 = 0; 
    double enAngle3 = -2*PI;  
    AcDbArc* pArc3 = new AcDbArc(AcGePoint3d(75, 128, 0), rad3, stAngle3, enAngle3); 
    ArcPar arc3;
    arc3.CentPoint = AcGePoint3d(75, 128, 0);
    arc3.Rad = rad3; 
    arc3.sAngle = stAngle3; 
    arc3.fAngle = enAngle3; 
    addToModelSpace(arc3Id, pArc3); 
    pArc3->addReactor(react);
    pArc3->close();
    IDArc.push_back(arc3Id);
    arcList.push_back(arc3); 

    /*AcDbObjectId line5Id;
    AcDbLine* pline5 = new AcDbLine(AcGePoint3d(10, 150, 0), AcGePoint3d(150, 10, 0));
    addToModelSpace(line5Id, pline5);
    pline5->close();

    AcDbObjectId line6Id;
    AcDbLine* pline6 = new AcDbLine(AcGePoint3d(150, 150, 0), AcGePoint3d(10, 10, 0));
    addToModelSpace(line6Id, pline6);
    pline6->close();*/

    AcDbObjectId line7Id;
    AcDbLine* pline7 = new AcDbLine(AcGePoint3d(20, 20, 0), AcGePoint3d(90, 70, 0));
    LineS line5;
    line5.StartPoint = AcGePoint3d(20, 20, 0);
    line5.EndPoint = AcGePoint3d(90, 70, 0);
    addToModelSpace(line7Id, pline7);
    pline7->addReactor(react);
    pline7->close();
    ID.push_back(line7Id);
    lineList.push_back(line5); 

    AcDbObjectId line8Id;
    AcDbLine* pline8 = new AcDbLine(AcGePoint3d(90, 70, 0), AcGePoint3d(112, 48, 0));
    LineS line6;
    line6.StartPoint = AcGePoint3d(90, 70, 0);
    line6.EndPoint = AcGePoint3d(112, 48, 0);
    addToModelSpace(line8Id, pline8);
    pline8->addReactor(react);
    pline8->close();
    ID.push_back(line8Id);
    lineList.push_back(line6); 

    AcDbObjectId line9Id;
    AcDbLine* pline9 = new AcDbLine(AcGePoint3d(112, 48, 0), AcGePoint3d(140, 140, 0));
    LineS line7;
    line7.StartPoint = AcGePoint3d(112, 48, 0);
    line7.EndPoint = AcGePoint3d(140, 140, 0);
    addToModelSpace(line9Id, pline9); 
    pline9->addReactor(react); 
    pline9->close();
    ID.push_back(line9Id); 
    lineList.push_back(line7); 

    AcDbObjectId line10Id;
    AcDbLine* pline10 = new AcDbLine(AcGePoint3d(20, 20, 0), AcGePoint3d(48, 112, 0));
    LineS line8;
    line8.StartPoint = AcGePoint3d(20, 20, 0);
    line8.EndPoint = AcGePoint3d(48, 112, 0); 
    addToModelSpace(line10Id, pline10);
    pline10->addReactor(react); 
    pline10->close();
    ID.push_back(line10Id);
    lineList.push_back(line8); 

    AcDbObjectId line11Id;
    AcDbLine* pline11 = new AcDbLine(AcGePoint3d(48, 112, 0), AcGePoint3d(70, 90, 0));
    LineS line9;
    line9.StartPoint = AcGePoint3d(48, 112, 0);
    line9.EndPoint = AcGePoint3d(70, 90, 0);
    addToModelSpace(line11Id, pline11); 
    pline11->addReactor(react);
    pline11->close();
    ID.push_back(line11Id);
    lineList.push_back(line9); 

    AcDbObjectId line12Id;
    AcDbLine* pline12 = new AcDbLine(AcGePoint3d(70, 90, 0), AcGePoint3d(140, 140, 0));
    LineS line10;
    line10.StartPoint = AcGePoint3d(70, 90, 0);
    line10.EndPoint = AcGePoint3d(140, 140, 0); 
    addToModelSpace(line12Id, pline12); 
    pline12->addReactor(react); 
    pline12->close();
    ID.push_back(line12Id);
    lineList.push_back(line10); 

    /*AcGePoint3dArray points; 
    points.empty(); 
    int i = 0;
    for (double fi = 0; fi <= 2 * PI; fi += PI / 20)
    {
        double r = 2 + sin(40 * fi);
       
        double x = r * cos(fi);
        double y = r * sin(fi);
        double z = fi / 2 * PI;
        AcGePoint3d coord (x, y, z);
        points.append(coord);
        i++;
        if (i > 2)
        {
            AcDbObjectId lineId;
            AcDbLine* line = new AcDbLine(points[i-2], points[i-1]);
            addToModelSpace(lineId, line); 
            line->close(); 
        }
        
    }*/

}

void addToModelSpace(AcDbObjectId& objId, AcDbEntity* pEntity)
{
    AcDbBlockTable* pBlockTable;
    AcDbBlockTableRecord* pBlock;

    acdbHostApplicationServices()->workingDatabase()->getSymbolTable(pBlockTable, AcDb::kForRead);
    pBlockTable->getAt(ACDB_MODEL_SPACE, pBlock, AcDb::kForWrite);
    pBlockTable->close();

    pBlock->appendAcDbEntity(objId, pEntity);
    pBlock->close();
}

extern "C" __declspec(dllexport) AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void* appId) 
{
  switch (msg) 
  {
  case AcRx::kInitAppMsg:
    acrxDynamicLinker->unlockApplication(appId);
    acrxDynamicLinker->registerAppMDIAware(appId);

    react = new MyReactor;

    acedRegCmds->addCommand(L"HELLONRX_GROUP",
                            L"_HELLONRX",
                            L"HELLONRX",
                            ACRX_CMD_TRANSPARENT,
                            helloNrxCmd);
    break;

  case AcRx::kUnloadAppMsg:
    acedRegCmds->removeGroup(L"HELLONRX_GROUP");
    break;
    delete react;
  }

  return AcRx::kRetOK;
}
