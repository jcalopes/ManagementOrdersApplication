/* 
 * File:   API_Leitura_Prototype.h
 * Author: Joaquim
 *
 * Created on 7 de Janeiro de 2013, 3:00
 */

#ifndef API_LEITURA_H
#define	API_LEITURA_H

#include <stdbool.h>

#ifdef	__cplusplus
extern "C" {
#endif

    void readShort(short *const value, const short minValue, 
            const short maxValue, char const* const message);
    
    void readInt(int *const value, const int minValue, 
            const int maxValue, char const* const message);
    
    void readLong(long *const value, const long minValue, 
            const long maxValue, char const* const message);
    
    void readFloat(float *const value, const float minValue, 
        const float maxValue, char const* const message);   
    
    void readDouble(double *const value, const double minValue, 
            const double maxValue, char const* const message);   

    void readChar(char *const value, char const* const message);
    
    bool readString(char *const value, const unsigned int size, char const* const message);
    
    void readBool(bool *const value, char const* const message);
    

#ifdef	__cplusplus
}
#endif

#endif	/* API_LEITURA_H */

