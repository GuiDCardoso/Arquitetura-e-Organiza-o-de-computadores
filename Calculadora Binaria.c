#include <stdio.h>
#include <math.h>
#include <string.h>

// Função para converter binário para decimal
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

// Função para converter decimal para binário
void decimal_para_binario(int decimal, char binario[]) {
    int i = 0;
    while (decimal > 0) {
        binario[i] = (decimal % 2) + '0';
        decimal = decimal / 2;
        i++;
    }
    binario[i] = '\0';

    // Inverter a string binária para o formato correto
    int n = strlen(binario);
    for (int j = 0; j < n / 2; j++) {
        char temp = binario[j];
        binario[j] = binario[n - 1 - j];
        binario[n - 1 - j] = temp;
    }
}

// Função para realizar complemento de dois
void complemento_de_dois(char binario[], char complemento[]) {
    int tamanho = strlen(binario);
    
    // Passo 1: Inverter todos os bits
    for (int i = 0; i < tamanho; i++) {
        complemento[i] = (binario[i] == '0') ? '1' : '0';
    }
    complemento[tamanho] = '\0';

    // Passo 2: Somar 1 ao resultado
    int carry = 1;
    for (int i = tamanho - 1; i >= 0; i--) {
        if (complemento[i] == '1' && carry == 1) {
            complemento[i] = '0';
        } else if (complemento[i] == '0' && carry == 1) {
            complemento[i] = '1';
            carry = 0;
        }
    }
}

// Função para somar dois números binários
int somar_binarios(char bin1[], char bin2[]) {
    int decimal1 = binario_para_decimal(bin1);
    int decimal2 = binario_para_decimal(bin2);
    return decimal1 + decimal2;
}

// Função para subtrair dois números binários
int subtrair_binarios(char bin1[], char bin2[]) {
    int decimal1 = binario_para_decimal(bin1);
    int decimal2 = binario_para_decimal(bin2);
    return decimal1 - decimal2;
}

// Função para multiplicar dois números binários
int multiplicar_binarios(char bin1[], char bin2[]) {
    int decimal1 = binario_para_decimal(bin1);
    int decimal2 = binario_para_decimal(bin2);
    return decimal1 * decimal2;
}

// Função para dividir dois números binários
int dividir_binarios(char bin1[], char bin2[]) {
    int decimal1 = binario_para_decimal(bin1);
    int decimal2 = binario_para_decimal(bin2);
    if (decimal2 == 0) {
        printf("Erro: Divisão por zero!\n");
        return 0;
    }
    return decimal1 / decimal2;
}

// Função para exibir o menu
void exibir_menu() {
    printf("\nCalculadora Binaria\n");
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

        // Verificar se é necessário fazer complemento de dois
        if (bin1[0] == '-') {
            char bin_temp[65];
            strcpy(bin_temp, bin1 + 1);  // Ignorar o sinal
            complemento_de_dois(bin_temp, bin1);  // Calcular complemento de dois
        }

        if (bin2[0] == '-') {
            char bin_temp[65];
            strcpy(bin_temp, bin2 + 1);  // Ignorar o sinal
            complemento_de_dois(bin_temp, bin2);  // Calcular complemento de dois
        }

        int resultado_decimal;
        switch (escolha) {
            case 1:
                resultado_decimal = somar_binarios(bin1, bin2);
                break;
            case 2:
                resultado_decimal = subtrair_binarios(bin1, bin2);
                break;
            case 3:
                resultado_decimal = multiplicar_binarios(bin1, bin2);
                break;
            case 4:
                resultado_decimal = dividir_binarios(bin1, bin2);
                break;
            default:
                printf("Opção inválida.\n");
                continue;
        }

        // Converter o resultado para binário e exibir
        decimal_para_binario(resultado_decimal, bin_resultado);
        printf("Resultado: %s\n", bin_resultado);

        printf("Deseja realizar outra operação? (s/n): ");
        scanf(" %c", &continuar);  // O espaço antes do %c serve para ignorar qualquer caractere de nova linha

    } while (continuar == 's' || continuar == 'S');

    printf("Fim da calculadora.\n");

    return 0;
}
