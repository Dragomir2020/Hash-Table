#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>

#include "HashTable.cpp"

using namespace std;

unsigned int hash_fn(const int& number){
  return abs(number);
}

unsigned int hash_fn(const string& thing){
  unsigned int ret = 7;
  for(unsigned int i = 0; i < thing.length(); i++){
    ret = ret * 31 * thing[i];
    // 31 is the next prime above 26
  }
  return ret;
}

HashTable<string> readFile(char* filename){
  HashTable<string> ret(hash_fn, 200000) ;
  fstream file;
  file.open(filename, ios::in);
  while(file){
    string word;
    file >> word;
    ret.insert(word);
  }
  file.close();
  return ret;
}

void printSuggestions(const HashTable<string>& dict, const string& word){
  // Change of letter
  for(unsigned int i = 0; i < word.length(); i++){
    for(int l = 'a'; l <= 'z'; l++){
      string newword = word;
      newword[i] = l;
      if(dict.find(newword)){
        cout << " " << newword;
      }
    }
  }
  // Delete a letter
  for(unsigned int i = 0; i < word.length(); i++){
    string newword = word.substr(0,i) + word.substr(i+1, word.length() - i);
    if(dict.find(newword)){
      cout << " " << newword;
    }
  }
  // Add a letter
  for(unsigned int i = 0; i <= word.length(); i++){
    for(int l = 'a'; l <= 'z'; l++){
      string newword = word.substr(0,i) + " " + word.substr(i, word.length() -i + 1);
      newword[i] = l;
      if(dict.find(newword)){
        cout << " " << newword;
      }
    }
  }
}

int main(int argc, char* argv[]){
    
	
    HashTable<int> a(hash_fn, 5);
    a.insert(5);
    HashTable<int> b(hash_fn, 5);
    b.insert(10);
    a = b;
    cout<< a.size()<< endl;
    cout<< b.size()<< endl;
    cout << a.find(10) << endl;
    cout << a.find(5) <<  endl;
#if 0	
	HashTable<int> a(hash_fn,5);
    a.insert(5);
	cout << "Find(5): " << a.find(5) << endl;
	cout << "Find(10): " << a.find(10) << endl;
	a.insert(2);
	a.insert(2);
	cout << "Find(2): " << a.find(2) << endl;
	a.insert(1);
	cout << "Find(1): " << a.find(1) << endl;
    HashTable<int> b(a);
    cout << a.size() << endl;
	cout << b.size() << endl;
	//Now try with string
    HashTable<string> c(hash_fn,10);
    c.insert("bob");
	cout << "Find(bob): " << c.find("bob") << endl;
	cout << c.size() << endl;


  if(argc != 2){
    cout << "Enter filename of dictionary!\n";
    return 1;
  }
  HashTable<string> dict = readFile(argv[1]);
  cout << "Words Loaded: " << dict.size() << endl;

  string word;
  while(1){
    cout << "Enter word:";
    cin >> word;
    if( word == "q"){
      return 0;
    }
    if(dict.find(word)){
      cout << "FOUND!\n";
    }else{
      cout << "Not Found.  Did you mean:";
      printSuggestions(dict, word);
      cout << endl;
    }
  }
#endif
}
