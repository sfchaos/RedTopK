#ifndef REDUNDANCY_CALCULATOR_HPP_
#define REDUNDANCY_CALCULATOR_HPP_

#include "itemset.hpp"
#include "itemset_dist_calculator.hpp"

namespace redtopk {
using namespace std;

class RedCalculator
{
  public:
    RedCalculator() {}
    ~RedCalculator() {}
    virtual double calcRed(const Itemset &is1, const Itemset &is2) = 0;

};

class RedCalculatorBasedOnJaccard : public RedCalculator
{
  public:
    RedCalculatorBasedOnJaccard() : RedCalculator() {}
    ~RedCalculatorBasedOnJaccard() {}
    double calcRed(const Itemset &is1, const Itemset &is2) {
      double red = (1 - jaccard(is1.getTranId(), is2.getTranId())) * 
										min(is1.getImp(), is2.getImp());
      return red;
    }
};

}

#endif
