import java.util.Random;
import cern.colt.map.*;

public class Benchmark {
    static long lookup(AbstractIntIntMap m, Integer[] b, int r) {	
	long sum = 0;

	long t1 = System.nanoTime();
	for (int i = 0; i < r; i ++) {
	    Integer x = m.get(b[i]); 
            if (x != 0) 
		sum += x;
	}
	long t2 = System.nanoTime();

	return (t2 - t1) / 1000;
    }

    static void randomize_input(Integer[] a, int n, Integer[] b, int r) {
	Random random = new Random();
	for (int i = 0; i < n; i ++) {
	    a[i] = random.nextInt(Integer.MAX_VALUE - 1) + 1;
	}
	for (int i = 0; i < r; i ++) {
	    b[i] = i % 2 == 1 ? a[random.nextInt(n)] : random.nextInt(Integer.MAX_VALUE - 1) + 1;
	}
	    
    }
    
    public static void main(String args[]) {
	if (args.length != 3) {
	    System.out.println("Usage: Java Benchmark <size> <requests> <measurements>");
	    System.exit(-1);
	}
	
	int n = Integer.parseInt(args[0]);
	int r = Integer.parseInt(args[1]);
	int k = Integer.parseInt(args[2]);
	Integer[] a = new Integer[n];
	Integer[] b = new Integer[r];
	long t = 0;

	for (int j = 0; j < k; j ++) {

	    AbstractIntIntMap m = new OpenIntIntHashMap(0, 0, 0.5);
	    randomize_input(a, n, b, r);
	    for (int i = 0; i < n; i ++) {
		m.put(a[i], i);
	    }
	    
	    t += lookup(m, b, r);
	    m.clear();
	}

	System.out.printf("%.2f MOPS\n", (double) r * k / (double) t);
    }
}
