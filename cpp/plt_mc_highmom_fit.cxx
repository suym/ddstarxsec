#include "TMath.h"
#include <math.h>
#include <fstream.h>
#include <iomanip.h>
#include <iostream.h>
#include <fstream.h>
#include <stdlib.h>
#include <math.h>
#include <Math/ProbFunc.h>
#include <Math/ProbFuncMathCore.h>
gSystem->Load("libRooFit");
using namespace RooFit;
using namespace std;
void plt_mc_highmom_fit(){

		gStyle->SetOptTitle(0);
		gStyle->SetOptStat(0);
		gStyle->SetOptFit(0);
		gROOT->Reset();
               // gROOT->ProcessLine(".L /afs/ihep.ac.cn/users/s/suym/plots/bes3plotstyle.h");
               // gROOT->ProcessLine(".L /afs/ihep.ac.cn/users/s/suym/plots/bes3plotstyle.C");
                gROOT->ProcessLine(".x datafile.C");
           
               // SetStyle();
               // SetPrelimStyle();

   TCanvas *can1 = new TCanvas("can1","can1",800,600); 
   can1->SetFillColor(0);
   can1->SetBorderSize(2);
   can1->SetLeftMargin(0.15);
   can1->SetRightMargin(0.05);
   can1->SetTopMargin(0.05);
   can1->SetBottomMargin(0.2);
   can1->SetFrameFillStyle(0);
   can1->SetFrameBorderMode(0);
   gStyle->SetLegendBorderSize(0);
   gStyle->SetPadBorderMode(0);
   gStyle->SetPadBorderSize(0);
   gStyle->SetPadTopMargin(0.05);
   gStyle->SetPadBottomMargin(0.1);
   gStyle->SetPadLeftMargin(0.05); //0.21
   gStyle->SetPadRightMargin(0.05); //0.05
   gStyle->SetOptStat(0000);
   gStyle->SetOptTitle(0000);
   //gPad->SetLogy();
    can1->SetFillColor(0);
    can1->SetBorderSize(2);
    can1->SetLeftMargin(0.15);
    can1->SetFrameFillStyle(0);
    can1->SetFrameBorderMode(0);

           
  const double x1min= 0.75;
  const double x1max= 1.098;
  const double n1bin= 58;


  RooRealVar xreg("xreg", "xreg", x1min,x1max);


  TH1F *hall= new TH1F("hall","",n1bin, x1min, x1max);
  TH1F *hall1= new TH1F("hall1","",n1bin, x1min, x1max);
  TH1F *hall2a= new TH1F("hall2a","",n1bin, x1min, x1max);
  TH1F *hall2b= new TH1F("hall2b","",n1bin, x1min, x1max);
  TH1F *hall2= new TH1F("hall2","",n1bin, x1min, x1max);
  TH1F *hall3= new TH1F("hall3","",n1bin, x1min, x1max);
  TH1F *hall4= new TH1F("hall4","",n1bin, x1min, x1max);
  TH1F *hall5= new TH1F("hall5","",n1bin, x1min, x1max);
  TH1F *hall6= new TH1F("hall6","",n1bin, x1min, x1max);
  TH1F *hall7= new TH1F("hall7","",n1bin, x1min, x1max);
  TH1F *hall8= new TH1F("hall8","",n1bin, x1min, x1max);
  TH1F *hall9= new TH1F("hall9","",n1bin, x1min, x1max);
  TH1F *hall10= new TH1F("hall10","",n1bin, x1min, x1max);
  TH1F *hall11= new TH1F("hall11","",n1bin, x1min, x1max);
  TH1F *hall12= new TH1F("hall12","",n1bin, x1min, x1max);
  TH1F *hall13= new TH1F("hall13","",n1bin, x1min, x1max);
  TH1F *hall14= new TH1F("hall14","",n1bin, x1min, x1max);
  TH1F *hall15= new TH1F("hall15","",n1bin, x1min, x1max);
  TH1F *hall16= new TH1F("hall16","",n1bin, x1min, x1max);
  TH1F *hall17= new TH1F("hall17","",n1bin, x1min, x1max);
  TH1F *hall18= new TH1F("hall18","",n1bin, x1min, x1max);
  TH1F *hall19= new TH1F("hall19","",n1bin, x1min, x1max);
  
  TH1F *hs= new TH1F("hs","",n1bin, x1min, x1max);
  TH1F *hs1= new TH1F("hs1","",n1bin, x1min, x1max);
  TH1F *hs2= new TH1F("hs2","",n1bin, x1min, x1max);
  TH1F *hs3= new TH1F("hs3","",n1bin, x1min, x1max);
  TH1F *hs4= new TH1F("hs4","",n1bin, x1min, x1max);
  TH1F *hs5= new TH1F("hs5","",n1bin, x1min, x1max);
  TH1F *hs6= new TH1F("hs6","",n1bin, x1min, x1max);
  TH1F *hs7= new TH1F("hs7","",n1bin, x1min, x1max);
  TH1F *hs8= new TH1F("hs8","",n1bin, x1min, x1max);
  TH1F *hs9= new TH1F("hs9","",n1bin, x1min, x1max);

   
  TCut cut1 =  "abs(mc4_ivtmass_ee_kpi-1.86484)<0.015"; 
  TCut cut1a = "abs(mc1_ivtmass_ee_antiD0D0_kpi-1.86484)<0.015"; 
  TCut cut1b = "abs(mc1_ivtmass_ee_antiD0D0star_kpi-1.86484)<0.015"; 
  TCut cut1c = "abs(mc2_ivtmass_ee_antiD0starD0_antiD0pi0_kpi-1.86484)<0.015"; 
  TCut cut1d = "abs(mc2_ivtmass_ee_antiD0starD0_antiD0gamma_kpi-1.86484)<0.015"; 
  TCut cut1e = "abs(mc2_ivtmass_ee_antiD0starD0star_antiD0pi0_kpi-1.86484)<0.015"; 
  TCut cut1f = "abs(mc2_ivtmass_ee_antiD0starD0star_antiD0gamma_kpi-1.86484)<0.015"; 
  TCut cut1g = "abs(mc3_ivtmass_ee_D_starDz_antiD0pi_kpi-1.86484)<0.015"; 
  TCut cut1h = "abs(mc3_ivtmass_ee_D_starDzstar_antiD0pi_kpi-1.86484)<0.015"; 
  TCut cut1i = "abs(mc1_ivtmass_ee_antiD0D0starpi0_kpi-1.86484)<0.015"; 
  TCut cut1j = "abs(mc1_ivtmass_ee_antiD0Dzstarpi_kpi-1.86484)<0.015"; 
  TCut cut2 = "mc4_mom_ee_kpi>0"; 
  TCut cut3 = "mc1_mom_ee_antiD0D0_kpi>0"; 
  TCut cut4a = "mc1_mom_ee_antiD0D0starpi0_kpi>0"; 
  TCut cut4b = "mc1_mom_ee_antiD0Dzstarpi_kpi>0"; 
  TCut cut4 = "mc1_mom_ee_antiD0D0star_kpi>0"; 
  TCut cut6 = "mc2_mom_ee_antiD0starD0_antiD0pi0_kpi>0"; 
  TCut cut7 = "mc2_mom_ee_antiD0starD0_antiD0gamma_kpi>0"; 
  TCut cut8 = "mc2_mom_ee_antiD0starD0star_antiD0pi0_kpi>0"; 
  TCut cut9 = "mc2_mom_ee_antiD0starD0star_antiD0gamma_kpi>0"; 
  TCut cut10 = "mc3_mom_ee_D_starDz_antiD0pi_kpi>0"; 
  TCut cut11 = "mc3_mom_ee_D_starDzstar_antiD0pi_kpi>0";
  TCut cut12 = "vtx_coskpi>-0.99";


   mcsig4.Draw("mc4_mom_ee_kpi>>hall",cut2&&cut1);
     hall->SetFillColor(1);
     hall->SetLineColor(1);
    sig.Draw("mc1_mom_ee_antiD0D0_kpi>>hall1",cut3&&cut1a);
    mcsig4.Draw("mc1_mom_ee_antiD0D0_kpi>>hall11",cut3&&cut1a);
     hall1->SetFillColor(2);
     hall1->SetLineColor(2);
    sig1.Draw("mc1_mom_ee_antiD0D0star_kpi>>hall2",cut4&&cut1b);
    mcsig4.Draw("mc1_mom_ee_antiD0D0star_kpi>>hall12",cut4&&cut1b);
    mcsig4.Draw("mc1_mom_ee_antiD0D0starpi0_kpi>>hall2a",cut4a&&cut1i);
    mcsig4.Draw("mc1_mom_ee_antiD0Dzstarpi_kpi>>hall2b",cut4b&&cut1j);
     hall2->SetFillColor(3);
     hall2->SetLineColor(3);
    sig3.Draw("mc2_mom_ee_antiD0starD0_antiD0pi0_kpi>>hall4",cut6&&cut1c);
    mcsig4.Draw("mc2_mom_ee_antiD0starD0_antiD0pi0_kpi>>hall14",cut6&&cut1c);
     hall4->SetFillColor(5);
     hall4->SetLineColor(5);
    sig4.Draw("mc2_mom_ee_antiD0starD0_antiD0gamma_kpi>>hall5",cut7&&cut1d);
    mcsig4.Draw("mc2_mom_ee_antiD0starD0_antiD0gamma_kpi>>hall15",cut7&&cut1d);
     hall5->SetFillColor(6);
     hall5->SetLineColor(6);
    sig5.Draw("mc2_mom_ee_antiD0starD0star_antiD0pi0_kpi>>hall6",cut8&&cut1e);
    mcsig4.Draw("mc2_mom_ee_antiD0starD0star_antiD0pi0_kpi>>hall16",cut8&&cut1e);
     hall6->SetFillColor(7);
     hall6->SetLineColor(7);
    sig6.Draw("mc2_mom_ee_antiD0starD0star_antiD0gamma_kpi>>hall7",cut9&&cut1f);
    mcsig4.Draw("mc2_mom_ee_antiD0starD0star_antiD0gamma_kpi>>hall17",cut9&&cut1f);
     hall7->SetFillColor(8);
     hall7->SetLineColor(8);
    sig7.Draw("mc3_mom_ee_D_starDz_antiD0pi_kpi>>hall8",cut10&&cut1g);
    mcsig4.Draw("mc3_mom_ee_D_starDz_antiD0pi_kpi>>hall18",cut10&&cut1g);
     hall8->SetFillColor(9);
     hall8->SetLineColor(9);
    sig8.Draw("mc3_mom_ee_D_starDzstar_antiD0pi_kpi>>hall9",cut11&&cut1h);
    mcsig4.Draw("mc3_mom_ee_D_starDzstar_antiD0pi_kpi>>hall19",cut11&&cut1h);
     hall9->SetFillColor(4);
     hall9->SetLineColor(4);

     hall->SetLineWidth(2);
     hall7->SetLineWidth(2);
     hall8->SetLineWidth(2);

     Double_t mentr = (Double_t)hall->GetEntries();
     hs->Add(hall,hall11,1,-1); 
     hs1->Add(hs,hall12,1,-1);hs2->Add(hs1,hall14,1,-1);
     hs3->Add(hs2,hall15,1,-1);
     hs4->Add(hs3,hall16,1,-1);hs5->Add(hs4,hall17,1,-1);
     hs6->Add(hs5,hall18,1,-1); 
     hs7->Add(hs6,hall19,1,-1);
     hs8->Add(hs7,hall2a,1,-1);
     hs9->Add(hs8,hall2b,1,-1);



         RooDataHist* mc = new RooDataHist("mc", "", xreg, hall);
	

	RooDataHist mcsig11("mcsig11","mcsig11",xreg,hall1);
	RooHistPdf mcsig1_pdf("mcsig1_pdf1","mcsig1_pdf1",RooArgSet(xreg),mcsig11);
 
	RooDataHist mcsig12("mcsig12","mcsig12",xreg,hall2);
	RooHistPdf mcsig2_pdf("mcsig2_pdf1","mcsig2_pdf1",RooArgSet(xreg),mcsig12);

	RooDataHist mcsig12a("mcsig12a","mcsig12a",xreg,hall2a);
	RooHistPdf mcsig2a_pdf("mcsig2a_pdf","mcsig2a_pdf",RooArgSet(xreg),mcsig12a);

	RooDataHist mcsig12b("mcsig12b","mcsig12b",xreg,hall2b);
	RooHistPdf mcsig2b_pdf("mcsig2b_pdf","mcsig2b_pdf",RooArgSet(xreg),mcsig12b);

//	RooDataHist mcsig13("mcsig13","mcsig13",xreg,hall3);
//	RooHistPdf mcsig3_pdf("mcsig3_pdf","mcsig3_pdf",RooArgSet(xreg),mcsig13);

	RooDataHist mcsig14("mcsig14","mcsig14",xreg,hall4);
	RooHistPdf mcsig4_pdf("mcsig4_pdf","mcsig4_pdf",RooArgSet(xreg),mcsig14);

	RooDataHist mcsig15("mcsig15","mcsig15",xreg,hall5);
	RooHistPdf mcsig5_pdf("mcsig5_pdf1","mcsig5_pdf",RooArgSet(xreg),mcsig15);

	RooDataHist mcsig16("mcsig16","mcsig16",xreg,hall16);
	RooHistPdf mcsig6_pdf("mcsig6_pdf","mcsig6_pdf",RooArgSet(xreg),mcsig16);

	RooDataHist mcsig17("mcsig17","mcsig17",xreg,hall17);
	RooHistPdf mcsig7_pdf("mcsig7_pdf","mcsig7_pdf",RooArgSet(xreg),mcsig17);

	RooDataHist mcsig18("mcsig18","mcsig18",xreg,hall8);
	RooHistPdf mcsig8_pdf("mcsig8_pdf","mcsig8_pdf",RooArgSet(xreg),mcsig18);

	RooDataHist mcsig19("mcsig19","mcsig19",xreg,hall19);
	RooHistPdf mcsig9_pdf("mcsig9_pdf","mcsig9_pdf",RooArgSet(xreg),mcsig19);

	RooDataHist bkg1("bkg1","bkg1",xreg,hs9);
	RooHistPdf bkg_pdf1("bkg_pdf","bkg_pdf",RooArgSet(xreg),bkg1);



        RooRealVar b0("b0","coefficient #b0", 0,-1000,1000);
        RooRealVar b1("b1","coefficient #b1", 0,-1000,1000);
        RooRealVar b2("b2","coefficient #b2", 0,-1000,1000);
        RooRealVar b3("b3","coefficient #b3", 0,-1000,1000);
        RooChebychev bkg_pdf2("bkg_pdf2","bkg PDF",xreg, RooArgList(b0,b1));

       
	RooRealVar nbkg_1("nbkg_1","nbkg_1", 1000,  0,  50000);
	RooRealVar nbkg_2("nbkg_2","nbkg_2", 4000,  0,  50000);

 

	RooRealVar signal1("signal1","signal1", 1000,  0, 10000);
	RooRealVar signal2("signal2","signal2", 6400,  0, 20000);
	RooRealVar signal2a("signal2a","signal2a", 1000,  0, 10000);
	RooRealVar signal2b("signal2b","signal2b", 1000,  0, 10000);
	RooRealVar signal4("signal4","signal4", 1000,  0, 10000);
	RooRealVar signal5("signal5","signal5", 6100,  0, 10000);
	RooRealVar signal6("signal6","signal6", 1000,  0, 10000);
	RooRealVar signal7("signal7","signal7", 1000,  0, 10000);
	RooRealVar signal8("signal8","signal8", 1000,  0, 10000);
	RooRealVar signal9("signal9","signal9", 1000,  0, 15000);



        

        RooAddPdf sum("sum","all-mcsig+bkg",RooArgList( mcsig1_pdf,mcsig2_pdf,mcsig4_pdf,mcsig5_pdf,mcsig7_pdf,mcsig8_pdf,bkg_pdf1),RooArgList(signal1,signal2,signal4,signal5,signal7,signal8,nbkg_1));
		sum.fitTo(*mc,Extended(kTRUE));
	

		RooPlot* epframe = xreg.frame();
	
                 mc->plotOn(epframe, LineWidth(2),MarkerSize(0.5));
                 sum.plotOn(epframe,LineColor(9),LineWidth(2));
                 sum.plotOn(epframe,Components(bkg_pdf1 ),LineColor(2),LineWidth(2),LineStyle(kDashed));
              //   sum.plotOn(epframe,Components(bkg_pdf2 ),LineColor(8),LineWidth(2),LineStyle(kDashed));
               //  sum.plotOn(epframe,Components(mcsig1_pdf ),LineColor(3),LineWidth(2),LineStyle(kDashed));
                // sum.plotOn(epframe,Components(mcsig2_pdf ),LineColor(3),LineWidth(2),LineStyle(kDashed));
                // sum.plotOn(epframe,Components(mcsig2a_pdf ),LineColor(33),LineWidth(2),LineStyle(kDashed));
                // sum.plotOn(epframe,Components(mcsig2b_pdf ),LineColor(44),LineWidth(2),LineStyle(kDashed));
               //  sum.plotOn(epframe,Components(mcsig4_pdf ),LineColor(2),LineWidth(2),LineStyle(kDashed));
                // sum.plotOn(epframe,Components(mcsig5_pdf ),LineColor(6),LineWidth(2),LineStyle(kDashed));
                //  sum.plotOn(epframe,Components(mcsig6_pdf ),LineColor(7),LineWidth(2),LineStyle(kDashed));
                // sum.plotOn(epframe,Components(mcsig7_pdf ),LineColor(4),LineWidth(2),LineStyle(kDashed));
               //  sum.plotOn(epframe,Components(mcsig8_pdf ),LineColor(5),LineWidth(2),LineStyle(kDashed));
               //  sum.plotOn(epframe,Components(mcsig9_pdf ),LineColor(3),LineWidth(2),LineStyle(kDashed));
 


               epframe->SetTitle("P*_{#bar{D^{0}}}");
               epframe->SetXTitle("P*_{#bar{D^{0}}} (GeV/c)");
               epframe->GetXaxis()->CenterTitle(true);
               epframe->GetXaxis()->SetTitleSize(0.05);
               epframe->GetXaxis()->SetLabelSize(0.03);
               epframe->SetYTitle("Events/6 MeV");
               epframe->GetYaxis()->CenterTitle(true);
               epframe->GetYaxis()->SetTitleSize(0.05);
               epframe->GetYaxis()->SetLabelSize(0.03);
               epframe->Draw("");
		

   // TLegend * leg = new TLegend(0.35, 0.65, 0.55, 0.85);
    TLegend * leg = new TLegend(0.2, 0.71, 0.32, 0.91);
    leg->AddEntry(hall,  "inclusive MC", "L");
    leg->AddEntry(hall8,  "fitted curve", "L");
    leg->AddEntry(hall1,  "background curve", "L");
    leg->SetFillStyle(0);
    leg->SetFillColor(0);
    leg->SetTextFont(6);
    leg->SetTextSize(25);
    leg->SetBorderSize(0);
    leg->Draw();



          cout<<"Filled events number = "<<mentr<<endl;
          cout<<" N_signal = "<<(signal1.getVal()+signal2.getVal()+signal4.getVal()+signal5.getVal()+signal7.getVal()+signal8.getVal())<<" +- "<<TMath::Sqrt(signal1.getError()*signal1.getError()+signal2.getError()*signal2.getError()+signal4.getError()*signal4.getError()+signal5.getError()*signal5.getError()+signal7.getError()*signal7.getError()+signal8.getError()*signal8.getError())<<endl;
          cout<<" N_signal1 = "<<signal1.getVal()<<" +- "<<signal1.getError()<<endl;
          cout<<" N_signal2 = "<<signal2.getVal()<<" +- "<<signal2.getError()<<endl;
          cout<<" N_signal4 = "<<signal4.getVal()<<" +- "<<signal4.getError()<<endl;
          cout<<" N_signal5 = "<<signal5.getVal()<<" +- "<<signal5.getError()<<endl;
          cout<<" N_signal7 = "<<signal7.getVal()<<" +- "<<signal7.getError()<<endl;
          cout<<" N_signal8 = "<<signal8.getVal()<<" +- "<<signal8.getError()<<endl;
          cout<<" N_bkg_1 = "<<nbkg_1.getVal()<<" +- "<<nbkg_1.getError()<<endl;
       //   cout<<" N_bkg_2 = "<<nbkg_2.getVal()<<" +- "<<nbkg_2.getError()<<endl;

        // can1->Print("../doc/fig/dd_mom_fit.pdf");

}
