/*
 * CFGrammar.java
 *
 * Created on July 26, 2007, 12:21 PM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

package libGEjava;

/**
 *
 * @author adilraja
 */
import java.util.*;
import java.util.ArrayList;
import java.util.Iterator;
import java.io.*;

public abstract class CFGrammar extends Grammar {
    protected Tree derivationTree;
    protected abstract boolean genotype2phenotype();
    protected abstract boolean phenotype2genotype();
    
    /** 
     * Creates a new instance of CFGrammar 
     */
    public CFGrammar() {
        super();
        this.derivationTree=new Tree();
    }
    /**
     *Constructor setting the genotype structure of this mapper to newGenotype.
     */
    public CFGrammar(final Genotype newGenotype){
        super(newGenotype);
        this.derivationTree=new Tree();
    }
    
    /**
     * Constructor setting the phenotype structure of this mapper to newPhenotype.
     */
    public CFGrammar(final Phenotype newPhenotype){
        super(newPhenotype);
        this.derivationTree=new Tree();
    }
    
    
    /**
     * Copy Constructor.
     */
public CFGrammar(final CFGrammar copy){
    super(copy);
    this.derivationTree=new Tree(copy.derivationTree);
    // Now must go through the copied grammar, and replace references to
    // the copy's lhs symbols with references to the new lhs symbols.
    Iterator<Rule> ruleIt=this.iterator();//iterator of Rule
    Iterator<Production> prodIt;
    Iterator<Symbol> symbIt;
    Rule rulePtr=null;
    int ruleCt=0, prodCt=0, symbCt=0;
    while(ruleIt.hasNext()){
        prodIt=ruleIt.next().iterator();//I think there should be a next here. Adil
        prodCt=0;
            while(prodIt.hasNext()){
                Production tmpProd=prodIt.next();
                symbIt=tmpProd.iterator();
                symbCt=0;
                    while(symbIt.hasNext()){
                            Symbol symb=null;
                            try{
                                symb=symbIt.next();
                            }
                            catch(java.util.ConcurrentModificationException e){
                                e.printStackTrace();
                            }
                            if(symb.getType().toString().compareTo("NTSymbol")==0){
				try{
                                    rulePtr=findRule(symb);
                                }
                                catch(Exception e){
                                    //do nothing
                                }
                                    if(rulePtr==null){
                                    /* Undefined NTSymbol - create new symbol */
                                            symb=new Symbol(symb.getSymbol(),null);
                                    }
                                    else{
					/* Point to symbol's definition */
                                        symb=rulePtr.lhs.get(rulePtr.lhs.size()-1);
                                    }
                                    
                                this.get(ruleCt).get(prodCt).insertSymbol(symb,symbCt);
                                
                                symbIt=tmpProd.iterator();
                                for(int ii=0;ii<symbCt+1;ii++){
                                    symbIt.next();
                                }
                               //    symbIt.next();
                            }
                        //    symbIt.next();
                            symbCt++;
                    }
                    //prodIt.next();
                    prodCt++;
            }
            //ruleIt.next();
            ruleCt++;
    }
    // Invalidate phenotype - lower classes in hierarchy can always call
    // genotype2Phenotype() to regenerate it
    phenotype.clear();
    phenotype.setValid(false);
    // Don't copy derivation tree: procedure is too complex and expensive.
    // If tree is requested, it will be regenerated.
}

 /**
  * Opens the file whose name is passed as an argument, reads its contents onto
  *a character string, and calls readBNFString.
  */
public boolean readBNFFile(final String filename){
	/*
	FILE *pFile;
	if(!(pFile=fopen(filename,"r"))){
		cerr << "Could not open grammar file " << filename << ".\nExecution aborted.\n";
		exit(1);
	}
	fseek(pFile,0,SEEK_END);
	int size = ftell(pFile);
	char program[size+1];
	strncpy(program,"",size);
	char line[1024];
	rewind(pFile);
	while(fgets(line,1024,pFile))
		strcat(program,line);
	fclose(pFile);
	strcat(program,"\n");
	return readBNFString(program);
	*/
        String program=new String();
        FileInputStream fileInputStream=null;
        try{
            fileInputStream = new FileInputStream(new File(filename));
        }
        catch(java.io.FileNotFoundException e){
            e.printStackTrace();
        }
        FileDescriptor fd = null;
        try{
            fd=fileInputStream.getFD();
        }
        catch(java.io.IOException e){
            e.printStackTrace();
        }


      //  try
//	{
            // Open the file that is the first 
            // command line parameter
            
         //   FileInputStream fstream = new FileInputStream(filename);
            // Convert our input stream to a
            // DataInputStream
            BufferedReader in=null;
            try{
                in = new BufferedReader(new FileReader(fd));
            }
            catch(java.lang.NullPointerException e){
                e.printStackTrace();
            }
            // Continue to read lines while 
            // there are still some left to read
   //         DataInput  s = new DataInputStream(new FileInputStream("~/mywork/GE/libGE-0.26/EXAMPLES/IntertwinedSpirals/GE_MITGALIB"));
            String thisLine;
            try{
                while ((thisLine=in.readLine()) !=null)
                {
                 //   program.concat(thisLine);
                    program=program+thisLine+"\n";
                }
                in.close();
            }
            catch(java.io.IOException e){
                e.printStackTrace();
            }
            
//	} 
  //      catch (Exception e)
//	{
  //          System.out.println(e+" File input error");
//	}
        program=program+"\n";
	//program.concat("\n");
     //  program="<expr>  ::= (<expr> <op> <expr>)\n| DIV(<expr>, <expr>)\n| ABS(<expr>)\n| GT(<expr>, <expr>)\n| <var>\n<op>    ::= + | - | *\n<var>   ::= X | V | (-1.0)\n";
	//System.out.println(program);
            return readBNFString(program);
}


/**
 * Reads in the BNF grammar specified by its argument text. Returns true if
 * loading of grammar was successful, false otherwise.
 */
public boolean readBNFString(String stream){//the stream was final
// Delete the current grammar, if any
this.clear();

Rule newRule=new Rule(0);				// Used to create new rules for grammar
boolean insertRule=false;		// If newRule is to be inserted onto grammar
Rule currentRule=null;			// Used in pass 2 to add productions to current rule
Production newProduction=new Production(1);
newProduction.clear();// Used to create new productions for grammar
Symbol newSymbol=new Symbol();			// Used to create new symbols for grammar
Symbol newTokenSeparator=new Symbol();		// Used to create token separators for grammar
int stream_size=stream.length();
int ii,jj;              		// Working variables
char currentChar;			// Current char of input
boolean skip=false;			// SKip an iteration on parser (for escaped newlines)
boolean quoted=false;			// If current char is quoted
boolean non_terminal=false;		// If current text is a non-terminal symbol
char separated=0;			// If there was a separator between previous token and current one
ArrayList<Symbol> nonTerminals=new ArrayList();	
nonTerminals.clear();                   // Contains pointers to all defined non-terminals
Iterator<Symbol> nonTerminalsIt;
String currentBuffer=new String();			// Buffer used to add new symbols to grammar
// States of parser
final int START	=		0;
final int START_RULE	=	1;
final int LHS_READ	=	2;
final int PRODUCTION	=	3;
final int START_OF_LINE	=	4;
int state=START;// Current state of parser
	
//#define libGE_DEBUG_CFGRAMMAR_PARSER
stream+="\n";
for(int pass=1;pass<=2;pass++){
    ii=jj=0;
    while(ii<=stream_size){
            if(ii<stream_size){
                    currentChar=stream.charAt(ii);
            }
            else{
                    // Simulate presence of endl at end of grammar
                    currentChar='\n';
            }
         //   System.out.println("I am here in readBNFString "+ii);
            if(stream.charAt(ii)=='\\'){// Escape sequence
                ii++;
                if(ii>=stream_size){
                        // Escape sequence as last char is invalid
                        ERROR_IN_GRAMMAR();
                }
                else if((non_terminal)&&(stream.charAt(ii)!='\n')){
                    // Only escaped newline allowed inside non-terminal
                     System.out.println("ERROR: Escape sequence detected inside non-terminal symbol.\n");
                     ERROR_IN_GRAMMAR();
                }
                if(stream.charAt(ii)=='\''){// Single quote
                    currentChar='\'';
                }
                else if(stream.charAt(ii)=='\"'){// Double quote
                    currentChar='\"';
                }
                else if(stream.charAt(ii)=='\\'){// Backslash
                    currentChar='\\';
                }
                else if(stream.charAt(ii)=='\u0000'){// Null character
                    currentChar='\u0000';
                }
      //          else if(stream.charAt(ii)=='a'){// Audible bell
        //                currentChar='\a';
          //      }
                else if(stream.charAt(ii)=='\b'){// Backspace
                        currentChar='\b';
                }
                else if(stream.charAt(ii)=='\f'){// Formfeed
                        currentChar='\f';
                }
                else if(stream.charAt(ii)=='\n'){// Newline
                        currentChar='\n';
                }
                else if(stream.charAt(ii)=='\r'){// Carriage return
                        currentChar='\r';
                }
                else if(stream.charAt(ii)=='\t'){// Horizontal tab
                        currentChar='\t';
                }
     //           else if(stream[ii]=='v'){// Vertical tab
   //                     currentChar='\v';
       //         }
                else if(stream.charAt(ii)=='\n'){// Escaped newline
                        // Ignore newline
                    skip=true;
                }
                else if(stream.charAt(ii)=='\r'){// Escaped DOS return
                    // Ignore newline
                    skip=true;
                    if(stream.charAt(++ii)!='\n'){
                        System.out.println("ERROR: \\r character not followed by \\n.");
                        ERROR_IN_GRAMMAR();
                    }
                }
                else{// Normal character
                    currentChar=stream.charAt(ii);
                }
                if((!skip)&&(pass>1)){
                    if(currentBuffer.length()==0){
                        newSymbol.setType(SymbolType.TSymbol);
                    }
                    if(currentBuffer.length()==0){
                        currentBuffer=Character.toString(currentChar);
                    }
                    else{
                        //currentBuffer.concat(Character.toString(currentChar));
                        currentBuffer+=currentChar;
                    }
                }
            }
            
        else{
            switch(state){
            case(START):
                if(currentChar=='\r'){
                    break;// Ignore DOS newline first char
                }
            switch(currentChar){
    //            case ' ':// Ignore whitespaces
                case '\u0020'://ignore space
                case '\t':// Ignore tabs
                case '\n':// Ignore newlines
                        break;
                case '<':// START OF RULE
                        newSymbol.setType(SymbolType.NTSymbol);
                        if(currentBuffer.length()==0){
                            currentBuffer=Character.toString(currentChar);
                        }
                        else{
                            //currentBuffer.concat(Character.toString(currentChar));
                            currentBuffer+=currentChar;
                        }
                        state=START_RULE;
                        break;
                default: // Illigal
                        System.out.println("ERROR: Character "+ currentChar + " caused an error.\n");
                        ERROR_IN_GRAMMAR();
            }
            break;
            case(START_RULE):// Read the lhs Non-terminal symbol 
                if(currentChar=='\r'){
                        break;// Ignore DOS newline first char
                }
                switch(currentChar){
                case '\n':// Newlines are illegal here
                    System.out.println("ERROR: Newline inside non-terminal.");
                    ERROR_IN_GRAMMAR();
                    break;
               case '>': // Possible end of non-terminal symbol
                    if(currentBuffer.length()==0){
                        currentBuffer=Character.toString(currentChar);
                    }
                    else{
                        //currentBuffer.concat(Character.toString(currentChar));
                        currentBuffer+=currentChar;
                    }
                    newSymbol.setSymbol(currentBuffer);
      //              newSymbol.setType(SymbolType.NTSymbol);//this was added adil
                    if(pass==1){
                        // First pass
                        // Check if new symbol definition
                        //insertRule=!(findRule(newSymbol));
                        Rule tmpRulePtr=null;
                        try{
                            tmpRulePtr=findRule(newSymbol);
                        }
                        catch(Exception e){
                            //do nothing
                        }
                        if(tmpRulePtr==null)
                            insertRule=true;
                        else
                            insertRule=false;
                        if(insertRule){
                            // Create new rule for symbol
                            newRule.clear();
                            try{
                                newRule.lhs.add(new Symbol(newSymbol));
                            }
                            catch(java.lang.Exception e){
                                System.out.println(e + "newRule sucks");
                                
                            }
                            // Add to grammar
                            try{
                                nonTerminals.add(newRule.lhs.get(newRule.lhs.size()-1));
                            }
                            catch(java.lang.NullPointerException e){
                                System.out.println(e+ "nonTerminals suck");
                            }
                        }
                        else{// Existing symbol, do nothing
                        }
                    }
                    else{
                        // Second pass
                        // Point currentRule to previously defined rule
                        try{
                            if((currentRule=findRule(newSymbol))==null){
                                System.out.println("ERROR: Grammar changed between parser passes.");
                                ERROR_IN_GRAMMAR();
                        }
                        }
                        catch(java.lang.NullPointerException e){
                            System.out.println(e+"ERROR: Grammar changed between parser passes.");
                                ERROR_IN_GRAMMAR();
                        }
                        catch(java.lang.Exception e){
                            System.out.println(e+"ERROR: Grammar changed between parser passes.");
                        }
                //        if((currentRule=findRule(newSymbol))==null){
                  //              System.out.println("ERROR: Grammar changed between parser passes.");
                    //            ERROR_IN_GRAMMAR();
                      //  }
                    }
                    // Reset the buffer
                    currentBuffer="";
                    // lhs for this rule has been read
                    state=LHS_READ;
                    break;
                default:// Check for non-escaped special characters
                    if(((currentChar=='"')||(currentChar=='|')||(currentChar=='<'))){
                            System.out.println("ERROR: Invalid character '" + currentChar + "' inside non-terminal symbol.");
                            ERROR_IN_GRAMMAR();
                    }
                    if(currentBuffer.length()==0){
                        currentBuffer=Character.toString(currentChar);
                    }
                    else{
                        //currentBuffer.concat(Character.toString(currentChar));
                        currentBuffer+=currentChar;
                    }
                 }
            break;
            case(LHS_READ):// Must read ::= token
                if(currentChar=='\r'){
                        break;// Ignore DOS newline first char
                }
                switch(currentChar){
  //                  case ' ':// Ignore whitespaces
                    case '\u0020'://Ignore space
                    case '\t':// Ignore tabs
                    case '\n':// Ignore newlines
                            break;
                    case ':':// Part of ::= token
                        if(currentBuffer.length()==0){
                            currentBuffer=Character.toString(currentChar);
                        }
                        else{
                             //currentBuffer.concat(Character.toString(currentChar));
                            currentBuffer+=currentChar;
                        }
                            break;
                    case '=':// Should be end of ::= token
                            try{
                            if(currentBuffer.length()==0){
                                currentBuffer=Character.toString(currentChar);
                            }
                            else{
                                 //currentBuffer.concat(Character.toString(currentChar));
                                currentBuffer+=currentChar;
                            }
                            //currentBuffer.concat(Character.toString(currentChar));
                        }
                        catch(java.lang.NullPointerException e){
                            System.out.println(e);
                        }
                        if(currentBuffer.equals("::=")==false){// Something other than ::= was read
                                System.out.println("ERROR: Token '" + currentBuffer + "' caused an error");
                                ERROR_IN_GRAMMAR();
                        }
                        // Reset the buffer
                        currentBuffer="";
                        // START OF PRODUCTION
                        newProduction.clear();
                        state=PRODUCTION;
                        break;
                    default: // Illigal
                        System.out.println("ERROR: Character '" + currentChar + "' caused an error.");
                        ERROR_IN_GRAMMAR();
                    }
                    break;
            case(PRODUCTION):// Read everything until | token or \n, or EOL
                if(currentChar=='\r'){
                    break;// Ignore DOS newline first char
                }
                if(pass==1){
                    if (currentChar=='\n')
                    state=START_OF_LINE;
                }
                else switch(currentChar){
                    case '|':// Possible end of production
                        if(quoted){// Normal character
                            //currentBuffer.concat(Character.toString(currentChar));
                            if(currentBuffer.length()==0){
                                currentBuffer=Character.toString(currentChar);
                            }
                            else{
                                currentBuffer+=currentChar;
                            }
                            break;
                        }
                        case '\n':// End of production (and possibly rule)
                            // Reset separator marker
                            separated=0;
                            if((currentBuffer.length()!=0)||(newProduction.size()!=0)){// There is a symbol to add
                                //System.out.println("A symbol '" + currentBuffer + "'" + newSymbol.getType().toString() + "\t");
                            if(currentBuffer.length()==0){
                                // No symbol exists; create terminal empty symbol
                                newSymbol.setType(SymbolType.TSymbol);
                            }
                            if(non_terminal){// Current non-terminal symbol isn't finished
                                System.out.println("ERROR: Symbol '" + currentBuffer + "' caused an error.");
                                ERROR_IN_GRAMMAR();
                            }
                            newSymbol.setSymbol(currentBuffer);
                            if(newSymbol.getType().toString().equals("NTSymbol")){
                                // Find rule that defines this symbol
                                Rule tempRule=null;
                                try{
                                    tempRule=findRule(newSymbol);
                                }
                                catch(Exception e){
                                    //do nothing again
                                }
                                if(tempRule!=null){
                                    newProduction.add(new Symbol(tempRule.lhs.get(tempRule.lhs.size()-1)));
                                }
                                else{
                                    // Undefined symbol, insert anyway
                                    newProduction.add(new Symbol(newSymbol));
                                }
                            }
                            else{// Add terminal symbol
                                newProduction.add(new Symbol(newSymbol));
                            }
                        // Reset the symbol
                        //newSymbol.clear();//this is not required, the garbage collector does this
                          newSymbol.clear();
                        }
                        else{// Empty token; ignored
                                ;
                        }
                        // END OF PRODUCTION
                        // Add production to current rule
                        try{
                            currentRule.add(new Production(newProduction));
                        }
                        catch(Exception e){
                            System.out.println(e+" But the currentRule is null...it sucks too");
                        }
                        // Reset the buffer
                        currentBuffer="";
                        if(currentChar=='\n')
                                state=START_OF_LINE;
                        else{
                                // START OF PRODUCTION
                                newProduction.clear();
                        }
                        break;
                    case '<':// Possible start of non-terminal symbol
                    case '>':// Possible end of non-terminal symbol
                    case ' ':// Possible token separator
                    case '\t':// Possible token separator
                    if((quoted)// Normal character
                    ||(((currentChar==' ')||(currentChar=='\t'))&&(non_terminal))){// Spaces inside non-terminals are accepted
                        if(currentBuffer.length()==0){
                            currentBuffer=Character.toString(currentChar);
                        }
                        else{
                            //currentBuffer.concat(Character.toString(currentChar));
                            currentBuffer+=currentChar;
                        }
                        if(!non_terminal) newSymbol.setType(SymbolType.TSymbol);
                        break;
                    }
                    if(currentChar=='>'){// This is also the end of a non-terminal symbol
                        if(currentBuffer.length()==0){
                           currentBuffer=Character.toString(currentChar);
                        }
                        else{
                           //currentBuffer.concat(Character.toString(currentChar));
                            currentBuffer+=currentChar;
                        }
                        non_terminal=false;
                    }
                    if(currentBuffer.length()>0){
                        if(non_terminal){// Current non-terminal symbol isn't finished
                            System.out.println("ERROR: Symbol " + currentBuffer + "' caused an error.");
                            ERROR_IN_GRAMMAR();
                        }
                        if((currentChar==' ')||(currentChar=='\t')){// Token separator
                            separated=1;
                        }
                        newSymbol.setSymbol(currentBuffer);
                        if(newSymbol.getType().toString().equals("NTSymbol")){
                            // Find rule that defines this symbol
                            Rule tempRule=null;
                            try{
                                tempRule=findRule(newSymbol);
                            }
                            catch(java.lang.Exception e){
                                System.out.println(e+"Finding the rule sucks... ");
                            }
                            if(tempRule!=null){
                                newProduction.add(new Symbol(tempRule.lhs.get(tempRule.lhs.size()-1)));
                            }
                            else{
                                // Undefined symbol, insert anyway
                                newProduction.add(new Symbol(newSymbol));
                            }
                        }
                        else{// Add terminal symbol
                            newProduction.add(new Symbol(newSymbol));
                        }
                        // Reset the symbol
                            newSymbol.clear();
                    }
                    else{// Empty buffer
                        if(((currentChar==' ')||(currentChar=='\t'))// Token separator
                                        &&(newProduction.size()>0)){
                                // Probably a token separator after a non-terminal symbol
                                separated=1;
                        }
                    }
                    // Reset the buffer
                    currentBuffer="";
                    if(currentChar=='<'){// This is also the start of a non-terminal symbol
                        // Special case; must create new Symbol here
                        newSymbol.clear();
                        newSymbol.setType(SymbolType.NTSymbol);
                        if(currentBuffer.length()==0){
                             currentBuffer=Character.toString(currentChar);
                        }
                        else{
                            //currentBuffer.concat(Character.toString(currentChar));
                            currentBuffer+=currentChar;
                        }
                        non_terminal=true;// Now reading a non-terminal symbol
                        if(separated!=0){// Insert a token separator
                            separated=0;
                            newTokenSeparator=new Symbol();
                            newTokenSeparator.setSymbol(" ");
                            newTokenSeparator.setType(SymbolType.TSymbol);
                            newProduction.add(new Symbol(newTokenSeparator));
                        }
                    }
                    break;
                    default: // Add character to current buffer
                    if(separated!=0){// Insert a token separator
                        separated=0;
                        newTokenSeparator=new Symbol();
                        newTokenSeparator.setSymbol(" ");
                        newTokenSeparator.setType(SymbolType.TSymbol);
                        newProduction.add(new Symbol(newTokenSeparator));
                    }
                    if(currentChar=='"'){// Start (or end) quoted section
                        quoted=!quoted;
                        newSymbol.setType(SymbolType.TSymbol);
                        break;
                    }
                    if(currentBuffer.length()==0){
                        newSymbol.setType(SymbolType.TSymbol);
                    }
                    if(currentBuffer.length()==0){
                        currentBuffer=Character.toString(currentChar);
                    }
                    else{
                        //currentBuffer.concat(Character.toString(currentChar));
                        currentBuffer+=currentChar;
                    }
                }
                break;
                case(START_OF_LINE):
                if(currentChar=='\r'){
                    break;// Ignore DOS newline first char
                }
                switch(currentChar){
                case ' ':// Ignore whitespaces
                case '\t':// Ignore tabs
                case '\n':// Ignore newlines
                        break;
                case '|':// Start of new production
                        state=PRODUCTION;
                        if(pass==2){
                                // START OF PRODUCTION
                                newProduction.clear();
                        }
                        break;
                case '<':// Start of lhs non-terminal symbol
                        
                    // END OF RULE
                    if(pass==1){
                            // Add current rule
                            if(insertRule){
                               try{
                                    this.add(new Rule(newRule));
                               }
                               catch(java.lang.NullPointerException e){
                                   System.out.println(e);
                               }
                            }
                    }
                    // START OF RULE
                    newSymbol.setType(SymbolType.NTSymbol);
                    if(currentBuffer.length()==0){
                        currentBuffer=Character.toString(currentChar);
                    }
                    else{
                        //currentBuffer.concat(Character.toString(currentChar));
                        currentBuffer+=currentChar;
                    }
                    state=START_RULE;
                    break;
                default: // Illigal
                    System.out.println("ERROR: Detected line starting with terminal symbol.");
                    ERROR_IN_GRAMMAR();
                }
                break;
            default://Impossible error, quit the program now!
                System.out.println("Internal error.\nPlease report error 'Impossible state in CFGrammar parser' to ..." );
                System.exit(0);
            }
        }
            
        skip=false;
        ii++;
    }
    // END OF PASS
    if(state!=START_OF_LINE){// This must be the state of the parser
        System.out.println("Parsing error reading grammar.");
        ERROR_IN_GRAMMAR();
    }
    if(pass==1){
        // Add current rule
        if(insertRule){
            this.add(new Rule(newRule));
        }
    }
}
//this.pruneSpaces();//removes extra spaces
updateRuleFields();
setValidGrammar(true);
//genotype2phenotype();
return true;
}

/**
 * pruneSpaces: some times, while reading a bnf file, and parsing it, white spaces are not
 * ignored or omitted properly. This function does that.
 */

public void pruneSpaces(){
    Iterator<Rule> ruleIt=this.iterator();
    String tmpStr;
    while(ruleIt.hasNext()){
        Rule tmpRule=ruleIt.next();
            //System.out.print(tmpRule.lhs.get(0).getSymbol()+"::=");
            Iterator<Production> prodIt=tmpRule.iterator();
            while(prodIt.hasNext()){
                Iterator<Symbol> symbIt2=prodIt.next().iterator(); 
                while(symbIt2.hasNext()){
                    tmpStr=symbIt2.next().getSymbol();
                    if(tmpStr.equalsIgnoreCase(" ") || tmpStr.equalsIgnoreCase("")){
                        symbIt2.remove();
                    }
                }
            }
        }
}

/**
 * Returns the production Rules in a String
 * @return 
 */
public String getRules(){
    Iterator<Rule> ruleIt=this.iterator();
    String tmpStr="";
    while(ruleIt.hasNext()){
        Rule tmpRule=ruleIt.next();
            //System.out.print(tmpRule.lhs.get(0).getSymbol()+"::=");
            tmpStr+=tmpRule.lhs.get(0).getSymbol();
            tmpStr+="::= ";
            Iterator<Production> prodIt=tmpRule.iterator();
            while(prodIt.hasNext()){
                Iterator<Symbol> symbIt2=prodIt.next().iterator(); 
                while(symbIt2.hasNext()){
                    tmpStr+=symbIt2.next().getSymbol();
                }
                tmpStr+=" | ";
            }
            tmpStr+="\n";
        }
    return tmpStr;
}

/**
 * Reads in the BNF grammar-part specified by its argument text, and adds it to
 *the current grammar. Returns true if loading of new grammar part was
 *successful, false otherwise.
 */
public boolean addBNFString(final String stream){
	// FIXME Slow implementation.
	
	// Copy current grammar
        ArrayList<Rule> grammarCopy=this;
	// Create appended grammar string
	String newGrammarStream=outputBNF();
	String newGrammar=new String(newGrammarStream);
	newGrammar=stream;
	// Read new grammar
        try{
            if(!readBNFString(newGrammar)){
                    // Restore previous state of Mapper
                    readBNFString(newGrammarStream);
                    return false;
            }
            return true;
        }
        catch(java.lang.Exception e){
            return false;    
        }
	 

}

/**
 * Pretty print the current BNF grammar.
 */
public String outputBNF(){
	String stream=null;
	if(!getValidGrammar()){
		return null;
	}
	Iterator<Rule> r_it=this.iterator();
	while(r_it.hasNext()){
                Rule tmp;
                tmp=r_it.next();
		stream.concat(tmp.lhs.get(tmp.lhs.size()-1).getSymbol() + " ::=");
		// go through productions
		Iterator<Production> p_it=tmp.iterator();
		while(p_it.hasNext()){
			// go through symbols
			Iterator<Symbol> s_it=p_it.next().iterator();
			while(s_it.hasNext()){
				stream.concat(s_it.next().getSymbol());
			}
				stream.concat(" | ");
		}
                stream=stream.trim();
		stream.concat("\n");
		// get next rule
	}
        return stream;
}

/**
 * Returns the address of the rule defining the argument non-terminal symbol,
 *if it exists; otherwise returns NULL.
 */
public Rule findRule(final Symbol nonterminal) throws Exception{
	
	Iterator<Rule> ruleIt=this.iterator();
        Rule tmp;
	while(ruleIt.hasNext()){
            tmp=ruleIt.next();
		if(tmp.lhs.get(tmp.lhs.size()-1).makeComparison(nonterminal))
                    return tmp;
	}
	return null;
}

/**
 *Returns the calculated recursive nature of the Rule passed as argument,
 *and updates its minimum mapping depth (minimumDepth)
 */
private boolean isRecursive(ArrayList<Symbol> visitedRules, Rule currentRule){
	Iterator<Production> prodIt=currentRule.iterator();
	Iterator<Symbol> symbIt;
	Iterator<Symbol> visitedRulesIt=visitedRules.iterator();
	Rule rulePtr=null;
	boolean result;

	// DON'T DO IT - otherwise minimumDepth is not updated properly
	// If this rule has already been labeled, exit
	//if(currentRule->getRecursive()!=SI_Undef){
	//	return currentRule->getRecursive();
	//}

	// Check if this is a recursive call to a previously visited rule
	while(visitedRulesIt.hasNext()){
		if(visitedRulesIt.next().makeComparison(currentRule.lhs.get(currentRule.lhs.size()-1))){
			currentRule.setRecursive(true);
			return true;
		}
	}

	// Go through each production in the rule
	while(prodIt.hasNext()){
                Production tmp_pd=prodIt.next();
		tmp_pd.setMinimumDepth(0);
		symbIt=tmp_pd.iterator();
		// Go through each symbol in the production
		while(symbIt.hasNext()){
                        Symbol tmp_symb=symbIt.next();
			if(tmp_symb.getType().toString().equals("NTSymbol")){// Symbol is non-terminal, possible recursion
				try{
                                    rulePtr=findRule(tmp_symb);// Find defining rule
                                }
                                catch(java.lang.Exception e){
                                    //do nothing
                                }
				if(rulePtr!=null){// Symbol is defined
					// Recursive call
					visitedRules.add(currentRule.lhs.get(currentRule.lhs.size()-1));
					result=isRecursive(visitedRules,rulePtr);
					visitedRules.remove(visitedRules.size()-1);
					if(result){// Production is recursive
						// Mark production as recursive
						tmp_pd.setRecursive(true);
						// Mark current rule also as recursive
						currentRule.setRecursive(true);
					}
					if(tmp_pd.getMinimumDepth()<(rulePtr.getMinimumDepth()+1)){
						tmp_pd.setMinimumDepth(rulePtr.getMinimumDepth()+1);
					}
				}
				else{ // Non-defined non-terminal symbols are considered terminal symbols
					if(tmp_pd.getMinimumDepth()<1){
						tmp_pd.setMinimumDepth(1);
					}
				}
			}
			else{// Terminal symbol
				if(tmp_pd.getMinimumDepth()<1){
					tmp_pd.setMinimumDepth(1);
				}
			}
		}
		//if(prodIt->getRecursive()==SI_Undef){// Production is not recursive
		//	prodIt->setRecursive(SI_NonRec);
		//}
		if(currentRule.getMinimumDepth()>tmp_pd.getMinimumDepth()){// Update rule minimumDepth
			currentRule.setMinimumDepth(tmp_pd.getMinimumDepth());
		}
		//prodIt++;
	}
	//if(currentRule->getRecursive()!=SI_Rec){// Rule is not recursive, as it contains no recursive productions
	//	currentRule->setRecursive(SI_NonRec);
	//	return SI_NonRec;
	//}
	//return SI_Rec;
	return currentRule.getRecursive();
}

/**
 * Update recursive and minimumDepth fields for every Rule
 */
// and Production in grammar.
private void updateRuleFields(){
	ArrayList<Symbol> visitedRules=new ArrayList();
	Iterator<Rule> ruleIt=this.iterator();
        

	clearRuleFields();

	// Go through each rule in the grammar
	while(ruleIt.hasNext()){
            try{
		visitedRules.clear();
            }
            catch(java.lang.NullPointerException e){
                System.out.println(e+"UpdateRuleFields sucks");
            }
                Rule tmp_rule=ruleIt.next();
		tmp_rule.setRecursive(isRecursive(visitedRules,tmp_rule));
	}
	// Second pass, to correctly update all recursive rules
	ruleIt=this.iterator();
	while(ruleIt.hasNext()){
		try{
                    visitedRules.clear();
                }
                catch(java.lang.NullPointerException e){
                     System.out.println(e+"UpdateRuleFields sucks");
                 }
                Rule tmp_rule=ruleIt.next();
		tmp_rule.setRecursive(isRecursive(visitedRules,tmp_rule));
        }
}

/**
 * Update recursive and minimumDepth fields for every Rule
 */
// and Production in grammar.
private void clearRuleFields(){
	Iterator<Rule> ruleIt=this.iterator();
	// Reset minimum depths and recursion fields
	while(ruleIt.hasNext()){
                Rule tmp_rule=ruleIt.next();
		tmp_rule.setMinimumDepth(32767>>1);
		tmp_rule.setRecursive(false);
	}
}

 // ERROR FUNCTION
private boolean ERROR_IN_GRAMMAR(){
    System.out.println("Grammar not loaded;"); 
    try{
        this.clear();
    }
    catch(java.lang.NullPointerException e){
        System.out.println(e);
    }
        setValidGrammar(false); 
        try{
            phenotype.clear();
            phenotype.setValid(false); 
        }
        catch(java.lang.NullPointerException e){
            System.out.println(e);
        }
        
        return false;
    
}
}
//First implementation is complete, this file may pose alot of bugs.
