package constants;

import java.text.NumberFormat;
import java.util.regex.Pattern;

/**
 * Spreadsheet calculator constants
 */
public class Constants {

    // The first 26 x 5000 cells will be in memory. Beyond that will be
    // paginated to & from disk
    public static final int MAX_COLUMNS = 5000;
    public static final int MAX_ROWS = 26;

    // Regular expression for matching cell references
    public static final String CELL_REF_REGEX = "^([A-Za-z])(\\d+)$";
    // Regular expression for matching positive integers
    public static final String NUMERIC_REGEX = "^(\\d+)$";
    // Regular expression for matching the arithmetic operators
    public static final String OPERATOR_REGEX = "^(\\*|\\+|\\/|\\-)$";

    public static final Pattern OPERATOR_PATTERN = Pattern.compile(OPERATOR_REGEX);
    public static final Pattern NUMERIC_PATTERN = Pattern.compile(NUMERIC_REGEX);
    public static final Pattern CELL_REF_PATTERN = Pattern.compile(CELL_REF_REGEX);

    // 'A' is 65 in ascii, our matrix starts with row index 0
    // so we need this value to convert the character to row index
    public static final int CHAR_TO_ROW_IDX_CONVERTER = 65;
}
