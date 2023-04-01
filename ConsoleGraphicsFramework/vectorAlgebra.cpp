#include "vectorAlgebra.h"

VectorAlgebra::Vec2::Vec2() : x(0.0f), y(0.0f) {
}

VectorAlgebra::Vec2::Vec2(const Vec2& v) : x(v.x), y(v.y)
{
}

VectorAlgebra::Vec2::Vec2(IVec2 iv) : x((float)iv.x), y((float)iv.y)
{
}

VectorAlgebra::Vec2::Vec2(float _xy) : x(_xy), y(_xy) {
}

VectorAlgebra::Vec2::Vec2(float _x, float _y) : x(_x), y(_y) {
}

VectorAlgebra::IVec2::IVec2(const IVec2& iv) : x(iv.x), y(iv.y)
{
}

VectorAlgebra::IVec2::IVec2(Vec2 v) : x((int)v.x), y((int)v.y)
{
}

VectorAlgebra::Vec3::Vec3() : x(0.0f), y(0.0f), z(0.0f)
{
}

VectorAlgebra::Vec3::Vec3(const Vec2& v) : x(v.x), y(v.y), z(0.0f)
{
}

VectorAlgebra::Vec3::Vec3(const Vec3& v) : x(v.x), y(v.y), z(v.z)
{
}

VectorAlgebra::Vec3::Vec3(IVec2 iv) : x(iv.x), y(iv.y), z(0.0f)
{
}

VectorAlgebra::Vec3::Vec3(float _xyz) : x(_xyz), y(_xyz), z(_xyz)
{
}

VectorAlgebra::Vec3::Vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z)
{
}

VectorAlgebra::Complex::Complex() : re(0.0f), im(0.0f)
{
}

VectorAlgebra::Complex::Complex(float _re) : re(_re), im(0.0f)
{
}

VectorAlgebra::Complex::Complex(float _re, float _im) : re(_re), im(_im)
{
}

VectorAlgebra::Complex::Complex(const Vec2& v) : re(v.x), im(v.y)
{
}
