  void plt_inc_exc(){
  gROOT->Reset();
 // gROOT->ProcessLine(".L /afs/ihep.ac.cn/users/s/suym/plots/bes3plotstyle.h");
 // gROOT->ProcessLine(".L /afs/ihep.ac.cn/users/s/suym/plots/bes3plotstyle.C");
  gROOT->ProcessLine(".x datafile.C");
 // gSystem->Load("libRooFit");
 // SetStyle();
 // SetPrelimStyle();
  
  gStyle->SetOptStat(0);
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

  const double xmin= 0.8;
  const double xmax= 1.1;
  const double nbin= 400;

  float  norm=10000;

  TCut cut1 = "abs(mc4_ivtmass_ee_kpi-1.86484)<0.015"; 
  TCut cut1a = "abs(mc1_ivtmass_ee_antiD0D0_kpi-1.86484)<0.015"; 
  TCut cut1b = "abs(mc1_ivtmass_ee_antiD0D0star_kpi-1.86484)<0.015"; 
  TCut cut1c = "abs(mc2_ivtmass_ee_antiD0starD0_antiD0pi0_kpi-1.86484)<0.015"; 
  TCut cut1d = "abs(mc2_ivtmass_ee_antiD0starD0_antiD0gamma_kpi-1.86484)<0.015"; 
  TCut cut1e = "abs(mc2_ivtmass_ee_antiD0starD0star_antiD0pi0_kpi-1.86484)<0.015"; 
  TCut cut1f = "abs(mc2_ivtmass_ee_antiD0starD0star_antiD0gamma_kpi-1.86484)<0.015"; 
  TCut cut1g = "abs(mc3_ivtmass_ee_D_starDz_antiD0pi_kpi-1.86484)<0.015"; 
  TCut cut1h = "abs(mc3_ivtmass_ee_D_starDzstar_antiD0pi_kpi-1.86484)<0.015"; 
  TCut cut2 = "mc4_mom_ee_kpi<10"; 
  TCut cut3 = "mc1_mom_ee_antiD0D0_kpi>0"; 
  TCut cut4 = "mc1_mom_ee_antiD0D0star_kpi>0"; 
  TCut cut6 = "mc2_mom_ee_antiD0starD0_antiD0pi0_kpi>0"; 
  TCut cut7 = "mc2_mom_ee_antiD0starD0_antiD0gamma_kpi>0"; 
  TCut cut8 = "mc2_mom_ee_antiD0starD0star_antiD0pi0_kpi>0"; 
  TCut cut9 = "mc2_mom_ee_antiD0starD0star_antiD0gamma_kpi>0"; 
  TCut cut10 = "mc3_mom_ee_D_starDz_antiD0pi_kpi>0"; 
  TCut cut11 = "mc3_mom_ee_D_starDzstar_antiD0pi_kpi>0";


  TH1F *EOP= new TH1F("EOP","",nbin, xmin, xmax);
    mcsig4.Draw("mc1_mom_ee_antiD0D0_kpi>>EOP",cut3&&cut1a);
 //     mcsig4.Draw("mc1_mom_ee_antiD0D0star_kpi>>EOP",cut4&&cut1b);
  //  mcsig4.Draw("mc2_mom_ee_antiD0starD0_antiD0pi0_kpi>>EOP",cut6&&cut1c);
 //   mcsig4.Draw("mc2_mom_ee_antiD0starD0_antiD0gamma_kpi>>EOP",cut7&&cut1d);
  //  mcsig4.Draw("mc2_mom_ee_antiD0starD0star_antiD0pi0_kpi>>EOP",cut8&&cut1e);
  //  mcsig4.Draw("mc2_mom_ee_antiD0starD0star_antiD0gamma_kpi>>EOP",cut9&&cut1f);
   // mcsig4.Draw("mc3_mom_ee_D_starDz_antiD0pi_kpi>>EOP",cut10&&cut1g);
  //  mcsig4.Draw("mc3_mom_ee_D_starDzstar_antiD0pi_kpi>>EOP",cut11&&cut1h);

  EOP->Scale(norm/EOP->Integral());
  EOP->SetLineColor(1);
 // FormatData(EOP);
  //NameAxes(EOP,"MManti_D0","");

  TH1F *EOP1= new TH1F("EOP1","",nbin, xmin, xmax);
    sig.Draw("mc4_mom_ee_kpi>>EOP1",cut1&&cut2);
 // test2sig.Draw("D0p>>EOP1","abs(Manti_D0-1.86484)<0.015");


  EOP1->Scale(norm/EOP1->Integral());
  EOP1->SetLineColor(2);
 // FormatMC1(EOP1);

 // NameAxes(EOP1,"MManti_D0","");

    RooRealVar xreg1("xreg1", "xreg1", xmin,xmax); 
 

  RooDataHist* mc = new RooDataHist("mc", "", xreg1, EOP);
  RooDataHist* mc1 = new RooDataHist("mc1", "", xreg1, EOP1);

  RooPlot* xframe1 = xreg1.frame();
 /* gStyle->SetPadLeftMargin(0.17);
  gStyle->SetPadBottomMargin(0.17);
  gStyle->SetPadRightMargin(0.05);
  gStyle->SetPadTopMargin(0.05);*/


  mc->plotOn(xframe1, LineColor(1),LineWidth(2),MarkerSize(0.5));
  mc1->plotOn(xframe1,LineColor(2),LineWidth(2),MarkerColor(2),MarkerSize(0.5));

  xframe1->SetTitle("P*_{#bar{D^{0}}}");
  xframe1->SetXTitle("P*_{#bar{D^{0}}} (GeV/c)");
  xframe1->GetXaxis()->CenterTitle(true);
  xframe1->GetXaxis()->SetTitleSize(0.05);
  xframe1->GetXaxis()->SetLabelSize(0.03);
  xframe1->SetYTitle("Events/0.5 MeV/c");
  xframe1->GetYaxis()->CenterTitle(true);
  xframe1->GetYaxis()->SetTitleSize(0.05);
  xframe1->GetYaxis()->SetLabelSize(0.03);

  
  xframe1->Draw("");


 

  Double_t mentr = (Double_t)EOP->GetEntries();

  Double_t mentr1 = (Double_t)EOP1->GetEntries();

  Double_t Smentr = (Double_t)EOP->Integral();

  Double_t Smentr1 = (Double_t)EOP1->Integral();
/*  TLegend * leg = new TLegend(0.4, 0.4, 0.5, 0.5);
  leg->AddEntry(EOP,  "inclusive MC", "L");
  
 // leg->SetFillColor(0);
  leg->AddEntry(EOP1, "MC", "L");

 // leg->SetFillColor(0);
  leg->SetFillColor(0);
  leg->SetTextFont(6);
  leg->SetTextSize(25);
  leg->Draw();

*/
  

  cout<<" mentr = "<<mentr<<endl;
  cout<<" mentr1 = "<<mentr1<<endl;
  cout<<" Smentr = "<<Smentr<<endl;
  cout<<" Smentr1 = "<<Smentr1<<endl;
 // can1->Print("canz1.eps");
}
