#ifndef SLICESAMPLER_H
#define SLICESAMPLER_H

#include "mcmc.h"

#include <cmath>
#include <functional>


/**
  * A multivariate slice sampler
  */
template <typename T>
struct SliceSampler : public MCMC<T>
{
    /**
      * Create a slice sampler.
      * @param uniformRandom    a uniform random number generator [0,1)
      * @param densityFunction  the probability density function
      * @param sliceWidths      the estimated slice widths for each variable
      */
    // g++ 4.4 supports std::function using c++0x
    SliceSampler(std::function<double()> uniformRandom,
                 std::function<double(const T&)> densityFunction,
                 const T& sliceWidths);
    /**
      * MCMC move state
      * @return true if the move was successful
      */
    bool move(T& state);

private:
    // Function that returns a uniformly distributed random number (0,1]
    std::function<double()> uniformRandom_;

    // Probabilty density function
    std::function<double(const T&)> densityFunction_;

    // Estimated slice widths
    T sliceWidths_;

    // Limit to the size of a slice : m_ * sliceWidths_
    int m_;

    // Single variate MCMC move
    bool move1D(T& state, typename T::size_type i);
};

//------------- Implementation -------------------------------------------------

template <typename T>
SliceSampler<T>::SliceSampler(std::function<double()> uniformRandom,
                              std::function<double(const T&)> densityFunction,
                              const T& sliceWidths) :
    uniformRandom_(uniformRandom),
    densityFunction_(densityFunction),
    sliceWidths_(sliceWidths)
{
}

// Multivariate MCMC move
template <typename T>
bool SliceSampler<T>::move(T& state) {
    bool ret = true;

    for (typename T::size_type i = 0; i < state.size(); i++) {
        if (!move1D(state, i)) ret = false;
    }

    return ret;
}

// Single variate MCMC move
//   Slice Sampling, Radford M. Neal,
//    The Annals of Statistics, 2003 vol 31, No 3, 707-767
//    Figures 3,5
//   i is the index to the variable being considered
template <typename T>
bool SliceSampler<T>::move1D(T& state, typename T::size_type i) {

   // Draw a value for the vertical that will define the horizontal slice
   double y  = uniformRandom_() * densityFunction_(state);

   const double x0 = state[i];

   // Stepping out algorithm (figure 3)
   double u  = uniformRandom_();
   double w  = sliceWidths_[i];
   double l  = x0 - w * u;
   double r  = l + w;
   double v  = uniformRandom_();
   int j     = static_cast<int>(std::floor(m_ * v));
   int k     = (m_ - 1) - j;

   while ( j > 0 ) {
       state[i] = l;
       if (densityFunction_(state) <= y) break;
       l = l - w;
       j = j - 1;
   }

   while ( k > 0 ) {
       state[i] = r;
       if (densityFunction_(state) <= y) break;
       r = r + w;
       k = k - 1;
   }

   // Shrinkage algorithm (figure 5)
   double ldash = l;
   double rdash = r;

   while (true) {
       u = uniformRandom_();
       double x1 = ldash + u * (rdash - ldash);
       state[i] = x1;
       if (y < densityFunction_(state)) break;
       if (x1 < x0) ldash = x1; else rdash = x1;
   }

   // Assume success
   // TODO : limit the number of iterations in the loops above
   return true;
}

#endif // SLICESAMPLER_H
