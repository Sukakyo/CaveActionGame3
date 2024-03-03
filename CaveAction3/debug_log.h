#pragma once

#include <string>
#include <eigen3/Eigen/Core>
#define EIGEN_NO_DEBUG 
#define EIGEN_DONT_VECTORIZE
#define EIGEN_DONT_PARALLELIZE
#define EIGEN_MPL2_ONLY
#include <cstdio>

using namespace Eigen;

namespace debug{
	void debugLog(const char* format,...);
	void print(std::string category,Vector3d vec);

}
