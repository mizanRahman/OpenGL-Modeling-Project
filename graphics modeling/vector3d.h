#ifndef VECTOR3D_H
#define VECTOR3D_H



#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <iostream>




class vector3d  {
public:

       double e[3];
    
    vector3d() {}
    vector3d(double e0, double e1, double e2) {e[0]=e0; e[1]=e1; e[2]=e2;}
    double x() const { return e[0]; }
    double y() const { return e[1]; }
    double z() const { return e[2]; }
    void SetX(double a) { e[0] = a; }
    void SetY(double a) { e[1] = a; }
    void SetZ(double a) { e[2] = a; }

    vector3d(const vector3d &v) {
         e[0] = v.e[0]; e[1] = v.e[1]; e[2] = v.e[2];
    }

    const vector3d& operator+() const { return *this; }
    vector3d operator-() const { return vector3d(-e[0], -e[1], -e[2]); }
    double& operator[](int i) { assert ( i >= 0 && i < 3 ); return e[i]; }
    double operator[](int i) const { assert ( i >= 0 && i < 3 ); return e[i];}

    vector3d& operator+=(const vector3d &v2);
    vector3d& operator-=(const vector3d &v2);
    vector3d& operator*=(const double t);
    vector3d& operator/=(const double t);


    
    double length() const { return sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]); }
    double squaredLength() const { return e[0]*e[0] + e[1]*e[1] + e[2]*e[2]; }

    void make_unit_vector();

    double min_component() const { return e[index_of_min_component()]; }
    double max_component() const { return e[index_of_max_component()]; }
    double max_abs_component() const { return e[index_of_max_abs_component()]; }
    double min_abs_component() const { return e[index_of_min_abs_component()]; }
    int index_of_min_component() const { 
	return (e[0]< e[1] && e[0]< e[2]) ? 0 : (e[1] < e[2] ? 1 : 2);
    }

    int index_of_min_abs_component() const {
	if (fabs(e[0]) < fabs(e[1]) && fabs(e[0]) < fabs(e[2]))
	    return 0;
	else if (fabs(e[1]) < fabs(e[2]))
	    return 1;
	else
	    return 2;
    }

    int index_of_max_component() const {
	return (e[0]> e[1] && e[0]> e[2]) ? 0 : (e[1] > e[2] ? 1 : 2);
    }

    int index_of_max_abs_component() const {
	if (fabs(e[0]) > fabs(e[1]) && fabs(e[0]) > fabs(e[2]))
	    return 0;
	else if (fabs(e[1]) > fabs(e[2]))
	    return 1;
	else
	    return 2;
    }

    
};


inline bool operator==(const vector3d &t1, const vector3d &t2) {
   return ((t1[0]==t2[0])&&(t1[1]==t2[1])&&(t1[2]==t2[2]));
}

inline bool operator!=(const vector3d &t1, const vector3d &t2) {
   return ((t1[0]!=t2[0])||(t1[1]!=t2[1])||(t1[2]!=t2[2]));
}
/*
inline istream &operator>>(istream &is, vector3d &t) {
   is >> t[0] >> t[1] >> t[2];
   return is;
}

inline ostream &operator<<(ostream &os, const vector3d &t) {
   os << t[0] << " " << t[1] << " " <<  t[2];
   return os;
}*/

inline vector3d unit_vector(const vector3d& v) {
    double k = 1.0 / sqrt(v.e[0]*v.e[0] + v.e[1]*v.e[1] + v.e[2]*v.e[2]);
    return vector3d(v.e[0]*k, v.e[1]*k, v.e[2]*k);
}

inline void vector3d::make_unit_vector() {
    double k = 1.0 / sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]);
    e[0] *= k; e[1] *= k; e[2] *= k;
}

inline vector3d operator+(const vector3d &v1, const vector3d &v2) {
    return vector3d( v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
}

inline vector3d operator-(const vector3d &v1, const vector3d &v2) {
    return vector3d( v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
}

inline vector3d operator*(double t, const vector3d &v) {
    return vector3d(t*v.e[0], t*v.e[1], t*v.e[2]); 
}

inline vector3d operator*(const vector3d &v, double t) {
    return vector3d(t*v.e[0], t*v.e[1], t*v.e[2]); 
}

inline vector3d operator/(const vector3d &v, double t) {
    return vector3d(v.e[0]/t, v.e[1]/t, v.e[2]/t); 
}


inline double dot(const vector3d &v1, const vector3d &v2) {
    return v1.e[0] *v2.e[0] + v1.e[1] *v2.e[1]  + v1.e[2] *v2.e[2];
}

inline vector3d cross(const vector3d &v1, const vector3d &v2) {
    return vector3d( (v1.e[1]*v2.e[2] - v1.e[2]*v2.e[1]),
                      (-(v1.e[0]*v2.e[2] - v1.e[2]*v2.e[0])),
                      (v1.e[0]*v2.e[1] - v1.e[1]*v2.e[0]));
}


inline vector3d& vector3d::operator+=(const vector3d &v){
    e[0]  += v.e[0];
    e[1]  += v.e[1];
    e[2]  += v.e[2];
    return *this;
}

inline vector3d& vector3d::operator-=(const vector3d& v) {
    e[0]  -= v.e[0];
    e[1]  -= v.e[1];
    e[2]  -= v.e[2];
    return *this;
}

inline vector3d& vector3d::operator*=(const double t) {
    e[0]  *= t;
    e[1]  *= t;
    e[2]  *= t;
    return *this;
}

inline vector3d& vector3d::operator/=(const double t) {
    e[0]  /= t;
    e[1]  /= t;
    e[2]  /= t;
    return *this;
}



#endif
