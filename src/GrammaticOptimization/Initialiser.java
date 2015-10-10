/*
 * Initialiser.java
 *
 * Created on July 2, 2007, 6:05 PM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

/**
 *
 * @author adilraja
 *
 */
package GrammaticOptimization;

public interface Initialiser{
    public int getPopSize();
    public void setPopSize(final int j);
    public int getIndex();
    public void setIndex(final int i);
    public boolean init(final int i);
    
}