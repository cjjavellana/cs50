package spreadsheet;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;

import static constants.Constants.MAX_COLUMNS;
import static constants.Constants.MAX_ROWS;

/**
 *
 */
public class Page implements Serializable {

    private int pageNumber;
    private String[][] data = new String[MAX_ROWS][MAX_COLUMNS];

    public Page(int pageNumber) {
        this.pageNumber = pageNumber;
    }

    public String getData(int row, int col) {
        return data[row][col];
    }

    public void setData(int row, int col, String exprOrValue) {
        data[row][col] = exprOrValue;
    }

    public int getPageNumber() {
        return pageNumber;
    }

    private void writeObject(ObjectOutputStream out) throws IOException {
        out.defaultWriteObject();
    }

    private void readObject(ObjectInputStream in) throws IOException, ClassNotFoundException {
        in.defaultReadObject();
    }
}
