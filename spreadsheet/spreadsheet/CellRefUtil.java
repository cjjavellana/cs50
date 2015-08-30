package spreadsheet;

import java.util.regex.Matcher;
import static constants.Constants.*;

/**
 * Convenience class for converting cell reference to 2d array coordinates and vice versa.
 */
public class CellRefUtil {

    /**
     * Converts a cell reference to a 2d array matrix coordinates
     *
     * @param cellRef e.g. A1, B2, etc
     * @return The row and column coordinates
     */
    public static ArrayCoordinates convertCellRefToArrayCoordinates(String cellRef) {
        Matcher m = CELL_REF_PATTERN.matcher(cellRef);
        if (m.matches()) {
            // normalize row number 'A' refers to row index 0
            int row = m.group(1).toUpperCase().charAt(0) - CHAR_TO_ROW_IDX_CONVERTER;

            // column identifier starts with 1, but arrays are 0 indexes.
            int col = Integer.parseInt(m.group(2)) - 1;

            // derive page number
            int pageNumber = (col / MAX_COLUMNS) + 1;
            if (pageNumber > 0) {
                col -= ((pageNumber - 1) * MAX_COLUMNS);
            }

            return new ArrayCoordinates(pageNumber, row, col);
        } else {
            throw new IllegalArgumentException(String.format("%s does not seem to be a valid cell", cellRef));
        }
    }

    /**
     * Converts the array coordinates (e.g. 0,0 0,1) to cell reference (A1, A2)
     *
     * @param coordinates
     * @return
     */
    public static String convertArrayCoordinatesToCellRef(ArrayCoordinates coordinates) {
        return convertArrayCoordinatesToCellRef(coordinates.getPageNumber(), coordinates.getRow(), coordinates.getCol());
    }

    /**
     * Converts the array coordinates (e.g. 0,0 0,1) to cell reference (A1, A2)
     *
     * @param pageNumber The page number
     * @param row        The row index
     * @param col        The column index
     * @return
     */
    public static String convertArrayCoordinatesToCellRef(int pageNumber, int row, int col) {
        col = ((pageNumber - 1) * MAX_COLUMNS) + col;
        if (pageNumber > 0) {
            col++;
        }
        return String.format("%s%s", (char) (row + CHAR_TO_ROW_IDX_CONVERTER), col);
    }
}
