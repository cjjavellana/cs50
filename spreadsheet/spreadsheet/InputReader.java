package spreadsheet;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;

import static constants.Constants.*;

/**
 * Reads the matrix input from an input stream
 */
public class InputReader {

    /**
     * Reads the matrix input from an input stream
     *
     * @param matrix
     * @param inputStream
     * @return
     */
    public void readInput(PaginatingMatrix matrix, InputStream inputStream) throws CyclicDependencyException {
        try (BufferedReader br = new BufferedReader(new InputStreamReader(inputStream))) {
            String line = null;

            int lineCounter = 0, rows = 0, columns = 0, currentRow = 0, currentCol = 0;

            while ((line = br.readLine()) != null) {
                if (lineCounter == 0) {
                    String[] rowCol = line.split("\\s");
                    columns = Integer.parseInt(rowCol[0]);
                    rows = Integer.parseInt(rowCol[1]);
                    matrix.setMatrixSize(rows, columns);
                } else {
                    int pageNumber = (currentCol / MAX_COLUMNS) + 1;
                    String cellRef = CellRefUtil.convertArrayCoordinatesToCellRef(pageNumber, currentRow, currentCol);
                    matrix.setCellContent(cellRef, line);

                    currentCol++;

                    if (lineCounter % columns == 0) {
                        currentRow++;
                        currentCol = 0;
                    }
                }

                lineCounter++;
            }
        } catch (IOException ioe) {
            throw new RuntimeException("Problem reading input", ioe);
        }
    }
}
