package spreadsheet;

import java.util.Stack;
import java.util.regex.Matcher;

import static constants.Constants.*;

/**
 * The expression evaluator class.
 */
public class ExprEvaluator {

    private PaginatingMatrix matrix;

    public ExprEvaluator(PaginatingMatrix matrix) {
        this.matrix = matrix;
    }

    /**
     * Evaluates the expression at {@code cellRef}
     *
     * @param cellRef A valid cell reference, e.g. A1, A2, etc
     * @return Evaluation result
     */
    public Double evaluateCellRef(String cellRef) {
        String expr = matrix.getCellContent(cellRef);
        return evaluate(expr);
    }

    /**
     * Evaluates an expression string using the stack
     *
     * @param expression A post fix expression
     * @return
     */
    public Double evaluate(String expression) {
        OpIdentifier op = new OpIdentifier();
        Stack<Double> stack = new Stack<Double>();

        String[] ops = expression.split("\\s");
        for (String val : ops) {
            // if number push to stack
            if (op.isNumber(val)) {
                Matcher m = NUMERIC_PATTERN.matcher(val);

                // minimize auto-boxing
                Double d = Double.valueOf(val);
                stack.push(d);
                continue;
            }

            // if cell ref evaluate & push to stack
            if (op.isCellReference(val)) {
                String content = matrix.getCellContent(val);
                Double result = evaluate(content);
                stack.push(result);
                continue;
            }

            // if operator, pop stack (A), pop stack (b) & evaluate.
            if (op.isOperator(val)) {
                Double a = stack.pop();
                Double b = stack.pop();
                Double result = 0d;
                switch (val) {
                    case "*":
                        result = a * b;
                        break;
                    case "/":
                        result = b / a;
                        break;
                    case "+":
                        result = a + b;
                        break;
                    case "-":
                        result = b - a;
                }

                stack.push(result);
            }
        }

        return (stack.isEmpty()) ? 0d : stack.pop();
    }
}
