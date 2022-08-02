#include "TFile.h"
#include "TH2D.h"
#include "TH1D.h"
#include "TF1.h"
#include "TFitResult.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TGraphErrors.h"
#include "TLegend.h"
#include "TPad.h"
#include "TStyle.h"

#include "./utilities.cc"

#include <string>
#include <iostream>

void gaussiane_angolo(double start = 0, double stop = 100, int n_int = 10, int reb = 1)
{
    // faccio un fit a intervalli regolari con una gaussiana più un costante
    TFile *f = new TFile("grafici.root", "READ");
    f->cd();
    TH2D *h2 = (TH2D *)f->Get("T_Angle");

    TFile *f_gauss = new TFile("./analisi_angolo/fit_gaussiani_angolo.root", "UPDATE");
    f_gauss->cd();

    TCanvas *c = new TCanvas("c", "c", 1800, 1300);
    c->Divide(3, 3);
    gStyle->SetOptFit();

    int count = 1;
    double inc = (stop - start) / n_int;
    for (int i = start; i < stop; i = i + inc)
    {
        c->cd(count++);
        c->SetName(("isto_intervallo_" + std::to_string(i)).c_str());

        std::string s1 = std::to_string(i);
        std::string s2 = std::to_string((i + inc));
        if (i < 10)
        {
            s1.resize(1);
        }
        else if (i < 100)
        {
            s1.resize(2);
        }
        else if (i >= 100)
        {
            s1.resize(3);
        }

        if (i + inc < 10)
        {
            s2.resize(1);
        }
        else if (i + inc < 100)
        {
            s2.resize(2);
        }
        else if (i + inc >= 100)
        {
            s2.resize(3);
        }

        std::string titolo = "proiezone L/#sigma_{L} " + s1 + "-" + s2;

        TH1D *temp = h2->ProjectionY(("temp" + s1).c_str(), h2->GetXaxis()->FindBin(i), h2->GetXaxis()->FindBin(i + inc));
        temp->Rebin(reb);

        // correggo i bin sullo spazio delle fasi
        for (int i = 1; i <= temp->GetNbinsX(); i++)
        {
            static Double_t area_cir;
            area_cir = int_settore_circolare(temp->GetBinLowEdge(i), temp->GetBinLowEdge(i + 1));
            temp->SetBinContent(i, temp->GetBinContent(i) / area_cir);
        }

        temp->SetTitle(titolo.c_str());
        temp->GetYaxis()->SetTitle("conteggi");
        temp->GetXaxis()->SetRangeUser(0, 0.15);
        temp->Draw();

        TF1 *f_fit = new TF1("f_fit", "[2]*exp( -pow((x-[0])/[1],2) )/sqrt(2*pi*[1]*[1]) + [3]*exp([4]*x)", 0, 0.03);

        f_fit->SetParameter(0, 0);
        f_fit->SetParLimits(0, 0, 0.000001);
        f_fit->SetParameter(1, 0.01);
        f_fit->SetParLimits(1, 0.005, 0.04);
        f_fit->SetParameter(2, temp->GetMaximum());
        f_fit->SetParameter(3, 0);

        temp->Fit(f_fit, "RS");
        TFitResultPtr r = temp->Fit(f_fit, "RS");
        if (reb == 1)
        {
            r->SetName(("ris_isto_" + std::to_string(i)).c_str());
            f_gauss->Delete(("ris_isto_" + std::to_string(i) + ";*").c_str());
        }
        else if (reb != 1)
        {
            r->SetName(("ris_isto_rebin" + std::to_string(reb) + "_" + std::to_string(i)).c_str());
            f_gauss->Delete(("ris_isto_rebin" + std::to_string(reb) + "_" + std::to_string(i) + ";*").c_str());
        }

        r->Write();
        c->SaveAs("./analisi_angolo/Fit_gaussini.png");
    }
}

void proiezioni_masse(std::string oggetto, double start = 2.6, double stop = 4, int n_int = 10)
{
    TFile *f = new TFile("grafici.root", "READ");
    f->cd();
    TH2D *h2 = (TH2D *)f->Get(oggetto.c_str());

    TFile *f_mass = new TFile(("./analisi_risoluzione_energia/proiezioni_" + oggetto + ".root").c_str(), "RECREATE");
    f_mass->cd();

    TCanvas *c = new TCanvas("c", "c", 1000, 450, 900, 650);
    c->cd();

    int *count = new int(1);
    double inc = (stop - start) / n_int;
    for (double i = start; i < stop; i = i + inc)
    {
        std::string s1 = std::to_string(i);
        s1.resize(4);
        std::string s2 = std::to_string(i + inc);
        s2.resize(4);

        TH1D *temp = h2->ProjectionY("temp", h2->GetXaxis()->FindBin(i), h2->GetXaxis()->FindBin(i + inc));
        temp->SetTitle(("proiezone massa invariante " + s1 + "-" + s2 + " GeV").c_str());
        temp->GetYaxis()->SetTitle("conteggi");
        temp->GetXaxis()->SetLimits(-2, 1);
        temp->GetXaxis()->SetRangeUser(-2, 1);
        temp->Draw();

        c->SetName(("intervallo" + std::to_string((*count)++)).c_str());
        c->Write();
        delete temp;
    }

    delete count;
    delete h2;
    delete f;
    delete c;
}

void medie_rms_proiezioni(double start = 2.6, double stop = 4, int n_int = 10)
{
    TFile *f = new TFile("grafici.root", "READ");
    f->cd();
    TH2D *h2 = (TH2D *)f->Get("Resolution");

    TFile *f_mass = new TFile("./analisi_risoluzione_energia/grafico_medie.root", "RECREATE");
    f_mass->cd();

    TCanvas *c = new TCanvas("c", "c", 1500, 600);
    c->SetName("media_rms");
    c->Divide(2, 1);

    TGraphErrors *g_mean = new TGraphErrors();
    g_mean->SetNameTitle("g_mean", "risoluzione media nel grafico (massa,risoluzione)");
    g_mean->SetMarkerStyle(20);
    g_mean->GetXaxis()->SetTitle("Massa invariante [GeV]");
    g_mean->GetYaxis()->SetTitle("media risoluzione");

    TGraphErrors *g_rms = new TGraphErrors();
    g_rms->SetNameTitle("g_rms", "rms medio nel grafico (massa,risoluzione)");
    g_rms->SetMarkerStyle(20);
    g_rms->GetXaxis()->SetTitle("Massa invariante [GeV]");
    g_rms->GetYaxis()->SetTitle("RMS");

    double inc = (stop - start) / n_int;
    for (double i = start; i < stop; i = i + inc)
    {
        TH1D *temp = h2->ProjectionY("temp", h2->GetXaxis()->FindBin(i), h2->GetXaxis()->FindBin(i + inc));
        double mean = temp->GetMean();
        double mean_err = temp->GetMeanError();
        double rms = temp->GetRMS();
        double rms_err = temp->GetRMSError();
        static int c_n = 0;

        g_mean->AddPoint(i + inc / 2, mean);
        g_mean->SetPointError(c_n, 0, mean_err);
        g_rms->AddPoint(i + inc / 2, rms);
        g_rms->SetPointError(c_n, 0, rms_err);
        c_n++;
        delete temp;
    }

    c->cd(1);
    gPad->SetGrid();
    g_mean->Draw("AP");

    c->cd(2);
    gPad->SetGrid();
    g_rms->Draw("AP");
    c->Write();
    c->SaveAs("./analisi_risoluzione_energia/media_rms.png");

    // delete g_mean;
    delete h2;
    delete f;
    // delete c
}

void proiezioni_masse_tot(double start = 2.6, double stop = 4, int n_int = 9)
{
    TFile *f = new TFile("grafici.root", "READ");
    f->cd();
    TH2D *h_coll = (TH2D *)f->Get("Resolution_coll");
    TH2D *h_imp_coll = (TH2D *)f->Get("Resolution_imp_coll");
    TH2D *h_non_coll = (TH2D *)f->Get("Resolution_non_coll");

    TFile *f_mass = new TFile("./analisi_risoluzione_energia/proiezioni_totale.root", "RECREATE");
    f_mass->cd();

    TCanvas *c = new TCanvas("c", "c", 1000, 450, 1800, 1300);
    c->cd();
    c->Divide(3, 3);

    int count = 1;
    double inc = (stop - start) / n_int;
    for (double i = start; i < stop; i = i + inc)
    {
        c->cd(count);
        std::string s1 = std::to_string(i);
        s1.resize(4);
        std::string s2 = std::to_string(i + inc);
        s2.resize(4);

        TH1D *temp_coll = h_coll->ProjectionY(("temp_coll" + s1).c_str(), h_coll->GetXaxis()->FindBin(i), h_coll->GetXaxis()->FindBin(i + inc));
        temp_coll->SetTitle(("proiezone massa invariante " + s1 + "-" + s2 + " GeV").c_str());
        temp_coll->GetYaxis()->SetTitle("conteggi");
        temp_coll->GetXaxis()->SetLimits(-3, 1);
        temp_coll->GetXaxis()->SetRangeUser(-3, 1);
        temp_coll->SetFillStyle(3002);
        temp_coll->SetLineWidth(2);
        temp_coll->SetLineColor(kRed);
        temp_coll->SetFillColorAlpha(kRed, 0.35);
        temp_coll->GetYaxis()->SetMaxDigits(3);
        temp_coll->SetStats(0);
        temp_coll->Draw();

        TH1D *temp_imp_coll = h_imp_coll->ProjectionY(("temp_imp_coll" + s1).c_str(), h_imp_coll->GetXaxis()->FindBin(i), h_imp_coll->GetXaxis()->FindBin(i + inc));
        temp_imp_coll->SetLineWidth(2);
        temp_imp_coll->SetLineColor(kBlue);
        temp_imp_coll->SetFillStyle(3002);
        temp_imp_coll->SetFillColorAlpha(kBlue, 0.35);
        temp_imp_coll->SetStats(0);
        temp_imp_coll->Draw("SAME");

        TH1D *temp_non_coll = h_non_coll->ProjectionY(("temp_non_coll" + s1).c_str(), h_non_coll->GetXaxis()->FindBin(i), h_non_coll->GetXaxis()->FindBin(i + inc));
        temp_non_coll->SetLineWidth(2);
        temp_non_coll->SetLineColor(kGreen);
        temp_non_coll->SetFillStyle(3002);
        temp_non_coll->SetFillColorAlpha(kGreen, 0.35);
        temp_non_coll->SetStats(0);
        temp_non_coll->Draw("SAME");

        count++;
    }

    c->SaveAs("./analisi_risoluzione_energia/proiezioni_totali.png");
    delete h_coll;
    delete h_imp_coll;
    delete h_non_coll;
    delete f;
}