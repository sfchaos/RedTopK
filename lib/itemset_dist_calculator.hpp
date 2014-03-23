#ifndef ITEMSET_DIST_CALCULATOR_
#define ITEMSET_DIST_CALCULATOR_

#include <algorithm>
#include "itemset.hpp"

namespace redtopk {
using namespace std;

double jaccard(const vector<size_t> &is1, const vector<size_t> &is2)
//double jaccard(const Itemset &is1, const Itemset &is2)
{
  // intersection of two itemsets
	vector<size_t> intersec;
  //vector<Item> intersec;
  set_intersection(is2.begin(), is2.end(), is1.begin(), is1.end(),
                  back_inserter(intersec));
  
  // calculate Jaccard coefficient
  size_t size_intersec = intersec.size();
  size_t size_union = is1.size() + is2.size() - size_intersec;
//cout << "size_intersec = " << size_intersec << endl;
//cout << "size_union = " << size_union << endl;

  return 1.0 - (double)size_intersec/size_union;
}

}

#endif
