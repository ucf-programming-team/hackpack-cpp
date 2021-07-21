//@
static class FastScanner {
    BufferedReader br;
    StringTokenizer st;
	
    public FastScanner(InputStream i) {
        br = new BufferedReader(new InputStreamReader(i));
        st = new StringTokenizer("");
    }
			
    public String next() throws IOException {
        if(st.hasMoreTokens())
            return st.nextToken();
        else
            st = new StringTokenizer(br.readLine());
        return next();
    }

    public int nextInt() throws IOException {
        return Integer.parseInt(next());
    }
    //#
    public long nextLong() throws IOException {
        return Long.parseLong(next());
    }
    public double nextDouble() throws IOException {
        return Double.parseDouble(next());
    }
    //$
}
