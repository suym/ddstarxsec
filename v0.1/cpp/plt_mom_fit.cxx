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
void plt_mom_fit(){

		gStyle->SetOptTitle(0);
		gStyle->SetOptStat(0);
		gStyle->SetOptFit(0);
		gROOT->Reset();
              //  gROOT->ProcessLine(".L /afs/ihep.ac.cn/users/s/suym/plots/bes3plotstyle.h");
               // gROOT->ProcessLine(".L /afs/ihep.ac.cn/users/s/suym/plots/bes3plotstyle.C");
                gROOT->ProcessLine(".x datafile.C");
           
              //  SetStyle();
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

           
  const double x1min= 0;
  const double x1max= 1.2;
  const double n1bin= 600;


  RooRealVar xreg("xreg", "xreg", x1min,x1max);


  TH1F *hall= new TH1F("hall","",n1bin, x1min, x1max);
  TH1F *hall1= new TH1F("hall1","",n1bin, x1min, x1max);
  TH1F *hall2= new TH1F("hall2","",n1bin, x1min, x1max);
  TH1F *hall3= new TH1F("hall3","",n1bin, x1min, x1max);
  TH1F *hall4= new TH1F("hall4","",n1bin, x1min, x1max);
  TH1F *hall5= new TH1F("hall5","",n1bin, x1min, x1max);
  TH1F *hall6= new TH1F("hall6","",n1bin, x1min, x1max);
  TH1F *hall7= new TH1F("hall7","",n1bin, x1min, x1max);
  TH1F *hall8= new TH1F("hall8","",n1bin, x1min, x1max);
  TH1F *hall9= new TH1F("hall9","",n1bin, x1min, x1max);
  TH1F *hall10= new TH1F("hall10","",n1bin, x1min, x1max);
  
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

   
  TCut cut1 = "abs(mc4_ivtmass_ee_kpi-1.86484)<0.015"; 
  TCut cut1a = "abs(mc1_ivtmass_ee_antiD0D0_kpi-1.86484)<0.015"; 
  TCut cut1b = "abs(mc1_ivtmass_ee_antiD0D0star_kpi-1.86484)<0.015"; 
  TCut cut1c = "abs(mc2_ivtmass_ee_antiD0starD0_antiD0pi0_kpi-1.86484)<0.015"; 
  TCut cut1d = "abs(mc2_ivtmass_ee_antiD0starD0_antiD0gamma_kpi-1.86484)<0.015"; 
  TCut cut1e = "abs(mc2_ivtmass_ee_antiD0starD0star_antiD0pi0_kpi-1.86484)<0.015"; 
  TCut cut1f = "abs(mc2_ivtmass_ee_antiD0starD0star_antiD0gamma_kpi-1.86484)<0.015"; 
  TCut cut1g = "abs(mc3_ivtmass_ee_D_starDz_antiD0pi_kpi-1.86484)<0.015"; 
  TCut cut1h = "abs(mc3_ivtmass_ee_D_starDzstar_antiD0pi_kpi-1.86484)<0.015"; 
  TCut cut2 = "mc4_mom_ee_kpi>0"; 
  TCut cut3 = "mc1_mom_ee_antiD0D0_kpi>0"; 
  TCut cut4 = "mc1_mom_ee_antiD0D0star_kpi>0"; 
  TCut cut6 = "mc2_mom_ee_antiD0starD0_antiD0pi0_kpi>0"; 
  TCut cut7 = "mc2_mom_ee_antiD0starD0_antiD0gamma_kpi>0"; 
  TCut cut8 = "mc2_mom_ee_antiD0starD0star_antiD0pi0_kpi>0"; 
  TCut cut9 = "mc2_mom_ee_antiD0starD0star_antiD0gamma_kpi>0"; 
  TCut cut10 = "mc3_mom_ee_D_starDz_antiD0pi_kpi>0"; 
  TCut cut11 = "mc3_mom_ee_D_starDzstar_antiD0pi_kpi>0";

   mcsig4.Draw("mc4_mom_ee_kpi>>hall",cut2&&cut1);
     hall->SetFillColor(1);
     hall->SetLineColor(1);
    mcsig4.Draw("mc1_mom_ee_antiD0D0_kpi>>hall1",cut3&&cut1a);
     hall1->SetFillColor(2);
     hall1->SetLineColor(2);
    mcsig4.Draw("mc1_mom_ee_antiD0D0star_kpi>>hall2",cut4&&cut1b);
     hall2->SetFillColor(3);
     hall2->SetLineColor(3);
    mcsig4.Draw("mc2_mom_ee_antiD0starD0_antiD0pi0_kpi>>hall4",cut6&&cut1c);
     hall4->SetFillColor(5);
     hall4->SetLineColor(5);
    mcsig4.Draw("mc2_mom_ee_antiD0starD0_antiD0gamma_kpi>>hall5",cut7&&cut1d);
     hall5->SetFillColor(6);
     hall5->SetLineColor(6);
    mcsig4.Draw("mc2_mom_ee_antiD0starD0star_antiD0pi0_kpi>>hall6",cut8&&cut1e);
     hall6->SetFillColor(7);
     hall6->SetLineColor(7);
    mcsig4.Draw("mc2_mom_ee_antiD0starD0star_antiD0gamma_kpi>>hall7",cut9&&cut1f);
     hall7->SetFillColor(8);
     hall7->SetLineColor(8);
    mcsig4.Draw("mc3_mom_ee_D_starDz_antiD0pi_kpi>>hall8",cut10&&cut1g);
     hall8->SetFillColor(9);
     hall8->SetLineColor(9);
    mcsig4.Draw("mc3_mom_ee_D_starDzstar_antiD0pi_kpi>>hall9",cut11&&cut1h);
     hall9->SetFillColor(4);
     hall9->SetLineColor(4);

     hall->SetLineWidth(2);
     hall7->SetLineWidth(2);
     hall8->SetLineWidth(2);

     Double_t mentr = (Double_t)hall->GetEntries();
     hs->Add(hall,hall1,1,-1); hs1->Add(hs,hall2,1,-1);hs2->Add(hs1,hall4,1,-1);
     hs3->Add(hs2,hall5,1,-1); hs4->Add(hs3,hall6,1,-1);hs5->Add(hs4,hall7,1,-1);
     hs6->Add(hs5,hall8,1,-1); hs7->Add(hs6,hall9,1,-1);//hs8->Add(hs7,hall3,1,-1);

   


         RooDataHist* mc = new RooDataHist("mc", "", xreg, hall);
	

        RooDataHist mcsigbkg("mcsigbkg","mcsigbkg",xreg,hall);
	RooHistPdf mcsigbkg_pdf("mcsigbkg_pdf","mcsigbkg_pdf",RooArgSet(xreg),mcsigbkg);
	
	RooDataHist mcsig11("mcsig11","mcsig11",xreg,hall1);
	RooHistPdf mcsig1_pdf("mcsig1_pdf","mcsig1_pdf",RooArgSet(xreg),mcsig11);
 
	RooDataHist mcsig12("mcsig12","mcsig12",xreg,hall2);
	RooHistPdf mcsig2_pdf("mcsig2_pdf","mcsig2_pdf",RooArgSet(xreg),mcsig12);

//	RooDataHist mcsig13("mcsig13","mcsig13",xreg,hall3);
//	RooHistPdf mcsig3_pdf("mcsig3_pdf","mcsig3_pdf",RooArgSet(xreg),mcsig13);

	RooDataHist mcsig14("mcsig14","mcsig14",xreg,hall4);
	RooHistPdf mcsig4_pdf("mcsig4_pdf","mcsig4_pdf",RooArgSet(xreg),mcsig14);

	RooDataHist mcsig15("mcsig15","mcsig15",xreg,hall5);
	RooHistPdf mcsig5_pdf("mcsig5_pdf","mcsig5_pdf",RooArgSet(xreg),mcsig15);

	RooDataHist mcsig16("mcsig16","mcsig16",xreg,hall6);
	RooHistPdf mcsig6_pdf("mcsig6_pdf","mcsig6_pdf",RooArgSet(xreg),mcsig16);

	RooDataHist mcsig17("mcsig17","mcsig17",xreg,hall7);
	RooHistPdf mcsig7_pdf("mcsig7_pdf","mcsig7_pdf",RooArgSet(xreg),mcsig17);

	RooDataHist mcsig18("mcsig18","mcsig18",xreg,hall8);
	RooHistPdf mcsig8_pdf("mcsig8_pdf","mcsig8_pdf",RooArgSet(xreg),mcsig18);

	RooDataHist mcsig19("mcsig19","mcsig19",xreg,hall9);
	RooHistPdf mcsig9_pdf("mcsig9_pdf","mcsig9_pdf",RooArgSet(xreg),mcsig19);

	RooDataHist bkg1("bkg1","bkg1",xreg,hs7);
	RooHistPdf bkg_pdf("bkg_pdf","bkg_pdf",RooArgSet(xreg),bkg1);


	RooRealVar signal1("signal1","signal1", 0,  0,  20000);
	RooRealVar signal2("signal2","signal2", 0,  0,  20000);
//	RooRealVar signal3("signal3","signal3", 0,  0,  10000);
	RooRealVar signal4("signal4","signal4", 0,  0,  20000);
	RooRealVar signal5("signal5","signal5", 0,  0,  20000);
	RooRealVar signal6("signal6","signal6", 0,  0,  20000);
	RooRealVar signal7("signal7","signal7", 0,  0,  20000);
	RooRealVar signal8("signal8","signal8", 0,  0,  20000);
	RooRealVar signal9("signal9","signal9", 0,  0,  20000);

	RooRealVar nbkg("bkg","bkg", 0,  0,  30000);


        
       // RooAddPdf sum37("sum37","mcsig3+mcsig7",RooArgList(mcsig3_pdf,mcsig7_pdf),RooArgList(signal3,signal7));

        RooAddPdf sum("sum","all-mcsig+bkg",RooArgList( mcsig1_pdf,mcsig2_pdf,mcsig4_pdf,mcsig5_pdf,mcsig6_pdf,mcsig7_pdf,mcsig8_pdf,mcsig9_pdf,bkg_pdf),RooArgList(signal1,signal2,signal4,signal5,signal6,signal7,signal8,signal9,nbkg));

		sum.fitTo(*mc,Extended(kTRUE));
	

		RooPlot* epframe = xreg.frame();
	
               //  mc.plotOn(epframe,MarkerSize(1.0),Binning(72),DataError(RooAbsData::SumW2));
                 mc->plotOn(epframe, LineWidth(2),MarkerSize(0.5));
                 sum.plotOn(epframe,LineColor(9),LineWidth(2),MarkerSize(0.5));
                /* sum.plotOn(epframe,Components(mcsig1_pdf ),LineColor(30),LineStyle(kDashed));
               sum.plotOn(epframe,Components(mcsig2_pdf ),LineColor(3),LineStyle(kDashed));
             //  sum.plotOn(epframe,Components(mcsig3_pdf ),LineColor(33),LineStyle(kDashed));
               sum.plotOn(epframe,Components(mcsig4_pdf ),LineColor(5),LineStyle(kDashed));
               sum.plotOn(epframe,Components(mcsig5_pdf ),LineColor(6),LineStyle(kDashed));
               sum.plotOn(epframe,Components(mcsig6_pdf ),LineColor(7),LineStyle(kDashed));
               sum.plotOn(epframe,Components(mcsig7_pdf ),LineColor(40),LineStyle(kDashed));
               sum.plotOn(epframe,Components(mcsig8_pdf ),LineColor(4),LineStyle(kDashed));
               sum.plotOn(epframe,Components(mcsig9_pdf ),LineColor(2),LineStyle(kDashed));*/
                 sum.plotOn(epframe,Components(bkg_pdf ),LineColor(8),LineWidth(2),MarkerSize(0.5),LineStyle(kDashed));
 
                /* sum.plotOn(epframe,Components("mcsig1_pdf,mcsig2_pdf,mcsig4_pdf,mcsig5_pdf,mcsig6_pdf,mcsig7_pdf,mcsig8_pdf,mcsig9_pdf" ),LineColor(30),LineStyle(kDashed));
               sum.plotOn(epframe,Components("mcsig2_pdf,mcsig4_pdf,mcsig5_pdf,mcsig6_pdf,mcsig7_pdf,mcsig8_pdf,mcsig9_pdf" ),LineColor(3),LineStyle(kDashed));
             //  sum.plotOn(epframe,Components(mcsig3_pdf ),LineColor(33),LineStyle(kDashed));
               sum.plotOn(epframe,Components("mcsig4_pdf,mcsig5_pdf,mcsig6_pdf,mcsig7_pdf,mcsig8_pdf,mcsig9_pdf" ),LineColor(5),LineStyle(kDashed));
               sum.plotOn(epframe,Components("mcsig5_pdf,mcsig6_pdf,mcsig7_pdf,mcsig8_pdf,mcsig9_pdf" ),LineColor(6),LineStyle(kDashed));
               sum.plotOn(epframe,Components("mcsig6_pdf,mcsig7_pdf,mcsig8_pdf,mcsig9_pdf" ),LineColor(7),LineStyle(kDashed));
               sum.plotOn(epframe,Components("mcsig7_pdf,mcsig8_pdf,mcsig9_pdf" ),LineColor(40),LineStyle(kDashed));
               sum.plotOn(epframe,Components("mcsig8_pdf,mcsig9_pdf" ),LineColor(4),LineStyle(kDashed));
               sum.plotOn(epframe,Components(mcsig9_pdf ),LineColor(2),LineStyle(kDashed));
                 sum.plotOn(epframe,Components(bkg ),LineColor(1),LineStyle(kDashed));*/
              // mcsigbkg_pdf.plotOn(epframe,LineColor(1),LineStyle(kDashed));


               epframe->SetTitle("P*_{#bar{D^{0}}}");
               epframe->SetXTitle("P*_{#bar{D^{0}}} (GeV/c)");
               epframe->GetXaxis()->CenterTitle(true);
               epframe->GetXaxis()->SetTitleSize(0.05);
               epframe->GetXaxis()->SetLabelSize(0.03);
               epframe->SetYTitle("Events/2 MeV");
               epframe->GetYaxis()->CenterTitle(true);
               epframe->GetYaxis()->SetTitleSize(0.05);
               epframe->GetYaxis()->SetLabelSize(0.03);
               epframe->Draw("");
		

   // TLegend * leg = new TLegend(0.35, 0.65, 0.55, 0.85);
    TLegend * leg = new TLegend(0.2, 0.71, 0.32, 0.91);
    leg->AddEntry(hall,  "inclusive MC", "L");
    leg->AddEntry(hall8,  "fitted curve", "L");
    leg->AddEntry(hall7,  "background curve", "L");
    leg->SetFillStyle(0);
    leg->SetFillColor(0);
    leg->SetTextFont(6);
    leg->SetTextSize(25);
    leg->SetBorderSize(0);
    leg->Draw();



          cout<<"Filled events number = "<<mentr<<endl;
          cout<<" N_signal = "<<(signal1.getVal()+signal2.getVal()+signal4.getVal()+signal5.getVal()+signal6.getVal()+signal7.getVal()+signal8.getVal()+signal9.getVal())<<" +- "<<TMath::Sqrt(signal1.getError()*signal1.getError()+signal2.getError()*signal2.getError()+signal4.getError()*signal4.getError()+signal5.getError()*signal5.getError()+signal6.getError()*signal6.getError()+signal7.getError()*signal7.getError()+signal8.getError()*signal8.getError()+signal9.getError()*signal9.getError())<<endl;
          cout<<" N_signal1 = "<<signal1.getVal()<<" +- "<<signal1.getError()<<endl;
          cout<<" N_signal2 = "<<signal2.getVal()<<" +- "<<signal2.getError()<<endl;
       //   cout<<" N_signal3 = "<<signal3.getVal()<<" +- "<<signal3.getError()<<endl;
          cout<<" N_signal4 = "<<signal4.getVal()<<" +- "<<signal4.getError()<<endl;
          cout<<" N_signal5 = "<<signal5.getVal()<<" +- "<<signal5.getError()<<endl;
          cout<<" N_signal6 = "<<signal6.getVal()<<" +- "<<signal6.getError()<<endl;
          cout<<" N_signal7 = "<<signal7.getVal()<<" +- "<<signal7.getError()<<endl;
          cout<<" N_signal8 = "<<signal8.getVal()<<" +- "<<signal8.getError()<<endl;
          cout<<" N_signal9 = "<<signal9.getVal()<<" +- "<<signal9.getError()<<endl;
          cout<<" N_bkg = "<<nbkg.getVal()<<" +- "<<nbkg.getError()<<endl;
          cout<<" chi2 = "<<epframe->chiSquare(6)<<endl;


         can1->Print("../doc/fig/dd_mom_fit.pdf");

}
