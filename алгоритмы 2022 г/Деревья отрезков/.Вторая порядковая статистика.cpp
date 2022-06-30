#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


//ostream & operator<<(ostream& os, vector<long long> a){
//  int l = a.size();
//  for(int i = 0; i < l; ++i){
//    os << a[i] << " ";
//  }
//  os << "\n";
//  return os;
//}

struct Data{
  int p_min1;
  int p_min2;
};

class sparse_tables{
 private:
  long long n;
  vector<vector<Data>> table;
  vector<int> log;
  vector<long long> bas;

  void precount(int n){
    log.resize(n+1);
    log[0] = 0;
    log[1] = 0;
    for(size_t i = 2; i < n+1; ++i){
      log[i] = log[i-1];
      if(!(i&(i-1))) {
        log[i] += 1;
      }
    }
  }

  void insert_min(const int p, Data& ans){
    if(bas[p] < bas[ans.p_min1]){
      ans.p_min2 = ans.p_min1;
      ans.p_min1 = p;
    }else if(ans.p_min2 == n){
      ans.p_min2 = p;
    }else if(bas[p] < bas[ans.p_min2]) {
      ans.p_min2 = p;
    }

  }

  Data mk_min_pair(const Data& a, const Data& b){
    Data ans = {a.p_min1, a.p_min2};

    if(b.p_min2 != ans.p_min1 && b.p_min2 != ans.p_min2){
      insert_min(b.p_min2, ans);
    }
    if(b.p_min1 != ans.p_min1 && b.p_min1 != ans.p_min2){
      insert_min(b.p_min1, ans);
    }

    return ans;
  }

 public:

  sparse_tables(int n, vector<long long>& bas){
    this->n = n;
    this->precount(n);
    this->bas = bas;
//    cout << this->bas;
    bas.push_back(0); //fake

    int size = log[n];
    table.resize(n);
    for(int i = 0; i < n; ++i) {
      table[i].resize(size + 1);
      table[i][0] = {i, n};
//      cout << table[i][0].p_min1 << " ";
    }

//    cout << "\n";
    for(size_t j = 1; j <= size; ++j){
      size_t new_s = n - (1<<(j-1));
      for(size_t i = 0; i < n; ++i){
        if((i + (1<<(j-1))) < n){
          table[i][j] = mk_min_pair(table[i][j-1], table[i + (1<<(j-1))][j-1]);
        } else{
          table[i][j] = mk_min_pair(table[i][j-1], table[new_s][j-1]);
        }
      }
    }
  }

  long long max_lr(size_t l, size_t r) {
    long long pow = log[r - l];
//    cout << r << " " <<  l << " " << pow << "\n";
    size_t p_min = mk_min_pair(table[l][pow], table[r+1-(1<<pow)][pow]).p_min2;
    return bas[p_min];
  }

  void show(){
    for(size_t i = 0; i <= log[n]; ++i) {
      for(size_t j = 0; j < n; ++j) {
        cout << table[j][i].p_min1 << " " << table[j][i].p_min2 << " ! ";
      }
      cout << i;
      cout << "\n";
    }
  }
};


void input(int& n, int& m, vector<long long>& bas){
  cin >> n >> m;
  bas.resize(n);
  for(size_t i = 0; i < n; ++i){
    cin >> bas[i];
  }
}

int main() {

  std::ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int n, m;
  vector<long long> bas;
  input(n,m,bas);
  sparse_tables table(n,bas);
//  table.show();
  size_t l,r;
  for(size_t i = 0; i < m; ++i) {
    cin >> l >> r;
    cout << table.max_lr(l - 1,r - 1) << "\n";
  }
  return 0;
}