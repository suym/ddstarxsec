gSystem->Load("libRooFit");
//gStyle->SetPaperSize(32,16);
using namespace RooFit;
void kpim_simufit()
{    
    gROOT->ProcessLine(".x datafile_3890.C");

    double xmin = 0.09;
    double xmax = 0.59;
    int nbins= 130;

    TCut cut12 = "vtx_coskpi>-0.998";
    TCut cut15 = "abs(vtx_mkpi-1.86484)<0.01625";
    //4.26_sideband
    TCut cut13 = "vtx_mkpi>1.79&&vtx_mkpi<1.82984";
    TCut cut14 = "vtx_mkpi>1.89984&&vtx_mkpi<1.93968";

    RooRealVar x("vtx_mom_kpi", "P^{*}(D^{0}) (GeV/c)", xmin, xmax);
    RooRealVar y("vtx_mkpi", "M(D^{0}) (GeV/c)",1.5, 2.1);
    RooRealVar z("vtx_coskpi", "  ", -2.0, 2.0);
//============================realdata============================//
    RooDataSet data("data", "dataset", t_data, RooArgSet(x,y,z), cut15&&cut12);

//============================sideband============================//
    RooDataSet side("side", "sideset", t_data, RooArgSet(x,y,z), (cut13||cut14)&&cut12);
    //TH1F *h_side = new TH1F("h_side","", 66, xmin, xmax);
    //t_side->Draw("vtx_mom_kpi>>h_side", (cut13||cut14)&&cut12);
    //h_side->Scale(0.496728);
    //RooDataHist side("side","sideset", x, h_side);    
    
//=============================sig MC================================D0barD0_kpi//
    TH1F *h_sig = new TH1F("h_sig","", nbins, xmin, xmax);
    t_sig.Draw("vtx_mom_kpi>>h_sig",cut15&&cut12);
    RooDataHist sig("sig","sig", x, h_sig);
    RooHistPdf sig1_pdf1("sig1_pdf1","sig1_pdf", RooArgSet(x), sig);

    RooRealVar mean1("mean1", "mean1", 0, 0, 0.01);
    //mean1.setConstant();
    RooRealVar sigma1("sigma1", "sigma1",0.01, 0.0,0.1);
    RooGaussian gaus1("gaus1"," gaus fit ", x, mean1,sigma1);
    RooFFTConvPdf sig1_pdf("sig1_pdf","sig1_pdf", x, sig1_pdf1,gaus1);

//=============================sig1 MC================================D0barD0star_kpi//
    TH1F *h_sig1 = new TH1F("h_sig1","", nbins, xmin, xmax);
    t_sig1.Draw("vtx_mom_kpi>>h_sig1",cut15&&cut12);
    RooDataHist sig1("sig1","sig1", x, h_sig1);
    RooHistPdf sig2_pdf1("sig2_pdf1","sig2_pdf1", RooArgSet(x), sig1);

    RooRealVar mean2("mean2", "mean2", 0,0,0.0);
    mean2.setConstant();
    RooRealVar sigma2("sigma2", "sigma2",0.01, 0.0,0.1);
    RooGaussian gaus2("gaus2"," gaus fit ",x, mean2,sigma2);
    RooFFTConvPdf sig2_pdf("sig2_pdf","sig2_pdf", x, sig2_pdf1,gaus2);

//=============================sig4 MC================================D0barstarD0_D0bargamma_kpi//
    TH1F *h_sig4 = new TH1F("h_sig4","", nbins, xmin, xmax);
    t_sig4.Draw("vtx_mom_kpi>>h_sig4",cut15&&cut12);
    RooDataHist sig4("sig4","sig4", x, h_sig4);
    RooHistPdf sig5_pdf("sig5_pdf","sig5_pdf", RooArgSet(x), sig4);

//=============================sig3 MC================================D0barstarD0_D0barpi0_kpi//
    TH1F *h_sig3 = new TH1F("h_sig3","", nbins, xmin, xmax);
    t_sig3.Draw("vtx_mom_kpi>>h_sig3",cut15&&cut12);
    RooDataHist sig3("sig3","sig3", x, h_sig3);
    RooHistPdf sig4_pdf("sig4_pdf","sig4_pdf", RooArgSet(x), sig3);

//=============================sig6 MC================================D0barstarD0star_D0bargamma_kpi//

//=============================sig7 MC================================D_starDz_D0barpi_kpi//
    TH1F *h_sig7 = new TH1F("h_sig7","", nbins, xmin, xmax);
    t_sig7.Draw("vtx_mom_kpi>>h_sig7",cut15&&cut12);
    RooDataHist sig7("sig7","sig7", x, h_sig7);
    RooHistPdf sig8_pdf("sig8_pdf","sig8_pdf", RooArgSet(x), sig7);

    RooRealVar signal1("signal1","signal1",  965,  0, 10000);
    RooRealVar signal2("signal2","signal2", 5757,  0, 20000);
    RooRealVar signal7("signal7","signal7", 1000,  0, 10000);
    RooRealVar signal8("signal8","signal8", 6600,  0, 20000);
    RooRealVar signal45("signal45","signal45", 1000,  0, 30000);
    RooRealVar signal67("signal67","signal67", 1000,  0, 30000);

    RooRealVar factor_gamma_45("factor_gamma_45","",0.3215);
    factor_gamma_45.setConstant(); 
    RooRealVar factor_pi_45("factor_pi_45","",0.6785);
    factor_pi_45.setConstant(); 
    RooFormulaVar signal4("signal4","signal45*factor_pi_45", RooArgSet(signal45, factor_pi_45));
    RooFormulaVar signal5("signal5","signal45*factor_gamma_45", RooArgSet(signal45, factor_gamma_45));

//===================== side bkg pdf ===============================//
    RooRealVar c1("c1","coefficienct #1",-0.1932, -1E2, 1E2);
    RooRealVar c2("c2","coefficienct #2",-0.059, -1E2, 1E2);
    RooRealVar c3("c3","coefficienct #3", 0.13, -1E2, 1E2);
    RooRealVar c4("c4","coefficienct #4", 0.13, -1E2, 1E2);
    RooChebychev bkg("bkg", "bkg p.d.f", x, RooArgList(c1,c2));
    RooRealVar nbkg2("nbkg2","nbkg2", 1767,  0,  50000);
    RooRealVar factor_nbkg2("factor_nbkg2","",0.399231);
    RooFormulaVar nbkg("nbkg","nbkg2*factor_nbkg2", RooArgSet(nbkg2,factor_nbkg2));

    RooAddPdf sum("sum","sum",RooArgList(sig1_pdf,sig2_pdf,sig4_pdf,sig5_pdf,sig8_pdf,bkg),RooArgList(signal1,signal2,signal4,signal5,signal8,nbkg));
    RooAddPdf sum2("sum2","sum2",RooArgList(bkg),RooArgList(nbkg2));


    // Define category to distinguish signal region and sideband region events
    RooCategory sample("sample","sample");
    sample.defineType("data_set") ;
    sample.defineType("side_set") ;
    // Construct combined dataset in (x,sample)
    RooDataSet combData("combData","combined data",x,Index(sample),Import("data_set",data),Import("side_set",side));
    // Construct a simultaneous pdf using category sample as index
    RooSimultaneous simPdf("simPdf","simultaneous pdf",sample);
    simPdf.addPdf(sum,"data_set");
    simPdf.addPdf(sum2,"side_set");
    //RooFitResult* result = simPdf.fitTo(combData, Extended(kTRUE),Range(0.70,1.25),Save(kTRUE));
    RooFitResult* result = simPdf.fitTo(combData, Extended(kTRUE),Save(kTRUE));



  TCanvas *cep = new TCanvas("cep","BESIII Plots", 1200,400);
  cep->Divide(2,1);
  cep->cd(1); 

  RooPlot* epframe = x.frame();
  data.plotOn(epframe,MarkerSize(0.8),Binning(130),DataError(RooAbsData::SumW2),Name("histdata"));
  sum.plotOn(epframe,LineColor(1),Name("pdfsum"));
std::cout<<"frame->chi^2  ==  "<<epframe->chiSquare("pdfsum","histdata",10)<<std::endl;
  TString Par8V = Form("%4.3f",  epframe->chiSquare("pdfsum","histdata",10));
  sum.plotOn(epframe,Components(sig1_pdf),LineColor(2),LineStyle(1));
  sum.plotOn(epframe,Components(sig2_pdf),LineColor(3),LineStyle(2));
  sum.plotOn(epframe,Components(sig4_pdf),LineColor(4),LineStyle(2));
  sum.plotOn(epframe,Components(sig5_pdf),LineColor(5),LineStyle(2));
  sum.plotOn(epframe,Components(sig8_pdf),LineColor(7),LineStyle(2));
  sum.plotOn(epframe,Components(bkg),LineColor(4),LineStyle(2));
  sum.plotOn(epframe,LineColor(1),Name("pdfsum"));
  //sum.paramOn(epframe,Layout(0.22,0.54,0.865));
  epframe->GetXaxis()->SetTitle("P^{*}(D^{0}) (GeV/c)");
  epframe->GetYaxis()->SetTitle("Events / (3.8MeV/c^{2})");
  epframe->GetXaxis()->SetTitleOffset(1.0);
  epframe->GetYaxis()->SetTitleOffset(1.0);
  epframe->Draw();

  TPaveText *pt = new TPaveText(0.48,0.55,0.65,0.65,"BRNDC");
  pt->SetBorderSize(0);
  pt->SetFillColor(0);
  pt->SetTextAlign(12);
  pt->SetTextSize(0.05);
  TString Par8  = "#chi^{2}/dof = " +  Par8V;
  TText *text = pt->AddText(Par8);
  pt->Draw();


  cep->cd(2);
  RooPlot* epframe2 = x.frame();
  side.plotOn(epframe2,MarkerSize(0.8),Binning(130),DataError(RooAbsData::SumW2));
  sum2.plotOn(epframe2,LineColor(4),LineStyle(2));
  sum2.paramOn(epframe2,Layout(0.22,0.54,0.865));
  epframe2->GetXaxis()->SetTitle("P^{*}(D^{0}) (GeV/c)");
  epframe2->GetYaxis()->SetTitle("Events / (3.8MeV/c^{2})");
  epframe2->GetXaxis()->SetTitleOffset(1.0);
  epframe2->GetYaxis()->SetTitleOffset(1.0);
  epframe2->Draw();

  ofstream  out;
  out.open("fit_3890.dat");

  out<<signal1.getVal()<<"    "<<signal1.getError()<<endl;
  out<<signal2.getVal()<<"    "<<signal2.getError()<<endl;
  out<<signal45.getVal()<<"    "<<signal45.getError()<<endl;
  out<<signal8.getVal()<<"    "<<signal8.getError()<<endl;


}
