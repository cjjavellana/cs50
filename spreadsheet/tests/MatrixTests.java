package tests;

import junit.framework.Assert;
import org.junit.Before;
import org.junit.Test;

import spreadsheet.*;

/**
 * Tests for the PaginatingMatrix
 */
public class MatrixTests {

    private PaginatingMatrix matrix;

    @Before
    public void setup() {
        matrix = new PaginatingMatrix();
    }

    @Test
    public void returnsAValue() throws CyclicDependencyException {
        matrix.setCellContent("A1", "A2");
        matrix.setCellContent("A2", "17 2 *");
        matrix.setCellContent("A3", "3");
        matrix.setCellContent("A4", "A1");
        matrix.setCellContent("B1", "25 50 +");
        matrix.setCellContent("B2", "B1");
        matrix.setCellContent("C1", "A5");

        Assert.assertEquals("A2", matrix.getCellContent("A1"));
        Assert.assertEquals("25 50 +", matrix.getCellContent("B1"));
        Assert.assertEquals("B1", matrix.getCellContent("B2"));
        Assert.assertEquals("A5", matrix.getCellContent("C1"));
    }

    @Test
    public void returnsNullWhenCellIsNotSet() throws CyclicDependencyException {
        Assert.assertNull(matrix.getCellContent("A2"));
    }

    @Test(expected = CyclicDependencyException.class)
    public void throwsCyclicDependencyException() throws CyclicDependencyException {
        matrix.setCellContent("A1", "A2");
        matrix.setCellContent("A2", "A1");
    }
}
