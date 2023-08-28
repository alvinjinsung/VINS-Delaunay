#ifndef H_TRIANGLE
#define H_TRIANGLE

#include "numeric.h"
#include "vector2.h"
#include "edge.h"
#include <algorithm>

namespace dt {

template<typename T>
struct Triangle
{
	using Type = T;
	using VertexType = Vector2<Type>;
	using EdgeType = Edge<Type>;

	Triangle() = default;
	Triangle(const Triangle&) = default;
	Triangle(Triangle&&) = default;
	Triangle(const VertexType &v1, const VertexType &v2, const VertexType &v3);

	bool containsVertex(const VertexType &v) const;
	bool circumCircleContains(const VertexType &v) const;

	Triangle &operator=(const Triangle&) = default;
	Triangle &operator=(Triangle&&) = default;
	bool operator ==(const Triangle &t) const;

	template<typename U>
	friend std::ostream &operator <<(std::ostream &str, const Triangle<U> &t);

	const VertexType *a;
	const VertexType *b;
	const VertexType *c;
	bool isBad = false;

	VertexType circumcenter();

	static_assert(std::is_floating_point<Triangle<T>::Type>::value,
		"Type must be floating-point");
};

template<typename T>
bool almost_equal(const Triangle<T> &t1, const Triangle<T> &t2)
{
	return	(almost_equal(*t1.a , *t2.a) || almost_equal(*t1.a , *t2.b) || almost_equal(*t1.a , *t2.c)) &&
			(almost_equal(*t1.b , *t2.a) || almost_equal(*t1.b , *t2.b) || almost_equal(*t1.b , *t2.c)) &&
			(almost_equal(*t1.c , *t2.a) || almost_equal(*t1.c , *t2.b) || almost_equal(*t1.c , *t2.c));
}

template<typename T>
bool CheckSkinnyTriangle(const Triangle<T> &t)
{
	T ax = static_cast<float>(t.a->x);
	T ay = static_cast<float>(t.a->y);
	T bx = static_cast<float>(t.b->x);
	T by = static_cast<float>(t.b->y);
	T cx = static_cast<float>(t.c->x);
	T cy = static_cast<float>(t.c->y);

	//std::cout << "\033[1;32m ax: " << ax << "\033[0m\n " << std::endl;
	//std::cout << "\033[1;32m ay: " << ay << "\033[0m\n " << std::endl;
	//std::cout << "\033[1;32m bx: " << bx << "\033[0m\n " << std::endl;
	//std::cout << "\033[1;32m by: " << by << "\033[0m\n " << std::endl;
	//std::cout << "\033[1;32m cx: " << cx << "\033[0m\n " << std::endl;
	//std::cout << "\033[1;32m cy: " << cy << "\033[0m\n " << std::endl;

	T v1_x = bx - ax;
	T v1_y = by - ay;
	T v2_x = cx - bx;
	T v2_y = cy - by;
	T v3_x = ax - cx;
	T v3_y = ay - cy;

	double theta_1 = (v1_x * v2_x + v1_y * v2_y) / ((v1_x * v1_x + v1_y * v1_y) * (v2_x * v2_x + v2_y * v2_y));
	theta_1  = std::min(theta_1, M_PI - theta_1);
	double theta_1_degree = theta_1 * (180.0 / M_PI);

	double theta_2 = (v2_x * v3_x + v2_y * v3_y) / ((v2_x * v2_x + v2_y * v2_y) * (v3_x * v3_x + v3_y * v3_y));
	theta_2  = std::min(theta_2, M_PI - theta_2);
	double theta_2_degree = theta_2 * (180.0 / M_PI);

	double theta_3 = (v3_x * v1_x + v3_y * v1_y) / ((v3_x * v3_x + v3_y * v3_y) * (v1_x * v1_x + v1_y * v1_y));
	theta_3  = std::min(theta_3, M_PI - theta_3);
	double theta_3_degree = theta_3 * (180.0 / M_PI);

	//std::cout << "\033[1;32m theta 1: " << theta_1_degree << "\033[0m\n " << std::endl;
	//std::cout << "\033[1;32m theta 2: " << theta_2_degree << "\033[0m\n " << std::endl;
	//std::cout << "\033[1;32m theta 3: " << theta_3_degree << "\033[0m\n " << std::endl;

	/*double theta_1 = acos(((bx-ax)*(cx-bx) + (by-ay)*(cy-by)) / (((bx-ax)*(bx-ax) + (by-ay)*(by-ay)) * ((cx-bx)*(cx-bx) + (cy-by)*(cy-by))));
	theta_1 = std::min(theta_1, M_PI - theta_1);
	double theta_1_degree = theta_1 * (180.0 / M_PI);

	std::cout << "\033[1;32m theta 1: " << theta_1_degree << "\033[0m\n " << std::endl;

	double theta_2 = acos(((cx-bx)*(ax-cx) + (cy-by)*(ay-cy)) / (((cx-bx)*(cx-bx) + (cy-by)*(cy-by)) * ((ax-cx)*(ax-cx) + (ay-cy)*(ay-cy))));
	theta_2 = std::min(theta_2, M_PI - theta_2);
	double theta_2_degree = theta_2 * (180.0 / M_PI);

	std::cout << "\033[1;32m theta 2: " << theta_2_degree << "\033[0m\n " << std::endl;

	double theta_3 = acos(((ax-cx)*(bx-ax) + (ay-cy)*(by-ay)) / (((ax-cx)*(ax-cx) + (ay-cy)*(ay-cy)) * ((bx-ax)*(bx-ax) + (by-ay)*(by-ay))));
	theta_3 = std::min(theta_3, M_PI - theta_3);
	double theta_3_degree = theta_3 * (180.0 / M_PI);

	std::cout << "\033[1;32m theta 3: " << theta_3_degree << "\033[0m\n " << std::endl;*/

	if ((theta_1_degree < 25) || (theta_2_degree < 25) || (theta_3_degree < 25))
	{
		return true;
	}

	return false;
}

template<typename T>
typename Triangle<T>::VertexType circumcenter(const Triangle<T> &t)
{
	T ab = t.a->norm2();
	T cd = t.b->norm2();
	T ef = t.c->norm2();

	T ax = t.a->x;
	T ay = t.a->y;
	T bx = t.b->x;
	T by = t.b->y;
	T cx = t.c->x;
	T cy = t.c->y;

	T circum_x = (ab * (cy - by) + cd * (ay - cy) + ef * (by - ay)) / (ax * (cy - by) + bx * (ay - cy) + cx * (by - ay));
	T circum_y = (ab * (cx - bx) + cd * (ax - cx) + ef * (bx - ax)) / (ay * (cx - bx) + by * (ax - cx) + cy * (bx - ax));

	Vector2<T> circum(circum_x / 2, circum_y / 2);
	return circum;
}

} // namespace dt

//bool CheckSkinnyTriangle();

//VertexType circumcenter();

#endif

