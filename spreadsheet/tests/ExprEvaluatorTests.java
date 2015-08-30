package tests;

import org.junit.Assert;
import org.junit.Test;

import spreadsheet.*;

public class ExprEvaluatorTests {

    private ExprEvaluator exprEvaluator;

    @Test
    public void testExprEvaluation1() throws CyclicDependencyException {
        PaginatingMatrix matrix = new PaginatingMatrix();
        matrix.setCellContent("A1", "10 20 +");
        matrix.setCellContent("A2", "A1");
        exprEvaluator = new ExprEvaluator(matrix);

        Assert.assertTrue(exprEvaluator.evaluateCellRef("A1") == 30d);
        Assert.assertTrue(exprEvaluator.evaluateCellRef("A2") == 30d);
    }

    @Test
    public void testExprEvaluation2() throws CyclicDependencyException {
        PaginatingMatrix matrix = new PaginatingMatrix();
        matrix.setCellContent("A1", "A2");
        matrix.setCellContent("A2", "4 5 *");
        matrix.setCellContent("A3", "A1");

        matrix.setCellContent("B1", "A1 B2 / 2 +");
        matrix.setCellContent("B2", "3");
        matrix.setCellContent("B3", "39 B1 B2 * /");

        exprEvaluator = new ExprEvaluator(matrix);

        Assert.assertEquals("20.00000", String.format("%.5f", exprEvaluator.evaluateCellRef("A1")));
        Assert.assertEquals("20.00000", String.format("%.5f", exprEvaluator.evaluateCellRef("A2")));
        Assert.assertEquals("20.00000", String.format("%.5f", exprEvaluator.evaluateCellRef("A3")));
        Assert.assertEquals("8.66667", String.format("%.5f", exprEvaluator.evaluateCellRef("B1")));
        Assert.assertEquals("3.00000", String.format("%.5f", exprEvaluator.evaluateCellRef("B2")));
        Assert.assertEquals("1.50000", String.format("%.5f", exprEvaluator.evaluateCellRef("B3")));
    }
}
