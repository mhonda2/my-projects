//
//  echo.c
//  
//
//  Created by mhonda2 on 1/27/20.
//

#include <stdio.h>

int main(int argc, const char * argv[]) {
    int c = getchar();
    
    while (c != EOF) {
        putchar(c);
    }
    
    return 0;
}
