#include "maths/vec.h"
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>

namespace MATH {
	vec2::vec2() {
		x = 0;
		y = 0;
	}
	vec2::vec2(const float& x, const float& y) {
		this -> x = x;
		this -> y = y;
	}
	vec2& vec2::add(const vec2& v) {
		 x += v.x;
		 y += v.y;
		 return *this;
	}
	vec2& vec2::sub(const vec2& v) {
		x -= v.x;
		y -= v.y;
		return *this;
	}
	vec2& vec2::multi(const vec2& v) {
		x *= v.x;
		y *= v.y;
		return *this;
	}
	vec2& vec2::divide(const vec2& v) {
		x /= v.x;
		y /= v.y;
		return *this;
	}
	

	vec2 vec2::operator+(vec2 v) {
		

		return v.add(*this);
	}
	vec2 vec2::operator-(vec2 v) {

		return v.sub(*this);
	}
	vec2 vec2::operator*(vec2 v) {

		return v.multi(*this);
	}

	vec2 vec2::operator/(vec2 v) {

		return v.divide(*this);
	}

	vec2& vec2::operator+=(const vec2& right) {
		return this->add(right);

	}
	vec2& vec2::operator-=(const vec2& right) {

		return this->sub(right);
	}
	vec2& vec2::operator*=(const vec2& right) {

		return this->multi(right);
	}
	vec2& vec2::operator/=(const vec2& right) {

		return this->divide(right);
	}

	//scalar op
	vec2& vec2::add(const float& s) {
		x += s;
		y += s;
		return *this;
	}
	vec2& vec2::sub(const float& s) {
		x -= s;
		y -= s;
		return *this;
	}
	vec2& vec2::multi(const float& s) {
		x *= s;
		y *= s;
		return *this;
	}
	vec2& vec2::divide(const float& s) {
		x /= s;
		y /= s;
		return *this;
	}
	//op scalar
	vec2 vec2::operator+(const float& s) {

		return vec2(x+s,y+s);
	}
	vec2 vec2::operator-(const float& s) {


		return vec2(x - s, y - s);
	}
	vec2 vec2::operator*(const float& s) {

		return vec2(x * s, y * s);
	}

	vec2 vec2::operator/(const float& s) {

		return vec2(x / s, y / s);
	}
	//op= scalar
	vec2& vec2::operator+=(const float& right) {

		return this->add(right);
	}
	vec2& vec2::operator-=(const float& right) {


		return this->sub(right);
	}
	vec2& vec2::operator*=(const float& right) {

		return this->multi(right);
	}

	vec2& vec2::operator/=(const float& right) {

		return this->divide(right);
	}

	void vec2::print() {
		printf("%f %f", x, y);
	}

	float vec2::norme() {
		return sqrt(x * x + y * y);
	}

	//alg func
	vec2 vec2::normalize() {
		if (!vec2::norme()) printf("divisuin par 0"); 
		return (*this) / vec2::norme();
	}
	float vec2::dot(vec2& v) {
		return x * v.x + y * v.y;
	}

	//vec3
	vec3::vec3() {
		x = 0;
		y = 0;
		z = 0;
	}
	vec3::vec3(const float& x, const float& y, const float& z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
	vec3& vec3::add(const vec3& v) {
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}
	vec3& vec3::sub(const vec3& v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}
	vec3& vec3::multi(const vec3& v) {
		x *= v.x;
		y *= v.y;
		z *= v.z;
		return *this;
	}
	vec3& vec3::divide(const vec3& v) {
		x /= v.x;
		y /= v.y;
		z /= v.z;
		return *this;
	}

	vec3 vec3::operator+(vec3 v) {


		return v.add(*this);
	}
	vec3 vec3::operator-(vec3 v) {

		return v.sub(*this);
	}
	vec3 vec3::operator*(vec3 v) {

		return v.multi(*this);
	}

	vec3 vec3::operator/(vec3 v) {

		return v.divide(*this);
	}

	vec3& vec3::operator+=(const vec3& right) {
		return this->add(right);

	}
	vec3& vec3::operator-=(const vec3& right) {

		return this->sub(right);
	}
	vec3& vec3::operator*=(const vec3& right) {

		return this->multi(right);
	}
	vec3& vec3::operator/=(const vec3& right) {

		return this->divide(right);
	}

	//scalar op
	vec3& vec3::add(const float& s) {
		x += s;
		y += s;
		z += s;
		return *this;
	}
	vec3& vec3::sub(const float& s) {
		x -= s;
		y -= s;
		z -= s;
		return *this;
	}
	vec3& vec3::multi(const float& s) {
		x *= s;
		y *= s;
		z *= s;
		return *this;
	}
	vec3& vec3::divide(const float& s) {
		x /= s;
		y /= s;
		z /= s;
		return *this;
	}
	//op scalar
	vec3 vec3::operator+(const float& s) {

		return vec3(x + s, y + s, z + s);
	}
	vec3 vec3::operator-(const float& s) {


		return vec3(x - s, y - s, z - s);
	}
	vec3 vec3::operator*(const float& s) {

		return vec3(x * s, y * s, z * s);
	}

	vec3 vec3::operator/(const float& s) {

		return vec3(x / s, y / s, z / s );
	}
	//op= scalar
	vec3& vec3::operator+=(const float& right) {

		return this->add(right);
	}
	vec3& vec3::operator-=(const float& right) {


		return this->sub(right);
	}
	vec3& vec3::operator*=(const float& right) {

		return this->multi(right);
	}

	vec3& vec3::operator/=(const float& right) {

		return this->divide(right);
	}

	void vec3::print() {
		printf("%f %f %f", x, y, z);
	}

	float vec3::norme() {
		return sqrt(x * x + y * y + z*z);
	}

	//alg func
	vec3 vec3::normalize() {
		if (!vec3::norme()) printf("divisuin par 0");
		return (*this) / vec3::norme();
	}
	float vec3::dot(vec3& v) {
		return x * v.x + y * v.y + z * v.z;
	}

	float* vec3::vecToList() const{
		float list[4] = {
			x, y, z
		};
		return list;
	}

	//vec4
	vec4::vec4() {
		x = 0;
		y = 0;
		z = 0;
		w = 0;
	}
	vec4::vec4(const float& x, const float& y, const float& z, const float& w) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}
	vec4& vec4::add(const vec4& v) {
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;
		return *this;
	}
	vec4& vec4::sub(const vec4& v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
		w -= v.w;
		return *this;
	}
	vec4& vec4::multi(const vec4& v) {
		int tx = y * v.z - z * v.y;
		int ty = z * v.x - x * v.z;
		int tz = x * v.y - y * v.x;
		int w = v.w;

		x = tx; y = ty; z = tz;
		return *this;
	}
	vec4& vec4::divide(const vec4& v) {
		x /= v.x;
		y /= v.y;
		z /= v.z;
		w /= v.w;
		return *this;
	}

	vec4 vec4::operator+(vec4 v) {


		return v.add(*this);
	}
	vec4 vec4::operator-(vec4 v) {

		return v.sub(*this);
	}
	vec4 vec4::operator*(vec4 v) {

		return v.multi(*this);
	}

	vec4 vec4::operator/(vec4 v) {

		return v.divide(*this);
	}

	vec4& vec4::operator+=(const vec4& right) {
		return this->add(right);

	}
	vec4& vec4::operator-=(const vec4& right) {

		return this->sub(right);
	}
	vec4& vec4::operator*=(const vec4& right) {

		return this->multi(right);
	}
	vec4& vec4::operator/=(const vec4& right) {

		return this->divide(right);
	}

	//scalar op
	vec4& vec4::add(const float& s) {
		x += s;
		y += s;
		z += s;
		w += s;
		return *this;
	}
	vec4& vec4::sub(const float& s) {
		x -= s;
		y -= s;
		z -= s;
		w -= s;
		return *this;
	}
	vec4& vec4::multi(const float& s) {
		x *= s;
		y *= s;
		z *= s;
		w *= s;
		return *this;
	}
	vec4& vec4::divide(const float& s) {
		x /= s;
		y /= s;
		z /= s;
		w /= s;
		return *this;
	}
	//op scalar
	vec4 vec4::operator+(const float& s) {

		return vec4(x + s, y + s, z + s, w + s);
	}
	vec4 vec4::operator-(const float& s) {


		return vec4(x - s, y - s, z - s, w - s);
	}
	vec4 vec4::operator*(const float& s) {

		return vec4(x * s, y * s, z * s, w * s);
	}

	vec4 vec4::operator/(const float& s) const{

		return vec4(x / s, y / s, z / s, w / s);
	}
	//op= scalar
	vec4& vec4::operator+=(const float& right) {

		return this->add(right);
	}
	vec4& vec4::operator-=(const float& right) {


		return this->sub(right);
	}
	vec4& vec4::operator*=(const float& right) {

		return this->multi(right);
	}

	vec4& vec4::operator/=(const float& right) {

		return this->divide(right);
	}

	void vec4::print() const{
		printf("%f %f %f %f \n", x, y, z, w);
	}

	float vec4::norme() const{
		return (float) sqrt(x * x + y * y + z * z + w * w);
	}

	//alg func
	vec4 vec4::normalize() const{
		if (!(*this).norme()) { printf("divisuin par 0 pour : "); (*this).print(); };
		return (*this) / vec4::norme();
	}

	float vec4::dot(vec4& v) {
		return x * v.x + y * v.y + z * v.z + w * v.w;
	}

	float* vec4::vec4ToList() {
		float list[4] = {
			x, y, z, w
		};
		return list;
	}

	//mat4
	mat4::mat4() {
		c1 = c2 = c3 = c4 = vec4();
		
	}
	mat4::mat4(const vec4& c1, const vec4& c2, const vec4& c3, const vec4& c4) {
		this->c1 = c1;
		this->c2 = c2;
		this->c3 = c3;
		this->c4 = c4;
		
	}
	mat4::mat4(const float& x1, const float& x2, const float& x3, const float& x4, const float& y1, const float& y2, const float& y3, const float& y4, const float& z1, const float& z2, const float& z3, const float& z4, const float& w1, const float& w2, const float& w3, const float& w4) {
		c1 = vec4(x1, y1, z1, w1);
		c2 = vec4(x2, y2, z2, w2);
		c3 = vec4(x3, y3, z3, w3);
		c4 = vec4(x4, y4, z4, w4);
		

	}


	mat4::mat4(const float& s) {
		c1 = vec4(s, 0, 0, 0);
		c2 = vec4(0, s, 0, 0);
		c3 = vec4(0, 0, s, 0);
		c4 = vec4(0, 0, 0, s);
	}

	mat4 mat4::orthographic(const float& r, const float& l, const float& t, const float& b, const float& n, const float& f) {
		mat4 resultat;
		resultat.c1 = vec4(2.0f / (r - l), 0, 0, 0);
		resultat.c2 = vec4(0, 2.0f / (t - b), 0, 0);
		resultat.c3 = vec4(0, 0, -2.0f / (f - n), 0);
		resultat.c4 = vec4((r + l) / (r - l), (t + b) / (t - b), (f + n) / (f - n), 1.0f);
		return resultat;
	}

	mat4 mat4::diag(const vec4& v) {
		return mat4(vec4(v.x, 0, 0, 0), vec4(0, v.y, 0, 0), vec4(0, 0, v.z, 0), vec4(0, 0, 0, v.w));
	}
	mat4 mat4::diag(const float& x, const float& y, const float& z, const float& w) {
		return mat4(vec4(x, 0, 0, 0), vec4(0, y, 0, 0), vec4(0, 0, z, 0), vec4(0, 0, 0, w));
	}
	mat4 mat4::identitee() {
		return mat4(vec4(1, 0, 0, 0), vec4(0, 1, 0, 0), vec4(0, 0, 1, 0), vec4(0, 0, 0, 1));
	}
	mat4 mat4::scalaire(const float& s) {
		return mat4::identitee() * s;
	}


	mat4 mat4::perspective(const float& fov, const float& aspect, const float& near, const float& far) {
		float tanHalfFov = tan(fov);
		//printf("tan fov : %f \n", tanHalfFov);
		mat4 result = mat4();
		result.c1.x = 1.0 / (aspect * tanHalfFov);
		result.c2.y = 1.0 / tanHalfFov;
		result.c3.z = -(far + near) / (far - near);
		result.c3.w = -1.0;
		result.c4.z = -(2.0 * far * near) / (far - near);
		return result;
	}
	vec3 vec3::cross(const vec3& v) const {
		return vec3(
			y * v.z - z * v.y,
			z * v.x - x * v.z,
			x * v.y - y * v.x
		);
	}

	mat4 mat4::view(vec3 eye, float pitch, float yaw) {
		float cosPitch = cos(pitch);
		float sinPitch = sin(pitch);
		float cosYaw   = cos(yaw);
		float sinYaw   = sin(yaw);
	

		vec3 forward(
			cosPitch * sinYaw,
			sinPitch,
			cosPitch * cosYaw
		);
	
		forward = forward.normalize(); 
	

		vec3 worldUp(0, 1, 0);
		vec3 right = worldUp.cross(forward).normalize();
	
	
		vec3 up = forward.cross(right);
	

		float tx = -right.dot(eye);
		float ty = -up.dot(eye);
		float tz = -forward.dot(eye);
	

		return mat4(
			right.x,   right.y,   right.z,   tx,
			up.x,      up.y,      up.z,      ty,
			forward.x, forward.y, forward.z, tz,
			0,         0,         0,         1.0f
		);
	}

	vec4 mat4::vecMulti(const vec4& v) {
		float x = c1.x * v.x + c2.x * v.y + c3.x * v.z + c4.x * v.w;
		float y = c1.y * v.x + c2.y * v.y + c3.y * v.z + c4.y * v.w;
		float z = c1.z * v.x + c2.z * v.y + c3.z * v.z + c4.z * v.w;
		float w = c1.w * v.x + c2.w * v.y + c3.w * v.z + c4.w * v.w;
		return vec4(x, y, z, w);
	}
	vec4 mat4::operator*(vec4& v) {
		return (*this).vecMulti(v);
	}

	mat4 mat4::transpose() {
		mat4 t;
		t.c1 = vec4(c1.x, c2.x, c3.x, c4.x);
		t.c2 = vec4(c1.y, c2.y, c3.y, c4.y);
		t.c3 = vec4(c1.z, c2.z, c3.z, c4.z);
		t.c4 = vec4(c1.w, c2.w, c3.w, c4.w);

		return t;
	}

	mat4 mat4::translation(const vec3& t) {
		mat4 trans = mat4::identitee();
		trans.c4 = vec4(t.x, t.y, t.z, 1);

		return trans;
	}
	
	mat4 mat4::rotation(const vec4& axis, const float& angle) {
		vec4 normAxis = axis.normalize();
		float cosA = cos(angle);
		float sinA = sin(angle);
		float oneMinusCosA = 1.0f - cosA;
		
		float x = normAxis.x;
		float y = normAxis.y;
		float z = normAxis.z;
		
		return mat4(
			cosA + x * x * oneMinusCosA,       x * y * oneMinusCosA - z * sinA, x * z * oneMinusCosA + y * sinA, 0,
			y * x * oneMinusCosA + z * sinA, cosA + y * y * oneMinusCosA,       y * z * oneMinusCosA - x * sinA, 0,
			z * x * oneMinusCosA - y * sinA, z * y * oneMinusCosA + x * sinA, cosA + z * z * oneMinusCosA,       0,
			0,                               0,                               0,                               1
		);
	}

	mat4 mat4::scale(const vec3& v){
		return diag(vec4(v.x, v.y, v.z, 1.0f));
	}

	mat4& mat4::add(const mat4& m) {
		c1 += m.c1;
		c2 += m.c2;
		c3 += m.c3;
		c4 += m.c4;
		return *this;
	}
	mat4& mat4::sub(const mat4& v) {
		c1 -= v.c1;
		c2 -= v.c2;
		c3 -= v.c3;
		c4 -= v.c4;
		return *this;
	}
	mat4& mat4::multi(const mat4& v) {
		vec4 newC1 = vecMulti(v.c1); // Replace with correct column computation
		vec4 newC2 = vecMulti(v.c2);
		vec4 newC3 = vecMulti(v.c3);
		vec4 newC4 = vecMulti(v.c4);
		c1 = newC1; 
		c2 = newC2; 
		c3 = newC3; 
		c4 = newC4;
		return *this;
	  }

	mat4 mat4::operator+(mat4 v) {
		return v.add(*this);
	}
	mat4 mat4::operator-(mat4 v) {
		return v.sub(*this);
	}
	mat4 mat4::operator*(mat4 v) {
		return v.multi(*this);
	}

	mat4& mat4::operator+=(const mat4& right) {
		return this->add(right);

	}
	mat4& mat4::operator-=(const mat4& right) {

		return this->sub(right);
	}
	mat4& mat4::operator*=(const mat4& right) {

		return this->multi(right);
	}

	//scalar op
	mat4& mat4::add(const float& s) {
		c1 += s;
		c2 += s;
		c3 += s;
		c4 += s;
		return *this;
	}
	mat4& mat4::sub(const float& s) {
		c1 -= s;
		c2 -= s;
		c3 -= s;
		c4 -= s;
		return *this;
	}
	mat4& mat4::multi(const float& s) {
		c1 *= s;
		c2 *= s;
		c3 *= s;
		c4 *= s;
		return *this;
	}
	mat4& mat4::divide(const float& s) {
		c1 /= s;
		c2 /= s;
		c3 /= s;
		c4 /= s;
		return *this;
	}
	//op scalar
	mat4 mat4::operator+(const float& s) {

		return mat4(c1 + s, c2 + s, c3 + s, c4 + s);
	}
	mat4 mat4::operator-(const float& s) {


		return mat4(c1 - s, c2 - s, c3 - s, c4 - s);
	}
	mat4 mat4::operator*(const float& s) {

		return mat4(c1 * s, c2 * s, c3 * s, c4 * s);
	}

	mat4 mat4::operator/(const float& s) {

		return mat4(c1 / s, c2 / s, c3 / s, c4 / s);
	}
	//op= scalar
	mat4& mat4::operator+=(const float& right) {

		return this->add(right);
	}
	mat4& mat4::operator-=(const float& right) {


		return this->sub(right);
	}
	mat4& mat4::operator*=(const float& right) {

		return this->multi(right);
	}

	mat4& mat4::operator/=(const float& right) {

		return this->divide(right);
	}

	void mat4::print() {
		for (int i = 0; 16 > i; i++) {
			printf("%f ", *(list + i));
			if ((i + 1) % 4 == 0) {
				printf("\n");
			}
		}
	}

}