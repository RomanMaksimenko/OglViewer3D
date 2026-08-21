#include "MathUtils.h"

#include <cmath>
#include <numbers>


namespace AngleUtils
{
// Перевод угла в градусах в радианы
float ToDegree(float angleRad)
{
  return (angleRad * std::numbers::pi) / 180.0f;
}

// Перевод угла в градусах в радианы
float ToRadians(float angleDeg)
{
  return angleDeg *std::numbers::pi / 180.0f;
}

} // namespace AngleUtils
