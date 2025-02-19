#include <stdio.h>
#include <math.h>
#include <string.h>

int binarioParaDecimal(char binario[]) {
    int decimal = 0;
    int tamanho = strlen(binario);

    for (int i = 0; i < tamanho; i++) {
        if (binario[i] == '1') {
            decimal += pow(2, tamanho - 1 - i);
        }
    }
    return decimal;
}

void decimalParaBinario(int decimal, char binario[]) {
    if (decimal == 0) {
        strcpy(binario, "0");
        return;
    }

    if (decimal < 0) decimal = -decimal;

    int i = 0;
    while (decimal > 0) {
        binario[i] = (decimal % 2) + '0';
        decimal /= 2;
        i++;
    }
    binario[i] = '\0';

    int n = strlen(binario);
    for (int j = 0; j < n / 2; j++) {
        char temp = binario[j];
        binario[j] = binario[n - 1 - j];
        binario[n - 1 - j] = temp;
    }

    if (decimal < 0) {
        
        char complemento[65];
        int tamanho = strlen(binario);

  
        for (int k = 0; k < tamanho; k++) {
    if (binario[k] == '0') {
        complemento[k] = '1';
    } else {
        complemento[k] = '0';
    }
}
    complemento[tamanho] = '\0';
      
        int carry = 1;
        for (int k = tamanho - 1; k >= 0; k--) {
            if (complemento[k] == '0' && carry == 1) {
                complemento[k] = '1';
                carry = 0;
                break;
            } else if (complemento[k] == '1' && carry == 1) {
                complemento[k] = '0';
            }
        }

        if (carry == 1) {
           
            for (int j = tamanho; j > 0; j--) {
                complemento[j] = complemento[j - 1];
            }
            complemento[0] = '1';
            complemento[tamanho + 1] = '\0';
        }

        strcpy(binario, complemento);
    }
}

int somarBinarios(char bin1[], char bin2[]) {
    int decimal1 = binarioParaDecimal(bin1);
    int decimal2 = binarioParaDecimal(bin2);
    return decimal1 + decimal2;
}

void subtrairBinarios(char bin1[], char bin2[], char resultado[]) {
    int decimal1 = binarioParaDecimal(bin1);
    int decimal2 = binarioParaDecimal(bin2);

    int aux = decimal1 - decimal2;

    decimalParaBinario(aux, resultado);
}

int multiplicarBinarios(char bin1[], char bin2[]) {
    int decimal1 = binarioParaDecimal(bin1);
    int decimal2 = binarioParaDecimal(bin2);
    return decimal1 * decimal2;
}

int dividirBinarios(char bin1[], char bin2[]) {
    int decimal1 = binarioParaDecimal(bin1);
    int decimal2 = binarioParaDecimal(bin2);
    if (decimal2 == 0) {
        printf("Erro: Não dividirás por zero!\n");
        return 0;
    }
    return decimal1 / decimal2;
}

void exibirMenu() {
    printf("\nCalculadora Binária\n");
    printf("1. Somar\n");
    printf("2. Subtrair\n");
    printf("3. Multiplicar\n");
    printf("4. Dividir\n");
    printf("5. Sair\n");
}

int main() {
    char bin1[65], bin2[65], binResultado[65];
    int escolha;
    char continuar;

    do {
        exibirMenu();
        printf("Escolha uma operação: ");
        scanf("%d", &escolha);

        if (escolha == 5) break;

        printf("Digite o primeiro número binário: ");
        scanf("%s", bin1);
        printf("Digite o segundo número binário: ");
        scanf("%s", bin2);

        switch (escolha) {
            case 1:
                decimalParaBinario(somarBinarios(bin1, bin2), binResultado);
                break;
            case 2:
                subtrairBinarios(bin1, bin2, binResultado);
                break;
            case 3:
                decimalParaBinario(multiplicarBinarios(bin1, bin2), binResultado);
                break;
            case 4:
                decimalParaBinario(dividirBinarios(bin1, bin2), binResultado);
                break;
            default:
                printf("Escolha apenas opções válidas.\n");
                continue;
        }

        printf("Resultado: %s\n", binResultado);
        printf("Deseja realizar outra operação? (s/n): ");
        scanf(" %c", &continuar);
    } while (continuar == 's');

    printf("Obrigado por utilizar minha calculadora!! S2\n");
    return 0;
}