/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package maxsat;

import static java.lang.Math.max;
import java.util.Arrays;
import java.util.Vector;

/**
 *
 * @author kubus
 */
public class Derandomization {
    private final Vector<Clause> vc;
    private int maxIndex = 0;
    
    public Derandomization(Vector<Clause> vc){
        this.vc = vc;
        
        for(int i=0; i<vc.size(); i++) {
            maxIndex = max(maxIndex, vc.elementAt(i).getMaxIndex());
        }
    }
    
    public double findSolution() {
        double w1, w0;
        int val[] = new int[maxIndex];
        Arrays.fill(val, -1);
        
        System.out.println("\nDerandomization");
        for(int i=0; i<maxIndex; i++) {
            val[i] = 0;
            w0 = sumProb(val);
            val[i] = 1;
            w1 = sumProb(val);
            if(w0 > w1) {
                val[i] = 0;
                System.out.println("0 " + w0);
            }
            else System.out.println("1 " + w1);
        }
        
        System.out.println("");
        return sumSolv(val);
    }
    
    private double sumProb(int[] val) {
        double summ = 0.0f;
        for(int i=0; i<vc.size(); i++) {
            summ += vc.elementAt(i).prob(val);
        }
        
        return summ;
    }
    
    private double sumSolv(int[] val) {
        double ret = 0.0f;
        for(int i=0; i<vc.size(); i++){
            double w = vc.elementAt(i).solve(val);
            ret += w;
            System.out.println(w + " " + ret);
        }
        System.out.println("");
        return ret;
    }
    
}
