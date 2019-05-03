#include "area.h"

#include <cmath>

using namespace LRender;

float Area::triangle(
	const Vector &a,
	const Vector &b,
	const Vector &c) {
	const auto la = (b - a).length();
	const auto lb = (b - c).length();
	const auto lc = (a - c).length();
	const auto p = (la + lb + lc) * 0.5f;
	const auto x = p * (p - la) * (p - lb) * (p - lc);

	if(x < 0)
		return 0;

	return sqrt(x);
}
