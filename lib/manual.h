#include <iostream>
using namespace std;

void print_manual(){
  cout<<"-----------------------------------------------------------\n";
  cout<<"|               Document Similarity checker               |\n";
  cout<<"-----------------------------------------------------------\n";
  cout<<"|  Instruction                                            |\n";
  cout<<"|  -> This program requires 2 or more files to operate.   |\n";
  cout<<"|  -> Please place the files you wish to compare in the   |\n";
  cout<<"|     designated folder \"./bin/origin\".                   |\n";
  cout<<"|  -> Upon completion, the results will be exported       |\n";
  cout<<"|     to a .csv format, readily accessible at the         |\n";
  cout<<"|     designated folder \"./bin/export\".                   |\n";
  cout<<"*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
  cout<<"===========================================================\n";
  cout<<"|  Commands                                               |\n";
  cout<<"|  -> Y/y and N/n to either proceed or halt               |\n";
  cout<<"|  -> 1-3 to choose the file                              |\n";
  cout<<"|  -> 1-3 to choose the sorting type(Alphabetical or Freq)|\n";
  cout<<"|  -> a-c to pick the sorting type(Ascend or Descend)     |\n";
  cout<<"|  -> Y/y and N/n to either export or proceed             |\n";
  cout<<"===========================================================\n";
}