typedef __int128 lll;

inline lll mult(lll a, lll b, lll mod) {
    lll result = 0;
    while (b) {
        if (b & 1)
            result = (result + a) % mod;
        a = (a + a) % mod;
        b >>= 1;
    }
    return result;
}

inline lll lllabs(lll x){ return x < 0 ? -x : x;}

inline lll lllgcd(lll a, lll b){
    if (a == 0) return b; 
    return lllgcd(b % a, a); 
}

inline lll f(lll x, lll c, lll mod) {
    return (mult(x, x, mod) + c) % mod;
}

inline lll pow(lll a, lll b, lll mod){
    lll res = 1;
    while(b){
        if(b&1) res = mult(res,a,mod);
        a = mult(a,a,mod);
        b>>=1;
    }
    return res;
}

inline int miller(lll d, lll n) { 
    lll a = 2 + rand() % (n - 4); 
    lll x = pow(a, d, n); 
    if (x == 1  || x == n-1) return 1; 
    while (d != n-1) { 
        x = mult(x,x,n); 
        d <<=1; 
        if (x == 1)      return 0; 
        if (x == n-1)    return 1; 
    }
    return 0; 
}

inline int isProbablePrime(lll n, lll k) 
{ 
    if (n <= 1 || n == 4)  return 0; 
    if (n <= 3) return 1; 
  
    lll d = n - 1; 
    while (!(d&1)) d >>= 1; 
  
    while(k--) if (!miller(d, n)) return 0; 
    return 1; 
}


lll brent(lll n, lll x0=2, lll c=1) {
    if(isProbablePrime(n, 20)) return n;
    lll x = x0, g = 1, q = 1, xs, y;

    int m = 128, l = 1;
    while (g == 1) {
        y = x;
        for (int i = 1; i < l; i++)
            x = f(x, c, n);
        int k = 0;
        while (k < l && g == 1) {
            xs = x;
            for (int i = 0; i < m && i < l - k; i++) {
                x = f(x, c, n);
                q = mult(q, lllabs(y - x), n);
            }
            g = lllgcd(q, n);
            k += m;
        }
        l *= 2;
    }
    if (g == n) {
        do {
            xs = f(xs, c, n);
            g = lllgcd(lllabs(xs - y), n);
        } while (g == 1);
    }
    return g;
}

int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

vector<lll> factor(lll x){
    vector<lll> ans(0);
    
    for(auto p:primes){
        while(x%p==0){
            x/=p;
            ans.emplace_back(p);
        }
    }
    while(x!=1){
        lll curf = brent(x);
        ans.emplace_back(curf);
        x/=curf;
    }
    return ans;
}

lll getlll(){
    string temp;
    cin >> temp;
    lll ans = 0;
    lll tpow = 1;
    for(int i = temp.size()-1; i >= 0; i--){
        ans += (lll)(temp[i]-'0')*tpow;
        tpow *= 10;
    }
    return ans;
}

void printlll(lll x){
    if(x==0){
        cout << 0;
        return;
    }
    vector<int> digits(0);
    while(x>0){
        digits.emplace_back((int)(x%10));
        x/=10;
    }
    for(int i = digits.size()-1; i >= 0; i--)cout << digits[i];
}