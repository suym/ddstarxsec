  void plt_mom(){
    gROOT->Reset();
 // gROOT->ProcessLine(".L /afs/ihep.ac.cn/users/s/suym/plots/bes3plotstyle.h");
 // gROOT->ProcessLine(".L /afs/ihep.ac.cn/users/s/suym/plots/bes3plotstyle.C");
    gROOT->ProcessLine(".x datafile.C");
 // gSystem->Load("libRooFit");
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
  const double x1max= 1.2;
  const double n1bin= 600;

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
  hall1->SetLineWidth(2);
  hall2->SetLineWidth(2);
  hall4->SetLineWidth(2);
  hall5->SetLineWidth(2);
  hall6->SetLineWidth(2);
  hall7->SetLineWidth(2);
  hall8->SetLineWidth(2);
  hall9->SetLineWidth(2);
 // FormatData(EOP);
  //NameAxes(EOP,"MManti_D0","");


    
    RooRealVar xreg1("xreg1", "xreg1", x1min,x1max); 

  RooDataHist* incmc = new RooDataHist("incmc", "", xreg1, hall);
  RooDataHist* incmc1 = new RooDataHist("incmc1", "", xreg1, hall1);
  RooDataHist* incmc2 = new RooDataHist("incmc2", "", xreg1, hall2);
  RooDataHist* incmc4 = new RooDataHist("incmc4", "", xreg1, hall4);
  RooDataHist* incmc5 = new RooDataHist("incmc5", "", xreg1, hall5);
  RooDataHist* incmc6 = new RooDataHist("incmc6", "", xreg1, hall6);
  RooDataHist* incmc7 = new RooDataHist("incmc7", "", xreg1, hall7);
  RooDataHist* incmc8 = new RooDataHist("incmc8", "", xreg1, hall8);
  RooDataHist* incmc9 = new RooDataHist("incmc9", "", xreg1, hall9);


  
  RooPlot* xframe1 = xreg1.frame();


  incmc->plotOn(xframe1, LineWidth(2),MarkerSize(0.5));
  incmc1->plotOn(xframe1,LineColor(2),LineWidth(2),MarkerColor(2),MarkerSize(0.5));
  incmc2->plotOn(xframe1,LineColor(3),LineWidth(2),MarkerColor(3),MarkerSize(0.5));
 // incmc3->plotOn(xframe1,LineColor(4),LineWidth(1),MarkerColor(4),MarkerSize(0.5));
  incmc4->plotOn(xframe1,LineColor(5),LineWidth(2),MarkerColor(5),MarkerSize(0.5));
  incmc5->plotOn(xframe1,LineColor(6),LineWidth(2),MarkerColor(6),MarkerSize(0.5));
  incmc6->plotOn(xframe1,LineColor(7),LineWidth(2),MarkerColor(7),MarkerSize(0.5));
  incmc7->plotOn(xframe1,LineColor(8),LineWidth(2),MarkerColor(8),MarkerSize(0.5));
  incmc8->plotOn(xframe1,LineColor(9),LineWidth(2),MarkerColor(9),MarkerSize(0.5));
  incmc9->plotOn(xframe1,LineColor(4),LineWidth(2),MarkerColor(4),MarkerSize(0.5));

  xframe1->SetTitle("P*_{#bar{D^{0}}}");
  xframe1->SetXTitle("P*_{#bar{D^{0}}} (GeV/c)");
  xframe1->GetXaxis()->CenterTitle(true);
  xframe1->GetXaxis()->SetTitleSize(0.05);
  xframe1->GetXaxis()->SetLabelSize(0.03);
  xframe1->SetYTitle("Events/2 MeV/c");
  xframe1->GetYaxis()->CenterTitle(true);
  xframe1->GetYaxis()->SetTitleSize(0.05);
  xframe1->GetYaxis()->SetLabelSize(0.03);

  

  xframe1->Draw("");




  Double_t incmentr = (Double_t)hall->GetEntries();
  Double_t incmentr1 = (Double_t)hall1->GetEntries();
  Double_t incmentr2 = (Double_t)hall2->GetEntries();
 // Double_t incmentr3 = (Double_t)hall3->GetEntries();
  Double_t incmentr4 = (Double_t)hall4->GetEntries();
  Double_t incmentr5 = (Double_t)hall5->GetEntries();
  Double_t incmentr6 = (Double_t)hall6->GetEntries();
  Double_t incmentr7 = (Double_t)hall7->GetEntries();
  Double_t incmentr8 = (Double_t)hall8->GetEntries();
  Double_t incmentr9 = (Double_t)hall9->GetEntries();

   // TLegend * leg = new TLegend(0.2, 0.35, 0.55, 0.92);
    TLegend * leg = new TLegend(0.2, 0.31, 0.55, 0.91);
    leg->AddEntry(hall,  "inclusive MC", "L");
    leg->AddEntry(hall1,  "#bar{D^{0}}D^{0}", "L");
    leg->AddEntry(hall2,  "#bar{D^{0}}D^{*0}", "L");
  //  leg->AddEntry(hall3,  "D0barD*0pi0", "L");
    leg->AddEntry(hall4,  "#bar{D^{*0}}D^{0}-#bar{D^{0}}#pi^{0}", "L");
    leg->AddEntry(hall5,  "#bar{D^{*0}}D^{0}-#bar{D^{0}}#gamma", "L");
    leg->AddEntry(hall6,  "#bar{D^{*0}}D^{*0}-#bar{D^{0}}#pi^{0}", "L");
    leg->AddEntry(hall7,  "#bar{D^{*0}}D^{*0}-#bar{D^{0}}#gamma", "L");
    leg->AddEntry(hall8,  "#bar{D^{*-}}D^{+}", "L");
    leg->AddEntry(hall9,  "#bar{D^{*-}}D^{*+}", "L");
  
    leg->SetFillColor(0);
    leg->SetLineWidth(2);
    leg->SetTextFont(6);
    leg->SetTextSize(25);
    leg->Draw();

  

  
  cout<<" incmentr = "<<incmentr<<endl;

  cout<<" signal1 = "<<incmentr1<<endl;
  cout<<" signal2 = "<<incmentr2<<endl;
  cout<<" signal4_pi = "<<incmentr4<<endl;
  cout<<" signal5 = "<<incmentr5<<endl;
  cout<<" signal6_pi = "<<incmentr6<<endl;
  cout<<" signal7 = "<<incmentr7<<endl;
  cout<<" signal8 = "<<incmentr8<<endl;
  cout<<" signal9 = "<<incmentr9<<endl;

  cout<<" signal = "<<(incmentr1+incmentr2+incmentr4+incmentr5+incmentr6+incmentr7+incmentr8+incmentr9)<<endl;
  can1->Print("../doc/fig/dd_mom.pdf");
 






}
