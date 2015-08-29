package tests;

import junit.framework.Assert;
import org.junit.Test;

import spreadsheet.*;
 
public class ExprTests {

    @Test
    public void returnsTrueIfExprIsACellRef() {
        OpIdentifier op = new OpIdentifier();
        Assert.assertTrue(op.isCellReference("A100"));
        Assert.assertTrue(op.isCellReference("Z1"));
        Assert.assertTrue(op.isCellReference("X15000"));
    }

    @Test
    public void returnsFalseIfExprIsANotCellRef() {
        OpIdentifier op = new OpIdentifier();
        Assert.assertFalse(op.isCellReference("100"));
        Assert.assertFalse(op.isCellReference("ZZ1"));
    }

    @Test
    public void returnsTrueIfExprIsANumber() {
        OpIdentifier op = new OpIdentifier();
        Assert.assertTrue(op.isNumber("100"));
        Assert.assertTrue(op.isNumber("0"));
        Assert.assertTrue(op.isNumber("15000"));
    }

    @Test
    public void returnsFalseIfExprIsNotANumber() {
        OpIdentifier op = new OpIdentifier();
        Assert.assertFalse(op.isNumber("A100"));
        Assert.assertFalse(op.isNumber("Z1"));
    }

    @Test
    public void returnsTrueIfExprIsNotAnOperator() {
        OpIdentifier op = new OpIdentifier();
        Assert.assertTrue(op.isOperator("*"));
        Assert.assertTrue(op.isOperator("+"));
        Assert.assertTrue(op.isOperator("-"));
        Assert.assertTrue(op.isOperator("/"));
    }
}
