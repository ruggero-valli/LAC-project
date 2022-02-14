#ifndef LIBUTILS_H
#define LIBUTILS_H

#include <string>
#include <fstream>
#include "Eigen/Dense"

typedef Eigen::ArrayXd Array1D;
typedef Eigen::ArrayXXd Array2D;

void parseLine(std::string line, std::string& command, std::string& value);
Array1D readArray1D(std::string str, int len);
Array2D readArray2D(std::ifstream& cfgFile, int rows, int cols);
std::string readString(std::string str);

/**
 * @brief removes all occurrences of `c` from the string `str`
 * 
 * @param str 
 * @param c 
 */
void erase(std::string& str, char c);

/**
 * @brief splits the array in half.
 * 
 * The array `U` is split in two equal-length parts. The first half is copied
 * into the array `r`, the second one into the array `v`.
 * 
 * @param[in] U the array to be split
 * @param[out] r the first half of the array
 * @param[out] v the second half of the array
 */
void split(Array1D& U, Array1D& r, Array1D& v);

/**
 * @brief concatenates two arrays into one.
 * 
 * The array `r` and the array `v` are concatenated into the array `U`.
 * 
 * @param[out] U the resulting array
 * @param[in] r the first half of the array
 * @param[in] v the second half of the array
 */
void join(Array1D& U, Array1D& r, Array1D& v);

//void join3(Array1D& U, Array1D& phi, Array1D& tt, Array1D& r);

/**
 * @brief Converts the solution array `U` into a position array `r` and a
 * velocity array `v`.
 * 
 * The array `U` has shape length 6*N where N is the number of particles.
 * The arrays `r` and `v` have shape (3,N)
 * For example, if N=2:
 * U = [r1x,r1y,r1z,r2x,r2y,r2z,v1x,v1y,v1z,v2x,v2y,v2z]
 * becomes
 * r = [[r1x,r2x],
 *      [r1y,r2y],
 *      [r1z,r2z]]
 * v = [[v1x,v2x],
 *      [v1y,v2y],
 *      [v1z,v2z]]
 * 
 * @param[in] U the solution array
 * @param[out] r the position 2d array
 * @param[out] v the velocity 2d array
 */
void UtoRV(Array1D& U, Array2D& r, Array2D& v);

/**
 * @brief Converts the position array `r` and the velocity array `v` into 
 * the solution array `U`.
 * 
 * The array `U` has shape length 6*N where N is the number of particles.
 * The arrays `r` and `v` have shape (3,N)
 * For example, if N=2:
 * r = [[r1x,r2x],
 *      [r1y,r2y],
 *      [r1z,r2z]]
 * v = [[v1x,v2x],
 *      [v1y,v2y],
 *      [v1z,v2z]]
 * becomes
 * U = [r1x,r1y,r1z,r2x,r2y,r2z,v1x,v1y,v1z,v2x,v2y,v2z]
 * 
 * @param[in] U the solution array
 * @param[out] r the position 2d array
 * @param[out] v the velocity 2d array
 */
void RVtoU(Array1D& U, Array2D& r, Array2D& v);


#endif