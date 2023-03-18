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

	constexpr const float comparisonBias = 0.0001f;
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
}