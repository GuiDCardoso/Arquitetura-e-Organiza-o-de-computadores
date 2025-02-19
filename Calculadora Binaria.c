#include <stdio.h>
#include <math.h>
#include <string.h>

int binario_para_decimal(char binario[]) {
    int decimal = 0;
    int tamanho = strlen(binario);

    for (int i = 0; i < tamanho; i++) {
        if (binario[i] == '1') {
            decimal += pow(2, tamanho - 1 - i);
        }
    }
    return decimal;
}

void decimal_para_binario(int decimal, char binario[]) {
    if (decimal == 0) {
        strcpy(binario, "0");
        return;
    }

    int negativo = (decimal < 0);
    if (negativo) decimal = -decimal;

    int i = 0;
    while (decimal > 0) {
        binario[i] = (decimal % 2) + '0';
        decimal /= 2;
        i++;
    }
    binario[i] = '\0';

    // Inverter o resultado
    int n = strlen(binario);
    for (int j = 0; j < n / 2; j++) {
        char temp = binario[j];
        binario[j] = binario[n - 1 - j];
        binario[n - 1 - j] = temp;
    }

    if (negativo) {
        // Aplicar complemento de dois para números negativos
        char complemento[65];
        int len = strlen(binario);

        // Inverter os bits (complemento de 1)
        for (int k = 0; k < len; k++) {
            complemento[k] = (binario[k] == '0') ? '1' : '0';
        }
        complemento[len] = '\0';

        // Adicionar 1
        int carry = 1;
        for (int k = len - 1; k >= 0; k--) {
            if (complemento[k] == '0' && carry == 1) {
                complemento[k] = '1';
                carry = 0;
                break;
            } else if (complemento[k] == '1' && carry == 1) {
                complemento[k] = '0';
            }
        }

        if (carry == 1) {
            // Adicionar bit extra
            for (int j = len; j > 0; j--) {
                complemento[j] = complemento[j - 1];
            }
            complemento[0] = '1';
            complemento[len + 1] = '\0';
        }

        strcpy(binario, complemento);
    }
}

int somar_binarios(char bin1[], char bin2[]) {
    int decimal1 = binario_para_decimal(bin1);
    int decimal2 = binario_para_decimal(bin2);
    return decimal1 + decimal2;
}

void subtrair_binarios(char bin1[], char bin2[], char resultado[]) {
    int decimal1 = binario_para_decimal(bin1);
    int decimal2 = binario_para_decimal(bin2);

    int aux = decimal1 - decimal2;

    decimal_para_binario(aux, resultado);
}

int multiplicar_binarios(char bin1[], char bin2[]) {
    int decimal1 = binario_para_decimal(bin1);
    int decimal2 = binario_para_decimal(bin2);
    return decimal1 * decimal2;
}

int dividir_binarios(char bin1[], char bin2[]) {
    int decimal1 = binario_para_decimal(bin1);
    int decimal2 = binario_para_decimal(bin2);
    if (decimal2 == 0) {
        printf("Erro: Divisão por zero!\n");
        return 0;
    }
    return decimal1 / decimal2;
}

void exibir_menu() {
    printf("\nCalculadora Binária\n");
    printf("1. Somar\n");
    printf("2. Subtrair\n");
    printf("3. Multiplicar\n");
    printf("4. Dividir\n");
    printf("5. Sair\n");
}

int main() {
    char bin1[65], bin2[65], bin_resultado[65];
    int escolha;
    char continuar;

    do {
        exibir_menu();
        printf("Escolha uma operação: ");
        scanf("%d", &escolha);

        if (escolha == 5) break;

        printf("Digite o primeiro número binário: ");
        scanf("%s", bin1);
        printf("Digite o segundo número binário: ");
        scanf("%s", bin2);

        switch (escolha) {
            case 1:
                decimal_para_binario(somar_binarios(bin1, bin2), bin_resultado);
                break;
            case 2:
                subtrair_binarios(bin1, bin2, bin_resultado);
                break;
            case 3:
                decimal_para_binario(multiplicar_binarios(bin1, bin2), bin_resultado);
                break;
            case 4:
                decimal_para_binario(dividir_binarios(bin1, bin2), bin_resultado);
                break;
            default:
                printf("Escolha apenas opções válidas.\n");
                continue;
        }

        printf("Resultado: %s\n", bin_resultado);
        printf("Deseja realizar outra operação? (s/n): ");
        scanf(" %c", &continuar);
    } while (continuar == 's');

    printf("Fim da calculadora.\n");
    return 0;
}
