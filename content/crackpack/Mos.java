class Mos {
    static int n, q, size;
    static int[] arr, out;
    static query[] qs;
    public static void main (String[] args){
        size = (int)Math.sqrt(n);
        
        // currently algorithm will find the number of distinct integers in a range [l, r]
        
        int[] freq = new int[1_000_001];
        int l = 0, r = -1;
        int ans = 0;
        for(query curr : qs){
            int cl = curr.l, cr = curr.r;
            
            while(l > cl){
                --l;
                ++freq[arr[l]];
                if(freq[arr[l]] == 1) ++ans;
            }
            while(r < cr){
                ++r;
                ++freq[arr[r]];
                if(freq[arr[r]] == 1) ++ans;
            }
            while(l < cl){
                --freq[arr[l]];
                if(freq[arr[l]] == 0) --ans;
                ++l;
            }
            while(r > cr){
                --freq[arr[r]];
                if(freq[arr[r]] == 0) --ans;
                --r;
            }
            
            out[curr.i] = ans;
        }
        
    }
    static class query implements Comparable<query> {
        int l, r, i, b;
        query(int ll, int rr, int ii){
            l = ll;
            r = rr;
            i = ii;
            b = l / size;
        }
        public int compareTo(query in){
            if(b != in.b) return b - in.b;
            if(b % 2 == 0) return r - in.r;
            return in.r - r;
        }
    }
}
