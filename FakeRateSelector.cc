#define FakeRateSelector_cxx
// The class definition in FakeRateSelector.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.


// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following se                                              FakeRateSelector.C")
// root> T->Process("FakeRateSelector.C","some options")
// root> T->Process("FakeRateSelector.C+")
//


#include "FakeRateSelector.h"
#include <TStyle.h>

void FakeRateSelector::SlaveBegin(TTree * /*tree*/)
{
     // The SlaveBegin() function is called after the Begin() function.
     // When running with PROOF SlaveBegin() is called on each slave server.
     // The tree argument is deprecated (on PROOF 0 is passed).

}

Bool_t FakeRateSelector::Process(Long64_t entry)
{
     // The Process() function is called for each entry in the tree (or possibly
     // keyed object in the case of PROOF) to be processed. The entry argument
     // specifies which entry in the currently loaded tree is to be processed.
     // When processing keyed objects with PROOF, the object is already loaded
     // and is available via the fObject pointer.
     //
     // This function should contain the \"body\" of the analysis. It can contain
     // simple or elaborate selection criteria, run algorithms on the data
     // of the event and typically fill histograms.
     //
     // The processing can be stopped by calling Abort().
     //
     // Use fStatus to set the return value of TTree::Process().
     //
     // The return value is currently not used.
    
    if (! SelectorBase::Process(entry)) return false;
    if (std::abs(static_cast<int>(*nWWLooseElec + *nWZLooseMuon) - 3) > 0.1)
        return false;
    if (!(*e1IsCBVIDTight &&
        ( *e1IsEB ? *e1PVDXY < 0.05 : *e1PVDXY < 0.1) &&
        ( *e1IsEB ? *e1PVDZ < 0.1 : *e1PVDZ < 0.2)) &&
        (*e2IsCBVIDTight &&
        ( *e2IsEB ? *e2PVDXY < 0.05 : *e2PVDXY < 0.1) &&
        ( *e2IsEB ? *e2PVDZ < 0.1 : *e2PVDZ < 0.2)))
            return false;
    passingLoose_->Fill(*e3Pt, *e3Eta);
    if (*e3IsCBVIDTight &&
        ( *e3IsEB ? *e3PVDXY < 0.05 : *e3PVDXY < 0.1) &&
        ( *e3IsEB ? *e3PVDZ < 0.1 : *e3PVDZ < 0.2))
        passingTight_->Fill(*e3Pt, *e3Eta);

    return true;
}

void FakeRateSelector::SetupNewDirectory()
{
    // Must call base class setup
    SelectorBase::SetupNewDirectory();
    AddObject<TH2D>(passingTight_, "passingTight", "Tight leptons; p_{T} [GeV]; Eta", 8, 10, 50, 5, -2.5, 2.5);
    AddObject<TH2D>(passingLoose_, "passingLoose", "Leptons passing tight failing loose; p_{T} [GeV]; Eta", 8, 10, 50, 5, -2.5, 2.5);
}

