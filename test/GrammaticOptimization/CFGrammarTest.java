/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package GrammaticOptimization;

import junit.framework.TestCase;

/**
 *
 * @author adil
 */
public class CFGrammarTest extends TestCase {
    
    public CFGrammarTest(String testName) {
        super(testName);
    }

    /**
     * Test of genotype2phenotype method, of class CFGrammar.
     */
    public void testGenotype2phenotype() {
        System.out.println("genotype2phenotype");
        CFGrammar instance = new CFGrammarImpl();
        boolean expResult = false;
        boolean result = instance.genotype2phenotype();
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of phenotype2genotype method, of class CFGrammar.
     */
    public void testPhenotype2genotype() {
        System.out.println("phenotype2genotype");
        CFGrammar instance = new CFGrammarImpl();
        boolean expResult = false;
        boolean result = instance.phenotype2genotype();
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of readBNFFile method, of class CFGrammar.
     */
    public void testReadBNFFile() {
        System.out.println("readBNFFile");
        String filename = "";
        CFGrammar instance = new CFGrammarImpl();
        boolean expResult = false;
        boolean result = instance.readBNFFile(filename);
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of readBNFString method, of class CFGrammar.
     */
    public void testReadBNFString() {
        System.out.println("readBNFString");
        String stream = "";
        CFGrammar instance = new CFGrammarImpl();
        boolean expResult = false;
        boolean result = instance.readBNFString(stream);
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of pruneSpaces method, of class CFGrammar.
     */
    public void testPruneSpaces() {
        System.out.println("pruneSpaces");
        CFGrammar instance = new CFGrammarImpl();
        instance.pruneSpaces();
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of addBNFString method, of class CFGrammar.
     */
    public void testAddBNFString() {
        System.out.println("addBNFString");
        String stream = "";
        CFGrammar instance = new CFGrammarImpl();
        boolean expResult = false;
        boolean result = instance.addBNFString(stream);
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of outputBNF method, of class CFGrammar.
     */
    public void testOutputBNF() {
        System.out.println("outputBNF");
        CFGrammar instance = new CFGrammarImpl();
        String expResult = "";
        String result = instance.outputBNF();
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of findRule method, of class CFGrammar.
     */
    public void testFindRule() throws Exception {
        System.out.println("findRule");
        Symbol nonterminal = null;
        CFGrammar instance = new CFGrammarImpl();
        Rule expResult = null;
        Rule result = instance.findRule(nonterminal);
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    public class CFGrammarImpl extends CFGrammar {

        public boolean genotype2phenotype() {
            return false;
        }

        public boolean phenotype2genotype() {
            return false;
        }
    }
    
}
