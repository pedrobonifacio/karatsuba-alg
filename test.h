#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "karatsuba.h"
#include <string.h>
#include <dirent.h>

/**
 * Função para testar o caso de teste N
 * @param inputFileName Nome do arquivo de entrada
 * @param outputFileName Nome do arquivo de saída
 */
void testCase(const char *inputFileName, const char *outputFileName)
{
  // Abre os arquivos de entrada e saída
  FILE *inputFile = fopen(inputFileName, "r");
  FILE *outputFile = fopen(outputFileName, "r");

  if (inputFile == NULL || outputFile == NULL)
  {
    perror("Erro ao abrir arquivos de entrada ou saída");
    return;
  }

  // Lê os valores dos arquivos de entrada
  unsigned long long int num1, num2;
  fscanf(inputFile, "%llu %llu", &num1, &num2);

  // Executa a função com os valores dos arquivos de entrada
  unsigned long long int resultado_real = karatsubaInit(num1, num2);

  // Lê o resultado esperado dos arquivos de saída
  unsigned long long int resultado_esperado;
  fscanf(outputFile, "%llu", &resultado_esperado);

  // Compara o resultado real com o resultado esperado
  if (resultado_real == resultado_esperado)
  {
    printf("Teste %s: OK\n\n", inputFileName);
  }
  else
  {
    printf("Teste %s: Falhou\n(Resultado Esperado: %llu, Resultado Real: %llu)\n\n", inputFileName, resultado_esperado, resultado_real);
  }

  // Fecha os arquivos de entrada e saída
  fclose(inputFile);
  fclose(outputFile);
}

/**
 * Função para testar todos os casos de teste, busca os arquivos e chama testCase()
 * @return 0 se o programa executou corretamente, 1 caso contrário
 */
int test()
{
  char inputFileName[1000];
  char outputFileName[1000];

  char currentDir[1000]; // Tamanho suficiente para armazenar o caminho

  if (getcwd(currentDir, sizeof(currentDir)) != NULL)
  {
    // Agora você pode construir os caminhos completos para as pastas de entrada e saída
    char inputDir[1000];
    char outputDir[1000];

    snprintf(inputDir, sizeof(inputDir), "%s/input/", currentDir);
    snprintf(outputDir, sizeof(outputDir), "%s/output/", currentDir);

    DIR *dir;
    struct dirent *ent;

    if ((dir = opendir(inputDir)) != NULL)
    {
      while ((ent = readdir(dir)) != NULL)
      {
        if (ent->d_type == DT_REG)
        { // Verifica se é um arquivo regular
          char inputFileName[1000];
          char outputFileName[1000];
          snprintf(inputFileName, sizeof(inputFileName), "%s%s", inputDir, ent->d_name);
          snprintf(outputFileName, sizeof(outputFileName), "%s%s", outputDir, ent->d_name);

          // Chama a função de teste para este caso
          testCase(inputFileName, outputFileName);
        }
      }
      closedir(dir);
    }
    else
    {
      perror("Erro ao abrir a pasta de entrada");
      return 1;
    }
  }
  else
  {
    perror("Erro ao obter o diretório atual");
    return 1;
  }

  return 0;
}
