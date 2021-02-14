#pragma once
#include <vector>
#include <iostream>
#include <windows.h>		// Header File For Windows
#include <stdio.h>
#include <cmath>

using namespace std;

class Vector3d
{
private:
    double x, y, z;

public:
	Vector3d(void);
	~Vector3d(void);
	Vector3d(double x, double y, double z);

	Vector3d add(const Vector3d& v) const;
	Vector3d subtract(const Vector3d& v) const;
	Vector3d Normalise() const;
	Vector3d ScalarMultiplication(const double &ScalarFactor) const;
	Vector3d crossProduct(const Vector3d& v) const;
	Vector3d operator*(const double &input) const;
	Vector3d operator*(const Vector3d &input) const;
	Vector3d operator-(const Vector3d &input) const;
	Vector3d operator+(const Vector3d &input) const;

	double CalculateMagnitude() const;
	double dotProduct(const Vector3d& v) const;

	void SetVector(const double &newX, const double &newY, const double &newZ);
	void SetVectorX(const double &newX);
	void SetVectorY(const double &newY);
	void SetVectorZ(const double &newZ);

	double X() const;
    double Y() const;
    double Z() const;
};
