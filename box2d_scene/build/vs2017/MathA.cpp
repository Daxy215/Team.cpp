#include "MathA.h"

gef::Matrix44 MathA::multiply(const gef::Matrix44& matrix, const gef::Matrix44& other) {
    gef::Matrix44 result;

    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            float sum = 0.0f;
            for (int k = 0; k < 4; ++k) {
                sum += matrix.GetRow(row)[k] * other.GetColumn(col)[k];
            }
            result.SetRow(row, gef::Vector4(sum, result.GetRow(row)[1], result.GetRow(row)[2], result.GetRow(row)[3]));
        }
    }

    return result;
}
