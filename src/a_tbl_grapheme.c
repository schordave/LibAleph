/*                                                                     
 * Copyright (c) 2006-2015 David Schor (david@zigwap.com), ZigWap LLC  
 *                                                                     
 * License: MIT                                                        
 */ 


/* this rule table was hand-made using the rules specified in the Unicode Standard Annex #29
 * see http://unicode.org/reports/tr29/#Grapheme_Cluster_Boundary_Rules
 * 
 * rules for breaking and not breaking between two adjacent code points.
 */
static const unsigned char a_grapheme_break_table[a_gcb_count][a_gcb_count] =
{
    /*          |  CR  |  XX  |  CN  |  EX  |  PP  |  SM  |  RI  |  L  |  V  |  T  |  LF  |  LV  |  LVT  
            /---|------|------|------|------|------|------|------|-----|-----|-----|------|------|-------  */
    /*  CR  | */{  1   ,  1   ,  1   ,  1   ,  1   ,  1   ,  1   ,  1  ,  1  ,  1  ,  0   ,  1   ,  1    },  
    /*  XX  | */{  1   ,  1   ,  1   ,  0   ,  1   ,  0   ,  1   ,  1  ,  1  ,  1  ,  1   ,  1   ,  1    },  
    /*  CN  | */{  1   ,  1   ,  1   ,  1   ,  1   ,  1   ,  1   ,  1  ,  1  ,  1  ,  1   ,  1   ,  1    },  
    /*  EX  | */{  1   ,  1   ,  1   ,  0   ,  1   ,  0   ,  1   ,  1  ,  1  ,  1  ,  1   ,  1   ,  1    },  
    /*  PP  | */{  1   ,  0   ,  1   ,  0   ,  0   ,  0   ,  0   ,  0  ,  0  ,  0  ,  1   ,  0   ,  0    },  
    /*  SM  | */{  1   ,  1   ,  1   ,  0   ,  1   ,  0   ,  1   ,  1  ,  1  ,  1  ,  1   ,  1   ,  1    },  
    /*  RI  | */{  1   ,  1   ,  1   ,  0   ,  1   ,  0   ,  0   ,  1  ,  1  ,  1  ,  1   ,  1   ,  1    },  
    /*   L  | */{  1   ,  1   ,  1   ,  0   ,  1   ,  0   ,  1   ,  0  ,  0  ,  1  ,  1   ,  0   ,  0    },  
    /*   V  | */{  1   ,  1   ,  1   ,  0   ,  1   ,  0   ,  1   ,  1  ,  0  ,  0  ,  1   ,  1   ,  1    },  
    /*   T  | */{  1   ,  1   ,  1   ,  0   ,  1   ,  0   ,  1   ,  1  ,  1  ,  0  ,  1   ,  1   ,  1    },  
    /*  LF  | */{  1   ,  1   ,  1   ,  1   ,  1   ,  1   ,  1   ,  1  ,  1  ,  1  ,  1   ,  1   ,  1    },  
    /*  LV  | */{  1   ,  1   ,  1   ,  0   ,  1   ,  0   ,  1   ,  1  ,  0  ,  0  ,  1   ,  1   ,  1    },  
    /* LVT  | */{  1   ,  1   ,  1   ,  0   ,  1   ,  0   ,  1   ,  1  ,  1  ,  0  ,  1   ,  1   ,  1    }   
};
