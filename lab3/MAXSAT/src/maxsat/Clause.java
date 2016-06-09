/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package maxsat;

import static java.lang.Math.*;

/**
 *
 * @author kubus
 */
public class Clause {
    private final double weight;
    private final int[] variables;
    private int maxIndex = 0;
    
    public Clause(String w, String[] v) {
        weight = Double.parseDouble(w);
        variables = new int[v.length];
        for(int i=0; i<v.length; i++) {
            variables[i] = Integer.parseInt(v[i]);
            maxIndex = max(maxIndex, abs(variables[i]));
        }
    }
    
    public double solve(int[] values){
        int ret = 0;
        for(int i=0; i<variables.length; i++)
        {
            if(variables[i]>0) ret |= values[variables[i]-1];
            else ret |= 1^values[-variables[i]-1];
        }
        if(ret>1 || ret<0) throw new IllegalArgumentException("Wrong argument");
        return weight * ret;
    }
    
    public int getMaxIndex() {
        return maxIndex;
    }
    
    public double prob(int[] values) {
        int unused = 0;
        int ret = 0;
        for(int i=0; i<variables.length; i++) {
            if(variables[i]>0) {
                if (values[variables[i]-1] < 0) unused++;
                else ret |= values[variables[i]-1];
            }
            else {
                if (values[-variables[i]-1] < 0) unused++;
                else ret |= 1^values[-variables[i]-1];
            }
        }
        
        if(ret>1 || ret<0) throw new IllegalArgumentException("Wrong argument");
        if(ret==1) return weight;
        return (1.0f -  pow(0.5f, (double) unused))*weight;
    }
    
    @Override
    public String toString(){
        String ret = "";
        ret += "w: " + weight + "\nv: ";
        for(int i=0; i<variables.length; i++) ret += variables[i] + " ";
        return ret+"\n";
    }
    
}
