package spreadsheet;

/**
 * This exception is thrown when a cell reference refers to a cell that refers to the original cell.
 */
public class CyclicDependencyException extends Exception {

    public CyclicDependencyException(String message) {
        super(message);
    }
}
