import java.util.ArrayList;

public class PolygonClipping {

	//only what is on side 1 of line will remain (positive cross product)
	static Vec[] clip(Vec[] poly, Seg line) {
		ArrayList<Vec> toReturn=new ArrayList<>();
		int nLeft=0, nRight=0, n=poly.length;
		int[] side=new int[n];
		for (int i=0; i<n; i++) {
			//old code checked cross with epsilon 1e-8
			side[i]=line.side(poly[i]);
			if (side[i]==1) nLeft++;
			if (side[i]==-1) nRight++;
		}
		if (nLeft==0) return new Vec[0];
		if (nRight==0) return poly;
		
		for (int i=0; i<n; i++) {
			int next=(i+1)%n;
			if (side[i]==1) toReturn.add(poly[i]);
			if (side[i]*side[next]!=1) {
				Vec intersect=line.lineIntersect(new Seg(poly[i], poly[next]));
				if (intersect!=null)
					toReturn.add(intersect);
			}
		}
	
		Vec[] res=new Vec[toReturn.size()];
		for (int i=0; i<res.length; i++)
			res[i]=toReturn.get(i);
		return res;
	}
	
	
	
}
