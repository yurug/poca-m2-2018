public class ColorPoint extends Point {
    private final String color;
    ColorPoint(int x, int y, String color) {
        super(x, y);
        this.color = color;
    }

    protected String makeName() {
       return super.makeName()
            + ":" + color;
    }

    public static void main(String[] args) {
        System.out.println
        (new ColorPoint(4, 2, "purple"));
    }
}
