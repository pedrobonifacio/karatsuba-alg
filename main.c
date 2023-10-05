#include "karatsuba.h"
#include "test.h"

/**
 * Função principal
 * @param argc Quantidade de argumentos
 * @param argv Vetor de argumentos, se houver o parametro --test, o programa executará a função de teste com os valores pré-definidos nos arquivos dentro de /input e /output
 * @return 0 se o programa executou corretamente, 1 caso contrário
 */
int main(int argc, char *argv[])
{
  if (argc > 1 && strcmp(argv[1], "--test") == 0)
  {
    // Se o primeiro argumento for "test", execute a função de teste
    return test();
  }
  else
  {
    // Caso contrário, execute a função principal normalmente
    printf("Executando a função para o usuário inserir os números a serem multiplicados.\n");

    return calculateMultiplication();
  }
  return 0;
}