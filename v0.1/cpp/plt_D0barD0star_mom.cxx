void plt_D0barD0star_mom(){
  
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



  TH1D *hall= new TH1D("hall","",n1bin, x1min, x1max);
  TH1D *hs= new TH1D("hs","",n1bin, x1min, x1max);
  TH1D *hall2= new TH1D("hall2","",n1bin, x1min, x1max);


  TCut cut1 = "abs(mc4_ivtmass_ee_kpi-1.86484)<0.015"; 
  TCut cut1b = "abs(mc1_ivtmass_ee_antiD0D0star_kpi-1.86484)<0.015"; 
  TCut cut2 = "mc4_mom_ee_kpi>0"; 
  TCut cut4 = "mc1_mom_ee_antiD0D0star_kpi>0"; 


    mcsig3.Draw("mc4_mom_ee_kpi>>hall",cut2&&cut1);
     hall->SetFillColor(1);
     hall->SetLineColor(1);
    mcsig3.Draw("mc1_mom_ee_antiD0D0star_kpi>>hall2",cut4&&cut1b);
     hall2->SetFillColor(3);
     hall2->SetLineColor(3);

    Double_t mentrhall = (Double_t)hall->GetEntries();
    Double_t mentr2 = (Double_t)hall2->GetEntries();

   hs->Add(hall,hall2,1.,-1.);


   Double_t mentr = (Double_t)hs->GetEntries();
 
     hs->SetXTitle("P*_{#bar{D^{0}}} (Gev/c)");
     hs->GetXaxis()->CenterTitle(true);
     hs->SetYTitle("Events/ 2 MeV/c");
     hs->GetYaxis()->CenterTitle(true);
     hs->SetFillColor(1);
     hs->SetLineColor(1);

     hs->Draw("");
   cout<<"Filled events number cha = "<<mentr<<endl;
   cout<<"total events number  = "<<mentrhall<<endl;
   cout<<"signal2 events number  = "<<mentr2<<endl;
   cout<<"bkg events number  = "<<(mentrhall-mentr2)<<endl;

  can1->Print("../doc/fig/d0bard0star_bkg.pdf");

}




