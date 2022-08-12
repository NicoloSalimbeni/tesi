#include "../AnalysisObjects/ObjColl.h"
#include "../AnalysisObjects/ObjImpColl.h"
#include "../AnalysisObjects/ObjNonColl.h"
#include "../AnalysisObjects/ObjAn.h"
#include "../AnalysisObjects/ObjAnColl.h"
#include "ViPrint.h"

ViPrint::ViPrint()
{
}

ViPrint::~ViPrint()
{
    delete c;
}

void ViPrint::Visit(ObjColl *obj)
{
    c = new TCanvas("c", "c", 900, 650);
    c->cd();
    obj->GetH()->Draw("CONT4Z");
    c->SaveAs("../analisi_risoluzione_energia/collinear/Resolution_coll.png");

    obj->GetP()->Draw();
    c->SaveAs("../analisi_risoluzione_energia/collinear/Profile_coll.png");
}

void ViPrint::Visit(ObjImpColl *obj)
{
    c = new TCanvas("c", "c", 900, 650);
    c->cd();

    obj->GetH()->Draw("CONT4Z");
    c->SaveAs("../analisi_risoluzione_energia/improved_collinear/Resolution_imp_coll.png");

    obj->GetP()->Draw();
    c->SaveAs("../analisi_risoluzione_energia/improved_collinear/Profile_imp_coll.png");
}

void ViPrint::Visit(ObjNonColl *obj)
{
    c = new TCanvas("c", "c", 900, 650);
    c->cd();

    obj->GetH()->Draw("CONT4Z");
    c->SaveAs("../analisi_risoluzione_energia/non_collinear/Resolution_non_coll.png");

    obj->GetP()->Draw();
    c->SaveAs("../analisi_risoluzione_energia/non_collinear/Profile_non_coll.png");
}

void ViPrint::Visit(ObjAn *obj)
{
    c = new TCanvas("c", "c", 900, 650);
    c->cd();

    obj->GetHMin()->Draw("CONT4Z");
    c->SaveAs("../analisi_risoluzione_energia/analitica/Resolution_an_min.png");
    obj->GetHMag()->Draw("CONT4Z");
    c->SaveAs("../analisi_risoluzione_energia/analitica/Resolution_an_mag.png");
    obj->GetHCorr()->Draw("CONT4Z");
    c->SaveAs("../analisi_risoluzione_energia/analitica/Resolution_an_corr.png");
    obj->GetHMean()->Draw("CONT4Z");
    c->SaveAs("../analisi_risoluzione_energia/analitica/Resolution_an_mean.png");
    obj->GetHCos()->Draw("CONT4Z");
    c->SaveAs("../analisi_risoluzione_energia/analitica/Resolution_an_cos.png");

    obj->GetPCorr()->Draw();
    c->SaveAs("../analisi_risoluzione_energia/analitica/Profile_an_corr.png");
    obj->GetPMean()->Draw();
    c->SaveAs("../analisi_risoluzione_energia/analitica/Profile_an_mean.png");
    obj->GetPCos()->Draw();
    c->SaveAs("../analisi_risoluzione_energia/analitica/Profile_an_cos.png");
}

void ViPrint::Visit(ObjAnColl *obj) {} // TODO
