public class Test {

    public static void main (String[] args) {

	int i = 5;
	int j = 0;
	j = i << 32;
	System.out.println (j);

	Integer x = new Integer (5);
	Integer y = new Integer (5);
	if (x == y) {
	    System.out.println ("A l'heure!");
	}
	x++;
	y++;
	if (x == y) {
	    System.out.println ("A l'heure en POCA!");
	}
    }

}
