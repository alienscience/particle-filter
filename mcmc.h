#ifndef MCMC_H
#define MCMC_H

/**
  * Interface provided by a Monte Carlo Markov Chain Sampler
  */
template <typename T>
struct MCMC {
    /**
      * Move the given state in order to sample a probabilty distribution function
      */
    virtual bool move(T& state) = 0;
};

#endif // MCMC_H
