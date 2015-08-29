package spreadsheet;

import java.util.regex.Matcher;
import static constants.Constants.CELL_REF_PATTERN;

/**
 * Checks for cyclic dependency
 */
public class DependencyInspector {

    private PaginatingMatrix matrix;

    public DependencyInspector(PaginatingMatrix matrix) {
        this.matrix = matrix;
    }

    public void checkForCyclicDependency(String prefix, ArrayCoordinates coord, String exprOrValue) throws CyclicDependencyException {
        if (exprOrValue == null) {
            return;
        }

        String[] arr = exprOrValue.split("\\s");
        for (String expr : arr) {
            Matcher m = CELL_REF_PATTERN.matcher(expr.trim());
            if (m.matches()) {
                String cellRef = CellRefUtil.convertArrayCoordinatesToCellRef(coord);

                // check if expr is in the prefix, this means that the
                // current cell back to the cell which pointed at it
                if (prefix.contains(expr)) {
                    String msg = String.format("Value of cell %s (%s) contains reference to cell %s which also refers to current cell",
                            cellRef, exprOrValue, prefix.trim());
                    throw new CyclicDependencyException(msg);
                }
                prefix += String.format("%s ", cellRef);
                checkForCyclicDependency(prefix, CellRefUtil.convertCellRefToArrayCoordinates(expr), matrix.getCellContent(expr));
            }
        }
    }
}
