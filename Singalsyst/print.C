void print(TString filename,TString varName)
{
  TFile *f1, *f2,*f3,*f4,*TF,*f5;
  int n=48;
  TH1D *cr;

  f1 = new TFile(filename);

  cr  = (TH1D*)f1->Get(varName);

  for(int i=0;i<n;i++)
    {
      //      cout<<cr->GetBinContent(i)<<" +- "<<cr->GetBinError(i)<<endl;
      cout<<cr->GetBinError(i)<<endl;
    }
  cout<<"Bin content "<<endl;
  for(int i=0;i<n;i++)
    {
      cout<<cr->GetBinContent(i)<<endl;
    }

  cout<<"relative stat unc : "<<endl;
  for(int i=0;i<n;i++)
    {
      cout<<cr->GetBinError(i)/cr->GetBinContent(i)<<endl;
    }

}

