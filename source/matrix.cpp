#include "matrix.h"

fMatrix4 Matrix::transpose(fMatrix4 matrix)
{
    fMatrix4 result;

    result.m[0][0] = matrix.m[0][0];
    result.m[0][1] = matrix.m[1][0];
    result.m[0][2] = matrix.m[2][0];
    result.m[0][3] = matrix.m[3][0];

    result.m[1][0] = matrix.m[0][1];
    result.m[1][1] = matrix.m[1][1];
    result.m[1][2] = matrix.m[2][1];
    result.m[1][3] = matrix.m[3][1];

    result.m[2][0] = matrix.m[0][2];
    result.m[2][1] = matrix.m[1][2];
    result.m[2][2] = matrix.m[2][2];
    result.m[2][3] = matrix.m[3][2];

    result.m[3][0] = matrix.m[0][3];
    result.m[3][1] = matrix.m[1][3];
    result.m[3][2] = matrix.m[2][3];
    result.m[3][3] = matrix.m[3][3];

    return result;
}

fMatrix4 Matrix::translate(fMatrix4 matrix, dVector3 vector)
{
    fMatrix4 result = matrix;

    result.m[3][0] += vector.x;
    result.m[3][1] += vector.y;
    result.m[3][2] += vector.z;

    return result;
}

fMatrix4 Matrix::add(fMatrix4 matrix1, fMatrix4 matrix2)
{
    matrix1.m[0][0] += matrix2.m[0][0];
    matrix1.m[0][1] += matrix2.m[0][1];
    matrix1.m[0][2] += matrix2.m[0][2];
    matrix1.m[0][3] += matrix2.m[0][3];

    matrix1.m[1][0] += matrix2.m[1][0];
    matrix1.m[1][1] += matrix2.m[1][1];
    matrix1.m[1][2] += matrix2.m[1][2];
    matrix1.m[1][3] += matrix2.m[1][3];

    matrix1.m[2][0] += matrix2.m[2][0];
    matrix1.m[2][1] += matrix2.m[2][1];
    matrix1.m[2][2] += matrix2.m[2][2];
    matrix1.m[2][3] += matrix2.m[2][3];

    matrix1.m[3][0] += matrix2.m[3][0];
    matrix1.m[3][1] += matrix2.m[3][1];
    matrix1.m[3][2] += matrix2.m[3][2];
    matrix1.m[3][3] += matrix2.m[3][3];

    return matrix1;
}

fMatrix4 Matrix::multiply(fMatrix4 matrix1, fMatrix4 matrix2)
{
    fMatrix4 result;

    result.m[0][0] = matrix1.m[0][0] * matrix2.m[0][0] + matrix1.m[0][1] * matrix2.m[1][0] + matrix1.m[0][2] * matrix2.m[2][0] + matrix1.m[0][3] * matrix2.m[3][0];
    result.m[0][1] = matrix1.m[0][0] * matrix2.m[0][1] + matrix1.m[0][1] * matrix2.m[1][1] + matrix1.m[0][2] * matrix2.m[2][1] + matrix1.m[0][3] * matrix2.m[3][1];
    result.m[0][2] = matrix1.m[0][0] * matrix2.m[0][2] + matrix1.m[0][1] * matrix2.m[1][2] + matrix1.m[0][2] * matrix2.m[2][2] + matrix1.m[0][3] * matrix2.m[3][2];
    result.m[0][3] = matrix1.m[0][0] * matrix2.m[0][3] + matrix1.m[0][1] * matrix2.m[1][3] + matrix1.m[0][2] * matrix2.m[2][3] + matrix1.m[0][3] * matrix2.m[3][3];

    result.m[1][0] = matrix1.m[1][0] * matrix2.m[0][0] + matrix1.m[1][1] * matrix2.m[1][0] + matrix1.m[1][2] * matrix2.m[2][0] + matrix1.m[1][3] * matrix2.m[3][0];
    result.m[1][1] = matrix1.m[1][0] * matrix2.m[0][1] + matrix1.m[1][1] * matrix2.m[1][1] + matrix1.m[1][2] * matrix2.m[2][1] + matrix1.m[1][3] * matrix2.m[3][1];
    result.m[1][2] = matrix1.m[1][0] * matrix2.m[0][2] + matrix1.m[1][1] * matrix2.m[1][2] + matrix1.m[1][2] * matrix2.m[2][2] + matrix1.m[1][3] * matrix2.m[3][2];
    result.m[1][3] = matrix1.m[1][0] * matrix2.m[0][3] + matrix1.m[1][1] * matrix2.m[1][3] + matrix1.m[1][2] * matrix2.m[2][3] + matrix1.m[1][3] * matrix2.m[3][3];

    result.m[2][0] = matrix1.m[2][0] * matrix2.m[0][0] + matrix1.m[2][1] * matrix2.m[1][0] + matrix1.m[2][2] * matrix2.m[2][0] + matrix1.m[2][3] * matrix2.m[3][0];
    result.m[2][1] = matrix1.m[2][0] * matrix2.m[0][1] + matrix1.m[2][1] * matrix2.m[1][1] + matrix1.m[2][2] * matrix2.m[2][1] + matrix1.m[2][3] * matrix2.m[3][1];
    result.m[2][2] = matrix1.m[2][0] * matrix2.m[0][2] + matrix1.m[2][1] * matrix2.m[1][2] + matrix1.m[2][2] * matrix2.m[2][2] + matrix1.m[2][3] * matrix2.m[3][2];
    result.m[2][3] = matrix1.m[2][0] * matrix2.m[0][3] + matrix1.m[2][1] * matrix2.m[1][3] + matrix1.m[2][2] * matrix2.m[2][3] + matrix1.m[2][3] * matrix2.m[3][3];

    result.m[3][0] = matrix1.m[3][0] * matrix2.m[0][0] + matrix1.m[3][1] * matrix2.m[1][0] + matrix1.m[3][2] * matrix2.m[2][0] + matrix1.m[3][3] * matrix2.m[3][0];
    result.m[3][1] = matrix1.m[3][0] * matrix2.m[0][1] + matrix1.m[3][1] * matrix2.m[1][1] + matrix1.m[3][2] * matrix2.m[2][1] + matrix1.m[3][3] * matrix2.m[3][1];
    result.m[3][2] = matrix1.m[3][0] * matrix2.m[0][2] + matrix1.m[3][1] * matrix2.m[1][2] + matrix1.m[3][2] * matrix2.m[2][2] + matrix1.m[3][3] * matrix2.m[3][2];
    result.m[3][3] = matrix1.m[3][0] * matrix2.m[0][3] + matrix1.m[3][1] * matrix2.m[1][3] + matrix1.m[3][2] * matrix2.m[2][3] + matrix1.m[3][3] * matrix2.m[3][3];

    return result;
}

fMatrix4 Matrix::scale(fMatrix4 matrix, dVector3 vector)
{
    fMatrix4 result = matrix;

    result.m[0][0] *= vector.x;
    result.m[1][1] *= vector.y;
    result.m[2][2] *= vector.z;

    return result;
}

fMatrix4 Matrix::rotate(fMatrix4 matrix, double xAngle, double yAngle, double zAngle)
{
    fMatrix4 result;
    fMatrix4 matrixX;
    fMatrix4 matrixY;
    fMatrix4 matrixZ;

    matrixX.identity();
    matrixY.identity();
    matrixZ.identity();

    matrixX.m[1][1] = cos(xAngle);
    matrixX.m[1][2] = sin(xAngle);
    matrixX.m[2][1] = -sin(xAngle);
    matrixX.m[2][2] = cos(xAngle);

    matrixY.m[0][0] = cos(yAngle);
    matrixY.m[0][2] = -sin(yAngle);
    matrixY.m[2][0] = sin(yAngle);
    matrixY.m[2][2] = cos(yAngle);

    matrixZ.m[0][0] = cos(zAngle);
    matrixZ.m[0][1] = sin(zAngle);
    matrixZ.m[1][0] = -sin(zAngle);
    matrixZ.m[1][1] = cos(zAngle);

    matrix = Matrix::multiply(matrixX, matrixY);
    matrix = Matrix::multiply(matrix, matrixZ);

    return Matrix::multiply(matrix, result);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// fMatrix4

fMatrix4::fMatrix4()
{
    empty();
}

fMatrix4::fMatrix4(std::vector<std::vector<double>> matrix)
{
    m[0][0] = matrix[0][0];
    m[0][1] = matrix[0][1];
    m[0][2] = matrix[0][2];
    m[0][3] = matrix[0][3];

    m[1][0] = matrix[1][0];
    m[1][1] = matrix[1][1];
    m[1][2] = matrix[1][2];
    m[1][3] = matrix[1][3];

    m[2][0] = matrix[2][0];
    m[2][1] = matrix[2][1];
    m[2][2] = matrix[2][2];
    m[2][3] = matrix[2][3];

    m[3][0] = matrix[3][0];
    m[3][1] = matrix[3][1];
    m[3][2] = matrix[3][2];
    m[3][3] = matrix[3][3];
}

void fMatrix4::empty()
{
    m[0][0] = 0;
    m[0][1] = 0;
    m[0][2] = 0;
    m[0][3] = 0;

    m[1][0] = 0;
    m[1][1] = 0;
    m[1][2] = 0;
    m[1][3] = 0;

    m[2][0] = 0;
    m[2][1] = 0;
    m[2][2] = 0;
    m[2][3] = 0;

    m[3][0] = 0;
    m[3][1] = 0;
    m[3][2] = 0;
    m[3][3] = 0;
}

void fMatrix4::identity()
{
    m[0][0] = 1;
    m[1][1] = 1;
    m[2][2] = 1;
    m[3][3] = 1;
}

void fMatrix4::transpose()
{
    fMatrix4 result;

    result.m[0][0] = m[0][0];
    result.m[0][1] = m[1][0];
    result.m[0][2] = m[2][0];
    result.m[0][3] = m[3][0];

    result.m[1][0] = m[0][1];
    result.m[1][1] = m[1][1];
    result.m[1][2] = m[2][1];
    result.m[1][3] = m[3][1];

    result.m[2][0] = m[0][2];
    result.m[2][1] = m[1][2];
    result.m[2][2] = m[2][2];
    result.m[2][3] = m[3][2];

    result.m[3][0] = m[0][3];
    result.m[3][1] = m[1][3];
    result.m[3][2] = m[2][3];
    result.m[3][3] = m[3][3];

    *this = result;
}

void fMatrix4::translate(dVector3 vector)
{
    m[3][0] += vector.x;
    m[3][1] += vector.y;
    m[3][2] += vector.z;
}

void fMatrix4::add(fMatrix4 matrix)
{
    m[0][0] += matrix.m[0][0];
    m[0][1] += matrix.m[0][1];
    m[0][2] += matrix.m[0][2];
    m[0][3] += matrix.m[0][3];

    m[1][0] += matrix.m[1][0];
    m[1][1] += matrix.m[1][1];
    m[1][2] += matrix.m[1][2];
    m[1][3] += matrix.m[1][3];

    m[2][0] += matrix.m[2][0];
    m[2][1] += matrix.m[2][1];
    m[2][2] += matrix.m[2][2];
    m[2][3] += matrix.m[2][3];

    m[3][0] += matrix.m[3][0];
    m[3][1] += matrix.m[3][1];
    m[3][2] += matrix.m[3][2];
    m[3][3] += matrix.m[3][3];
}

void fMatrix4::multiply(fMatrix4 matrix)
{
    fMatrix4 result;

    result.m[0][0] = m[0][0] * matrix.m[0][0] + m[0][1] * matrix.m[1][0] + m[0][2] * matrix.m[2][0] + m[0][3] * matrix.m[3][0];
    result.m[0][1] = m[0][0] * matrix.m[0][1] + m[0][1] * matrix.m[1][1] + m[0][2] * matrix.m[2][1] + m[0][3] * matrix.m[3][1];
    result.m[0][2] = m[0][0] * matrix.m[0][2] + m[0][1] * matrix.m[1][2] + m[0][2] * matrix.m[2][2] + m[0][3] * matrix.m[3][2];
    result.m[0][3] = m[0][0] * matrix.m[0][3] + m[0][1] * matrix.m[1][3] + m[0][2] * matrix.m[2][3] + m[0][3] * matrix.m[3][3];

    result.m[1][0] = m[1][0] * matrix.m[0][0] + m[1][1] * matrix.m[1][0] + m[1][2] * matrix.m[2][0] + m[1][3] * matrix.m[3][0];
    result.m[1][1] = m[1][0] * matrix.m[0][1] + m[1][1] * matrix.m[1][1] + m[1][2] * matrix.m[2][1] + m[1][3] * matrix.m[3][1];
    result.m[1][2] = m[1][0] * matrix.m[0][2] + m[1][1] * matrix.m[1][2] + m[1][2] * matrix.m[2][2] + m[1][3] * matrix.m[3][2];
    result.m[1][3] = m[1][0] * matrix.m[0][3] + m[1][1] * matrix.m[1][3] + m[1][2] * matrix.m[2][3] + m[1][3] * matrix.m[3][3];

    result.m[2][0] = m[2][0] * matrix.m[0][0] + m[2][1] * matrix.m[1][0] + m[2][2] * matrix.m[2][0] + m[2][3] * matrix.m[3][0];
    result.m[2][1] = m[2][0] * matrix.m[0][1] + m[2][1] * matrix.m[1][1] + m[2][2] * matrix.m[2][1] + m[2][3] * matrix.m[3][1];
    result.m[2][2] = m[2][0] * matrix.m[0][2] + m[2][1] * matrix.m[1][2] + m[2][2] * matrix.m[2][2] + m[2][3] * matrix.m[3][2];
    result.m[2][3] = m[2][0] * matrix.m[0][3] + m[2][1] * matrix.m[1][3] + m[2][2] * matrix.m[2][3] + m[2][3] * matrix.m[3][3];

    result.m[3][0] = m[3][0] * matrix.m[0][0] + m[3][1] * matrix.m[1][0] + m[3][2] * matrix.m[2][0] + m[3][3] * matrix.m[3][0];
    result.m[3][1] = m[3][0] * matrix.m[0][1] + m[3][1] * matrix.m[1][1] + m[3][2] * matrix.m[2][1] + m[3][3] * matrix.m[3][1];
    result.m[3][2] = m[3][0] * matrix.m[0][2] + m[3][1] * matrix.m[1][2] + m[3][2] * matrix.m[2][2] + m[3][3] * matrix.m[3][2];
    result.m[3][3] = m[3][0] * matrix.m[0][3] + m[3][1] * matrix.m[1][3] + m[3][2] * matrix.m[2][3] + m[3][3] * matrix.m[3][3];

    *this = result;
}

void fMatrix4::scale(dVector3 vector)
{
    fMatrix4 matrix;

    matrix.identity();

    matrix.m[0][0] = vector.x;
    matrix.m[1][1] = vector.y;
    matrix.m[2][2] = vector.z;

    this->multiply(matrix);
}

void fMatrix4::rotate(double xAngle, double yAngle, double zAngle)
{
    fMatrix4 matrix;
    fMatrix4 matrixX;
    fMatrix4 matrixY;
    fMatrix4 matrixZ;

    matrixX.identity();
    matrixY.identity();
    matrixZ.identity();

    matrixX.m[1][1] = cos(xAngle);
    matrixX.m[1][2] = sin(xAngle);
    matrixX.m[2][1] = -sin(xAngle);
    matrixX.m[2][2] = cos(xAngle);

    matrixY.m[0][0] = cos(yAngle);
    matrixY.m[0][2] = -sin(yAngle);
    matrixY.m[2][0] = sin(yAngle);
    matrixY.m[2][2] = cos(yAngle);

    matrixZ.m[0][0] = cos(zAngle);
    matrixZ.m[0][1] = sin(zAngle);
    matrixZ.m[1][0] = -sin(zAngle);
    matrixZ.m[1][1] = cos(zAngle);

    matrix = Matrix::multiply(matrixX, matrixY);
    matrix = Matrix::multiply(matrix, matrixZ);

    this->multiply(matrix);
}

void fMatrix4::orthographic(double left, double right, double bottom, double top, double near, double far)
{
    fMatrix4 result;
    std::vector<double> vector = {left, right, bottom, top};
    double max = *max_element(vector.begin(), vector.end());
    left = left * 2 / max - 1;
    right = right * 2 / max - 1;
    bottom = bottom * 2 / max - 1;
    top = top * 2 / max - 1;
    result.identity();
    result.m[0][0] = 2.0 / (right - left);
    result.m[1][1] = 2.0 / (top - bottom);
    result.m[2][2] = -2.0 / (far - near);
    result.m[3][0] = -(right + left) / (right - left);
    result.m[3][1] = -(top + bottom) / (top - bottom);
    result.m[3][2] = -(far + near) / (far - near);
    *this = result;
}

void fMatrix4::print()
{
    std::cout << m[0][0] << " " << m[1][0] << " " << m[2][0] << " " << m[3][0] << "\n";
    std::cout << m[0][1] << " " << m[1][1] << " " << m[2][1] << " " << m[3][1] << "\n";
    std::cout << m[0][2] << " " << m[1][2] << " " << m[2][2] << " " << m[3][2] << "\n";
    std::cout << m[0][3] << " " << m[1][3] << " " << m[2][3] << " " << m[3][3] << "\n\n";
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------