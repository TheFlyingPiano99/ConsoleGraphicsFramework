#pragma once

#include <math.h>


namespace VectorAlgebra {
	
	struct IVec2;

	/*
	* 2D float vector
	*/
	struct Vec2 {
		float x;
		float y;

		Vec2();

		Vec2(const Vec2& v);

		Vec2(IVec2 iv);

		Vec2(float _xy);

		Vec2(float _x, float _y);
	};

	// Operator overrides:--------------------------

	inline constexpr float comparisonBias = 0.0001f;

	inline bool operator==(Vec2 a, Vec2 b) {
		return a.x < b.x + comparisonBias && a.y < b.y + comparisonBias
			&& a.x > b.x - comparisonBias && a.y > b.y - comparisonBias;
	}

	inline bool operator!=(Vec2 a, Vec2 b) {
		return !(a == b);
	}

	inline Vec2 operator+(const Vec2& a, const Vec2& b) {
		Vec2 res;
		res.x = a.x + b.x;
		res.y = a.y + b.y;
		return res;
	}

	inline Vec2 operator-(const Vec2& a, const Vec2& b) {
		Vec2 res;
		res.x = a.x - b.x;
		res.y = a.y - b.y;
		return res;
	}

	inline Vec2 operator*(const Vec2& a, const Vec2& b) {
		Vec2 res;
		res.x = a.x * b.x;
		res.y = a.y * b.y;
		return res;
	}

	inline Vec2 operator*(const Vec2& a, float b) {
		Vec2 res;
		res.x = a.x * b;
		res.y = a.y * b;
		return res;
	}

	inline Vec2 operator*(float b, const Vec2& a) {
		Vec2 res;
		res.x = a.x * b;
		res.y = a.y * b;
		return res;
	}

	// -------------------------------------------

	inline Vec2& operator+=(Vec2& a, const Vec2& b) {
		a.x += b.x;
		a.y += b.y;
		return a;
	}

	inline Vec2& operator-=(Vec2& a, const Vec2& b) {
		a.x -= b.x;
		a.y -= b.y;
		return a;
	}

	inline Vec2& operator*=(Vec2& a, const Vec2& b) {
		a.x *= b.x;
		a.y *= b.y;
		return a;
	}

	inline Vec2 operator*=(Vec2& a, float b) {
		a.x *= b;
		a.y *= b;
		return a;
	}

	/*
	* 2D vektorok osszege
	*/
	inline Vec2 sum(const Vec2& a, const Vec2& b) {
		Vec2 res;
		res.x = a.x + b.x;
		res.y = a.y + b.y;
		return a;
	}

	/*
	* 2D vektor negaltja
	*/
	inline Vec2 neg(Vec2 v) {
		v.x = -v.x;
		v.y = -v.y;
		return v;
	}

	/*
	* Skalar es 2D vektor szorzata
	*/
	inline Vec2 mul(float f, Vec2 v) {
		v.x *= f;
		v.y *= f;
		return v;
	}

	/*
	* 2D vektorok skalar / pont szorzata
	*/
	inline float dot(Vec2 a, Vec2 b) {
		return a.x * b.x + a.y * b.y;
	}

	/*
	* 2D vektorok kereszt szorzata
	*/
	inline float cross(Vec2 a, Vec2 b) {
		return a.x * b.y - a.y * b.x;
	}

	/*
	* 2D pontok tavolsaga
	*/
	inline float distance(Vec2 a, Vec2 b) {
		float dx = a.x - b.x;
		float dy = a.y - b.y;
		return sqrtf(dx * dx + dy * dy);
	}

	/*
	* 2D vektor hossza
	*/
	inline float length(Vec2 v) {
		return sqrtf(v.x * v.x + v.y * v.y);
	}

	/*
	* 2D vektor normalizaltja
	* Azonos iranyu, egyseg hosszu vektor.
	*/
	inline Vec2 normal(Vec2 v) {
		float l = length(v);
		v.x /= l;
		v.y /= l;
		return v;
	}

	//------------------------------------------------
	// Integer vector:

	struct IVec2 {
		IVec2() {
			x = 0;
			y = 0;
		}

		IVec2(int _xy) {
			x = _xy;
			y = _xy;
		}

		IVec2(int _x, int _y) {
			x = _x;
			y = _y;
		}

		IVec2(const IVec2& iv);

		IVec2(Vec2 v);

		int x;
		int y;
	};

	inline bool operator==(IVec2 a, IVec2 b) {
		return a.x == b.x && a.y == b.y;
	}

	inline bool operator!=(IVec2 a, IVec2 b) {
		return !(a == b);
	}

	/*
	* Ket 2D integer vektor tavolsaga
	*/
	inline float distance(IVec2 a, IVec2 b) {
		int dx = a.x - b.x;
		int dy = a.y - b.y;
		return sqrtf((float)(dx * dx + dy * dy));
	}


	// ---------------------------------------------------
	// Type conversion:

	/*
	* Integer 2D vektor floatta alakitasa
	*/
	inline Vec2 int2float(IVec2 iv) {
		Vec2 res;
		res.x = (float)iv.x;
		res.y = (float)iv.y;
		return res;
	}

	/*
	* Float 2D vektor integerre alakitasa
	*/
	inline IVec2 float2int(Vec2 fv) {
		IVec2 res;
		res.x = (int)fv.x;
		res.y = (int)fv.y;
		return res;
	}

// ---------------------------------------------------------

	/*
	* 3D float vector
	*/
	struct Vec3 {
		float x;
		float y;
		float z;

		Vec3();

		Vec3(const Vec2& v);

		Vec3(const Vec3& v);

		Vec3(IVec2 iv);

		Vec3(float _xyz);

		Vec3(float _x, float _y, float _z);
	};

	// Operator overrides:--------------------------

	inline bool operator==(Vec3 a, Vec3 b) {
		return a.x < b.x + comparisonBias && a.y < b.y + comparisonBias && a.z < b.z + comparisonBias
			&& a.x > b.x - comparisonBias && a.y > b.y - comparisonBias && a.z > b.z - comparisonBias;
	}

	inline bool operator!=(Vec3 a, Vec3 b) {
		return !(a == b);
	}

	inline Vec3 operator+(const Vec3& a, const Vec3& b) {
		return Vec3{ a.x + b.x, a.y + b.y, a.y + b.y };
	}	
		
	inline Vec3 operator-(const Vec3& a, const Vec3& b) {
		return Vec3{ a.x - b.x , a.y - b.y, a.z - b.z };
	}

	inline Vec3 operator*(const Vec3& a, const Vec3& b) {
		return Vec3{ a.x * b.x , a.y * b.y, a.z * b.z };
	}

	inline Vec3 operator*(const Vec3& a, float b) {
		return Vec3{ a.x * b , a.y * b, a.z * b };
	}

	inline Vec3 operator*(float b, const Vec3& a) {
		return Vec3{ a.x * b , a.y * b, a.z * b };
	}

	// -------------------------------------------

	inline Vec3& operator+=(Vec3& a, const Vec3& b) {
		a.x += b.x;
		a.y += b.y;
		a.z += b.z;
		return a;
	}

	inline Vec3& operator-=(Vec3& a, const Vec3& b) {
		a.x -= b.x;
		a.y -= b.y;
		a.z -= b.z;
		return a;
	}

	inline Vec3& operator*=(Vec3& a, const Vec3& b) {
		a.x *= b.x;
		a.y *= b.y;
		a.z *= b.z;
		return a;
	}

	inline Vec3& operator*=(Vec3& a, float b) {
		a.x *= b;
		a.y *= b;
		a.z *= b;
		return a;
	}

	/*
	* 3D vektorok osszege
	*/
	inline Vec3 sum(const Vec3& a, const Vec3& b) {
		return Vec3{ a.x + b.x, a.y + b.y, a.y + b.y };

	}

	/*
	* 3D vektor negaltja
	*/
	inline Vec3 neg(const Vec3& v) {
		return Vec3{ -v.x, -v.y, -v.y };
	}

	/*
	* 3D vektorok skalar / pont szorzata
	*/
	inline float dot(const Vec3& a, const Vec3& b) {
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}

	/*
	* 3D vektorok kereszt szorzata
	*/
	inline Vec3 cross(const Vec3& a, const Vec3& b) {
		return Vec3{ 
			a.y * b.z - a.z * b.y, 
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x 
		};
	}

	/*
	* 3D pontok tavolsaga
	*/
	inline float distance(const Vec3& a, const Vec3& b) {
		float dx = a.x - b.x;
		float dy = a.y - b.y;
		float dz = a.z - b.z;
		return sqrtf(dx * dx + dy * dy + dz * dz);
	}

	/*
	* 3D vektor hossza
	*/
	inline float length(const Vec3& v) {
		return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
	}

	/*
	* 3D vektor normalizaltja
	* Azonos iranyu, egyseg hosszu vektor.
	*/
	inline Vec3 normal(const Vec3& v) {
		float l = length(v);
		return Vec3{ v.x / l, v.y / l, v.z / l };
	}

	// ----------------------------------------------------
	
	struct Complex {
		float re;
		float im;
		
		Complex();

		Complex(float _re);

		Complex(float _re, float _im);

		explicit Complex(const Vec2& v);
	
		float amplitude() {
			return sqrtf(re * re + im * im);
		}

		float angle() {
			return atanf(im / re );
		}
	};

	inline Complex fromEuler(float amplitude, float angle) {
		return Complex{ amplitude * cosf(angle), amplitude * sinf(angle) };
	}

	inline Complex conjugate(const Complex& c) {
		return Complex{ c.re, -c.im };
	}

	inline Complex operator+(const Complex& a, const Complex& b) {
		return Complex{ a.re + b.re, a.im + b.im };
	}

	inline Complex operator-(const Complex& a, const Complex& b) {
		return Complex{ a.re - b.re, a.im - b.im };
	}

	inline Complex operator*(const Complex& a, const Complex& b) {
		return Complex{ 
			a.re * b.re - a.im * b.im,
			a.re * b.im + a.im * b.re 
		};
	}

	inline Complex operator/(const Complex& a, const Complex& b) {
		float divider = b.re * b.re + b.im * b.im;
		return Complex{ 
			(a.re * b.re + a.im * b.im ) / divider, 
			(a.im * b.re - a.re * b.im) / divider 
		};
	}

}

