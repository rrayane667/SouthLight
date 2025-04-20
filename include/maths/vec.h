#pragma once
#include "utilite/dataStruct.h"
#include <ostream>


namespace MATH {


	struct vec2 {
		float x, y;

		vec2& operator=(DATASTRUCT::List<float> *l){
			x = l->get(0); y =l->get(1);// a refaire
		}
		vec2(DATASTRUCT::List<float> *l){x = l->get(0); y =l->get(1);}

		vec2();
		vec2(const float& x, const float& y);
		vec2& add(const vec2& v);
		vec2& sub(const vec2& v);
		vec2& multi(const vec2& v);
		vec2& divide(const vec2& v);

		vec2 operator+(vec2 v);
		vec2 operator-(vec2 v);
		vec2 operator*(vec2 v);
		vec2 operator/(vec2 v);

		vec2& operator+=(const vec2& right);
		vec2& operator-=(const vec2& right);
		vec2& operator*=(const vec2& right);
		vec2& operator/=(const vec2& right);
		friend std::ostream& operator<<(std::ostream& o, vec2 v){
			o << "vec2 : " << v.x << ", " << v.y;
			return o;
		}

		vec2& add(const float& v);
		vec2& sub(const float& v);
		vec2& multi(const float& v);
		vec2& divide(const float& v);

		vec2 operator+(const float& s);
		vec2 operator-(const float& s);
		vec2 operator*(const float& s);
		vec2 operator/(const float& s);

		vec2& operator+=(const float& right);
		vec2& operator-=(const float& right);
		vec2& operator*=(const float& right);
		vec2& operator/=(const float& right);

		float norme();
		vec2 normalize();
		float dot(vec2& v);

		bool operator==(const vec2& other) const {
			return x == other.x && y == other.y;
		}

		void print();
		
	};

	struct vec3 {
		float x, y, z;
		vec3 cross(const vec3& v) const ;
		vec3();
		inline vec3(const vec2& v){x=v.x; y=v.y; z=0;}
		vec3(const float& x, const float& y, const float& z);
		vec3& add(const vec3& v);
		vec3& sub(const vec3& v);
		vec3& multi(const vec3& v);
		vec3& divide(const vec3& v);

		vec3 operator+(vec3 v);
		vec3 operator-(vec3 v);
		vec3 operator*(vec3 v);
		vec3 operator/(vec3 v);

		vec3& operator+=(const vec3& right);
		vec3& operator-=(const vec3& right);
		vec3& operator*=(const vec3& right);
		vec3& operator/=(const vec3& right);

		vec3& add(const float& v);
		vec3& sub(const float& v);
		vec3& multi(const float& v);
		vec3& divide(const float& v);

		vec3 operator+(const float& s);
		vec3 operator-(const float& s);
		vec3 operator*(const float& s);
		vec3 operator/(const float& s);

		vec3& operator+=(const float& right);
		vec3& operator-=(const float& right);
		vec3& operator*=(const float& right);
		vec3& operator/=(const float& right);

		bool operator==(const vec3& other) const {
			return x == other.x && y == other.y && z == other.z;
		}

		friend std::ostream& operator<<(std::ostream& o, vec3 v){
			o << "vec3 : " << v.x << ", " << v.y << ", " << v.z;
			return o;
		}

		vec3& operator=(DATASTRUCT::List<float> *l){
			x = l->get(0); y =l->get(1); z = l->get(2);// a refaire
		}
		vec3(DATASTRUCT::List<float> *l){x = l->get(0); y =l->get(1); z = l->get(2);}

		float norme();     
		vec3 normalize();  
		float dot(vec3& v); 
		float* vecToList() const;

		void print();

	};

	struct vec4 {
		float x, y, z, w;

		vec4();
		vec4(const float& x, const float& y, const float& z, const float& w);


		vec4& add(const vec4& v);
		vec4& sub(const vec4& v);
		vec4& multi(const vec4& v);
		vec4& divide(const vec4& v);

		vec4 operator+(vec4 v);
		vec4 operator-(vec4 v);
		vec4 operator*(vec4 v);
		vec4 operator/(vec4 v);

		vec4& operator+=(const vec4& right);
		vec4& operator-=(const vec4& right);
		vec4& operator*=(const vec4& right);
		vec4& operator/=(const vec4& right);

		vec4& add(const float& v);
		vec4& sub(const float& v);
		vec4& multi(const float& v);
		vec4& divide(const float& v);

		vec4 operator+(const float& s);
		vec4 operator-(const float& s);
		vec4 operator*(const float& s);
		vec4 operator/(const float& s) const;

		vec4& operator+=(const float& right);
		vec4& operator-=(const float& right);
		vec4& operator*=(const float& right);
		vec4& operator/=(const float& right);

		float norme() const;
		vec4 normalize() const;
		float dot(vec4& v);

		void print() const;
		float* vec4ToList();
		friend std::ostream& operator<<(std::ostream& o, vec4 v){
			o << "vec4 : " << v.x << ", " << v.y << ", " << v.z<< ", " << v.w;
			return o;
		}

	};

	struct mat4 {

		union {
			struct {
				vec4 c1, c2, c3, c4;
			};
			float list[16];
		};

		friend std::ostream& operator<<(std::ostream& o, mat4 m){
			o << "column1 : " << m.c1 << std::endl; 
			o << "column2 : " << m.c2 << std::endl;
			o << "column3 : " << m.c3 << std::endl;
			o << "column4 : " << m.c4 << std::endl;
			return o;
		}

		mat4();
		mat4(const float& s);
		mat4(const vec4& c1, const vec4& c2, const vec4& c3, const vec4& c4);
		mat4(const float& x1, const float& y1, const float& z1, const float& w1, const float& x2, const float& y2, const float& z2, const float& w2, const float& x3, const float& y3, const float& z3, const float& w3, const float& x4, const float& y4, const float& z4, const float& w4);

		//matrice diagonale
		static mat4 diag(const vec4& v);
		static mat4 diag(const float& x, const float& y, const float& z, const float& w);
		static mat4 scalaire(const float& s);
		static mat4 identitee();


		//matrice de projection
		static mat4 orthographic(const float& r, const float& l, const float& t, const float& b, const float& n, const float& f);
		static mat4 perspective(const float& fov, const float& ratio, const float& n, const float& f);

		//multiplication matrice*vecteur
		vec4 vecMulti(const vec4& v);
		vec4 operator*(vec4& v);

		//operation standard matrice-matrice
		mat4& add(const mat4& m);
		mat4& sub(const mat4& m);
		mat4& multi(const mat4& m);

		

		mat4 transpose();
		static mat4 rotation(const vec4& axis, const float& angle);
		static mat4 translation(const vec3& t);
		static mat4 view(vec3 eye, float pitch, float yaw);
		static mat4 scale(const vec3& v);

		mat4 operator+(mat4 v);
		mat4 operator-(mat4 v);
		mat4 operator*(mat4 v);

		mat4& operator+=(const mat4& right);
		mat4& operator-=(const mat4& right);
		mat4& operator*=(const mat4& right);

		//operation standard float-matrice
		mat4& add(const float& v);
		mat4& sub(const float& v);
		mat4& multi(const float& v);
		mat4& divide(const float& v);

		mat4 operator+(const float& s);
		mat4 operator-(const float& s);
		mat4 operator*(const float& s);
		mat4 operator/(const float& s);

		mat4& operator+=(const float& right);
		mat4& operator-=(const float& right);
		mat4& operator*=(const float& right);
		mat4& operator/=(const float& right);

		//remplacer par union apres
		void print();
		
	};
	
}

