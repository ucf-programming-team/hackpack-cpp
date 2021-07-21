class JS {
	public int BS = 1<<16;
	public char NC = (char)0;
	byte[] buf = new byte[BS];
	int bId = 0, size = 0;
	char c = NC;
	double num = 1;
	BufferedInputStream in;

	public JS() {
		in = new BufferedInputStream(System.in, BS);
	}

	public JS(String s) throws FileNotFoundException {
		in = new BufferedInputStream(new FileInputStream(new File(s)), BS);
	}

	public char nextChar(){
		while(bId==size) {
			try {
				size = in.read(buf);
			}catch(Exception e) {
				return NC;
			}
			if(size==-1)return NC;
			bId=0;
		}
		return (char)buf[bId++];
	}

	public int nextInt() {
		return (int)nextLong();
	}

	public long nextLong() {
		num=1;
		boolean neg = false;
		if(c==NC)c=nextChar();
		for(;(c<'0' || c>'9'); c = nextChar()) {
			if(c=='-')neg=true;
		}
		long res = 0;
		for(; c>='0' && c <='9'; c=nextChar()) {
			res = (res<<3)+(res<<1)+c-'0';
			num*=10;
		}
		return neg?-res:res;
	}

	public double nextDouble() {
		double cur = nextLong();
		return c!='.' ? cur:cur+(cur < 0 ? -1*nextLong()/num : nextLong()/num);
	}

	public String next() {
		StringBuilder res = new StringBuilder();
		while(c<=32)c=nextChar();
		while(c>32) {
			res.append(c);
			c=nextChar();
		}
		return res.toString();
	}
}
