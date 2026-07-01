package prog12_13;

public class Tray implements ResizableTray {

    private int width;
    private int length;
    private int plateWidth;
    private int plateLength;

    @Override
    public void W(int width) {
        this.width = width;
    }

    @Override
    public void L(int length) {
        this.length = length;
    }

    public void setPlateSize(int plateWidth, int plateLength) {
        this.plateWidth = plateWidth;
        this.plateLength = plateLength;
    }

    public int calculatePlateCount() {
        if (width <= 0 || length <= 0 || plateWidth <= 0 || plateLength <= 0) {
            return 0;
        }

        int countNormal = (width / plateWidth) * (length / plateLength);
        int countRotated = (width / plateLength) * (length / plateWidth);

        return Math.max(countNormal, countRotated);
    }

    public void display() {
        System.out.println("Tray Details");
        System.out.println("Tray Width: " + width);
        System.out.println("Tray Length: " + length);
        System.out.println("Plate Width: " + plateWidth);
        System.out.println("Plate Length: " + plateLength);
        System.out.println("Number of Plates that can fit: " + calculatePlateCount());
    }
}