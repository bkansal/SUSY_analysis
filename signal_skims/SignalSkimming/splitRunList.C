#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<iomanip>
#include<stdlib.h>

using namespace std;
void splitRunList(string infile,int nfPerJob){
  //------------ needed for condor files --------------
  string exeCondor  = "worker2.sh";

   // string exeAna     = "skimmingSR_TChiNG";
   // string filesToTransfer = "processSigFile_TChiNG_.C,TChiNG_Summer16v3Fast.SMS-TChiNG_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_job0.root,EWeakino_N2N1Xsec.root";

  //  string filesToTransfer = "processSigFile_TChiNG_.C,TChiNG_Fall17_MassScan.root,EWeakino_Xsec.root";
  //  string exeAna     = "skimmingSR_TChiWG";
  //  string filesToTransfer = "processSigFile_TChiWG_.C,TChiWG_MassScan.root,EWeakino_Xsec.root";

  // string exeAna     = "skimmingSR_T5ttttZg";
  // string filesToTransfer = "processSigFile_T5ttttZg_.C,T5ttttZG_Summer16v3Fast_MassScan.root,mGl_Xsecpb_absUnc.root";

  string exeAna     = "skimmingSR_T6ttZg";
  string filesToTransfer = "processSigFile_T6ttZg_.C,T6ttZG_Summer16v3_MassScan.root,mStop_Xsecpb_absUnc.root";

  // string exeAna     = "skimmingSR_T5bbbbZg";
  // string filesToTransfer = "processSigFile_T5bbbbZg_.C,T5bbbbZg_MassScan.root,mGl_Xsecpb_absUnc.root";
  // string filesToTransfer = "processSigFile.C,T5bbbbZg_MassScan.root,T5qqqqHg_MassScan.root,T6ttZg_MassScan.root,TChiNG_MassScan.root,TChiWG_MassScan.root,T6ttZg_MassScan.root,GGM_M1M3_MassScan.root ";

  //  string exeAna     = "skimmingSR";
  // string filesToTransfer = "processSigFile_T5bbbbZg_.C,T5bbbbZG_Fall17Fast.SMS-T5bbbbZg_TuneCP2_13TeV-madgraphMLM-pythia8_job0.root,mGl_Xsecpb_absUnc.root";
   //string filesToTransfer = "processSigFile_T5bbbbZg_.C,T5bbbbZG_Autumn18Fast.SMS-T5bbbbZg_TuneCP2_13TeV-madgraphMLM-pythia8_job0.root,mGl_Xsecpb_absUnc.root";
  //string filesToTransfer = "processSigFile.C,T5bbbbZg_MassScan.root,T5qqqqHg_MassScan.root,T6ttZg_MassScan.root,TChiNG_MassScan.root,TChiWG_MassScan.root,T6ttZg_MassScan.root,GGM_M1M3_MassScan.root ";
  // string exeAna     = "skimmingSR_T5qqqqHg";
  // string filesToTransfer = "processSigFile_T5qqqqHg_.C,T5qqqqHg_Summer16v3_MassScan.root,mGl_Xsecpb_absUnc.root";

  //---------------------------------------------------
  nfPerJob = 1;
  cout<<"executable at worker node : "<<exeCondor<<endl
      <<"Analysis executable : "<<exeAna<<endl
      <<"Number of files per job is set to 1"<<endl;
    //      <<"dataset name for analysis : "<<datasetAna<<endl;
  //----------------- split the input files into smaller ones ------------------
  ifstream file(infile);
  if(!file){cout<<"Couldn't Open File "<<infile<<endl;}
  string str,dataset=infile;
  dataset.pop_back();  dataset.pop_back();  dataset.pop_back();  dataset.pop_back();
  vector<string> fname;
  while (std::getline(file, str))
    {
      fname.push_back(str);
    }
  file.close();

  int jobid=0;
  char name[200];
  ofstream outf;
  for(int i=0,j=0;i<fname.size();){
    sprintf(name,"FileList_%s_job%i.txt",dataset.c_str(),jobid);
    outf.open(name);
    for(j=0;j<nfPerJob && i<fname.size();j++){
      outf<<fname[i]<<endl;
      i++;
    }
    jobid++;
    outf.close();
  }

  //--------------------- make files for codor ------------------------------------
  char fileListName[200],logFile[200];
  for(int i=0;i<jobid;i++){
    sprintf(name,"%s_job%i.jdl",dataset.c_str(),i);
    sprintf(fileListName,"FileList_%s_job%i.txt",dataset.c_str(),i);
    sprintf(logFile,"%s_job%i",dataset.c_str(),i);
    outf.open(name);
    outf<<"universe = vanilla"<<endl
	<<"Executable = "<<exeCondor<<endl
      //	<<"Requirements = OpSys == \"LINUX\" && (Arch != \"DUMMY\" )"<<endl
	// <<"request_disk = 10000000"<<endl
	// <<"request_memory = 10000"<<endl
	<<"Should_Transfer_Files = YES"<<endl
	<<"WhenToTransferOutput = ON_EXIT_OR_EVICT"<<endl
	<<"Transfer_Input_Files = "<<exeAna<<","<<fileListName<<","<<filesToTransfer<<endl
      //	<<"PeriodicRemove = ( JobStatus == 2 ) && ( ( CurrentTime - EnteredCurrentStatus ) > 600 )"<<endl
	<<"Output = "<<logFile<<".stdout"<<endl
	<<"Error = "<<logFile<<".stderr"<<endl
	<<"Log = "<<logFile<<".condor"<<endl
	<<"notification = Error"<<endl
      //	<<"notify_user = vhegde@FNAL.GOV"<<endl
      //      	<<"x509userproxy = $ENV(X509_USER_PROXY)"<<endl
	<<"Arguments = "<<fileListName<<" "<<logFile<<".root "<<endl
    //    <<"Arguments = "<<exeAna<<" "<<fileListName<<" "<<logFile<<".root "<<datasetAna<<endl;
	<<"+LENGTH=\"SHORT\""<<endl
	<<endl
	<<"Queue 1";
    outf.close();
  }
  //------------------------ submit to condor --------------------------------------
  int t1=100;
  cout<<"Do you want to submit "<<jobid<<" jobs? If yes enter 100"<<endl;
  cin>>t1;
  for(int i=0;i<jobid && t1==100;i++){
    sprintf(name,"condor_submit %s_job%i.jdl",dataset.c_str(),i);
    system(name); 
  }
  
}

void splitRunList(){
  cout<<"Please specify the input txt file to use and no. of files per job"<<endl;
  cout<<"splitRunList(string infile,int nfPerJob)"<<endl;
}
