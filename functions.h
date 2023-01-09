#pragma once
using namespace std;
#include "vector"
#include "string"
#include <fstream>

vector<string> get_args(int argc,char **argv){
  vector<string> ret;
  ret.resize(argc);
  for(int i = 0; i < argc;i++){
    ret[i] = argv[i];
  }
  return ret;
}

