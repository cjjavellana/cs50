package spreadsheet;

import java.util.regex.Matcher;
import static constants.Constants.*;


/**
 * A utility class for identifying a value in a postfix expression
 */
public class OpIdentifier {

    /**
     * Returns true if {@code val} is one of the '*', '/', '+', '-' operators
     *
     * @param val The string to evaluate
     * @return
     */
    public boolean isOperator(String val) {
        Matcher m = OPERATOR_PATTERN.matcher(val);
        return m.matches();
    }

    /**
     * Returns true if {@code val} is a cell reference. e.g. A1, B100, etc
     *
     * @param val
     * @return
     */
    public boolean isCellReference(String val) {
        Matcher m = CELL_REF_PATTERN.matcher(val);
        return m.matches();
    }

    /**
     * Returns true if {@code val} is a positive integer
     *
     * @param val
     * @return
     */
    public boolean isNumber(String val) {
        Matcher m = NUMERIC_PATTERN.matcher(val);
        return m.matches();
    }
}
