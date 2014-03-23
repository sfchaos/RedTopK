#ifndef TRANSACTION_HPP_
#define TRANSACTION_HPP_

#include <vector>
#include <string>
#include <algorithm>
#include <iterator>

namespace redtopk {
using namespace std;

class Transaction
{
  public:
    Transaction() {}
    Transaction(std::size_t id) : id_(id) {}
    ~Transaction() {}
    void addItem(const Item &item) {
      tran_.push_back(item);
    }
    void addItem(const string &item) {
      tran_.push_back(Item(item));
    }
    void clear() { tran_.clear(); }
    bool find(const string &item) {
      return std::find(tran_.begin(), tran_.end(), item) == tran_.end();  
    }
    void sort () { std::sort(tran_.begin(), tran_.end()); }
 
  public:
    typedef vector<Item>::const_iterator const_iterator;
  
    const_iterator begin() const { return tran_.begin(); }
    const_iterator end() const { return tran_.end(); }

  private:
    std::size_t id_;
    vector<Item> tran_;
};

class TransactionSet
{
  public:
    TransactionSet() {}
    ~TransactionSet() {}
    void addTransaction(const Transaction &tran) {
      transet_.push_back(tran);
    }

  public:
    typedef vector<Transaction>::const_iterator const_iterator;
  
    const_iterator begin() const { return transet_.begin(); }
    const_iterator end() const { return transet_.end(); }

  private:
    vector<Transaction> transet_;
};

}

#endif
