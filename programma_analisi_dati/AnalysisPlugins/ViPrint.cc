#include "../AnalysisObjects/ObjColl.h"
#include "../AnalysisObjects/ObjImpColl.h"
#include "../AnalysisObjects/ObjNonColl.h"
#include "../AnalysisObjects/ObjAnEs.h"
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

    obj->GetHResidui()->Draw();
    c->SaveAs("../analisi_risoluzione_energia/collinear/Histo_residui_rel_coll.png");
    c->Close();
}

void ViPrint::Visit(ObjImpColl *obj)
{
    c = new TCanvas("c", "c", 900, 650);
    c->cd();

    obj->GetH()->Draw("CONT4Z");
    c->SaveAs("../analisi_risoluzione_energia/improved_collinear/Resolution_imp_coll.png");

    obj->GetP()->Draw();
    c->SaveAs("../analisi_risoluzione_energia/improved_collinear/Profile_imp_coll.png");

    obj->GetHResidui()->Draw();
    c->SaveAs("../analisi_risoluzione_energia/improved_collinear/Histo_residui_rel_imp_coll.png");
    c->Close();
}

void ViPrint::Visit(ObjNonColl *obj)
{
    c = new TCanvas("c", "c", 900, 650);
    c->cd();

    obj->GetH()->Draw("CONT4Z");
    c->SaveAs("../analisi_risoluzione_energia/non_collinear/Resolution_non_coll.png");

    obj->GetP()->Draw();
    c->SaveAs("../analisi_risoluzione_energia/non_collinear/Profile_non_coll.png");

    obj->GetHResidui()->Draw();
    c->SaveAs("../analisi_risoluzione_energia/non_collinear/Histo_residui_rel_non_coll.png");
    c->Close();
}

void ViPrint::Visit(ObjAnEs *obj)
{
    c = new TCanvas("c", "c", 900, 650);
    c->cd();

    obj->GetHMin()->Draw("CONT4Z");
    c->SaveAs("../analisi_risoluzione_energia/analitica/esatta/Resolution_anEs_min.png");
    obj->GetHMag()->Draw("CONT4Z");
    c->SaveAs("../analisi_risoluzione_energia/analitica/esatta/Resolution_anEs_mag.png");
    obj->GetHCorr()->Draw("CONT4Z");
    c->SaveAs("../analisi_risoluzione_energia/analitica/esatta/Resolution_anEs_corr.png");
    obj->GetHMean()->Draw("CONT4Z");
    c->SaveAs("../analisi_risoluzione_energia/analitica/esatta/Resolution_anEs_mean.png");
    obj->GetHCos()->Draw("CONT4Z");
    c->SaveAs("../analisi_risoluzione_energia/analitica/esatta/Resolution_anEs_cos.png");

    obj->GetPCorr()->Draw();
    c->SaveAs("../analisi_risoluzione_energia/analitica/esatta/Profile_anEs_corr.png");
    obj->GetPMean()->Draw();
    c->SaveAs("../analisi_risoluzione_energia/analitica/esatta/Profile_anEs_mean.png");
    obj->GetPCos()->Draw();
    c->SaveAs("../analisi_risoluzione_energia/analitica/esatta/Profile_anEs_cos.png");

    obj->GetHResiduiMin()->Draw("CONT4Z");
    c->SaveAs("../analisi_risoluzione_energia/analitica/esatta/hist_residui_AnEs_min.png");
    obj->GetHResiduiMag()->Draw("CONT4Z");
    c->SaveAs("../analisi_risoluzione_energia/analitica/esatta/hist_residui_AnEs_mag.png");
    obj->GetHResiduiCorr()->Draw("CONT4Z");
    c->SaveAs("../analisi_risoluzione_energia/analitica/esatta/hist_residui_AnEs_corr.png");
    obj->GetHResiduiMean()->Draw("CONT4Z");
    c->SaveAs("../analisi_risoluzione_energia/analitica/esatta/hist_residui_AnEs_mean.png");
    obj->GetHResiduiCos()->Draw("CONT4Z");
    c->SaveAs("../analisi_risoluzione_energia/analitica/esatta/hist_residui_AnEs_cos.png");

    c->Close();
}

void ViPrint::Visit(ObjAnColl *obj)
{
    c = new TCanvas("c", "c", 900, 650);
    c->cd();

    obj->GetHMin()->Draw("CONT4Z");
    c->SaveAs("../analisi_risoluzione_energia/analitica/collineare/Resolution_anColl_min.png");
    obj->GetHMag()->Draw("CONT4Z");
    c->SaveAs("../analisi_risoluzione_energia/analitica/collineare/Resolution_anColl_mag.png");
    obj->GetHCorr()->Draw("CONT4Z");
    c->SaveAs("../analisi_risoluzione_energia/analitica/collineare/Resolution_anColl_corr.png");
    obj->GetHMean()->Draw("CONT4Z");
    c->SaveAs("../analisi_risoluzione_energia/analitica/collineare/Resolution_anColl_mean.png");
    obj->GetHCos()->Draw("CONT4Z");
    c->SaveAs("../analisi_risoluzione_energia/analitica/collineare/Resolution_anColl_cos.png");

    obj->GetPCorr()->Draw();
    c->SaveAs("../analisi_risoluzione_energia/analitica/collineare/Profile_anColl_corr.png");
    obj->GetPMean()->Draw();
    c->SaveAs("../analisi_risoluzione_energia/analitica/collineare/Profile_anColl_mean.png");
    obj->GetPCos()->Draw();
    c->SaveAs("../analisi_risoluzione_energia/analitica/collineare/Profile_anColl_cos.png");

    obj->GetHResiduiMin()->Draw("CONT4Z");
    c->SaveAs("../analisi_risoluzione_energia/analitica/collineare/hist_residui_AnColl_min.png");
    obj->GetHResiduiMag()->Draw("CONT4Z");
    c->SaveAs("../analisi_risoluzione_energia/analitica/collineare/hist_residui_AnColl_mag.png");
    obj->GetHResiduiCorr()->Draw("CONT4Z");
    c->SaveAs("../analisi_risoluzione_energia/analitica/collineare/hist_residui_AnColl_corr.png");
    obj->GetHResiduiMean()->Draw("CONT4Z");
    c->SaveAs("../analisi_risoluzione_energia/analitica/collineare/hist_residui_AnColl_mean.png");
    obj->GetHResiduiCos()->Draw("CONT4Z");
    c->SaveAs("../analisi_risoluzione_energia/analitica/collineare/hist_residui_AnColl_cos.png");

    c->Close();
}
