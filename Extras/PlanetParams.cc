#include<stdio.h>
#include<cmath>

void CalcMass(double *Mb,double *i,double *P,double *Ms,double *K,double *e);
void CalcRadius(double *Rp,double *RpRs,double *Rs);
void CalcDensity(double *pb,double *Mp,double *Rp);
void CalcTemp1(double *Teff,double *Teq,double *aRs);
void CalcSemiMajorAxis(double *a,double *aRs,double *Rs);
void CalcSafronovNum(double *SN,double *Mb,double *a,double *Ms,double *Rb);
void CalcSurfaceGrav(double *sg,double *P,double *a,double *Rp,double *i,double *e,double *K);
void CalcStellarDensity(double *ps,double *P,double *aRs,double *pb,double *RpRs);
void CalcSDensity(double *p,double *m,double *r);

int main()
{
    /************************************************************
                  Enter Initial Parameters Below
    ************************************************************/
    // Parameters for HAT-P-16b    { value, error }
    double P[] = { 2.77596, 0.000003 };   // Period [day]
    double i[] = { 86.6, 0.7 };           // inclination [deg]
    double e[] = { 0.036, 0.004 };        // eccentricity
    double aRs[] = { 7.17, 0.28 };        // a/R* 
    double RpRs[] = { 0.1071, 0.0014 };   // Rp/R*
    double K[] = { 531.1, 2.8 };          // Velocity Semi-amplitude [m/s]    

    // Parameters of HAT-P-16
    double Ms[] = { 1.218, 0.039 }; // Mass of Star [solar mass]
    double Rs[] = { 1.237, 0.054 }; // Radius of Star [solar radii]
    double Teff[] = { 6158, 80 };   // Effective Temp [Kelvin]



      /**********************************************************
Other Programming Stuff Below, Try not to alter unless you know what's up
      ***********************************************************/
    // Planet: Mass, Radius, Density, Temp-equil, Semi-Major Axis, Safronov Num, Surface Grav    
    double Mb[2], Rp[2], pb[2], Teq[2], a[2], SN[2];
    double sg[2];
    // Star: Density
    double ps[2], p[2]; //density of star, calculated two different ways
   
    i[0] *= 2.*M_PI/360.; i[1] *= 2.*M_PI/360.; // convert to radians
    
    CalcSemiMajorAxis(a,aRs,Rs);
    CalcRadius(Rp, RpRs, Rs);
    CalcSurfaceGrav(sg,P,a,Rp,i,e,K);
    CalcStellarDensity(ps,P,aRs,pb,RpRs);

    P[0] /= 365.24; P[1] /= 365.24; // convert to years

    CalcMass(Mb, i, P, Ms, K, e);
    CalcDensity(pb,Mb,Rp);
    CalcTemp1(Teff, Teq, aRs);
    CalcSafronovNum(SN,Mb,a,Ms,Rp);
    
    FILE *fp;
    fp = fopen("latex_output.tex","w+");

    printf("Your Planet's \n");
    printf(" Mass = %f +- %f M_jup \n",Mb[0],Mb[1]);
    printf("        %f +- %f M_earth \n",(Mb[0]*317.94),(Mb[1]*317.94));
    printf(" Radii = %f +- %f R_jup \n", Rp[0], Rp[1] );
    printf("         %f +- %f R_earth \n", (Rp[0]*10.863), (Rp[1]*10.863));
    printf(" Density = %f +- %f g/cm^3 \n", pb[0], pb[1]);
    printf(" Temperature = %f +- %f Kelvin \n", Teq[0], Teq[1]);
    printf(" semi major axis = %f +- %f AU \n", a[0],a[1]);
    printf(" Safronov number = %f +- %f \n", SN[0], SN[1]);
    printf(" Surface Grav: = %f +- %f (cm/s^2) \n", sg[0] , sg[1]);
    
    fprintf(fp,"Mass of Planet ($M_{Jup}$)       &$M_{p}$    &%0.8f\\pm%0.8f\\\\ \n",Mb[0],Mb[1]);
    fprintf(fp,"Mass of Planet (&$R_{Earth}$)    &$M_{p}$    &%0.8f\\pm%0.8f\\\\ \n",(Mb[0]*317.94),(Mb[1]*317.94));
    fprintf(fp,"Radius of Planet ($R_{Jup}$)     &$R_{p}$    &%0.8f\\pm%0.8f\\\\ \n",Rp[0], Rp[1]);
    fprintf(fp,"Radius of Planet ($R_{Earth}$)   &$R_{p}$    &%0.8f\\pm%0.8f\\\\ \n",(Rp[0]*10.863), (Rp[1]*10.863));
    fprintf(fp,"Equilibrium Temperature (K)      &$T_{eq}$   &%0.8f\\pm%0.8f\\\\ \n",Teq[0], Teq[1]);
    fprintf(fp,"Semi-major Axis (AU)             &$a$        &%0.8f\\pm%0.8f\\\\ \n",a[0],a[1]);
    fprintf(fp,"Safronov Number                  &\\theta    &%0.8f\\pm%0.8f\\\\ \n",SN[0], SN[1]);
    fprintf(fp,"Surface Gravity (cm/s^{2}))      &g          &%0.8f\\pm%0.8f\\\\ \n",sg[0] , sg[1]);

    sg[1] = sg[1]/(log(10)*sg[0]);
    printf(" Surface Grav: = %f +- %f log(g) (cgs) \n", log10(sg[0]), sg[1]);
    fprintf(fp,"Surface Gravity (cgs)            &log_{g}    &%0.8f\\pm%0.8f\\\\ \n",log10(sg[0]) , sg[1]);

    printf(" Density = %f +- %f g/cm^3 \n", pb[0], pb[1]);
    fprintf(fp,"Density of Planet (g/cm^3)       &\\rho_{p}  &%0.8f\\pm%0.8f\\\\ \n",pb[0], pb[1]);

    printf(" Stellar Density = %f +- %f \n", ps[0], ps[1]); 
    fprintf(fp,"Stellar Density (g/cm^{3})       &\\rhostar  &%0.8f\\pm%0.8f\\\\ \n",ps[0], ps[1]);
 
    CalcSDensity(p,Ms,Rs);
    printf(" Density = %f +- %f \n",p[0],p[1]);
    fprintf(fp,"Stellar Density (g/cm^{3})       &\\rhostar  &%0.8f\\pm%0.8f\\\\ %traditional calc M/V\n",p[0],p[1]);
    fclose(fp);  
    printf("latex_output.tex was created \n");
}


// Equation 25, Exoplanets by Sara Seager
void CalcMass(double *Mb,double *i,double *P,double *Ms,double *K,double *e)
{
	double Ebar[5], ee28;
	double P13 = pow(P[0],(1./3.));
	double M23 = pow(Ms[0],(2./3.));
	double Ki = K[0]/sin(i[0]);
	if(e[0] != 0) ee28 = sqrt(1-e[0]*e[0])/28.4329;
	else ee28 = 1./28.4329;
	
	Mb[0] = ee28 * Ki * P13 * M23;                                  // Mb Error
	Ebar[0] = P13 * M23 * ee28 * (1./sin(i[0]));                    // K Error
	Ebar[1] = P13 * M23 * K[0] * -1. * tan(M_PI_2 - i[0]) / (28.4329 * sin(i[0]));  // i Error
	Ebar[2] = Ki * M23 * ee28 / (pow(P[0],(2./3.)) * 3.);           // P Error
	Ebar[3] = P13 * Ki * ee28 * pow(Ms[0],(-1./3.)) * (2./3.);      // Ms Error
	Ebar[4] = P13 * M23 * Ki * e[0] / (28.4329*sqrt(1-e[0]*e[0]));  // e Error
	
	// for(int j=0;j<5;j++) printf("Ebar[%i] = %f \n",j,Ebar[j]);
	for(int j=0;j<5;j++) Ebar[j] *= Ebar[j];
	
	Mb[1] = sqrt( Ebar[0]*K[1]*K[1] + Ebar[1]*i[1]*i[1] + Ebar[2]*P[1]*P[1] + Ebar[3]*Ms[1]*Ms[1] + Ebar[4]*e[1]*e[1] );
	// cot(x) = tan(M_PI_2 - x)
}


void CalcRadius(double *Rp,double *RpRs,double *Rs)
{
	double R_s = 6.955e5;  // solar radius in [km]
	double R_J = 7.1492e4; // jupiter radius in [km]	
	
	Rp[0] = RpRs[0]*R_s*Rs[0]; // in km
	double term1 = (Rs[0]*R_s)*RpRs[1];
	term1 *= term1;
	
	double term2 = RpRs[0]*Rs[1]*R_s;
	term2 *= term2;
	
	Rp[0] /= R_J; // in jup radii
	Rp[1] = sqrt(term1+term2)*(1./R_J);
}


void CalcDensity(double *pb,double *Mp,double *Rp)
{
    double M_J = 1.89865e30; // jupiter radii in [g]
    double R_J = 7149200000; // jupiter radius in [cm]
    double Const = 1./((4./3.)*M_PI);
    double Rp3 = pow((Rp[0]*R_J),3);    

    pb[0] = Mp[0]*M_J*Const/Rp3;
    
    double Merr = Const/Rp3;
    double Rerr = Mp[0]*M_J*Const*(-3.)/(Rp3*Rp[0]*R_J);

    pb[1] = sqrt(Merr*Merr*Mp[1]*Mp[1]*M_J*M_J + Rerr*Rerr*Rp[1]*Rp[1]*R_J*R_J);
}

// Equation Southworth 2010
void CalcTemp1(double *Teff,double *Teq,double *aRs)
{
    double Const = pow(0.5,0.5); // (1/4)^(1/4) * (1/2)^(1/2)
    Teq[0] = Teff[0]*Const/sqrt(aRs[0]);

    double Teff_part = Const/sqrt(aRs[0]);
    double aRs_part = Const/(2.*pow(aRs[0],1.5));
    Teq[1] = sqrt(Teff_part*Teff_part*Teff[1]*Teff[1] + aRs_part*aRs_part*aRs[1]*aRs[1]);
}


// Equation 31, Surface Gravity in Exoplanets by Sara Seager
void CalcSurfaceGrav(double *sg, double *P,double *a,double *Rp,double *i,double *e,double *K)
{
    double Ebar[6];
    double AU = 14959787070000.; // AU in [cm] 
    double R_J = 7149200000.; // jupiter radius in [cm]    
    
    sg[0] =  (2.*M_PI*(a[0]*a[0]*AU*AU)*sqrt(1.-e[0]*e[0])*K[0]*100.)/(P[0]*24.*60.*60.*Rp[0]*Rp[0]*R_J*R_J*sin(i[0]));

    double esini = sqrt(1.-e[0]*e[0])/sin(i[0]);
    double pip = 2.*M_PI/(P[0]*24.*60.*60.);
    double ar = (a[0]*a[0]*AU*AU)/(Rp[0]*Rp[0]*R_J*R_J);

    Ebar[0] = esini*(K[0]*100.)*ar*pip/(P[0]*24.*60.*60.);              // Partial P_b
    Ebar[1] = pip*esini*(K[0]*100.)*2.*a[0]*AU/(Rp[0]*Rp[0]*R_J*R_J);   // Partial a
    Ebar[2] = pip*esini*(K[0]*100.)*(-2.)*ar/(Rp[0]*R_J);               // Partial R_b
    Ebar[3] = pip*esini*ar;                                             // Partial K
    Ebar[4] = pip*ar*(K[0]*100.)*e[0]/(sqrt(1.-e[0]*e[0])*sin(i[0]));   // Partial e
    Ebar[5] = pip*ar*(K[0]*100.)*sqrt(1.-e[0]*e[0])*2.*cos(i[0])/(cos(2.*i[0])-1.); // Partial i, -cot(i)csc(i) = 2cos(i)/[cos(2i)-1]
   
    for(int j=0;j<6;j++) Ebar[j] *= Ebar[j];

   // for(int j=0;j<6;j++) printf("Ebar[%i] = %f \n",j,Ebar[j]);
    
    sg[1] = sqrt( Ebar[0]*(P[1]*24.*60.*60.)*(P[1]*24.*60.*60.) + Ebar[1]*a[1]*a[1]*AU*AU + Ebar[2]*Rp[1]*Rp[1]*R_J*R_J + Ebar[3]*K[1]*K[1]*10000. + Ebar[4]*e[1]*e[1] + Ebar[5]*i[1]*i[1] );

    //sg[1] = sqrt( Ebar[0]*P[1]*P[1]*24.*60.*60.*24.*60.*60. + Ebar[1]*a[1]*a[1] + Ebar[2]*Rp[1]*Rp[1]*R_J*R_J  + Ebar[3]*K[1]*K[1] + Ebar[4]*e[1]*e[1] + Ebar[5]*i[1]*i[1] );
}

void CalcSemiMajorAxis(double *a,double *aRs,double *Rs)
{
    double AU = 149597871; // AU in kilometers
    double R_s = 6.955e5;  // solar radius in [km]
    a[0] = aRs[0]*Rs[0];
    a[1] = sqrt(Rs[0]*Rs[0]*aRs[1]*aRs[1] + aRs[0]*aRs[0]*Rs[1]*Rs[1]); // in solar radius
    a[0] *= R_s/AU; // convert to AU from solar radii
    a[1] *= R_s/AU;
}

void CalcSafronovNum(double *SN,double *Mb,double *a,double *Ms,double *Rb)
{
    double AU = 149597870700; // AU in [m] 
    double R_J = 71492000; // jupiter radius in [m]
    double M_J = 1.89865e30; // jupiter radii in [g]
    double M_S = 1.988547e33; // solarmass in [g]

    SN[0] = Mb[0]*M_J*a[0]*AU/(Ms[0]*M_S*Rb[0]*R_J);

    double mb_part = a[0]*AU/(Ms[0]*M_S*Rb[0]*R_J);
    double a_part = Mb[0]*M_J/(Ms[0]*M_S*Rb[0]*R_J);
    double ms_part = Mb[0]*M_J*a[0]*AU*(-1.)/(Rb[0]*R_J*Ms[0]*M_S*Ms[0]*M_S);
    double rb_part =  Mb[0]*M_J*a[0]*AU*(-1.)/(Ms[0]*M_S*Rb[0]*R_J*Rb[0]*R_J);
    SN[1] = sqrt(mb_part*mb_part*Mb[1]*Mb[1]*M_J*M_J + a_part*a_part*a[1]*a[1]*AU*AU + ms_part*ms_part*Ms[1]*Ms[1]*M_S*M_S + rb_part*rb_part*Rb[1]*Rb[1]*R_J*R_J );
}

void CalcStellarDensity(double *ps,double *P,double *aRs,double *pb,double *RpRs)
{
    double G = 6.674e-8; 
    double SD = 24.*60.*60.;  // day to seconds

    ps[0] = 3.*M_PI*pow(aRs[0],3.)/(G*P[0]*P[0]*SD*SD)-pb[0]*pow(RpRs[0],3);
    
    double ar3 = pow(aRs[0],3.);
    double rps3 = pow(RpRs[0],3.);
    double gp2 = 3.*M_PI/(G*P[0]*P[0]*SD*SD);
    
    double P_part = gp2*(-2.)*ar3/(P[0]*SD)-pb[0]*rps3;
    double ar_part = gp2*3*pow(aRs[0],2.)-pb[0]*rps3;
    double rp_part = gp2*ar3-pb[0]*3*pow(RpRs[0],2.);
    double pb_part = gp2*ar3-rps3;
    
    ps[1] = sqrt( P_part*P_part*P[1]*P[1]*SD*SD + ar_part*ar_part*aRs[1]*aRs[1] + rp_part*rp_part*RpRs[1]*RpRs[1] + pb_part*pb_part*pb[1]*pb[1] );
}

void CalcSDensity(double *p,double *m,double *r)
{
    double Const = (4./3.)*M_PI;
    p[0] =  m[0]*1.988547e33 / (Const*r[0]*r[0]*r[0]*6.955e10*6.955e10*6.955e10);
    
    double m_part = 1./(Const*r[0]*r[0]*r[0]*6.955e10*6.955e10*6.955e10);
    double r_part = m[0]*3./(Const*r[0]*r[0]*r[0]*6.955e10*r[0]*6.955e10*6.955e10*6.955e10);
    p[1] = sqrt(m_part*m_part*m[1]*m[1]*1.988547e33*1.988547e33 + r_part*r_part*r[1]*r[1]*6.955e10*6.955e10);
}

/*  Might be useful
    double R_J = 7.1492e9;    // jupiter radius in [cm]
    double R_s = 6.955e10;    // solar radius in [cm]
    double M_J = 1.89865e30;  // jupiter radii in [g]
    double M_S = 1.988547e33; // solarmass in [g]
*/
