#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <unistd.h>

#include "../lib/itemset_reader.hpp"
#include "../lib/transaction_reader.hpp"
#include "../lib/redtopk.hpp"

using namespace redtopk;

int main(int argc, char *argv[])
{
  string ifn_is; // itemset file name
  string sep=" "; // separator between itemset and importance]
  string sep_item=","; // separator between items 
  size_t k; // number of items extracted
  string ifn_tr; // separator between items in a transaction
  string ofn; // output file name 


  int opt;
  while ((opt = getopt(argc, argv, "i:sSk:t:o:")) != -1) {
    switch(opt) {
      case 'i':
        ifn_is = string(optarg);
        break;
      case 's':
        sep = string(optarg);
        break;
      case 'S':
        sep_item = string(optarg);
        break;
      case 'k':
        k = atoi(optarg);
        break;
      case 't':
        ifn_tr = string(optarg);
        break;
      case 'o':
        ofn = string(optarg);
        break;
      default:
        cout << "Usage: " << argv[0]
              << " [-i itemset file name] [-s separator between itemset and importance] [-S separator between items ] [-k number of items extracted] [-t separator between items in a transaction]" << endl; 
    }
  }


  // read itemset
  vector<Itemset> itemsets;
  ItemsetReader ir;
  ir.readItemset(ifn_is, itemsets, sep, sep_item);

  // read transaction
  TransactionSet transet;
  TransactionReader tr;
  tr.readTransaction(ifn_tr, transet);

  // match itemset
  for_each(itemsets.begin(), itemsets.end(),
           [&transet](Itemset &itemset) { itemset.matchTran(transet); } );

  // extract redundancy-aware top-k itemsets
  MAS mas(itemsets);
  vector<Itemset> nonred_itemsets;
  mas.extract(nonred_itemsets, k);

  // write the extracted itemsets to the file
  ofstream ofs(ofn.c_str());
  for_each(nonred_itemsets.begin(), nonred_itemsets.end(),
            [&ofs](Itemset &itemset) {
              ofs << itemset.getItemset() << " " << itemset.getImp() << endl;
            });
  
  return 0;
}
