#ifndef ITEMSET_HPP_
#define ITEMSET_HPP_

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <boost/algorithm/string/join.hpp>
#include "item.hpp"
#include "transaction.hpp"

namespace redtopk {
using namespace std;

class Itemset
{
  public:
    Itemset() {}
    ~Itemset() {}
    void addItem(const Item& item) { is_.push_back(item); }
    void addItem(const string& item) { is_.push_back(Item(item)); }

    string getItemset() const {
      vector<string> result(is_.size());
      transform(is_.begin(), is_.end(),  result.begin(), 
                [](const Item &item) { return item.getItem(); });
      return "{" + boost::algorithm::join(result, ",") + "}";
    }

    void addId(size_t id) { id_ = id; }
    size_t getId() const { return id_; }

    double getImp() const { return imp_; }
    void addImp(double imp) { imp_ = imp; }
    void clear() { is_.clear(); };
    size_t size() const { return is_.size(); }
    void sort() {
      std::sort(is_.begin(), is_.end());
    }
		const vector<size_t> &getTranId() const {
			return tranid_;
		}

    void matchTran(TransactionSet &transet) {
      vector<Transaction>::const_iterator itr = transet.begin();
      vector<Transaction>::const_iterator itrEnd = transet.end();
    
      this->sort();

      while (itr != itrEnd) {
        bool matched = isSubset(is_, *itr);
//copy(is_.begin(), is_.end(), ostream_iterator<Item>(cout, ","));
//cout << endl;
//copy(itr->begin(), itr->end(), ostream_iterator<Item>(cout, ","));
//cout << endl;
//cout << "matched = " << matched << endl;
//cout << endl;

        if (matched) {
          tranid_.push_back(itr - transet.begin());
        }
        itr++;
      }
//			copy(is_.begin(), is_.end(), ostream_iterator<Item>(cout, ","));
//			copy(tranid_.begin(), tranid_.end(), ostream_iterator<size_t>(cout, ","));
//			cout << endl;
    }

    bool operator < (const Itemset& is) const {
      return imp_ < is.imp_;
    }
 
  public:
    typedef vector<Item>::const_iterator const_iterator;
  
    const_iterator begin() const { return is_.begin(); }
    const_iterator end() const { return is_.end(); }


  private:
    vector<Item> is_;
    double imp_;
    size_t id_;
    vector<size_t> tranid_;

    template <typename T>
    bool isSubset(vector<T> &a, const Transaction &tran) {
      //return includes(a.begin(), a.end(), tran.begin(), tran.end());
      return includes(tran.begin(), tran.end(), a.begin(), a.end());
    }

};

}

#endif
