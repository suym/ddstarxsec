  void plt_data4260_mom(){
    gROOT->Reset();
 // gROOT->ProcessLine(".L /afs/ihep.ac.cn/users/s/suym/plots/bes3plotstyle.h");
 // gROOT->ProcessLine(".L /afs/ihep.ac.cn/users/s/suym/plots/bes3plotstyle.C");
    gROOT->ProcessLine(".x datafile.C");
    gSystem->Load("libRooFit");
 // SetStyle();
 // SetPrelimStyle();
  
 // gStyle->SetOptStat(0);
  using namespace RooFit ;
  TCanvas * can1 = new TCanvas("can1","BESIII Plots", 800,600);
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
  const double x1max= 2;
  const double n1bin= 500;

  TH1D *hall= new TH1D("hall","",n1bin, x1min, x1max);
  TH1D *hall1= new TH1D("hall1","",n1bin, x1min, x1max);

  TCut cut1 = "abs(vtx_mkpi-1.86484)<0.015"; 
  TCut cut3 = "vtx_coskpi>-0.99"; 
  //4.26_sideband
  TCut cut5 = "vtx_mkpi>1.80345&&vtx_mkpi<1.82984"; 
  TCut cut6 = "vtx_mkpi>1.89984&&vtx_mkpi<1.93291"; 

  datasig_4260.Draw("vtx_mom_kpi>>hall",cut1&&cut3);
  hall->SetFillColor(1);
  hall->SetLineColor(1);
  hall->SetLineWidth(2);

  RooRealVar xreg1("xreg1", "xreg1", x1min,x1max); 
  RooDataHist* incmc = new RooDataHist("incmc", "", xreg1, hall);
  RooPlot* xframe1 = xreg1.frame();
  incmc->plotOn(xframe1, LineWidth(2),MarkerSize(0.5));

  xframe1->SetTitle("P*_{#bar{D^{0}}}");
  xframe1->SetXTitle("P*_{#bar{D^{0}}} (GeV/c)");
  xframe1->GetXaxis()->CenterTitle(true);
  xframe1->GetXaxis()->SetTitleSize(0.05);
  xframe1->GetXaxis()->SetLabelSize(0.03);
  xframe1->SetYTitle("Events/4 MeV/c");
  xframe1->GetYaxis()->CenterTitle(true);
  xframe1->GetYaxis()->SetTitleSize(0.05);
  xframe1->GetYaxis()->SetLabelSize(0.03);

  xframe1->Draw("");

  Double_t incmentr = (Double_t)hall->GetEntries();

  /* // TLegend * leg = new TLegend(0.2, 0.35, 0.55, 0.92);
    TLegend * leg = new TLegend(0.2, 0.31, 0.55, 0.91);
    leg->AddEntry(hall,  "data", "L");
  
    leg->SetFillColor(0);
    leg->SetLineWidth(2);
    leg->SetTextFont(6);
    leg->SetTextSize(25);
    leg->Draw();

  */

  
  cout<<" incmentr = "<<incmentr<<endl;

 // can1->Print("../doc/fig/dd_mom.pdf");
 



}
