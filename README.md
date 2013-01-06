
# Resample move particle filter

> Following a moving target -- Monte Carlo inference for dynamic Bayesian models
> Walter R. Gilks, Carlo Berzuini
> Journal of the Royal Statistical Society: Series B (Statistical Methodology) (2001), pp. 127-146

This is unfinished but is meant to become an implementation of a resample-move particle filter
that uses slice sampling for the Montecarlo Markov Chain (MCMC) move step. 

A particle filter is a relatively robust way of tracking and predicting real-world data using 
a mathematical model.

I previously implemented a resample-move particle filter as part of my PhD research. At the time, the
research was looking at model idenfication and this particular type of particle filter turned out 
to be not that useful to us because it adapts to give good predictions with incorrect models!

I wanted a small side project where I still got to practice some of the skills I learnt during
my research. I hope complete this "clean room" implementation and then play with what
appears to be a significantly robust and high performing algorithm.

If you'd like a particle filter implementation that is already complete and heavily used I 
recommend the excellent [dysii](http://www.indii.org/research/dysii) package.

# Licence

This software licenced under the MIT licence.
