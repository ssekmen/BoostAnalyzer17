// Razor recipe taken from the RazorBoost gurus: N. Strobbe, S. Sekmen
// also info here:
//   https://twiki.cern.ch/twiki/bin/view/CMSPublic/RazorLikelihoodHowTo
//#include "TLorentzVector.h"
#include "Math/LorentzVector.h"
typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;
typedef ROOT::Math::DisplacementVector3D<ROOT::Math::Cartesian3D<ROOT::Math::PxPyPzE4D<float>::Scalar> > Vector3;

namespace Razor {
  
  // deltaR:
  double fdeltaR(double eta1, double phi1, double eta2, double phi2) {
    double deltaphi = fabs(phi1 - phi2);
    if (deltaphi > TMath::Pi())
      deltaphi = TMath::TwoPi() - deltaphi;
    double deltaeta = fabs(eta1 - eta2);
    double deltaR = sqrt(deltaphi*deltaphi + deltaeta*deltaeta);
    return deltaR;
  }
  
  // deltaPhi:
  double fdeltaPhi(double phi1, double phi2) {
    double deltaphi = fabs(phi1 - phi2);
    if (deltaphi > TMath::Pi())
      deltaphi = TMath::TwoPi() - deltaphi;
    return deltaphi;
  }
  
  // Hemispheres:
  std::vector<LorentzVector> CombineJets(const std::vector<LorentzVector>& myjets) {
    std::vector<LorentzVector> mynewjets;
    LorentzVector j1, j2;
    //bool foundGood = false;
    int N_comb = 1;
    for(unsigned int i = 0; i < myjets.size(); i++) {
      N_comb *= 2;
    }
    double M_min = 9999999999.0;
    int j_count;
    for(int i = 1; i < N_comb-1; i++) {
      LorentzVector j_temp1, j_temp2;
      int itemp = i;
      j_count = N_comb/2;
      int count = 0;
      while(j_count > 0) {
        if(itemp/j_count == 1) {
          j_temp1 += myjets[count];
        } else {
          j_temp2 += myjets[count];
        }
        itemp -= j_count*(itemp/j_count);
        j_count /= 2;
        count++;
      }
      double M_temp = j_temp1.M2()+j_temp2.M2();
      // smallest mass
      if(M_temp < M_min) {
        M_min = M_temp;
        j1 = j_temp1;
        j2 = j_temp2;
      }
    }
    if(j2.Pt() > j1.Pt()) {
      LorentzVector temp = j1;
      j1 = j2;
      j2 = temp;
    }
    mynewjets.push_back(j1);
    mynewjets.push_back(j2);
    return mynewjets;
  }
  // Hemispheres:
  std::vector<LorentzVector> CombineJetsNew(const std::vector<LorentzVector>& myjets, std::vector<size_t > iJet_Boost) {
    std::vector<LorentzVector> mynewjets;
    LorentzVector j1, j2;
    //bool foundGood = false;
    int N_comb = 1;
    for(unsigned int i = 0; i < myjets.size(); i++) {
      N_comb *= 2;
    }
    double M_min = 9999999999.0;
    int j_count;
    std::vector<int> iHemi;
    iHemi.assign(myjets.size(), 0);
    for(int i = 1; i < N_comb-1; i++) {
      LorentzVector j_temp1, j_temp2;
      std::fill(iHemi.begin(), iHemi.end(), 0);
      int itemp = i;
      j_count = N_comb/2;
      int count = 0;
      while(j_count > 0) {
        if(itemp/j_count == 1) {
          j_temp1 += myjets[count];
        } else {
          j_temp2 += myjets[count];
          iHemi[count] = 1;
        }
        itemp -= j_count*(itemp/j_count);
        j_count /= 2;
        count++;
      }
      double M_temp = j_temp1.M2()+j_temp2.M2();
      // smallest mass
      if(M_temp < M_min) {
        bool objects_on_separate_hemis = true;
        if (iJet_Boost.size()>=2) {
          if (iHemi[iJet_Boost[0]]==iHemi[iJet_Boost[1]]) objects_on_separate_hemis = false;
        }
        // All objects satisfy separate hemisphere condition
        if (objects_on_separate_hemis) {
          M_min = M_temp;
          j1 = j_temp1;
          j2 = j_temp2;
        }
      }
    }
    if(j2.Pt() > j1.Pt()) {
      LorentzVector temp = j1;
      j1 = j2;
      j2 = temp;
    }
    mynewjets.push_back(j1);
    mynewjets.push_back(j2);
    return mynewjets;
  }
  
  // MR
  double CalcMR(LorentzVector ja, LorentzVector jb) {
    double A = ja.P();
    double B = jb.P();
    double az = ja.Pz();
    double bz = jb.Pz();
    Vector3 jaT, jbT;
    jaT.SetXYZ(ja.Px(),ja.Py(),0.0);
    jbT.SetXYZ(jb.Px(),jb.Py(),0.0);
    double ATBT = (jaT+jbT).Mag2();
    double temp = sqrt((A+B)*(A+B)-(az+bz)*(az+bz)-
      		 (jbT.Dot(jbT)-jaT.Dot(jaT))*(jbT.Dot(jbT)-jaT.Dot(jaT))/(jaT+jbT).Mag2());
    double mybeta = (jbT.Dot(jbT)-jaT.Dot(jaT))/sqrt(ATBT*((A+B)*(A+B)-(az+bz)*(az+bz)));
    double mygamma = 1./sqrt(1.-mybeta*mybeta);
    //gamma times MRstar
    temp *= mygamma;
    return temp;
  }
  
  // MTR
  double CalcMTR(LorentzVector ja, LorentzVector jb, Vector3 met) {
    double temp = std::sqrt(met.Mag2())*(ja.Pt()+jb.Pt()) - met.Dot(ja.Vect()+jb.Vect());
    temp /= 2.;
    temp = sqrt(temp);
    return temp;
  }

}


// MT
double CalcMT(LorentzVector lepton, LorentzVector pfmet) {
  return sqrt( 2 * lepton.Pt() * pfmet.Pt() * ( 1 - cos( pfmet.Phi() - lepton.Phi() ) ) );
}

// DeltaPhi
float DeltaPhi(float phi1, float phi2) {
  float dPhi = phi1 - phi2;
  while (dPhi  >  TMath::Pi()) dPhi -= 2*TMath::Pi();
  while (dPhi <= -TMath::Pi()) dPhi += 2*TMath::Pi();
  return fabs(dPhi);
}

// DeltaR
float DeltaR(float eta1, float eta2, float phi1, float phi2) {
  float dEta = eta1 - eta2;
  float dPhi = DeltaPhi(phi1, phi2);
  return TMath::Sqrt(dEta*dEta + dPhi*dPhi);
}
float DeltaR(LorentzVector v1, LorentzVector v2) {
  return DeltaR(v1.eta(), v2.eta(), v1.phi(), v2.phi()); 
}
  
float Perp(Vector3 v1, Vector3 v2) {
  Double_t per = v1.Mag2();
  Double_t tot = v2.Mag2();
  Double_t ss  = v1.Dot(v2);
  if (tot > 0.0) per -= ss*ss/tot;
  if (per < 0)   per = 0;
  return per;
}
