#ifndef PREDEFINE_H
#define PREDEFINE_H

//#define USINGQVECTOR
//#ifdef USINGQVECTOR
//#define Vector QVector
//#else
//#include<vector>
//#define Vector vector
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned long ulong;
typedef unsigned long long ulonglong;

#define PI 3.1415926535898


#include<limits>
#include<math.h>
#include <string>
namespace Utility {

#define UINTFLAG  std::numeric_limits<unsigned int>::max()


inline double dot(const double *e1,const double *e2,const int dim = 3){
    double d = 0.0f;
    for(int i =0;i<dim;++i)d+=e1[i]*e2[i];
    return d;
}
inline void normalize(double *face_normal,const int dim = 3){
    double len = sqrt(dot(face_normal,face_normal,dim));
    for(int i =0;i<dim;++i)face_normal[i] /= len;
}
inline void inversevec(double *p_s, double *p_d, const int dim =3){
    for(int i =0;i<dim;++i)p_d[i] = -p_s[i];
}
inline void product(const double a,const double *vin, double *vout,int dim = 3){
    for(int i =0;i<dim;++i)vout[i]=a*vin[i];
}
inline void cross(const double *e1,const double *e2,double *pn){
    pn[0] = e1[1] * e2[2] - e2[1] * e1[2];
    pn[1] = e1[2] * e2[0] - e2[2] * e1[0];
    pn[2] = e1[0] * e2[1] - e2[0] * e1[1];
}
//    static double dot(double *e1,double *e2){
//        return e1[0]*e2[0]+e1[1]*e2[1]+e1[2]*e2[2];
//    }
inline void add(const double *p_v1,const double *p_v2, double *p_vc, int vdim=3){
    for(int i = 0;i<vdim;++i)p_vc[i] = (p_v1[i] + p_v2[i]);
}
inline void minusVec(const double *v1,const double *v2,double *e,const int dim = 3){
    for(int i =0;i<dim;++i)e[i]= v1[i]-v2[i];
}
inline double normVec(const double *e){return sqrt(dot(e,e));}
inline double len(const double *e){
    return dot(e,e);
}
inline void copyVec(double *vo, double *vd,int dim = 3){
    for(int i =0;i<dim;i++)vd[i] = vo[i];
}
inline void rotateTriVec3D(uint *vo, uint *vd){
    vd[0] = vo[2];vd[1] = vo[1];vd[2] = vo[0];
}
inline double cosine(const double *e1,const double *e2){
    double a = dot(e1,e2)/normVec(e1)/normVec(e2);
    if(a>1)a=1;
    if(a<-1)a=-1;
    return a;
}
inline double angleNor(const double *e1,const double *e2){
    return acos(cosine(e1,e2));
}

inline double _VerticesDistance(const double *p_v1,const double *p_v2,const int vdim=3){
    double dist = 0.0f;
    for(int i = 0;i<vdim;++i)dist += (p_v1[i] - p_v2[i] )*(p_v1[i] - p_v2[i] );
    return sqrt(dist);
}

inline double vecSquareDist(const double *p_v1,const double *p_v2){
    double dist = 0.0f;
    for(int i = 0;i<3;++i)dist += (p_v1[i] - p_v2[i] )*(p_v1[i] - p_v2[i] );
    return dist;
}

inline void _VerticesMidpoint(const double *p_v1,const double *p_v2, double *p_vc,const int vdim = 3){
    for(int i = 0;i<vdim;++i)p_vc[i] = (p_v1[i] + p_v2[i]) /2;
}

inline void _TriangleMidpoint(const double *p_v1,const double *p_v2,const  double *p_v3,double *p_vc,const int vdim = 3){
    for(int i = 0;i<vdim;++i)p_vc[i] = (p_v1[i] + p_v2[i] + p_v3[i]) /3;
}

double inline _TriangleArea(const double *v1,const double *v2,const double *v3){
    double e1[3], e2[3], p_n[3];
    for (uint j = 0; j < 3; ++j){
        e1[j] = v2[j] - v1[j];
        e2[j] = v3[j] - v2[j];
    }
    p_n[0] = e1[1] * e2[2] - e2[1] * e1[2];
    p_n[1] = e1[2] * e2[0] - e2[2] * e1[0];
    p_n[2] = e1[0] * e2[1] - e2[0] * e1[1];
    return(0.5*sqrt(p_n[0] * p_n[0] + p_n[1] * p_n[1] + p_n[2] * p_n[2]));
}

void inline _TriangleCircumcenter(const double *pv1,const double *pv2,const double *pv3,double *cc,double &r){

    double n[3],e1[3],e2[3];
    for(int i = 0;i<3;++i){e1[i]=pv1[i]-pv2[i];e2[i]=pv1[i]-pv3[i];}
    cross(e1,e2,n);normalize(n);
    double c1[3],c2[3];
    _VerticesMidpoint(pv1,pv2,c1,3);
    _VerticesMidpoint(pv1,pv3,c2,3);
    double n1[3],n2[3];
    cross(e1,n,n1);cross(e2,n,n2);
    double t = ((c2[0]-c1[0])*n2[1] - (c2[1]-c1[1])*n2[0])/(n1[0]*n2[1] - n1[1]*n2[0]);
    for(int i = 0;i<3;++i)cc[i] = c1[i] + n1[i]*t;
    r = _VerticesDistance(pv1,cc,3);
    //cout<<VerticesDistance(pv1,cc,3)<<' '<<VerticesDistance(pv2,cc,3)<<' '<<VerticesDistance(pv3,cc,3)<<endl;
}
double inline _TriangleLeastAngle(const double *pv1, const double *pv2, const double *pv3,const int dim){
    double leastangle;
    double vdis1,vdis2,vdis3;
    double dot1,dot2,dot3;
    double e1[3],e2[3],e3[3];
    vdis1 = _VerticesDistance(pv1,pv2,dim);
    vdis2 = _VerticesDistance(pv1,pv3,dim);
    vdis3 = _VerticesDistance(pv2,pv3,dim);
    minusVec(pv1,pv2,e1,dim);minusVec(pv1,pv3,e2,dim);minusVec(pv2,pv3,e3,dim);
    dot1 = dot(e1,e2,dim);dot2 = -dot(e1,e3,dim);dot3 = dot(e2,e3,dim);
    leastangle = fmax(fmax(dot1/vdis1/vdis2,dot2/vdis1/vdis3),dot3/vdis2/vdis3);
    //        angle1 = acosf(dot1/vdis1/vdis2);
    //        angle2 = acosf(dot2/vdis1/vdis3);
    //        angle3 = acosf(dot3/vdis2/vdis3);
    //        return min(min(angle1,angle2),angle3);
    return acosf(leastangle);
}

double inline _TetrahedronVolume(const double *v1,const double *v2,const double *v3,const double *v4){
    double e1[3], e2[3], e3[3],p_n[3];
    for (uint j = 0; j < 3; ++j){
        e1[j] = v2[j] - v1[j];
        e2[j] = v3[j] - v1[j];
        e3[j] = v4[j] - v1[j];
    }
    cross(e2,e3,p_n);
    return(dot(e1,p_n)/6.);
}



inline double projectVectorUNor(const double *proj, const double *normal,double *vec){
    double dis = dot(proj,normal);
    double tmp[3];
    product(dis,normal,tmp);
    minusVec(proj,tmp,vec);
    return (dis);
}
double inline _angleBetweenTwoPlanes(const double *ev1,const double *ev2,const double *v3,const double *v4){
    double e1[3], e2[3],e[3], p_n1[3],p_n2[3];
    for (uint j = 0; j < 3; ++j){
        e[j] = ev2[j] - ev1[j];
        e1[j] = v3[j] - ev1[j];
        e2[j] = v4[j] - ev1[j];
    }
    cross(e,e1,p_n1);cross(e,e2,p_n2);
    return(acos(cosine(p_n1,p_n2)));
}
double inline _cotBetweenTwoPlanes(const double *ev1,const double *ev2,const double *v3,const double *v4){
    double e1[3], e2[3],e[3], p_n1[3],p_n2[3],p_n3[3];
    for (uint j = 0; j < 3; ++j){
        e[j] = ev2[j] - ev1[j];
        e1[j] = v3[j] - ev1[j];
        e2[j] = v4[j] - ev1[j];
    }
    cross(e,e1,p_n1);cross(e,e2,p_n2);
    normalize(p_n1);normalize(p_n2);cross(p_n1,p_n2,p_n3);
    double cotTheta = dot( p_n1, p_n2 ) / normVec(p_n3);
    if( cotTheta < 1e-7 )cotTheta = 1e-7;
    return cotTheta;

}
inline double projectVectorNor(const double *proj, const double *normal,double *vec){
    double dis = projectVectorUNor(proj,normal,vec);
    normalize(vec);
    return (dis);
}
inline double projectVectorLeng(const double *proj, const double *normal,double *vec){
    double dis = projectVectorNor(proj,normal,vec);
    double lengg = normVec(proj);
    product(lengg,vec,vec);
    return (dis);
}

inline void weightedAddVec(const double weight, const double *orivec,double *desvec){
    for(int i =0;i<3;++i)desvec[i] += weight*orivec[i];
}
inline void weightedAddVec(const double weight1,const double weight2, const double *orivec1,const double *orivec2,double *desvec){
    for(int i =0;i<3;++i)desvec[i] = weight1*orivec1[i] + weight2*orivec2[i];
}

inline double computePoint2LineDistance(const double *p, const double *lst, const double *ldir){
    double vec[3];
    minusVec(p,lst,vec);
    double d2st =dot(vec,ldir);
    product(d2st,ldir,vec);
    add(lst,vec,vec);
    return _VerticesDistance(p,vec);

}

inline double computePoint2LineDistance(const double *p, const double *lst, const double *ldir, double& d2st){
    double vec[3];
    minusVec(p,lst,vec);
    d2st =dot(vec,ldir);
    product(d2st,ldir,vec);
    add(lst,vec,vec);
    return _VerticesDistance(p,vec);

}


inline double relativeAngle(const double *vec,const double *ref, const double *normal){
    double tmpcross[3];
    double dd = angleNor(vec,ref);
    cross(ref,vec,tmpcross);
    if(dot(tmpcross,normal)<0)dd=-dd;
    return dd;

}

inline double point2TriSquareDistance(const double *P, const double *v1, const double *v2, const double *v3,double *cp){
    double vec[3],E0[3],E1[3];
    const double *B = v1;
    minusVec(v2,v1,E0);
    minusVec(v3,v1,E1);
    double a = dot(E0,E0);
    double b = dot(E0,E1);
    double c = dot(E1,E1);
    minusVec(B,P,vec);
    double d = dot(E0,vec);
    double e = dot(E1,vec);
    double f = dot(vec,vec);

    double det = a*c-b*b, s = b*e-c*d, t = b*d-a*e;

    auto f0 = [&s,&t,&det](){double invdet = 1/det; s*=invdet;t*=invdet;};
    auto f1 = [&s,&t,&det,&a,&b,&c,&d,&e,&f](){
        double numer = c+e-b-d;
        if ( numer <= 0 ){
            s = 0;
        }else{
            double denom = a-2*b+c;
            s = ( numer >= denom ? 1 : numer/denom );
        }
        t = 1-s;
    };
    auto f2 = [&s,&t,&det,&a,&b,&c,&d,&e,&f](){
        double tmp0 = b+d;
        double tmp1 = c+e;
        if ( tmp1 > tmp0 ){
            double numer = tmp1 - tmp0;
            double denom = a-2*b+c;
            s = ( numer >= denom ? 1 : numer/denom );
            t = 1-s;
        }else {
            s = 0;
            t = ( tmp1 <= 0 ? 1 : ( e >= 0 ? 0 : -e/c ) );
        }
    };
    auto f3 = [&s,&t,&det,&e,&c](){
        s = 0;
        t = ( e >= 0 ? 0 : ( -e >= c ? 1 : -e/c ) );
    };
    auto f4 = [&s,&t,&det,&a,&b,&c,&d,&e,&f](){
        if (d < 0){
            t = 0;
            s = ( -d >= a ? 1 : -d/a );

        }else{
            s = 0;
            t = ( e >= 0 ? 0 : ( -e >= c ? 1 : -e/c ) );
        }


    };
    auto f5 = [&s,&t,&det,&a,&d](){
        t = 0;
        s = ( d >= 0 ? 0 : ( -d >= a ? 1 : -d/a ) );
    };
    auto f6 = [&s,&t,&det,&a,&b,&c,&d,&e,&f](){
        double tmp0 = b+e;
        double tmp1 = a+d;
        if ( tmp1 > tmp0 ){
            double  numer = tmp1 - tmp0;
            double denom = a-2*b+c;
            t = ( numer >= denom ? 1 : numer/denom );
            s = 1-t;
        }else {
            t = 0;
            s = ( tmp1 <= 0 ? 1 : ( d >= 0 ? 0 : -d/a ) );
        }
    };




    if ( s+t <= det )
    {
        if ( s < 0 ) { if ( t < 0 ) { f4(); } else { f3(); } }
        else if ( t < 0 ) { f5(); }
        else { f0(); }
    }
    else
    {
        if ( s < 0 ) { f2();}
        else if ( t < 0 ) { f6(); }
        else { f1();}
    }

    product(s,E0,E0);product(t,E1,E1);
    add(B,E0,cp);add(cp,E1,cp);
    minusVec(P,cp,vec);
    return dot(vec,vec);
}

inline double point2TriDistance(const double *P, const double *v1, const double *v2, const double *v3,double *cp){
    return sqrt(point2TriSquareDistance(P,v1,v2,v3,cp));
}


/****************************************************************/

inline void SplitFileName (const std::string& fullfilename,std::string &filepath,std::string &filename,std::string &extname) {
    int pos;
    pos = fullfilename.find_last_of('.');
    filepath = fullfilename.substr(0,pos);
    extname = fullfilename.substr(pos);
    pos = filepath.find_last_of("\\/");
    filename = filepath.substr(pos+1);
    pos = fullfilename.find_last_of("\\/");
    filepath = fullfilename.substr(0,pos+1);
    //cout<<modname<<' '<<extname<<' '<<filepath<<endl;
}

}






#endif



