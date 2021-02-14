#include "Matrix33d.h"

Matrix33d::Matrix33d()
{

}

Matrix33d::Matrix33d(double a11, double a12, double a13,
	double a21, double a22, double a23,
	double a31, double a32, double a33)
{
	row1 = Vector3d(a11, a12, a13);
	row2 = Vector3d(a21, a22, a23);
	row3 = Vector3d(a31, a32, a33);
}

Matrix33d::Matrix33d(const Vector3d& row1, const Vector3d& row2, const Vector3d& row3)
{
	this->row1 = row1;
	this->row2 = row2;
	this->row3 = row3;
}

const Vector3d& Matrix33d::getRow1() const
    {

        return row1;
    }
 

const Vector3d& Matrix33d::getRow2() const
    {

        return row2;
    }
 

const Vector3d& Matrix33d::getRow3() const
    {

        return row3;
    }

Matrix33d Matrix33d::scaledBy(double scale) const
{
	return Matrix33d(row1.ScalarMultiplication(scale),
		row2.ScalarMultiplication(scale),
		row3.ScalarMultiplication(scale));
}

Matrix33d Matrix33d::Add(const Matrix33d &m) const
{
	return Matrix33d(row1.add(m.getRow1()), row2.add(m.getRow2()), row3.add(m.getRow3()));
}

Matrix33d Matrix33d::Subtract(const Matrix33d &m) const
{
	return Matrix33d(row1.subtract(m.getRow1()), row2.subtract(m.getRow2()), row3.subtract(m.getRow3()));
}