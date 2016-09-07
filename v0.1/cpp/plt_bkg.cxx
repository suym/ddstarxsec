void plt_bkg(){
  
    gROOT->Reset();
 // gROOT->ProcessLine(".L /afs/ihep.ac.cn/users/s/suym/plots/bes3plotstyle.h");
 // gROOT->ProcessLine(".L /afs/ihep.ac.cn/users/s/suym/plots/bes3plotstyle.C");
    gROOT->ProcessLine(".x datafile.C");
    gSystem->Load("libRooFit");
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
  const double x1min= 0.0;
  const double x1max= 1.2;
  const double n1bin= 600;
 
//  TH1::SetDefaultSumw2();




  TH1D *hall= new TH1D("hall","",n1bin, x1min, x1max);
  TH1D *hall1= new TH1D("hall1","",n1bin, x1min, x1max);
  TH1D *hall2= new TH1D("hall2","",n1bin, x1min, x1max);
  TH1D *hall3= new TH1D("hall3","",n1bin, x1min, x1max);
  TH1D *hall4= new TH1D("hall4","",n1bin, x1min, x1max);
  TH1D *hall5= new TH1D("hall5","",n1bin, x1min, x1max);
  TH1D *hall6= new TH1D("hall6","",n1bin, x1min, x1max);
  TH1D *hall7= new TH1D("hall7","",n1bin, x1min, x1max);
  TH1D *hall8= new TH1D("hall8","",n1bin, x1min, x1max);
  TH1D *hall9= new TH1D("hall9","",n1bin, x1min, x1max);
  TH1D *hs= new TH1D("hs","",n1bin, x1min, x1max);
  TH1D *hs1= new TH1D("hs1","",n1bin, x1min, x1max);
  TH1D *hs2= new TH1D("hs2","",n1bin, x1min, x1max);
  TH1D *hs3= new TH1D("hs3","",n1bin, x1min, x1max);
  TH1D *hs4= new TH1D("hs4","",n1bin, x1min, x1max);
  TH1D *hs5= new TH1D("hs5","",n1bin, x1min, x1max);
  TH1D *hs6= new TH1D("hs6","",n1bin, x1min, x1max);
  TH1D *hs7= new TH1D("hs7","",n1bin, x1min, x1max);
  TH1D *hs8= new TH1D("hs8","",n1bin, x1min, x1max);
  TH1D *hs9= new TH1D("hs9","",n1bin, x1min, x1max);


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
     hall1->SetFillColor(30);
     hall1->SetLineColor(30);
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
     hall7->SetFillColor(40);
     hall7->SetLineColor(40);
    mcsig4.Draw("mc3_mom_ee_D_starDz_antiD0pi_kpi>>hall8",cut10&&cut1g);
     hall8->SetFillColor(4);
     hall8->SetLineColor(4);
    mcsig4.Draw("mc3_mom_ee_D_starDzstar_antiD0pi_kpi>>hall9",cut11&&cut1h);
     hall9->SetFillColor(2);
     hall9->SetLineColor(2);
   
    Double_t mentrhall = (Double_t)hall->GetEntries();
    Double_t mentr1 = (Double_t)hall1->GetEntries();
    Double_t mentr2 = (Double_t)hall2->GetEntries();
    Double_t mentr4 = (Double_t)hall4->GetEntries();
    Double_t mentr5 = (Double_t)hall5->GetEntries();
    Double_t mentr6 = (Double_t)hall6->GetEntries();
    Double_t mentr7 = (Double_t)hall7->GetEntries();
    Double_t mentr8 = (Double_t)hall8->GetEntries();
    Double_t mentr9 = (Double_t)hall9->GetEntries();

  


     hs->Add(hall,hall1,1.,-1.); hs1->Add(hs,hall2,1.,-1.);hs2->Add(hs1,hall4,1.,-1.);
     hs3->Add(hs2,hall5,1.,-1.); hs4->Add(hs3,hall6,1.,-1.);hs5->Add(hs4,hall7,1.,-1.);
     hs6->Add(hs5,hall8,1.,-1.); hs7->Add(hs6,hall9,1.,-1.);

    Double_t mentr = (Double_t)hs7->GetEntries();


   //  FormatData(hs7);
   //  NameAxes(hs7, "P*_{anti-D0} (GeV/c)", "Events/ 2 MeV/c"); 
     hs7->SetXTitle("P*_{#bar{D^{0}}} (Gev/c)");
     hs7->GetXaxis()->CenterTitle(true);
     hs7->SetYTitle("Events/ 2 MeV/c");
     hs7->GetYaxis()->CenterTitle(true);
     hs7->SetFillColor(1);
     hs7->SetLineColor(1);

     hs7->Draw("");
   cout<<"Filled events number cha = "<<mentr<<endl;
   cout<<"total events number  = "<<mentrhall<<endl;
   cout<<"signal1 events number  = "<<mentr1<<endl;
   cout<<"signal2 events number  = "<<mentr2<<endl;
   cout<<"signal4 events number  = "<<mentr4<<endl;
   cout<<"signal5 events number  = "<<mentr5<<endl;
   cout<<"signal6 events number  = "<<mentr6<<endl;
   cout<<"signal7 events number  = "<<mentr7<<endl;
   cout<<"signal8 events number  = "<<mentr8<<endl;
   cout<<"signal9 events number  = "<<mentr9<<endl;
   cout<<"bkg events number  = "<<(mentrhall-mentr1-mentr2-mentr4-mentr5-mentr6-mentr7-mentr8-mentr9)<<endl;


   can1->Print("../doc/fig/dd_bkg.eps");
  /* ofstream  out;
   out.open("bkg.dat");

   out<<"Filled events number = "<<n_total<<endl;
   out<<"Filled events number1 = "<<n_total1<<endl;
   out<<"Filled events number2 = "<<n_total2<<endl;
   out<<"Filled events number4 = "<<n_total4<<endl;
   out<<"Filled events number5 = "<<n_total5<<endl;
   out<<"Filled events number6 = "<<n_total6<<endl;
   out<<"Filled events number7 = "<<n_total7<<endl;
   out<<"Filled events number8 = "<<n_total8<<endl;
   out<<"Filled events number9 = "<<n_total9<<endl;
   out<<"Filled events number cha = "<<(n_total-n_total1-n_total2-n_total4-n_total5-n_total6-n_total7-n_total8-n_total9)<<endl;


*/

}
