#include"Event.C"

void test(char *filename="numu_faser_1M.dump.root", char *treename="tree"){

	TFile *_file0 = TFile::Open(filename);
	TTree *tree = (TTree *) _file0->Get(treename);

	Event *ev = new Event(tree);
	
	for(int iev=0; iev<10; iev++){
		printf("iev=%d\n", iev);
		ev->GetEntry(iev);
		printf("neutrino pdgid %d %s neutrino energy = %7.2f\n", ev->PDGnu, ev->cc?"CC":"NC", ev->Enu_true);
		
		for(int i=0; i<ev->nfsp; i++){
			printf("pdgid %5d E %7.2f ", ev->pdg[i], ev->E[i]);
			printf("P %7.2f %7.2f %7.2f ", ev->px[i], ev->py[i], ev->pz[i]);
			
			
			printf("\n");
			
		}
		
	}
}
