// INPUT:
// Dois unsigned long long int
// OUTPUT:
// O produto deste dois unsigned long long int

// Algoritmo de Karatsuba
// github: https://github.com/pedrobonifacio/karatsuba-alg
#include <stdio.h>
#include <math.h>

// Evita erros de redefinição ao incluir o arquivo karatsuba.h no test.h e main.c.
#ifndef KARATSUBA_H
#define KARATSUBA_H

/**
 * Obtem a quantidade de digitos de um numero
 * @param number Numero a ser calculado
 * @return Quantidade de digitos do numero
 */
unsigned char getNumberOfDigits(unsigned long long int number)
{
  unsigned char digits = 0;
  while (number != 0)
  {
    number /= 10;
    digits++;
  }
  return digits;
}

/**
 * Algoritmo de Karatsuba
 * @param firstNumber Primeiro numero a ser multiplicado
 * @param secondNumber Segundo numero a ser multiplicado
 * @param digits Quantidade de digitos dos numeros
 * @return Produto dos dois numeros
 */
unsigned long long int karatsuba(unsigned long long int firstNumber, unsigned long long int secondNumber, unsigned char digits)
{
  if (digits <= 3)
  {
    return firstNumber * secondNumber;
  }

  unsigned char halfDigits = digits / 2;
  if (digits % 2 != 0)
  {
    halfDigits++;
  }

  unsigned long long int mostSignificantPartFirst = firstNumber / pow(10, halfDigits);
  unsigned long long int leastSignificantDigitsFirst = firstNumber % (unsigned long long int)pow(10, halfDigits);
  unsigned long long int mostSignificantPartSecond = secondNumber / pow(10, halfDigits);
  unsigned long long int leastSignificantDigitsSecond = secondNumber % (unsigned long long int)pow(10, halfDigits);
  /*
    Sabemos que o u e v podem ser escritos como:
    (A1 · 10^(n/2) + A0)
    sendo A1 a parte mais significativa e A0 a menos significativa

    Entao a equaçao tem o formato assim:
    AxB = (A1 · 10^(n/2) + A0) × (B1 · 10^(n/2) + B0)

    Segundo o paper da USP, isso pode se converter para:

    A*B = A1*B1*10^n + (A1*B0 + A1*B1)*10^(n/2) + A0*B0 

    "A multiplicação por 10n não conta como multiplicação porque representa um mero deslocamento (= shift) do vetor todo para a esquerda. Esse deslocamento é muito mais barato que uma multiplicação pois consome meras n unidades de tempo. Observação análoga vale para a multiplicação por 10n/2."


    vamos trocar as variaveis para ficar mais facil de entender:
    A1 = p
    A0 = q
    B1 = r
    B0 = s

    A*B = p*r*10^n + (p*s + q*r)*10^(n/2) + q*s

 De alguma forma o (p*s + q*r) pode ser calculado com menos multiplicações, e isso é o que o algoritmo de karatsuba faz.
 Entao o algoritmo vira:

 p × r × 10^n + (p × s + q × r) × 10^(n/2) + q × s

 Trocamos o parenteses por variavel:
 y = (p + q) × (r + s)

  equaçao final:
  u × v  =  p × r × 10^(2*m) + ( y − p × r − q × s) × 10^m + q × s 

  substitui as partes por variaveis
  pr = p*r
  qs = q*s
  z = y - pr - qs

  ficando:
  u × v  =  pr × 10^(2*m) + ( z) × 10^m + qs

  */
  unsigned long long int pr = karatsuba(mostSignificantPartFirst, mostSignificantPartSecond, halfDigits);
  unsigned long long int qs = karatsuba(leastSignificantDigitsFirst, leastSignificantDigitsSecond, halfDigits);
  unsigned long long int y = karatsuba(mostSignificantPartFirst + leastSignificantDigitsFirst, mostSignificantPartSecond + leastSignificantDigitsSecond, halfDigits + 1);
  unsigned long long int uv = pr * pow(10, 2 * halfDigits) + (y - pr - qs) * pow(10, halfDigits) + qs;

  return uv;
}

/**
 * Inicia o algoritmo de Karatsuba, é usado para calcular a quantidade de digitos dos numeros, e chamar o algoritmo de karatsuba. Usado no test e no calculateMultiplication.
 * @param firstNumber Primeiro numero a ser multiplicado
 * @param secondNumber Segundo numero a ser multiplicado
 * @return Produto dos dois numeros
 */
unsigned long long int karatsubaInit(unsigned long long int firstNumber, unsigned long long int secondNumber)
{
  unsigned char maxDigits = getNumberOfDigits(firstNumber);
  unsigned char yDigits = getNumberOfDigits(secondNumber);
  if (yDigits > maxDigits)
  {
    maxDigits = yDigits;
  }
  return karatsuba(firstNumber, secondNumber, maxDigits);
}

/**
 * Funcao usada para testar o algoritmo de karatsuba, printa o resultado.
 * @return 0
 */
int calculateMultiplication()
{
  unsigned long long int x, y;
  scanf("%llu %llu", &x, &y);

  unsigned long long int result = karatsubaInit(x, y);

  printf("%llu\n", result);

  return 0;
}
#endif // KARATSUBA_H
