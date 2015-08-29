package spreadsheet;

/**
 * A class that represents a coordinate in a 2d array
 */
public class ArrayCoordinates {

    private int pageNumber;
    private int row;
    private int col;

    public ArrayCoordinates(int pageNumber, int row, int col) {
        this.pageNumber = pageNumber;
        this.row = row;
        this.col = col;
    }

    public int getRow() {
        return row;
    }

    public int getCol() {
        return col;
    }

    public int getPageNumber() {
        return pageNumber;
    }
}
