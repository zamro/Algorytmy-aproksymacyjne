package maxsat;

import java.io.IOException;
import java.io.FileReader;
import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.util.Vector;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author kubus
 */
public class MAXSAT 
{
    public static void main(String[] args) {
        Vector<Clause> clauses = new Vector<>();
        try {
            FileReader fr = new FileReader("ex02");
            BufferedReader tr = new BufferedReader(fr);
            String line = tr.readLine();
            while (line!=null)
            {
                String[] str = line.split(" ", 2);
                clauses.add(new Clause(str[0], str[1].split(" ")));
                System.out.println(clauses.lastElement());
                
                line = tr.readLine();
            }
            fr.close();
        } catch (FileNotFoundException ex) {
            Logger.getLogger(MAXSAT.class.getName()).log(Level.SEVERE, null, ex);
        } catch (IOException ex) {
            Logger.getLogger(MAXSAT.class.getName()).log(Level.SEVERE, null, ex);
        }
        
        Johnson J = new Johnson(clauses);
        double wJ = J.findSolution();
        
        Derandomization D = new Derandomization(clauses);
        double wD = D.findSolution();
        
        System.out.println("\nJohnson: " + wJ + "\nDerandomization: " + wD);
        
        /*
        TEST for ex01 file
        
        int[] val = new int[] {0,1,0};
        System.out.println("");
        for(int i=0; i<clauses.size(); i++){
            System.out.println(clauses.elementAt(i).solve(val));
        }*/
        
    }
    
}
