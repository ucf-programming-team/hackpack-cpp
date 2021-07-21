const int MAX_LEN = 5'000'000;
const ll base[] = {999'999'001, 999'999'005};
const ll mod[] = {999'999'929, 999'999'937};
const ll basei[] = {975'215'448, 129'828'318};
ll pw[2][MAX_LEN + 1], pwi[2][MAX_LEN + 1];
void setupM(int mi){
	pw[mi][0] = pwi[mi][0] = 1;
	for(int i = 1; i <= MAX_LEN; ++i){
		pw[mi][i] = (pw[mi][i - 1] * base[mi]) % mod[mi];
		pwi[mi][i] = (pwi[mi][i - 1] * basei[mi]) % mod[mi];
	}
}
vll getPreM(vi &arr, int mi){
	vll pre(size(arr));
	pre[0] = arr[0];
	for(int i = 1; i < size(arr); ++i) pre[i] = (pre[i - 1] + arr[i] * pw[mi][i]) % mod[mi];
	return pre;
}
vector<vll> getPre(vi &arr){
	return {getPreM(arr, 0), getPreM(arr, 1)};
}
ll subM(vector<vll> &pre, int l, int r, int mi){
	if(l > r) return 0;
	ll out = (pre[mi][r] - (l == 0 ? 0 : pre[mi][l - 1]) + mod[mi]) % mod[mi];
	return (out * pwi[mi][l]) % mod[mi];
}
pll sub(vector<vll> &pre, int l, int r){
	return {subM(pre, l, r, 0), subM(pre, l, r, 1)};
}
