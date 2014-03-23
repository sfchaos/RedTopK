#ifndef ITEMSET_READER_
#define ITEMSET_READER_

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>
#include <memory>
#include <boost/tokenizer.hpp>
#include "itemset.hpp"

namespace redtopk {

// setting tokenizer
typedef boost::char_separator<char> char_separator;
typedef boost::tokenizer<char_separator> tokenizer;

class ItemsetReader
{
  public:
    ItemsetReader() {}
    ~ItemsetReader() {}
    void readItemset(
      string fn, 
      vector<Itemset> &itemsets,
      string sep=" ", string sep_item=","
    ) {
      string line;
      Itemset is;
      string item;
      ifstream ifs(fn.c_str());

      char_separator separator(sep.c_str(), "", boost::keep_empty_tokens);

      // read each itemset
      size_t id = 1;
      while (ifs && getline(ifs, line)) {
        is.clear();

        // split each itemset into items
        tokenizer tokens(line, separator);
        tokenizer::iterator tok_itr = tokens.begin();
        string str = *tok_itr;
        istringstream istrs((char *) str.c_str());
        while (getline(istrs, item, ',')) {
          is.addItem(item);
        }
        is.addId(id);
        is.sort();

        // get importance of the itemset
        tok_itr++;
        double imp;
        stringstream ss;
        ss << *tok_itr;
        ss >> imp;
        is.addImp(imp);

        // add the itemset to list
        itemsets.push_back(is);
        id++;
      }
    }
};

}

#endif
