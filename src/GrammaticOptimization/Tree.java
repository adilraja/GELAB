/*
 * Tree.java
 *
 * Created on July 27, 2007, 3:53 PM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

package GrammaticOptimization;

/**
 *
 * @author adilraja
 */
import java.util.*;
import java.util.ArrayList;

public class Tree extends ArrayList<Tree> {
    
    private Symbol data;//Tree is made of objects of type symbol as opposed to arbitrary type.
    private int depth;
    private int currentLevel;
    private boolean valid;
    /** Creates a new instance of Tree */
    public Tree() {
    }
/**
 * Constructor; initialises depth and current level.
 */
 
public Tree(final int newDepth, final int newCurrentLevel){
        depth=newDepth;
        currentLevel=newCurrentLevel;
	setValid(false);
}

/**
 *Constructor; initialises data to match arguments.
 */
 
public Tree(final Symbol newData, final int newCurrentLevel, final int newDepth){
                data=newData;
                depth=newDepth;
		currentLevel=newCurrentLevel;
                setValid(true);
}

/**
 *Copy constructor.
 */
public Tree(final Tree copy){
    super(copy);
    setData(copy.getData());
    setDepth(copy.getDepth());
    setCurrentLevel(copy.getCurrentLevel());
    setValid(copy.getValid());
}

/**
 * Return depth from this node until the deepest leaf.
 */
//template<class T>
public final int getDepth(){
	return depth;
}

/**
 *Set new depth of this node.
 */

public void setDepth(final int newDepth){
	depth=newDepth;
}

/**
 *Return level of this node.
 */

public final int getCurrentLevel(){
	return currentLevel;
}

/**
 *Set new current level of this node.
 */

public void setCurrentLevel(final int newCurrentLevel){

	currentLevel=newCurrentLevel;
}

/**
 *Return data stored in this node.
 */

public final Symbol getData(){
	if(getValid()){
		return data;
	}
	else{
		return null;
	}
}
/**
 * Set data to store in this node.
 */

public void setData(final Symbol newData){
	data=new Symbol(newData);
	setValid(true);
}

/**
 *Return validity of this node.
 */

public final boolean getValid(){
	return valid;
}

/**
 * Set validity of this node.
 */
public void setValid(final boolean newValid){
	valid=newValid;
}
}
//complete