#include "TFile.h"
#include "TH2D.h"
#include "TH1D.h"
#include "TF1.h"
#include "TFitResult.h"
#include "TCanvas.h"
#include "TAxis.h"

#include <string>
#include <iostream>

void gaussiane_angolo()
{
    // faccio un fit a intervalli regolari con una gaussiana più un costante
    TFile *f = new TFile("grafici.root", "READ");
    f->cd();
    TH2D *h2 = (TH2D *)f->Get("T_Angle");

    TFile *f_gauss = new TFile("./analisi_angolo/fit_gaussini_angolo.root", "RECREATE");
    f_gauss->cd();

    TCanvas *c = new TCanvas("c", "c", 1000, 450, 900, 650);
    c->cd();

    for (int i = 0; i < 5; i++)
    {
        c->SetName(("istogramma_intervallo_" + std::to_string(i)).c_str());

        TH1D *temp = h2->ProjectionY("temp", i * 10, (i + 1) * 10 - 0.01);
        temp->SetTitle(("proiezone L/#sigma " + std::to_string(i * 2 * 10) + "-" + std::to_string((i + 1) * 2 * 10)).c_str());
        temp->Rebin(2);
        temp->GetYaxis()->SetTitle("conteggi");
        temp->GetXaxis()->SetRangeUser(0, 0.15);
        temp->Draw();

        TF1 *f_fit = new TF1("f_fit", "[2]*exp( -pow((x-[0])/[1],2) )/sqrt(2*pi*[1]*[1]) + [3]", 0, 0.15);
        f_fit->SetParameter(0, 0);
        f_fit->SetParameter(1, 0.01);
        f_fit->SetParameter(2, 6000);
        f_fit->SetParameter(3, 0);

        TFitResultPtr r = temp->Fit(f_fit, "RS");
        r->SetName(("ris_isto_" + std::to_string(i)).c_str());

        c->Write();
        r->Write();
        delete temp;
        delete f_fit;
    }

    delete h2;
    delete f;
    delete c;
}

void proiezioni_masse(double start, double stop, int n_int)
{
    TFile *f = new TFile("grafici.root", "READ");
    f->cd();
    TH2D *h2 = (TH2D *)f->Get("Resolution");

    TFile *f_mass = new TFile("./analisi_risoluzione_energia/proiezioni_massa_invariante.root", "RECREATE");
    f_mass->cd();

    TCanvas *c = new TCanvas("c", "c", 1000, 450, 900, 650);
    c->cd();

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
        temp->GetXaxis()->SetRangeUser(0, 1);
        temp->Draw();

        static int count = 1;
        c->SetName(("intervallo" + std::to_string(count++)).c_str());
        c->Write();
        delete temp;
    }

    delete h2;
    delete f;
    delete c;
}