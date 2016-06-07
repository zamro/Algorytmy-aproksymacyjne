/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package maxsat;

import java.util.Vector;

/**
 *
 * @author kubus
 */
public class Derandomization {
    private final Vector<Clause> vc;
    
    public Derandomization(Vector<Clause> vc){
        this.vc = (Vector<Clause>) vc;
    }
    
}
