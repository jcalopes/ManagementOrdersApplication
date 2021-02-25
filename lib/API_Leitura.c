/** 
 * @file
 * @author ESTGF.LP
 *
 * @brief Biblioteca para leitura de dados do standard input.
 *      Tipos suportados: Inteiro, Real, Caracter, Booleano (simples) e Frase (String).
 
 * @warning Esta biblioteca pretende ser uma base de trabalho. Caso pretenda 
 *      pode melhorar ou acrescentar novas funcionalidades de acordo com o 
 *      objectivo
 * 
 * @date 2014-09-01 14:00
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "API_Utils.h"

    /**
     * @brief Mensagem a mostrar ao utilizador caso o número inteiro introduzido 
     *  nao respeite o limite inicial e final definido.
     */
    #define MSG_LEITURA_INT_GAMA_INVALIDA "O numero que introduziu e invalido. \n"
/**
     * @brief Mensagem a mostrar ao utilizador caso o número inteiro introduzido 
     *  nao respeite o limite inicial e final definido.
     */
    #define MSG_LEITURA_LONG_GAMA_INVALIDA "O numero que introduziu e invalido. Introduza um valor entre %ld e %ld.\n"
    /**
     * @brief Mensagem a informar o utilizador caso o número real introduzido 
     *  nao respeite o limite inicial e final definido.
     */
    #define MSG_LEITURA_REAL_GAMA_INVALIDA "\nO numero que introduziu e invalido. Introduza um valor entre %.3lf e %.3lf.\n"
    /**
     * @brief Mensagem a mostrar ao utilizador caso o número (real ou inteiro) 
     *  introduzido seja inválido.
     */
    #define MSG_LEITURA_NUMERO_INVALIDO "\nO valor que introduziu nao e um numero valido.\n"

    /**
     * @brief Mensagem a mostrar ao utilizador caso o número (real ou inteiro) 
     *  introduzido seja inválido.
     */
    #define MSG_LEITURA_BOOLEANO_INVALIDO "\nO valor que introduziu nao e um numero valido.\n"

    /**
     * @brief Número de argumentos esperados na leitura de números (inteiro ou real)
     */
    static const unsigned short SCANF_ARGUMENTOS_ESPERADOS = 1;
    static const char CAR_NOVA_LINHA = '\n';
    static const char CAR_FRASE_FIM = '\0';
    
    /**
     * Envia uma mensagem para o standard output (tipicamente o ecra)
     * @param message   A mensagem a ser visualizada
     * 
     * Exemplo:
     * @code
     * displayMessage("Mostra a minha mensagem no ecra!!!!");
     * @endcode
     */
    void displayMessage(char const *const message){
        printf("\n%s", message);
    }
    
    /**
     * Solicita um valor ao standard input
     * @param value A referência para onde será lido o valor (tipicamente introduzido pelo utilizador)
     */
    void readShortFromStdin(short *const value) {
      
        while (scanf("%hd", value) != SCANF_ARGUMENTOS_ESPERADOS) {
            printf(MSG_LEITURA_NUMERO_INVALIDO); 
            cleanInputBuffer();
        }
        cleanInputBuffer();
   }
    
    /**
     * Solicita um valor ao standard input
     * @param value A referência para onde será lido o valor (tipicamente introduzido pelo utilizador)
     */
    void readIntFromStdin(int *const value) {

        while (scanf("%d", value) != SCANF_ARGUMENTOS_ESPERADOS) {
            printf(MSG_LEITURA_NUMERO_INVALIDO);   
            cleanInputBuffer();
        }
        cleanInputBuffer();
   }    
    /**
     * Solicita um valor ao standard input
     * @param value A referência para onde será lido o valor (tipicamente introduzido pelo utilizador)
     */
    void readLongFromStdin(long *const value) {

        while (scanf("%ld", value) != SCANF_ARGUMENTOS_ESPERADOS) {
            printf(MSG_LEITURA_NUMERO_INVALIDO);    
            cleanInputBuffer();
        }
        cleanInputBuffer();
   }

    /**
     * Solicita um valor do o standard input
     * @param value A referência para onde será lido o valor (tipicamente introduzido pelo utilizador)
     */
    void readFloatFromStdin(float *const value) {

        while (scanf("%f", value) != SCANF_ARGUMENTOS_ESPERADOS) {
            printf(MSG_LEITURA_NUMERO_INVALIDO);    
            cleanInputBuffer();
        }
        cleanInputBuffer();
    }
        
    /**
     * Solicita um valor ao standard input
     * @param value A referência para onde será lido o valor (tipicamente introduzido pelo utilizador)
     */
    void readDoubleFromStdin(double *const value) {

        while (scanf("%lf", value) != SCANF_ARGUMENTOS_ESPERADOS) {
            printf(MSG_LEITURA_NUMERO_INVALIDO);   
            cleanInputBuffer();
        }
        cleanInputBuffer();
    }

    /**
     * @brief Solicita um número inteiro longo ao utilizador. 
     * O número introduzido pelo utilizador está entre um valor mínimo e máximo.
     *      
     * @param value A referência (endereço de memória) onde o valor lido sera armazenado.
     * @param minValue O valor mínimo permitido.
     * @param maxValue O valor máximo permitido.
     * @param message A mensagem a mostrar ao utilizador
     * 
     * Exemplo:
     * @code
     *  long num;
     *  readLong(&num, 0, 1000, "Introduza um numero entre 0 e 1000: ");
     * @endcode
     */
     void readLong(long *const value, const long minValue, 
            const long maxValue, char const* const message) {
        
        displayMessage(message);
        readLongFromStdin(value);
        while (*value < minValue || *value > maxValue) {
            printf(MSG_LEITURA_LONG_GAMA_INVALIDA, minValue, maxValue);
            displayMessage(message);
            readLongFromStdin(value);
        }
    }
    
      /**
     * @brief Solicita um número inteiro ao utilizador. 
     * O número introduzido pelo utilizador está entre um valor mínimo e máximo.
     *      
     * @param value A referência (endereço de memória) onde o valor lido sera armazenado.
     * @param maxValue O valor mínimo permitido.
     * @param maxValue O valor máximo permitido.
     * @param message A mensagem a mostrar ao utilizador
     * 
     * Exemplo:
     * @code
     *  int num;
     *  readShort(&num, 0, 200, "Introduza um numero entre 0 e 200: ");
     * @endcode
     */
    void readInt(int *const value, const int minValue, 
            const int maxValue, char const* const message) {
        
        displayMessage(message);
        readIntFromStdin(value);
        while (*value < minValue || *value > maxValue) {
            printf(MSG_LEITURA_INT_GAMA_INVALIDA, minValue, maxValue);
            displayMessage(message);
            readIntFromStdin(value);
        }
    }
    
     /**
     * @brief Solicita um número inteiro pequeno ao utilizador. 
     * O número introduzido pelo utilizador está entre um valor mínimo e máximo.
     *      
     * @param value A referência (endereço de memória) onde o valor lido sera armazenado.
     * @param maxValue O valor mínimo permitido.
     * @param maxValue O valor máximo permitido.
     * @param message A mensagem a mostrar ao utilizador
     * 
     * Exemplo:
     * @code
     *  short num;
     *  readShort(&num, 0, 200, "Introduza um numero entre 0 e 200: ");
     * @endcode
     */
    void readShort(short *const value, const short minValue, 
            const short maxValue, char const* const message) {
        
        displayMessage(message);
        readShortFromStdin(value);
        while (*value < minValue || *value > maxValue) {
            printf(MSG_LEITURA_INT_GAMA_INVALIDA, minValue, maxValue);
            displayMessage(message);
            readShortFromStdin(value);
        }
    }
    
    /**
     * @brief Solicita um número real pequeno ao utilizador. 
     * O número introduzido pelo utilizador está entre um valor mínimo e máximo.
     *      
     * @param value A referência (endereço de memória) onde o valor lido sera armazenado.
     * @param minValue O valor mínimo permitido.
     * @param maxValue O valor máximo permitido.
     * @param message A mensagem a mostrar ao utilizador
     * 
     * Exemplo:
     * @code
     *  floar num;
     *  readFloat(&num, 10.0, 999.99, "Introduza um numero entre 10.0 e 999.99: ");
     * @endcode
     */
    void readFloat(float *const value, const float minValue, 
            const float maxValue, char const* const message) {
        
        displayMessage(message);
        readFloatFromStdin(value);
        while (*value < minValue || *value > maxValue) {
            printf(MSG_LEITURA_REAL_GAMA_INVALIDA, minValue, maxValue);
            displayMessage(message);
            readFloatFromStdin(value);
        }
    }
        
    /**
     * @brief Solicita um número real longo ao utilizador. 
     * O número introduzido pelo utilizador está entre um valor mínimo e máximo.
     *      
     * @param value A referência (endereço de memória) onde o valor lido sera armazenado.
     * @param minValue O valor mínimo permitido.
     * @param maxValue O valor máximo permitido.
     * @param message A mensagem a mostrar ao utilizador
     * 
     * Exemplo:
     * @code
     *  double num;
     *  readDouble(&num, 0.0, 999.99, "Introduza um numero entre 0.0 e 999.99: ");
     * @endcode
     */
    void readDouble(double *const value, const double minValue, 
            const double maxValue, char const* const message) {
        
        displayMessage(message);
        readDoubleFromStdin(value);
        while (*value < minValue || *value > maxValue) {
            printf(MSG_LEITURA_REAL_GAMA_INVALIDA, minValue, maxValue);
            displayMessage(message);
            readDoubleFromStdin(value);
        }
    }

    /**
     * @brief Solicita um caracter ao utilizador. 
     *      
     * @param value A referência (endereço de memória) onde o valor lido sera armazenado.
     * @param message A mensagem a mostrar ao utilizador
     * 
     * Exemplo:
     * @code
     *  char genero;
     *  readChar(&genero, "Introduza o genero do aluno (M/F): ");
     * @endcode
     */
    void readChar(char *const value, char const* const message) { 
        displayMessage(message);
        *value = getchar();
        cleanInputBuffer();
    }
    
    /**
     * @brief Lê uma cadeia de caracteres (string) através da stream stdin
     * 
     * @param frase - Apontador para a frase lida.
     * @param tamanho - Tamanho máximo da frase a ser lida. @warning: O tamanho 
     *  da frase deve ter em conta o espaço para o  carácter de término da 
     *  string ('\0')
     * @param message A mensagem a mostrar ao utilizador
     * 
     * @return 1 em caso de leitura com sucesso, 0 caso ocorra um erro.
     *  
     * Exemplo:
     * @code
     *  char nome[100 + 1];
     * 
     *  printf("Introduza o seu nome: ");
     *  if (lerFrase (nome, 100 + 1) == 1)
     *      printf("O nome lido e: %s", nome);
     * @endcode
     */
    bool readString(char * const value, const unsigned int size, char const* const message) {

        displayMessage(message);
        if (fgets(value, size, stdin) != NULL) {
            const unsigned int sTam = strlen(value) - 1;

            if (value[sTam] == CAR_NOVA_LINHA) {
                value[sTam] = CAR_FRASE_FIM;
            }else{
                cleanInputBuffer();
            }            
            return true;
        } else
            return false;
    }
    
    /**
     * @brief Solicita um valor booleano (1 ou 0) ao utilizador. 
     *      
     * @param value A referência (endereço de memória) onde o valor lido sera armazenado.
     * @param message A mensagem a mostrar ao utilizador
     * 
     * Exemplo:
     * @code
     *  bool estado;
     *  readBool(&estado, "Introduza o estado do aluno (0/1): ");
     * @endcode
     */
    void readBool(bool *const value, char const* const message){
        
        const unsigned short minValue = 0, maxValue = 1;
        short temp;
        
        displayMessage(message);
        readShortFromStdin(&temp);
        while (temp < minValue || temp > maxValue) {
            printf(MSG_LEITURA_BOOLEANO_INVALIDO);
            displayMessage(message);
            readShortFromStdin(&temp);
        }
        
        *value = temp;
    }