  void plt_stack_mom(){
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






  THStack *hs = new THStack("hs","Stacked Background");
  hs->Add(hall9);hs->Add(hall1);hs->Add(hall7);
  hs->Add(hall5);hs->Add(hall6);hs->Add(hall8);hs->Add(hall4);
  hs->Add(hall2);//hs->Add(hall);
  
   mcsig4.Draw("mc4_mom_ee_kpi>>hall",cut2&&cut1);
    hall->SetFillColor(1);
    hall->SetLineColor(1);

    // FormatData(hall);
   //  NameAxes(hall, "P*_{anti-D0} (GeV/c)", "Events/ 2 MeV/c"); 
     hall->SetXTitle("P*_{#bar{D^{0}}} (Gev/c)");
     hall->GetXaxis()->CenterTitle(true);
     hall->GetXaxis()->SetLabelSize(0.03);
     hall->GetXaxis()->SetTitleSize(0.05);
     hall->SetYTitle("Events/ 2 MeV/c");
     hall->GetYaxis()->SetLabelSize(0.03);
     hall->GetYaxis()->SetTitleSize(0.05);
     hall->GetYaxis()->CenterTitle(true);
     
     hall->SetFillColor(1);
     hall->SetLineColor(1);

     hs->Draw("same");



    Double_t incmentr = (Double_t)hall->GetEntries();

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
    leg->SetTextFont(6);
    leg->SetTextSize(25);
    leg->Draw();


  can1->Print("../doc/fig/dd_stack_mom.pdf");
  cout<<" incmentr = "<<incmentr<<endl;
 






}
