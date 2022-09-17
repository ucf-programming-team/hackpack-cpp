static class ST{
 
		int n;
		int[] lo;
		int[] hi;
		long[] sum;
		long[] lazy;
 
		public ST(int nn){
			n = nn;
			lo = new int[n*4+1];
			hi = new int[n*4+1];
			sum = new long[n*4+1];
			lazy = new long[n*4+1];
			build(1, 0, n-1);
		}
 
		void build(int i, int a, int b){
			lo[i] = a;
			hi[i] = b;
			if(a == b) return;
			int m = (a+b)/2;
			build(2*i, a, m);
			build(2*i+1, m+1, b);
		}
 
		void prop(int i){
			sum[2*i] += (hi[2*i]-lo[2*i]+1)*lazy[i];
			sum[2*i+1] += (hi[2*i+1]-lo[2*i+1]+1)*lazy[i];
			lazy[2*i] += lazy[i];
			lazy[2*i+1] += lazy[i];
			lazy[i] = 0;
		}
 
		void add(int l, int r, long v){
			if(l > r){
				add(1, l, n-1, v);
				add(1, 0, r, v);
			}
			else{
				add(1, l, r, v);
			}
		}
 
		void add(int i, int l, int r, long v){
			if(r < lo[i] || l > hi[i]) return;
			if(l <= lo[i] && hi[i] <= r){
				lazy[i] += v;
				sum[i] += (hi[i]-lo[i]+1)*v;
				return;
			}
			prop(i);
			add(2*i, l, r, v);
			add(2*i+1, l, r, v);
			sum[i] = sum[2*i]+sum[2*i+1];
		}
 
		long sum(int l, int r){
			if(l > r){
				return sum(1, l, n-1)+sum(1, 0, r);
			}
			else{
				return sum(1, l, r);
			}
		}
 
		long sum(int i, int l, int r){
			if(r < lo[i] || l > hi[i]) return 0;
			if(l <= lo[i] && hi[i] <= r){
				return sum[i];
			}
			prop(i);
			long res = 0;
			res += sum(2*i, l, r);
			res += sum(2*i+1, l, r);
			return res;
		}
	}
