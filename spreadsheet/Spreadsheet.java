import static constants.Constants.MAX_COLUMNS;
import spreadsheet.*;


public class Spreadsheet {

    public static void main(String... args) {
        try {
            PaginatingMatrix matrix = new PaginatingMatrix();

            // Read input
            InputReader reader = new InputReader();
            reader.readInput(matrix, System.in);

            ExprEvaluator exprEvaluator = new ExprEvaluator(matrix);

            // Display output
            System.out.println(String.format("%d %d", matrix.getColCount(), matrix.getRowCount()));
            for (int i = 'A'; i < 'A' + matrix.getRowCount(); i++) {
                for (int j = 1; j < matrix.getColCount() + 1; j++) {
                    String cellRef = String.format("%s%s", (char) i, j);
                    System.out.println(String.format("%.5f", exprEvaluator.evaluateCellRef(cellRef)));
                }
            }

        } catch (CyclicDependencyException e) {
            System.out.println(String.format("Error: %s", e.getMessage()));
            System.exit(1);
        } catch (Exception e) {
            e.printStackTrace();
            System.exit(1);
        }
    }
}
