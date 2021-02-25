#include <stdio.h>
/**
 * @brief Mensagem a informar o utilizador para pressionar uma tecla
 */
#define MSG_PAUSA_TECLA "Prima [Enter] para continuar!!"

const char CAR_NOVA_LINHA = '\n';
const char CAR_FRASE_FIM = '\0';

/**
 * @brief Limpa o buffer de entrada de dados.
 * @warning Caso não exista nenhuma informação no buffer, o programa pode
 *  ficar a aguardar que exista informação no buffer.
 * 
 * Exemplo:
 * @code
 *  char car:
 * 
 *  car = getchar();
 *  cleanInputBuffer();
 * @endcode
 */
void cleanInputBuffer(){
    char ch;

    while ((ch = getchar()) != CAR_NOVA_LINHA && ch != EOF);
}