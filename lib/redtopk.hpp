#ifndef REDTOPK_HPP_
#define REDTOPK_HPP_

#include <iostream>
#include <vector>
#include <map>
#include <iterator>
#include <algorithm>
#include "itemset.hpp"
#include "redundancy_calculator.hpp"

namespace redtopk {
using namespace std;

class RedTopK
{
  public:
    RedTopK(const vector<Itemset> &itemsets) : itemsets_(itemsets) {
      gain_.reserve(itemsets_.size());
      redcalc_ = new RedCalculatorBasedOnJaccard;
    }
    virtual ~RedTopK() { delete redcalc_; }
    virtual void extract(vector<Itemset> &nonred_itemsets, size_t k) = 0;

  protected:
    vector<Itemset> itemsets_;
    vector<double> gain_;
    map<pair<size_t, size_t>, double> red_;
    RedCalculator *redcalc_;
};

class MAS : public RedTopK
{
  public:
    typedef pair<size_t, size_t> red_idx;
    typedef map<red_idx, double> red_container;

  public:
    MAS(const vector<Itemset> &itemsets) : RedTopK(itemsets) {}
    ~MAS() {}
    void extract(vector<Itemset> &nonred_itemsets, size_t k) {
      size_t n_is = 0;
      while (n_is < k) {
//cout << "n_is = " << n_is << endl;
        if (n_is == 0) {
          vector<Itemset>::iterator itr = itemsets_.begin();
          while (itr != itemsets_.end()) {
            gain_.push_back(itr->getImp());
            itr++; 
          }
        } else {
          vector<Itemset>::iterator itr;
          Itemset last = nonred_itemsets.back();
          size_t id_last = last.getId();
          for (itr = itemsets_.begin(); itr != itemsets_.end(); ++itr) {
            double imp = itr->getImp();
            size_t id = itr->getId();
            size_t id_max = max(id, id_last);
            size_t id_min = min(id, id_last);

            // if redundancy has not yet been calculated, do it
            if (red_.count(pair<size_t, size_t>(id_min, id_max)) == 0) {
              red_.insert(red_container::value_type(
                            make_pair(id_min, id_max), 
                            redcalc_->calcRed(last, *itr)));
            }

            // update gains
            size_t i = itr - itemsets_.begin();
            gain_[i] = imp - 1.0/n_is * ((n_is -1) * (imp - gain_[i]) + 
                       red_[make_pair(id_min, id_max)]);
cout << "gain_[" << i << "] = " << gain_[i] << endl;
cout << "red_[" << id_min << "," << id_max << "] = " << red_[make_pair(id_min, id_max)] << endl;
          }
        }
        // add the itemset with maximum gain
        vector<double>::iterator itr_max = max_element(gain_.begin(), gain_.end());
        size_t idx = itr_max - gain_.begin();
//copy(itemsets_[idx].begin(), itemsets_[idx].end(), ostream_iterator<Item>(cout, ","));
//cout << endl;
        nonred_itemsets.push_back(itemsets_[idx]);
        itemsets_.erase(itemsets_.begin() + idx);
        gain_.erase(gain_.begin() + idx);
        n_is++;
      }
    }
};

}

#endif
