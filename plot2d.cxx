void plot2d(){
  TFile *f = new TFile("FASERnu1.root");
  f->ls();
  TTree *tree = nullptr;
  TH2F* hist = new TH2F("yz","Hit Collection",1000,-600,200,100,-50,50);
  f->GetObject("FASERnu",tree);
  auto branch = tree->GetBranch("row_wise_branch");
  branch->Print();
  auto leafx = branch->GetLeaf("x");
  auto leafy = branch->GetLeaf("y");
  auto leafz = branch->GetLeaf("z");
  tree->Scan("x","y","z");
  int n = leafx->GetLen();
  for (int i=0; i<n; i++){
  hist->Fill(leafz->GetValue(i),leafy->GetValue(i));
}
  f->ls();
  TCanvas *c = new TCanvas();
  hist->Draw();
  hist->GetXaxis()->SetTitle("z (cm)");
  hist->GetYaxis()->SetTitle("y (cm)");
  hist->SetMarkerStyle(6);
  hist->SetMarkerSize(1.4);
  c->Print("hist2d.png");
//  cout << "Entries: " << n << endl;
}
