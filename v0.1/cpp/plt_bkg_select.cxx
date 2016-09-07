 void plt_bkg_select(){
  gROOT->Reset();
 // gROOT->ProcessLine(".L /afs/ihep.ac.cn/users/s/suym/plots/bes3plotstyle.h");
 // gROOT->ProcessLine(".L /afs/ihep.ac.cn/users/s/suym/plots/bes3plotstyle.C");
  gROOT->ProcessLine(".x datafile.C");
  gSystem->Load("libRooFit");
  gStyle->SetOptStat(0);
  using namespace RooFit ;
  
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
  const double x1max= 14;
  const double n1bin= 28;

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



  TCut cut1 = "abs(mc4_ivtmass_ee_kpi-1.86484)<0.015";
  TCut cut2 = "mc4_mom_ee_kpi>0.5";
  TCut cut3 = "mc4_mom_ee_kpi<0.5&&mc4_mom_ee_kpi>0";
   

   mcsig4.Draw("mc_ngam>>hall",cut1);
     hall->SetFillColor(1);
     hall->SetLineColor(1);
   mcsig4.Draw("mc_ngam>>hall1",cut1&&cut2);
     hall1->SetFillColor(2);
     hall1->SetLineColor(2);
   mcsig4.Draw("mc_ngam>>hall2",cut1&&cut3);
     hall2->SetFillColor(3);
     hall2->SetLineColor(3);  
 /*  mcsig4.Draw("mc_ncharged>>hall",cut1);
     hall->SetFillColor(1);
     hall->SetLineColor(1);
   mcsig4.Draw("mc_ncharged>>hall1",cut1&&cut2);
     hall1->SetFillColor(2);
     hall1->SetLineColor(2);
   mcsig4.Draw("mc_ncharged>>hall2",cut1&&cut3);
     hall2->SetFillColor(3);
     hall2->SetLineColor(3);  */ 
 /*  mcsig4.Draw("mc_visibleE>>hall",cut1);
     hall->SetFillColor(1);
     hall->SetLineColor(1);
   mcsig4.Draw("mc_visibleE>>hall1",cut1&&cut2);
     hall1->SetFillColor(2);
     hall1->SetLineColor(2);
   mcsig4.Draw("mc_visibleE>>hall2",cut1&&cut3);
     hall2->SetFillColor(3);
     hall2->SetLineColor(3);   */

   hall->SetLineWidth(2);
   hall1->SetLineWidth(2);
   hall2->SetLineWidth(2);


   RooRealVar xreg("xreg", "xreg", x1min,x1max);

   RooDataHist* mc = new RooDataHist("mc", "", xreg, hall);
   RooDataHist* mc1 = new RooDataHist("mc1", "", xreg, hall1);
   RooDataHist* mc2 = new RooDataHist("mc2", "", xreg, hall2);

   RooPlot* xframe1 = xreg.frame();
  
   mc->plotOn(xframe1, LineWidth(2),MarkerSize(0.5));
   mc1->plotOn(xframe1,LineColor(2),LineWidth(2),MarkerSize(0.5));
   mc2->plotOn(xframe1,LineColor(3),LineWidth(2),MarkerSize(0.5));

  xframe1->SetTitle("Gamnumber");
  xframe1->SetXTitle("Gamnumber");
  xframe1->GetXaxis()->CenterTitle(true);
  xframe1->GetXaxis()->SetTitleSize(0.05);
  xframe1->GetXaxis()->SetLabelSize(0.03);
  xframe1->SetYTitle("Events/0.5  ");
  xframe1->GetYaxis()->CenterTitle(true);
  xframe1->GetYaxis()->SetTitleSize(0.05);
  xframe1->GetYaxis()->SetLabelSize(0.03);
 // xframe1->GetYaxis()->SetRangeUser(0,30000);

  

  xframe1->Draw("");



  TLegend * leg = new TLegend(0.2, 0.71, 0.32, 0.91);
  leg->AddEntry(hall,  "MC", "L");
  leg->AddEntry(hall1, " kpi momentum > 0.5 ", "L");
  leg->AddEntry(hall2, "0 < kpi momentum < 0.5 ", "L");

  leg->SetFillColor(0);
  leg->SetTextFont(6);
  leg->SetTextSize(25);
  leg->Draw();

 // can1->Print("../doc/fig/gammanumber.pdf");









}
