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
