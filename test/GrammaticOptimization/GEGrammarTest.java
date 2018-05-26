/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package GrammaticOptimization;

import libGEjava.Production;
import libGEjava.Symbol;
import libGEjava.Tree;
import libGEjava.GEGrammar;
import java.util.ArrayList;
import java.util.ListIterator;
import java.util.Stack;
import junit.framework.TestCase;

/**
 *
 * @author adil
 */
public class GEGrammarTest extends TestCase {
    
    public GEGrammarTest(String testName) {
        super(testName);
    }

    /**
     * Test of getMaxWraps method, of class GEGrammar.
     */
    public void testGetMaxWraps() {
        System.out.println("getMaxWraps");
        GEGrammar instance = new GEGrammar();
        int expResult = 0;
        int result = instance.getMaxWraps();
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of setMaxWraps method, of class GEGrammar.
     */
    public void testSetMaxWraps() {
        System.out.println("setMaxWraps");
        int newMaxWraps = 0;
        GEGrammar instance = new GEGrammar();
        instance.setMaxWraps(newMaxWraps);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of getTree method, of class GEGrammar.
     */
    public void testGetTree() throws Exception {
        System.out.println("getTree");
        GEGrammar instance = new GEGrammar();
        Tree expResult = null;
        Tree result = instance.getTree();
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of getProductions method, of class GEGrammar.
     */
    public void testGetProductions() throws Exception {
        System.out.println("getProductions");
        GEGrammar instance = new GEGrammar();
        ArrayList<Production> expResult = null;
        ArrayList<Production> result = instance.getProductions();
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of genotype2phenotype method, of class GEGrammar.
     */
    public void testGenotype2phenotype_0args() {
        System.out.println("genotype2phenotype");
        GEGrammar instance = new GEGrammar();
        boolean expResult = false;
        boolean result = instance.genotype2phenotype();
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of genotype2phenotype method, of class GEGrammar.
     */
    public void testGenotype2phenotype_boolean() {
        System.out.println("genotype2phenotype");
        boolean buildDerivationTree = false;
        GEGrammar instance = new GEGrammar();
        boolean expResult = false;
        boolean result = instance.genotype2phenotype(buildDerivationTree);
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of phenotype2genotype method, of class GEGrammar.
     */
    public void testPhenotype2genotype() {
        System.out.println("phenotype2genotype");
        GEGrammar instance = new GEGrammar();
        boolean expResult = false;
        boolean result = instance.phenotype2genotype();
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of genotype2phenotypeStep method, of class GEGrammar.
     */
    public void testGenotype2phenotypeStep() {
        System.out.println("genotype2phenotypeStep");
        Stack<Symbol> nonterminals = null;
        Integer codonGenoIt = null;
        boolean buildDerivationTree = false;
        GEGrammar instance = new GEGrammar();
        int expResult = 0;
        int result = instance.genotype2phenotypeStep(nonterminals, codonGenoIt, buildDerivationTree);
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of buildDTree method, of class GEGrammar.
     */
    public void testBuildDTree() {
        System.out.println("buildDTree");
        Tree currentNode = null;
        ListIterator<Production> prodIt = null;
        GEGrammar instance = new GEGrammar();
        instance.buildDTree(currentNode, prodIt);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }
    
}
