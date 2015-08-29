package spreadsheet;

import java.io.File;
import java.io.Serializable;

import static constants.Constants.MAX_COLUMNS;
import static constants.Constants.MAX_ROWS;

/**
 * This class paginates the matrix contents to & from disk if the number of matrix columns
 * exceeds the threshold constant defined in {@link stdin.Constants#MAX_COLUMNS}
 */
public class PaginatingMatrix implements Serializable {

    private int rowCount;
    private int colCount;
    private Page page;
    private PageManager mm = new PageManager();

    /**
     * Creates a new {@link PaginatingMatrix} instance.
     */
    public PaginatingMatrix() {
        // create default page
        page = new Page(1);
    }

    public void setMatrixSize(int row, int col) {
        this.rowCount = row;
        this.colCount = col;
    }

    /**
     * Returns the content of the cell identified by {@code cellId}.
     *
     * @param cellRef The cell reference.
     * @return
     */
    public String getCellContent(String cellRef) {
        ArrayCoordinates coord = CellRefUtil.convertCellRefToArrayCoordinates(cellRef);
        if (coord.getPageNumber() != page.getPageNumber()) {
            // persist current page before loading a new one
            mm.writePage(page);

            // load new page; if page does not exists loadpage()
            // returns null
            Page temp = mm.loadPage(coord.getPageNumber());
            if (temp != null) {
                page = temp;
            }
        }

        return getCellContent(coord.getRow(), coord.getCol());
    }

    public void setCellContent(String cellRef, String exprOrValue) throws CyclicDependencyException {
        ArrayCoordinates coord = CellRefUtil.convertCellRefToArrayCoordinates(cellRef);
        if (coord.getPageNumber() != page.getPageNumber()) {
            // write current page to disk
            mm.writePage(page);

            // check if page already exist
            String filename = String.format("%s.dat", coord.getPageNumber());
            File file = new File(filename);
            if (file.exists()) {
                page = mm.loadPage(coord.getPageNumber());
            } else {
                page = new Page(coord.getPageNumber());
            }
        }

        // keep track of current page, before checking for cyclic dependency
        // because the DependencyInspector can alter the page during inspection
        Page temp = page;

        DependencyInspector inspector = new DependencyInspector(this);
        inspector.checkForCyclicDependency("", coord, exprOrValue);

        // restore page after checking for cyclic dependency
        page = temp;
        page.setData(coord.getRow(), coord.getCol(), exprOrValue);
    }

    /**
     * Returns the matrix row count
     *
     * @return
     */
    public int getRowCount() {
        return rowCount;
    }

    /**
     * Returns the matrix column count
     *
     * @return
     */
    public int getColCount() {
        return colCount;
    }

    // ~ Private methods ================

    private String getCellContent(int row, int col) {
        if (hasExceededBoundary(row, col)) {
            throw new IllegalArgumentException(String.format("Invalid cell access. Row: %s, Column: %s", row, col));
        }

        return page.getData(row, col);
    }

    private boolean hasExceededBoundary(int row, int col) {
        return row > MAX_ROWS || row < 0 || col > MAX_COLUMNS || col < 0;
    }

}
