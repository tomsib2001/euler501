#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cmath>
#include <primecount.hpp>
#include <primesieve.h>
using namespace std;

uint64_t solve1(uint64_t n,int* primes,size_t* size){
  uint64_t res = (uint64_t) 0;
  uint64_t scn = (uint64_t) (pow(n,1/3.)+2);
  uint64_t sn = ((uint64_t) (sqrt(n)))+1;
  for(int i=0;(i< *size && (uint64_t) primes[i] <= scn);i++){
    for(int j=i+1;(j<*size && (((uint64_t) (sqrt(primes[i])))* (uint64_t) primes[j] <= sn));j++){
      uint64_t denom = (uint64_t) (primes[i]*primes[j]);
      uint64_t quo = floor (((uint64_t) n) / denom);
      uint64_t delta_res;
      uint64_t piquo = primecount::pi(quo);
      if (quo <= primes[j]){
	delta_res = 0;
      }
      else{
	delta_res = (piquo - primecount::pi(primes[j]));
      }
      res += delta_res;
    }
  }
  cerr << "first sum : " << res << endl;
  return res;
}

uint64_t solve2(uint64_t n,int* primes,size_t* size){
  uint64_t res = (uint64_t) 0;
  uint64_t lim = (uint64_t) (n / 2 + 1);
  for(int i=0;(i<*size && primes[i]<= lim);i++){
    double r = pow(n / (uint64_t) (primes[i]),1./3.);
    uint64_t quo = floor (r);
    if ((double) pow(floor(r)+1,3) <= (double) n / (double) (primes[i]))
      quo += 1;
    res += primecount::pi(quo);
    if (primes[i] <= quo){
      res -= 1;
    }
  }
  cerr << "second sum : " << res << endl;
  return res;
}


uint64_t solve2bis(uint64_t n,int* primes,size_t* size){
  uint64_t res1 = (uint64_t) 0;
  uint64_t lim1 = (uint64_t) (pow(n,1/3.)+1);
  for(int i=0;(i<*size && primes[i]<= lim);i++){
    double r = pow(n / (uint64_t) (primes[i]),1./3.);
    uint64_t quo = floor (r);
    if ((double) pow(floor(r)+1,3) <= (double) n / (double) (primes[i]))
      quo += 1;
    res += primecount::pi(quo);
    if (primes[i] <= quo){
      res -= 1;
    }
  }
  cerr << "second sum : " << res << endl;
  return res;
}


uint64_t solve3(uint64_t n){
  uint64_t res;
  uint64_t m = floor(pow(n,1/7.));
  res = primecount::pi(m);
  size_t size;
  int* primes = (int*) primesieve_generate_primes ((uint64_t) 0, (uint64_t) m, &size, INT_PRIMES);
  for (int k=0;k < size;k++)
    {
      cerr << "p : " << primes[k] << " and the value is  " 
	   << pow(primes[k],7) << endl;
    }
  return res;
}

int main(){
  uint64_t n = (uint64_t) pow(10,9);
  uint64_t sn = (uint64_t) pow(10,8);
  size_t size;
  int* primes = (int*) primesieve_generate_primes ((uint64_t) 0, (uint64_t) sn, &size, INT_PRIMES);
  cerr << "prime generation done" << endl;
  int64_t prime_count = primecount::pi(n);
  uint64_t sum1 = solve1(n,primes,&size);
  cerr << endl;
  cerr << "computing sum 2" << endl;
  uint64_t sum2 = solve2(n,primes,&size);
  cerr << "computing sum 3" << endl;
  uint64_t sum3 = solve3(n);
  uint64_t res = sum1 + sum2 + sum3;
  cout << res << endl;
  return 0;
}
