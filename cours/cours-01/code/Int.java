public class Int {

    public static void main (String[] args) {
	int j = 5;
	int i = 0;
	i = j << 32;
	System.out.println (i);
	Integer a = new Integer (5);
	Integer b = new Integer (5);
	if (a == b) System.out.println ("1");
	a++;
	b++;
	if (a == b) System.out.println ("2");
	a = 317;
	b = 317;
	if (a == b) System.out.println ("3");
    }

}
