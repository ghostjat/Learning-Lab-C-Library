/*
MIT License

Copyright (c) 2018 Viviano Riccardo

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files ((the "LICENSE")), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/


#include "llab.h"

float get_mean_fitness(species* s, int n_species){
    int i,j;
    float sum = 0,d = 0;
    for(i = 0; i < n_species; i++){
        d+=s[i].numb_all_other_genomes;
        for(j = 0; j < s[i].numb_all_other_genomes; j++){
            sum+=s[i].all_other_genomes[j]->fitness;
        }
    }
    
    if(!d)
        return 0;
        
    return sum/d;
}

float get_mean_specie_fitness(species* s, int i){
    int j;
    float sum = 0,d = 0;
    d = s[i].numb_all_other_genomes;
    if(!d)
        return 0;
    for(j = 0; j < s[i].numb_all_other_genomes; j++){
        sum += s[i].all_other_genomes[j]->fitness;
    }
    return sum/d;
}

genome** sort_genomes_by_fitness(genome** g, int size){
    int i,j = 0,k,z,flag;
    genome** gg = (genome**)malloc(sizeof(genome*)*size);
    genome* temp1;
    genome* temp2;

	
    for(i = 0; i < size; i++){
		flag = 0;
        for(k = 0; k < j; k++){
            if(g[i]->fitness > gg[k]->fitness){
                temp1 = gg[k];
                for(z = k; z < j-1; z++){
                    temp2 = gg[z+1];
                    gg[z+1] = temp1;
                    temp1 = temp2;
                }
                flag = 1;
                gg[z+1] = temp1;
                gg[k] = g[i];
                break;
            }
    
        }
        
        if(!j)
            gg[0] = g[i];
        else if(!flag)
			gg[j] = g[i];
        j++;
    }
    
    return gg;
}