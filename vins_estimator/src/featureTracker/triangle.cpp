#include "triangle.h"

namespace dt {

template<typename T>
Triangle<T>::Triangle(const VertexType &v1, const VertexType &v2, const VertexType &v3) :
	a(&v1), b(&v2), c(&v3), isBad(false)
{}

template<typename T>
bool
Triangle<T>::containsVertex(const VertexType &v) const
{
	// return p1 == v || p2 == v || p3 == v;
	return almost_equal(*a, v) || almost_equal(*b, v) || almost_equal(*c, v);
}

template<typename T>
bool
Triangle<T>::circumCircleContains(const VertexType &v) const
{
	const T ab = a->norm2();
	const T cd = b->norm2();
	const T ef = c->norm2();

	const T ax = a->x;
	const T ay = a->y;
	const T bx = b->x;
	const T by = b->y;
	const T cx = c->x;
	const T cy = c->y;

	const T circum_x = (ab * (cy - by) + cd * (ay - cy) + ef * (by - ay)) / (ax * (cy - by) + bx * (ay - cy) + cx * (by - ay));
	const T circum_y = (ab * (cx - bx) + cd * (ax - cx) + ef * (bx - ax)) / (ay * (cx - bx) + by * (ax - cx) + cy * (bx - ax));

	const VertexType circum(circum_x / 2, circum_y / 2);
	const T circum_radius = a->dist2(circum);
	const T dist = v.dist2(circum);
	return dist <= circum_radius;
}

/*template<typename T>
typename Triangle<T>::VertexType
Triangle<T>::circumcenter()
{
	T ab = a->norm2();
	T cd = b->norm2();
	T ef = c->norm2();

	T ax = a->x;
	T ay = a->y;
	T bx = b->x;
	T by = b->y;
	T cx = c->x;
	T cy = c->y;

	T circum_x = (ab * (cy - by) + cd * (ay - cy) + ef * (by - ay)) / (ax * (cy - by) + bx * (ay - cy) + cx * (by - ay));
	T circum_y = (ab * (cx - bx) + cd * (ax - cx) + ef * (bx - ax)) / (ay * (cx - bx) + by * (ax - cx) + cy * (bx - ax));

	VertexType circum(circum_x / 2, circum_y / 2);
	return circum;
}*/


/*template<typename T>
bool
Triangle<T>::CheckSkinnyTriangle()
{
	T ax = a->x;
	T ay = a->y;
	T bx = b->x;
	T by = b->y;
	T cx = c->x;
	T cy = c->y;

	double theta_1 = acos(((bx-ax)*(cx-bx) + (by-ay)*(cy-by)) / ((bx-ax)*(bx-ax) + (by-ay)*(by-ay)) * ((cx-bx)*(cx-bx) + (cy-by)*(cy-by)));
	theta_1 = std::min(theta_1, M_PI - theta_1);
	double theta_1_degree = theta_1 * 180 / M_PI;

	double theta_2 = acos(((cx-bx)*(ax-cx) + (cy-by)*(ay-cy)) / ((cx-bx)*(cx-bx) + (cy-by)*(cy-by)) * ((ax-cx)*(ax-cx) + (ay-cy)*(ay-cy)));
	theta_2 = std::min(theta_2, M_PI - theta_2);
	double theta_2_degree = theta_2 * 180 / M_PI;

	double theta_3 = acos(((ax-cx)*(bx-ax) + (ay-cy)*(by-ay)) / ((ax-cx)*(ax-cx) + (ay-cy)*(ay-cy)) * ((bx-ax)*(bx-ax) + (by-ay)*(by-ay)));
	theta_3 = std::min(theta_3, M_PI - theta_3);
	double theta_3_degree = theta_3 * 180 / M_PI;

	if ((theta_1_degree < 25) || (theta_2_degree < 25) || (theta_3_degree < 25))
	{
		return true;
	}

	return false;
}*/

template<typename T>
bool
Triangle<T>::operator ==(const Triangle &t) const
{
	return	(*this->a == *t.a || *this->a == *t.b || *this->a == *t.c) &&
			(*this->b == *t.a || *this->b == *t.b || *this->b == *t.c) &&
			(*this->c == *t.a || *this->c == *t.b || *this->c == *t.c);
}



template<typename U>
std::ostream&
operator <<(std::ostream &str, const Triangle<U> &t)
{
	return str << "Triangle:" << "\n\t" <<
			*t.a << "\n\t" <<
			*t.b << "\n\t" <<
			*t.c << '\n';
}

template struct Triangle<float>;
template struct Triangle<double>;

} // namespace dt


/*
template<typename T>
typename Triangle<T>::VertexType
Triangle<T>::circumcenter()
{
	T ab = a->norm2();
	T cd = b->norm2();
	T ef = c->norm2();

	T ax = a->x;
	T ay = a->y;
	T bx = b->x;
	T by = b->y;
	T cx = c->x;
	T cy = c->y;

	T circum_x = (ab * (cy - by) + cd * (ay - cy) + ef * (by - ay)) / (ax * (cy - by) + bx * (ay - cy) + cx * (by - ay));
	T circum_y = (ab * (cx - bx) + cd * (ax - cx) + ef * (bx - ax)) / (ay * (cx - bx) + by * (ax - cx) + cy * (bx - ax));

	VertexType circum(circum_x / 2, circum_y / 2);
	return circum;
}

template<typename T>
bool
Triangle<T>::CheckSkinnyTriangle()
{
	T ax = a->x;
	T ay = a->y;
	T bx = b->x;
	T by = b->y;
	T cx = c->x;
	T cy = c->y;

	double theta_1 = acos(((bx-ax)*(cx-bx) + (by-ay)*(cy-by)) / ((bx-ax)*(bx-ax) + (by-ay)*(by-ay)) * ((cx-bx)*(cx-bx) + (cy-by)*(cy-by)));
	theta_1 = std::min(theta_1, M_PI - theta_1);
	double theta_1_degree = theta_1 * 180 / M_PI;

	double theta_2 = acos(((cx-bx)*(ax-cx) + (cy-by)*(ay-cy)) / ((cx-bx)*(cx-bx) + (cy-by)*(cy-by)) * ((ax-cx)*(ax-cx) + (ay-cy)*(ay-cy)));
	theta_2 = std::min(theta_2, M_PI - theta_2);
	double theta_2_degree = theta_2 * 180 / M_PI;

	double theta_3 = acos(((ax-cx)*(bx-ax) + (ay-cy)*(by-ay)) / ((ax-cx)*(ax-cx) + (ay-cy)*(ay-cy)) * ((bx-ax)*(bx-ax) + (by-ay)*(by-ay)));
	theta_3 = std::min(theta_3, M_PI - theta_3);
	double theta_3_degree = theta_3 * 180 / M_PI;

	if ((theta_1_degree < 25) || (theta_2_degree < 25) || (theta_3_degree < 25))
	{
		return true;
	}

	return false;
}*/