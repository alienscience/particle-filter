#include "slice-sampler.h"

#include <iostream>
#include <boost/random.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/math/distributions/normal.hpp>

using namespace std;
typedef boost::numeric::ublas::vector<double> vec;


// Return a uniformly distributed random double [0,1)
// http://www.bnikolic.co.uk/blog/cpp-boost-uniform01.html
double uniformRandom() {
    boost::mt19937 rng;   // Will be optimised away
    static boost::random::uniform_01<boost::mt19937> uniform(rng);

    return uniform();
}

// Single variate Gaussian probability density function
double gaussianDensity(const vec& x)
{
    static boost::math::normal_distribution<double> dist;
    return boost::math::pdf(dist, x[0]);
}

int main()
{
    vec sliceWidths(1);
    sliceWidths[1]  = 1.0;

    SliceSampler<vec> sampler(uniformRandom, gaussianDensity, sliceWidths);
    return 0;
}

