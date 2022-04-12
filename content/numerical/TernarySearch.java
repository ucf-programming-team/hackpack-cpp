class TernarySearch {
	public static void main (String[] args){
	    double l = -(1e9 + 3), r = 1e9 + 3;
	    for(int i = 0; i < 200; ++i){
	        double g1 = (l * 2 + r) / 3;
	        double g2 = (l + r * 2) / 3;
	        //if finding min
	        if(go(g1) > go(g2)) l = g1;
	        else r = g2;
	        //if finding max
	        if(go(g1) > go(g2)) r = g2;
	        else l = g1;
	    }
	    double out = go(l);
	}
	static double go(double in){
	    //function you're min/max ing
	    return -Math.pow(in - 4, 2) + 3;
	}
}
