/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package maxsat;

import static java.lang.Math.*;
import java.util.Random;
import java.util.Vector;

/**
 *
 * @author kubus
 */
public class Johnson {
    private final Vector<Clause> vc;
    private int maxIndex = 0;
    
    public Johnson(Vector<Clause> vc){
        this.vc = vc;
        
        for(int i=0; i<vc.size(); i++) {
            maxIndex = max(maxIndex, vc.elementAt(i).getMaxIndex());
        }
    }
    
    public double findSolution() {
        Random rand = new Random();
        int[] val = new int[maxIndex];
        System.out.println("\nJohnson");
        for(int i=0; i<maxIndex; i++) {
            val[i] = rand.nextBoolean()?1:0;
            System.out.print(val[i] + " ");
        }
        
        double ret = 0.0f;
        System.out.println("\n");
        for(int i=0; i<vc.size(); i++){
            double w = vc.elementAt(i).solve(val);
            ret += w;
            System.out.println(w + " " + ret);
        }
        System.out.println("");
        return ret;
    }
}
