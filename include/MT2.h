/*

 MT2 methods taken from:
 https://github.com/cmstas/CORE/blob/master/Tools/hemJet.h
 https://github.com/cmstas/CORE/blob/master/Tools/hemJet.cc
 https://github.com/cmstas/CORE/blob/master/Tools/MT2/MT2Utility.h
 https://github.com/cmstas/CORE/blob/master/Tools/MT2/MT2Utility.cc
 https://github.com/cmstas/CORE/blob/master/Tools/MT2/MT2.h
 https://github.com/cmstas/CORE/blob/master/Tools/MT2/MT2.cc

*/

// hemJet
#include <vector>
#include "Math/LorentzVector.h"
#include "Math/Vector3D.h"

typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;

bool sortByMass(LorentzVector, LorentzVector);
float LundDist(LorentzVector&, LorentzVector&);
std::vector<LorentzVector> getHemJets(std::vector<LorentzVector>&);

typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;

using namespace std;


float LundDist(LorentzVector& v1, LorentzVector& v2){
  //v1 is the hemisphere axis
  float p2 = sqrt( v2.Px()*v2.Px() + v2.Py()*v2.Py() + v2.Pz()*v2.Pz() );
  return ( (v1.E() - (v1.Vect()).Dot(v2.Vect())/p2) * ( v1.E()/( (v1.E() + v2.E())*(v1.E() + v2.E()) ) ) );
}

std::vector<LorentzVector> getHemJets(std::vector<LorentzVector>& jets){

  if(jets.size() < 2) throw std::runtime_error("less than 2 jets used for hemisphere reconstruction");

  LorentzVector axis1;
  LorentzVector axis2;
  LorentzVector tempAxis1;
  LorentzVector tempAxis2;
  unsigned int axis1Index = 0;
  unsigned int axis2Index = 0;

  std::vector<int> hemAssoc (jets.size(), 0);

  //seed the axes with the pair of jets that form the highest invariant mass
  float maxMass = -1.0;
  for(unsigned int i=0; i<jets.size(); i++) {
    for(unsigned int j=0; j<jets.size(); j++) {

      if(i==j) continue;
      if( (jets.at(i) + jets.at(j)).M() > maxMass ){
        maxMass = (jets.at(i) + jets.at(j)).M();
        axis1Index = i;
        axis2Index = j;
      }

    }
  }

  //set initial axes 
  axis1 = jets.at(axis1Index);
  axis2 = jets.at(axis2Index);

//debug
//cout << "axis1Index = " << axis1Index << endl;
//cout << "axis2Index = " << axis2Index << endl;
  
  //store hemisphere associations for jets that serve as axis seeds
  hemAssoc.at(axis1Index) = 1;
  hemAssoc.at(axis2Index) = 2;

  int counter = 0;
  bool move = true;

  while (move && counter<100) { 

    move = false;
    ++counter;
    if (counter==200) cout << "hemisphere reconstruction not converging" << endl;

    tempAxis1 = LorentzVector(0,0,0,0);
    tempAxis2 = LorentzVector(0,0,0,0);

    //assign each jet to a hemisphere, max of one can be moved per iteration
    for(unsigned int jet=0; jet<jets.size(); jet++){
      if (jet==axis1Index) {
        tempAxis1 += jets.at(jet);
      }
      else if (jet==axis2Index) {
        tempAxis2 += jets.at(jet);
      }
      else {
        if(!move) {
          LorentzVector newAxis1 = hemAssoc.at(jet)==1 ? axis1 - jets.at(jet) : axis1;
          LorentzVector newAxis2 = hemAssoc.at(jet)==2 ? axis2 - jets.at(jet) : axis2;
          //cout << "newAxis1: " << newAxis1.E() << endl;
          //cout << "newAxis2: " << newAxis2.E() << endl;
          //cout << "lund dists: " << LundDist(newAxis1, jets.at(jet)) << ", " << LundDist(newAxis2, jets.at(jet)) << endl;//debug
          if (LundDist(newAxis1, jets.at(jet)) <= LundDist(newAxis2, jets.at(jet))) {
            if (hemAssoc.at(jet) != 1 && hemAssoc.at(jet) != 0) move = true;
            tempAxis1 += jets.at(jet);
            hemAssoc.at(jet) = 1;
          }
          else {
            if (hemAssoc.at(jet) != 2 && hemAssoc.at(jet) != 0) move = true;
            tempAxis2 += jets.at(jet);
            hemAssoc.at(jet) = 2;
          }
        }
        else {
          if (hemAssoc.at(jet)==1) tempAxis1 += jets.at(jet);
          else if (hemAssoc.at(jet)==2) tempAxis2 += jets.at(jet);
        }
      }
    }
    
    //new axes for each hemisphere composed of the momenta of the jets in that hemisphere
    axis1 = tempAxis1;
    axis2 = tempAxis2;

    if (counter <= 1) move = true;
  }

  std::vector<LorentzVector> result;

//don't make hemispheres to be massless at this step
/*
  float E1 = sqrt(axis1.Px()*axis1.Px() + axis1.Py()*axis1.Py() + axis1.Pz()*axis1.Pz()); //used to force hemisphere to be massless
  LorentzVector hem1 = LorentzVector(axis1.Px(), axis1.Py(), axis1.Pz(), E1);
  float E2 = sqrt(axis2.Px()*axis2.Px() + axis2.Py()*axis2.Py() + axis2.Pz()*axis2.Pz()); //used to force hemisphere to be massless
  LorentzVector hem2 = LorentzVector(axis2.Px(), axis2.Py(), axis2.Pz(), E2);
  result.push_back(hem1);
  result.push_back(hem2);
*/

  result.push_back(axis1);
  result.push_back(axis2);

/*
  //for debugging
  cout << endl;
  for(unsigned int i=0; i<hemAssoc.size(); i++){
    cout << i << ", " << hemAssoc.at(i) << endl;
  }
*/

  return(result);  

}





// MT2Utility
/*The user can change the desired precision below, the larger one of the following two definitions is used. Relative precision less than 0.00001 is not guaranteed to be achievable--use with caution*/ 

#define RELATIVE_PRECISION 0.00001 //defined as precision = RELATIVE_PRECISION * scale, where scale = max{Ea, Eb}
#define ABSOLUTE_PRECISION 0.0     //absolute precision for mt2, unused by default


//Reserved for expert
#define MIN_MASS  0.1   //if ma<MINMASS and mb<MINMASS, use massless code
#define ZERO_MASS 0.000 //give massless particles a small mass
#define SCANSTEP 0.1
namespace mt2_bisect
{
class mt2
{  
   public:

      mt2();
      void   mt2_bisect();
      void   mt2_massless();
      void   set_momenta(double *pa0, double *pb0, double* pmiss0);
      void   set_mn(double mn);
      double get_mt2();
      void   print();
      int    nevt;
   private:  

      bool   solved;
      bool   momenta_set;
      double mt2_b;

      int    nsols(double Dsq);
      int    nsols_massless(double Dsq);
      inline int    signchange_n( long double t1, long double t2, long double t3, long double t4, long double t5);
      inline int    signchange_p( long double t1, long double t2, long double t3, long double t4, long double t5);
      int scan_high(double &Deltasq_high);
      int find_high(double &Deltasq_high);
      //data members
      double pax, pay, ma, Ea;
      double pmissx, pmissy;
      double pbx, pby, mb, Eb;
      double mn, mn_unscale;
     
      //auxiliary definitions
      double masq, Easq;
      double mbsq, Ebsq;
      double pmissxsq, pmissysq;
      double mnsq;

      //auxiliary coefficients
      double a1, b1, c1, a2, b2, c2, d1, e1, f1, d2, e2, f2;
      double d11, e11, f12, f10, d21, d20, e21, e20, f22, f21, f20;

      double scale;
      double precision;
};

}//end namespace mt2_bisect

#include <iostream>
#include <math.h>

using namespace std;

namespace mt2_bisect
{
mt2::mt2()
{
   solved = false;
   momenta_set = false;
   mt2_b  = 0.;
   scale = 1.;
}

double mt2::get_mt2()
{
   if (!momenta_set)
   {
       cout <<" Please set momenta first!" << endl;
       return 0;
   }
        
   if (!solved) mt2_bisect();
   return mt2_b*scale;
}

void mt2::set_momenta(double* pa0, double* pb0, double* pmiss0)
{
   solved = false;     //reset solved tag when momenta are changed.
   momenta_set = true;

   ma = fabs(pa0[0]);  // mass cannot be negative

   if (ma < ZERO_MASS) ma = ZERO_MASS;

   pax  = pa0[1]; 
   pay  = pa0[2];
   masq = ma*ma;
   Easq = masq+pax*pax+pay*pay;
   Ea   = sqrt(Easq);
   
   mb = fabs(pb0[0]);

   if (mb < ZERO_MASS) mb = ZERO_MASS;

   pbx  = pb0[1]; 
   pby  = pb0[2];
   mbsq = mb*mb;
   Ebsq = mbsq+pbx*pbx+pby*pby;
   Eb   = sqrt(Ebsq);
     
   pmissx   = pmiss0[1]; pmissy = pmiss0[2];
   pmissxsq = pmissx*pmissx;
   pmissysq = pmissy*pmissy;

// set ma>= mb
   if(masq < mbsq)
   {
      double temp;
      temp = pax;  pax  = pbx;  pbx  = temp;
      temp = pay;  pay  = pby;  pby  = temp;
      temp = Ea;   Ea   = Eb;   Eb   = temp;
      temp = Easq; Easq = Ebsq; Ebsq = temp;
      temp = masq; masq = mbsq; mbsq = temp;
      temp = ma;   ma   = mb;   mb   = temp;   
   }
//normalize max{Ea, Eb} to 100
   if (Ea > Eb) scale = Ea/100.;
   else scale = Eb/100.;
   
   if (sqrt(pmissxsq+pmissysq)/100 > scale) scale = sqrt(pmissxsq+pmissysq)/100;
   //scale = 1;
   double scalesq = scale * scale;
   ma  = ma/scale;
   mb  = mb/scale;
   masq = masq/scalesq;
   mbsq = mbsq/scalesq;
   pax = pax/scale; pay = pay/scale;
   pbx = pbx/scale; pby = pby/scale;
   Ea  = Ea/scale;  Eb = Eb/scale;
   
   Easq = Easq/scalesq;
   Ebsq = Ebsq/scalesq;
   pmissx = pmissx/scale;
   pmissy = pmissy/scale;
   pmissxsq = pmissxsq/scalesq;
   pmissysq = pmissysq/scalesq;
   mn   = mn_unscale/scale; 
   mnsq = mn*mn;
  
   if (ABSOLUTE_PRECISION > 100.*RELATIVE_PRECISION) precision = ABSOLUTE_PRECISION;
   else precision = 100.*RELATIVE_PRECISION;
}

void mt2::set_mn(double mn0)
{
   solved = false;    //reset solved tag when mn is changed.
   mn_unscale   = fabs(mn0);  //mass cannot be negative
   mn = mn_unscale/scale;
   mnsq = mn*mn;
}

void mt2::print()
{
   cout << " pax = " << pax*scale << ";   pay = " << pay*scale << ";   ma = " << ma*scale <<";"<< endl;
   cout << " pbx = " << pbx*scale << ";   pby = " << pby*scale << ";   mb = " << mb*scale <<";"<< endl;
   cout << " pmissx = " << pmissx*scale << ";   pmissy = " << pmissy*scale <<";"<< endl;
   cout << " mn = " << mn_unscale<<";" << endl;
}

//special case, the visible particle is massless
void mt2::mt2_massless()
{
   
//rotate so that pay = 0 
   double theta,s,c;
   theta = atan(pay/pax);
   s = sin(theta);
   c = cos(theta);

   double pxtemp,pytemp;
   Easq   = pax*pax+pay*pay;
   Ebsq   = pbx*pbx+pby*pby;
   Ea     = sqrt(Easq);
   Eb     = sqrt(Ebsq);
  
   pxtemp = pax*c+pay*s;
   pax    = pxtemp;
   pay    = 0;
   pxtemp = pbx*c+pby*s;
   pytemp = -s*pbx+c*pby;
   pbx    = pxtemp;
   pby    = pytemp;
   pxtemp = pmissx*c+pmissy*s;
   pytemp = -s*pmissx+c*pmissy;
   pmissx = pxtemp;
   pmissy = pytemp;

   a2  = 1-pbx*pbx/(Ebsq);
   b2  = -pbx*pby/(Ebsq);
   c2  = 1-pby*pby/(Ebsq);

   d21 = (Easq*pbx)/Ebsq;
   d20 = - pmissx +  (pbx*(pbx*pmissx + pby*pmissy))/Ebsq;
   e21 = (Easq*pby)/Ebsq;
   e20 = - pmissy +  (pby*(pbx*pmissx + pby*pmissy))/Ebsq;
   f22 = -(Easq*Easq/Ebsq);
   f21 = -2*Easq*(pbx*pmissx + pby*pmissy)/Ebsq;
   f20 = mnsq + pmissxsq + pmissysq - (pbx*pmissx + pby*pmissy)*(pbx*pmissx + pby*pmissy)/Ebsq;

   double Deltasq0    = 0; 
   double Deltasq_low, Deltasq_high;
   int    nsols_high, nsols_low;

   Deltasq_low = Deltasq0 + precision;
   nsols_low = nsols_massless(Deltasq_low);
   
   if(nsols_low > 1) 
   { 
      mt2_b = (double) sqrt(Deltasq0+mnsq);
      return;
   }

/*   
   if( nsols_massless(Deltasq_high) > 0 )
   {
      mt2_b = (double) sqrt(mnsq+Deltasq0);
      return;
   }*/

//look for when both parablos contain origin  
   double Deltasq_high1, Deltasq_high2;
   Deltasq_high1 = 2*Eb*sqrt(pmissx*pmissx+pmissy*pmissy+mnsq)-2*pbx*pmissx-2*pby*pmissy;
   Deltasq_high2 = 2*Ea*mn;
 
   if(Deltasq_high1 < Deltasq_high2) Deltasq_high = Deltasq_high2;
     else Deltasq_high = Deltasq_high1;

   nsols_high=nsols_massless(Deltasq_high);
  
   int foundhigh;
   if (nsols_high == nsols_low)
   {
      
      
      foundhigh=0;
      
      double minmass, maxmass;
      minmass  = mn ;
      maxmass  = sqrt(mnsq + Deltasq_high);
      for(double mass = minmass + SCANSTEP; mass < maxmass; mass += SCANSTEP)
      {
	 Deltasq_high = mass*mass - mnsq;
      
         nsols_high = nsols_massless(Deltasq_high);
         if(nsols_high>0)
         {
            foundhigh=1;
            Deltasq_low = (mass-SCANSTEP)*(mass-SCANSTEP) - mnsq;
            break;
         }
      }
      if(foundhigh==0) 
      {
       
	//cout<<"Deltasq_high not found at event " << nevt <<endl;
        
       
         mt2_b = (double)sqrt(Deltasq_low+mnsq);
         return;
      }
   }

   if(nsols_high == nsols_low)
   { 
     //cout << "error: nsols_low=nsols_high=" << nsols_high << endl;
     //cout << "Deltasq_high=" << Deltasq_high << endl;
    
      mt2_b = sqrt(mnsq + Deltasq_low);
      return;
   }
   double minmass, maxmass;
   minmass = sqrt(Deltasq_low+mnsq);
   maxmass = sqrt(Deltasq_high+mnsq);
   while(maxmass - minmass > precision)
   {
      double Delta_mid, midmass, nsols_mid;
      midmass   = (minmass+maxmass)/2.;
      Delta_mid = midmass * midmass - mnsq;
      nsols_mid = nsols_massless(Delta_mid);
      if(nsols_mid != nsols_low) maxmass = midmass;
      if(nsols_mid == nsols_low) minmass = midmass;
   }
   mt2_b = minmass;
   return;
}

int mt2::nsols_massless(double Dsq)
{
  double delta;
  delta = Dsq/(2*Easq);
  d1    = d11*delta;
  e1    = e11*delta;
  f1    = f12*delta*delta+f10;
  d2    = d21*delta+d20;
  e2    = e21*delta+e20;
  f2    = f22*delta*delta+f21*delta+f20;
  
  double a,b;
  if (pax > 0) a = Ea/Dsq;
  else         a = -Ea/Dsq;
  if (pax > 0) b = -Dsq/(4*Ea)+mnsq*Ea/Dsq;
  else         b = Dsq/(4*Ea)-mnsq*Ea/Dsq;
  
  double A4,A3,A2,A1,A0;

  A4 = a*a*a2;
  A3 = 2*a*b2/Ea;
  A2 = (2*a*a2*b+c2+2*a*d2)/(Easq);
  A1 = (2*b*b2+2*e2)/(Easq*Ea);
  A0 = (a2*b*b+2*b*d2+f2)/(Easq*Easq);
  
  long  double A3sq;
  A3sq = A3*A3;

  long double B3, B2, B1, B0;
  B3 = 4*A4;
  B2 = 3*A3;
  B1 = 2*A2;
  B0 = A1;
  long double C2, C1, C0;
  C2 = -(A2/2 - 3*A3sq/(16*A4));
  C1 = -(3*A1/4. -A2*A3/(8*A4));
  C0 = -A0 + A1*A3/(16*A4);
  long double  D1, D0;
  D1 = -B1 - (B3*C1*C1/C2 - B3*C0 -B2*C1)/C2;
  D0 = -B0 - B3 *C0 *C1/(C2*C2)+ B2*C0/C2;
 
  long double E0;
  E0 = -C0 - C2*D0*D0/(D1*D1) + C1*D0/D1;
 
  long  double t1,t2,t3,t4,t5;
   
//find the coefficients for the leading term in the Sturm sequence  
   t1 = A4;
   t2 = A4;
   t3 = C2;
   t4 = D1;
   t5 = E0;
  
   int nsol;
   nsol = signchange_n(t1,t2,t3,t4,t5)-signchange_p(t1,t2,t3,t4,t5);
   if( nsol < 0 ) nsol=0;

   return nsol;
  
}

void mt2::mt2_bisect()
{
  
   
   solved = true;
   cout.precision(11);

//if masses are very small, use code for massless case.  
   if(masq < MIN_MASS && mbsq < MIN_MASS) 
   { 
      mt2_massless();
      return;
   }
 

   double Deltasq0;     
   Deltasq0 = ma*(ma + 2*mn); //The minimum mass square to have two ellipses 
 
// find the coefficients for the two quadratic equations when Deltasq=Deltasq0.
  
   a1 = 1-pax*pax/(Easq);
   b1 = -pax*pay/(Easq);
   c1 = 1-pay*pay/(Easq);
   d1 = -pax*(Deltasq0-masq)/(2*Easq);
   e1 = -pay*(Deltasq0-masq)/(2*Easq);
   a2 = 1-pbx*pbx/(Ebsq);
   b2 = -pbx*pby/(Ebsq);
   c2 = 1-pby*pby/(Ebsq);
   d2 = -pmissx+pbx*(Deltasq0-mbsq)/(2*Ebsq)+pbx*(pbx*pmissx+pby*pmissy)/(Ebsq);
   e2 = -pmissy+pby*(Deltasq0-mbsq)/(2*Ebsq)+pby*(pbx*pmissx+pby*pmissy)/(Ebsq);
   f2 = pmissx*pmissx+pmissy*pmissy-((Deltasq0-mbsq)/(2*Eb)+
        (pbx*pmissx+pby*pmissy)/Eb)*((Deltasq0-mbsq)/(2*Eb)+
        (pbx*pmissx+pby*pmissy)/Eb)+mnsq;
   
// find the center of the smaller ellipse 
   double x0,y0;
   x0 = (c1*d1-b1*e1)/(b1*b1-a1*c1);
   y0 = (a1*e1-b1*d1)/(b1*b1-a1*c1);

   
// Does the larger ellipse contain the smaller one? 
   double dis=a2*x0*x0+2*b2*x0*y0+c2*y0*y0+2*d2*x0+2*e2*y0+f2;

   if(dis<=0.01)
   { 
      mt2_b  = (double) sqrt(mnsq+Deltasq0);
      return;
   }
   

/* find the coefficients for the two quadratic equations           */
/* coefficients for quadratic terms do not change                  */
/* coefficients for linear and constant terms are polynomials of   */
/*       delta=(Deltasq-m7sq)/(2 E7sq)                             */  
   d11 = -pax;
   e11 = -pay;
   f10 = mnsq;
   f12 = -Easq;
   d21 = (Easq*pbx)/Ebsq;
   d20 = ((masq - mbsq)*pbx)/(2.*Ebsq) - pmissx +
         (pbx*(pbx*pmissx + pby*pmissy))/Ebsq;
   e21 = (Easq*pby)/Ebsq;
   e20 = ((masq - mbsq)*pby)/(2.*Ebsq) - pmissy +
         (pby*(pbx*pmissx + pby*pmissy))/Ebsq;
   f22 = -Easq*Easq/Ebsq;
   f21 = (-2*Easq*((masq - mbsq)/(2.*Eb) + (pbx*pmissx + pby*pmissy)/Eb))/Eb;
   f20 = mnsq + pmissx*pmissx + pmissy*pmissy - 
         ((masq - mbsq)/(2.*Eb) + (pbx*pmissx + pby*pmissy)/Eb)
         *((masq - mbsq)/(2.*Eb) + (pbx*pmissx + pby*pmissy)/Eb);

//Estimate upper bound of mT2
//when Deltasq > Deltasq_high1, the larger encloses the center of the smaller 
   double p2x0,p2y0;
   double Deltasq_high1;
   p2x0 = pmissx-x0;
   p2y0 = pmissy-y0;
   Deltasq_high1 = 2*Eb*sqrt(p2x0*p2x0+p2y0*p2y0+mnsq)-2*pbx*p2x0-2*pby*p2y0+mbsq;
   
//Another estimate, if both ellipses enclose the origin, Deltasq > mT2

   double Deltasq_high2, Deltasq_high21, Deltasq_high22;
   Deltasq_high21 = 2*Eb*sqrt(pmissx*pmissx+pmissy*pmissy+mnsq)-2*pbx*pmissx-2*pby*pmissy+mbsq;
   Deltasq_high22 = 2*Ea*mn+masq;
  
   if ( Deltasq_high21 < Deltasq_high22 ) Deltasq_high2 = Deltasq_high22;
   else Deltasq_high2 = Deltasq_high21;

//pick the smaller upper bound   
   double Deltasq_high;
   if(Deltasq_high1 < Deltasq_high2) Deltasq_high = Deltasq_high1;
   else Deltasq_high = Deltasq_high2;
   
  
   double Deltasq_low; //lower bound
   Deltasq_low = Deltasq0;

//number of solutions at Deltasq_low should not be larger than zero
   if( nsols(Deltasq_low) > 0 )
   {
     //cout << "nsolutions(Deltasq_low) > 0"<<endl;
     mt2_b = (double) sqrt(mnsq+Deltasq0);
     return;
   }
  
   int nsols_high, nsols_low;

   nsols_low  = nsols(Deltasq_low);
   int foundhigh;
  

//if nsols_high=nsols_low, we missed the region where the two ellipse overlap 
//if nsols_high=4, also need a scan because we may find the wrong tangent point.

   nsols_high = nsols(Deltasq_high);
  
   if(nsols_high == nsols_low || nsols_high == 4)
   {
      //foundhigh = scan_high(Deltasq_high);
      foundhigh = find_high(Deltasq_high);
      if(foundhigh == 0) 
      {
	//cout << "Deltasq_high not found at event " << nevt << endl;
         mt2_b = sqrt( Deltasq_low + mnsq );
         return;
      }
      
   }

   while(sqrt(Deltasq_high+mnsq) - sqrt(Deltasq_low+mnsq) > precision)
   {
      double Deltasq_mid,nsols_mid;
      //bisect
      Deltasq_mid = (Deltasq_high+Deltasq_low)/2.;
      nsols_mid = nsols(Deltasq_mid);
      // if nsols_mid = 4, rescan for Deltasq_high
      if ( nsols_mid == 4 ) 
      {
         Deltasq_high = Deltasq_mid;
         //scan_high(Deltasq_high);
         find_high(Deltasq_high);
         continue;
      } 
         
      
      if(nsols_mid != nsols_low) Deltasq_high = Deltasq_mid;
      if(nsols_mid == nsols_low) Deltasq_low  = Deltasq_mid;
   }
   mt2_b = (double) sqrt( mnsq + Deltasq_high);
   return;
}

int mt2::find_high(double & Deltasq_high)
{
   double x0,y0;
   x0 = (c1*d1-b1*e1)/(b1*b1-a1*c1);
   y0 = (a1*e1-b1*d1)/(b1*b1-a1*c1);
   double Deltasq_low = (mn + ma)*(mn + ma) - mnsq;
   do 
   {
      double Deltasq_mid = (Deltasq_high + Deltasq_low)/2.;
      int nsols_mid = nsols(Deltasq_mid);
      if ( nsols_mid == 2 )
      {
         Deltasq_high = Deltasq_mid;
         return 1;
      }
      else if (nsols_mid == 4)
      {
         Deltasq_high = Deltasq_mid;
         continue;
      }
      else if (nsols_mid ==0)
      {
         d1 = -pax*(Deltasq_mid-masq)/(2*Easq);
         e1 = -pay*(Deltasq_mid-masq)/(2*Easq);
         d2 = -pmissx + pbx*(Deltasq_mid - mbsq)/(2*Ebsq)
              + pbx*(pbx*pmissx+pby*pmissy)/(Ebsq);
         e2 = -pmissy + pby*(Deltasq_mid - mbsq)/(2*Ebsq)
              + pby*(pbx*pmissx+pby*pmissy)/(Ebsq);
         f2 = pmissx*pmissx+pmissy*pmissy-((Deltasq_mid-mbsq)/(2*Eb)+
              (pbx*pmissx+pby*pmissy)/Eb)*((Deltasq_mid-mbsq)/(2*Eb)+
              (pbx*pmissx+pby*pmissy)/Eb)+mnsq;
// Does the larger ellipse contain the smaller one? 
         double dis = a2*x0*x0 + 2*b2*x0*y0 + c2*y0*y0 + 2*d2*x0 + 2*e2*y0 + f2;
         if (dis < 0) Deltasq_high = Deltasq_mid;
           else Deltasq_low = Deltasq_mid;
      }
      
   } while ( Deltasq_high - Deltasq_low > 0.001);
   return 0;
}  
int mt2::scan_high(double & Deltasq_high)
{
   int foundhigh = 0 ;
   int nsols_high;

   
   double tempmass, maxmass;
   tempmass = mn + ma;
   maxmass  = sqrt(mnsq + Deltasq_high);
   //if (nevt == 32334) cout << "Deltasq_high = " << Deltasq_high << endl;
   for(double mass = tempmass + SCANSTEP; mass < maxmass; mass += SCANSTEP)
   {
      Deltasq_high = mass*mass - mnsq;
      nsols_high   = nsols(Deltasq_high);
      
      if( nsols_high > 0)
      {
         foundhigh   = 1;
         break;
      }
    }
    return foundhigh;
}
int mt2::nsols(  double Dsq)
{
   double delta = (Dsq-masq)/(2*Easq);
  
//calculate coefficients for the two quadratic equations
   d1 = d11*delta;
   e1 = e11*delta;
   f1 = f12*delta*delta+f10;
   d2 = d21*delta+d20;
   e2 = e21*delta+e20;
   f2 = f22*delta*delta+f21*delta+f20;

//obtain the coefficients for the 4th order equation 
//devided by Ea^n to make the variable dimensionless
   long double A4, A3, A2, A1, A0;

   A4 = 
   -4*a2*b1*b2*c1 + 4*a1*b2*b2*c1 +a2*a2*c1*c1 + 
   4*a2*b1*b1*c2 - 4*a1*b1*b2*c2 - 2*a1*a2*c1*c2 + 
   a1*a1*c2*c2;  

   A3 =
     (-4*a2*b2*c1*d1 + 8*a2*b1*c2*d1 - 4*a1*b2*c2*d1 - 4*a2*b1*c1*d2 + 
   8*a1*b2*c1*d2 - 4*a1*b1*c2*d2 - 8*a2*b1*b2*e1 + 8*a1*b2*b2*e1 + 
   4*a2*a2*c1*e1 - 4*a1*a2*c2*e1 + 8*a2*b1*b1*e2 - 8*a1*b1*b2*e2 - 
     4*a1*a2*c1*e2 + 4*a1*a1*c2*e2)/Ea;

   
   A2 =
     (4*a2*c2*d1*d1 - 4*a2*c1*d1*d2 - 4*a1*c2*d1*d2 + 4*a1*c1*d2*d2 - 
   8*a2*b2*d1*e1 - 8*a2*b1*d2*e1 + 16*a1*b2*d2*e1 + 
   4*a2*a2*e1*e1 + 16*a2*b1*d1*e2 - 8*a1*b2*d1*e2 - 
   8*a1*b1*d2*e2 - 8*a1*a2*e1*e2 + 4*a1*a1*e2*e2 - 4*a2*b1*b2*f1 + 
   4*a1*b2*b2*f1 + 2*a2*a2*c1*f1 - 2*a1*a2*c2*f1 + 
     4*a2*b1*b1*f2 - 4*a1*b1*b2*f2 - 2*a1*a2*c1*f2 + 2*a1*a1*c2*f2)/Easq;
  
   A1 =
     (-8*a2*d1*d2*e1 + 8*a1*d2*d2*e1 + 8*a2*d1*d1*e2 - 8*a1*d1*d2*e2 - 
   4*a2*b2*d1*f1 - 4*a2*b1*d2*f1 + 8*a1*b2*d2*f1 + 4*a2*a2*e1*f1 - 
   4*a1*a2*e2*f1 + 8*a2*b1*d1*f2 - 4*a1*b2*d1*f2 - 4*a1*b1*d2*f2 - 
     4*a1*a2*e1*f2 + 4*a1*a1*e2*f2)/(Easq*Ea);
  
   A0 =
     (-4*a2*d1*d2*f1 + 4*a1*d2*d2*f1 + a2*a2*f1*f1 + 
   4*a2*d1*d1*f2 - 4*a1*d1*d2*f2 - 2*a1*a2*f1*f2 + 
     a1*a1*f2*f2)/(Easq*Easq);
   
   long  double A3sq;
   A3sq = A3*A3;
   
   long double B3, B2, B1, B0;
   B3 = 4*A4;
   B2 = 3*A3;
   B1 = 2*A2;
   B0 = A1;
   
   long double C2, C1, C0;
   C2 = -(A2/2 - 3*A3sq/(16*A4));
   C1 = -(3*A1/4. -A2*A3/(8*A4));
   C0 = -A0 + A1*A3/(16*A4);
   
   long double D1, D0;
   D1 = -B1 - (B3*C1*C1/C2 - B3*C0 -B2*C1)/C2;
   D0 = -B0 - B3 *C0 *C1/(C2*C2)+ B2*C0/C2;
   
   long double E0;
   E0 = -C0 - C2*D0*D0/(D1*D1) + C1*D0/D1;
   
   long  double t1,t2,t3,t4,t5;
//find the coefficients for the leading term in the Sturm sequence  
   t1 = A4;
   t2 = A4;
   t3 = C2;
   t4 = D1;
   t5 = E0;
 

//The number of solutions depends on diffence of number of sign changes for x->Inf and x->-Inf
   int nsol;
   nsol = signchange_n(t1,t2,t3,t4,t5) - signchange_p(t1,t2,t3,t4,t5);

//Cannot have negative number of solutions, must be roundoff effect
   if (nsol < 0) nsol = 0;

   return nsol;
  
}  

inline int mt2::signchange_n( long double t1, long double t2, long double t3, long double t4, long double t5)
{
   int nsc;
   nsc=0;
   if(t1*t2>0) nsc++;
   if(t2*t3>0) nsc++;
   if(t3*t4>0) nsc++;
   if(t4*t5>0) nsc++;
   return nsc;
}
inline int mt2::signchange_p( long double t1, long double t2, long double t3, long double t4, long double t5)
{
   int nsc;
   nsc=0;
   if(t1*t2<0) nsc++;
   if(t2*t3<0) nsc++;
   if(t3*t4<0) nsc++;
   if(t4*t5<0) nsc++;
   return nsc;
}

}//end namespace mt2_bisect



// MT2
#include "Math/LorentzVector.h"
#include "TMath.h"
#include <vector>

typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;

enum enum_mt2_method { BISECT, GRID };

///////////////////////////////////////////////////////////////
// MT2 Calculated with the Bisection method from Cheng & Han //
///////////////////////////////////////////////////////////////

double HemMT2(
  const float,
  const float,
  const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> >,
  const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> >,
  float = 0.0
);

// MT2 declaration
double MT2(
  const float,
  const float,
  const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> >,
  const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> >,
  float = 0.0,
  bool = false
);

// MT2J declaration
double MT2J(
  const float,
  const float,
  const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> >,
  const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> >,
  const std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > >,
  float = 0.0,
  enum_mt2_method = BISECT,
  bool = false
);

///////////////////////////////////////////////
// MT2 Calculated Using a Simple Grid Method //
///////////////////////////////////////////////

class TMt2 {

  private:
    
    int           grid_size_;
    int           grid_spacing_;
    float         mt2_;
    LorentzVector p4_nu1_;
    LorentzVector p4_nu2_;

  public:

    TMt2    (void);
    ~TMt2   (void);

    float GetMt2  ( const float , const float , const LorentzVector , const LorentzVector ,                               const float = 0.0, bool = false );
    //float GetMt2j ( const float , const float , const LorentzVector , const LorentzVector , const vector<LorentzVector> , const float = 0.0, bool = false );

    inline float         Mt2   (void) { return mt2_;    }
    inline LorentzVector Nu1p4 (void) { return p4_nu1_; }
    inline LorentzVector Nu2p4 (void) { return p4_nu2_; }

};

#include "math.h"
#include "Math/VectorUtil.h"
#include "iostream"

using namespace std;

// Constructor & Destructor
TMt2::TMt2  (void) { 
  grid_size_    = 500;
  grid_spacing_ = 2;
  mt2_          = -999.0;
};
TMt2::~TMt2 (void) { };

///////////////////////////////////////////////////////////////
// MT2 Calculated with the Bisection method from Cheng & Han //
///////////////////////////////////////////////////////////////

// HemMT2( MET_MAGNITUDE, MET_PHI, P4_HEM_1, P4_HEM_2, MASS_INVISIBLE_PARTICLE )
double HemMT2(
  const float met,
  const float metPhi,
  const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > v1,
  const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > v2,
  float invisible_particle_mass
){

//--- code here follows documentation in MT2Utility.cc ---//

  // initialize arrays for lepton 1, lepton 2, MET
  double pa[3]    = {0,0,0};
  double pb[3]    = {0,0,0};
  double pmiss[3] = {0,0,0};

  // Set the masses
    pa[0] = 0.0;
    pb[0] = 0.0;

  // set the transverse momenta for the leptons & MET
  pa[1]     = (double) v1.Px();
  pa[2]     = (double) v1.Py();
  pb[1]     = (double) v2.Px();
  pb[2]     = (double) v2.Py();
  pmiss[0]  = 0.0;                      // not used
  pmiss[1]  = (double) met*cos(metPhi);
  pmiss[2]  = (double) met*sin(metPhi);

  // instantiate mt2 class, set momenta and mass of invisible particle
  mt2_bisect::mt2 mt2_event;
  mt2_event.set_momenta( pa, pb, pmiss );
  mt2_event.set_mn( invisible_particle_mass );

  //
  return mt2_event.get_mt2();
}

// MT2( MET_MAGNITUDE, MET_PHI, P4_LEPTON_1, P4_LEPTON_2, MASS_INVISIBLE_PARTICLE )
double MT2(
  const float met,
  const float metPhi,
  const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > v1,
  const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > v2,
  float invisible_particle_mass,
  bool verbose
){

//--- code here follows documentation in MT2Utility.cc ---//

  // initialize arrays for lepton 1, lepton 2, MET
  double pa[3]    = {0,0,0};
  double pb[3]    = {0,0,0};
  double pmiss[3] = {0,0,0};

  // Set the masses
  if( v1.M2() >= 0 ){
    pa[0] = v1.M();
  } else {
    pa[0] = 0.0;
    if(verbose) cout << "ERROR: v1.M2 < 0 ... Setting v1.M() = 0" << endl;
  }
  if( v2.M2() >= 0 ){
    pb[0] = v2.M();
  } else {
    pb[0] = 0.0;
    if(verbose) cout << "ERROR: v2.M2 < 0 ... Setting v2.M() = 0" << endl;
  }

  // set the transverse momenta for the leptons & MET
  pa[1]     = (double) v1.Px();
  pa[2]     = (double) v1.Py();
  pb[1]     = (double) v2.Px();
  pb[2]     = (double) v2.Py();
  pmiss[0]  = 0.0;                      // not used
  pmiss[1]  = (double) met*cos(metPhi);
  pmiss[2]  = (double) met*sin(metPhi);

  // instantiate mt2 class, set momenta and mass of invisible particle
  mt2_bisect::mt2 mt2_event;
  mt2_event.set_momenta( pa, pb, pmiss );
  mt2_event.set_mn( invisible_particle_mass );

  //
  return mt2_event.get_mt2();
}

// MT2J( MET_MAGNITUDE, MET_PHI, P4_LEPTON_1, P4_LEPTON_2, VECT_P4_Jets, MASS_INVISIBLE_PARTICLE, MT2_CALCULATION_METHOD )
double MT2J(
  const float met,
  const float metPhi,
  const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > p4_lepton_1,
  const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > p4_lepton_2,
  const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > vect_p4_jets,
  float invisible_particle_mass,
  enum enum_mt2_method method_mt2,
  bool
){
  if( vect_p4_jets.size() < 2 ){
    cout << "MT2.cc: error MT2J called with less than 2 jets... returning mt2 value of -1.0" << endl;
    return -1.0; 
  }
  double mt2_min = std::numeric_limits<double>::max();
  for(unsigned int j1=0; j1 < vect_p4_jets.size(); j1++){
  for(unsigned int j2=0; j2 < vect_p4_jets.size(); j2++){
    if(j1==j2) continue;
    double mt2_j1_j2;
    if( method_mt2 == BISECT){
      mt2_j1_j2 = MT2( met, metPhi, p4_lepton_1 + vect_p4_jets.at(j1), p4_lepton_2 + vect_p4_jets.at(j2), invisible_particle_mass );
    } else {
      cout << "ERROR: Undefined calculation method... returning -1" << endl;
      return -1.0;
    }
    if(mt2_j1_j2 < mt2_min){
      mt2_min = mt2_j1_j2;
    }
  }}
  return mt2_min;
}

//////////
// GRID //
//////////

//float TMt2::GetMt2j (
//  const float                 met,
//  const float                 metPhi,
//  const LorentzVector         p4_lep1,
//  const LorentzVector         p4_lep2,
//  const vector<LorentzVector> v_p4_jets,
//  const float                 invisible_particle_mass,
//  const bool                  verbose
//){
//  mt2_ = -999.0;
//  return mt2_;
//}

float TMt2::GetMt2 (
  const float         met,
  const float         metPhi,
  const LorentzVector p4_lep1,
  const LorentzVector p4_lep2,
  const float         invisible_particle_mass,
  const bool          verbose
){

  //
  mt2_ = -999.0;

  // Check Input
  if( invisible_particle_mass != 0 ){
    cout << "ERROR: Non zero invisible particle masses are not implemented... Exiting." << endl;
    exit(1);
  }
  if( grid_spacing_ > grid_size_ ){
    cout << endl;
    cout << "ERROR: Grid size must be larger than grid spacing... Exiting." << endl;
    cout << endl;
    exit(1);
  }

  // Particle masses... M^2 < 0 sometimes due to floating poing imprecision, leptons are in the massless limit anyway, set M = 0 when M^2 < 0
  double mass1;
  double mass2;
  if( p4_lep1.M2() >= 0 ){
    mass1 = p4_lep1.M();
  }
  else {
    mass1 = 0.0;
    if(verbose) cout << "p4_lep1.M() < 0... Setting p4_lep1.M() = 0" << endl;
  }
  if( p4_lep2.M2() >= 0 ){
    mass2 = p4_lep2.M();
  }
  else{
    mass2 = 0.0;
    if(verbose) cout << "p4_lep2.M() < 0... Setting p4_lep2.M() = 0" << endl;
  }

  // Set transverse quantities 
  double Et1    = p4_lep1.Et();
  double Et2    = p4_lep2.Et();
  double px1    = p4_lep1.Px();
  double py1    = p4_lep1.Py();
  double px2    = p4_lep2.Px();
  double py2    = p4_lep2.Py();
  double metx   = met*cos(metPhi);
  double mety   = met*sin(metPhi);

  // Initialize grid variables
  double EtNu1 = 0;
  double EtNu2 = 0;
  double mtsq1 = 0;
  double mtsq2 = 0;
  double nu1Px = 0;
  double nu1Py = 0;
  double nu2Px = 0;
  double nu2Py = 0;
  double Max   = 0;
  double Min   = std::numeric_limits<double>::max();

  // Grid Minimization
  for(int x = ( -1*grid_size_ ); x <= grid_size_; x += grid_spacing_ ){
  for(int y = ( -1*grid_size_ ); y <= grid_size_; y += grid_spacing_ ){
      double trial1_Px = x;
      double trial1_Py = y;
      double trial2_Px = ( metx - x );
      double trial2_Py = ( mety - y );
      EtNu1            = sqrt( pow( trial1_Px, 2 ) + pow( trial1_Py, 2 ) );
      EtNu2            = sqrt( pow( trial2_Px, 2 ) + pow( trial2_Py, 2 ) );
      mtsq1            = pow( mass1, 2 ) + 2 * ( Et1 * EtNu1 - px1 * trial1_Px - py1 * trial1_Py );
      mtsq2            = pow( mass2, 2 ) + 2 * ( Et2 * EtNu2 - px2 * trial2_Px - py2 * trial2_Py );
      Max              = max( sqrt( mtsq1 ), sqrt( mtsq2 ) );
      if ( Max < Min ){
        Min = Max;
        nu1Px = trial1_Px;
        nu1Py = trial1_Py;
        nu2Px = trial2_Px;
        nu2Py = trial2_Py;
      }
  } }
  if( Min == std::numeric_limits<double>::max() ){
    cout << "MT2_GRID: Error could not find minimum." << endl;
    exit(1);
  }

  // Get the ( transverse ) 4-vectors of the neutrinos chosen by MT2
  p4_nu1_.SetPxPyPzE( nu1Px, nu1Py, 0.0, sqrt( pow( nu1Px, 2) + pow( nu1Py, 2) ) );
  p4_nu2_.SetPxPyPzE( nu2Px, nu2Py, 0.0, sqrt( pow( nu2Px, 2) + pow( nu2Py, 2) ) );

  //
  mt2_ = Min;
  return mt2_;

}
