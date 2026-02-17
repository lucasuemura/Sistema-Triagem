// Bibliotecas da linguagem C
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <locale.h>

//----------------------------------------------------------------------------------------------------//

/* Lê uma resposta do usuário esperando 's' ou 'n' (sim ou não)
   Retorna 1 para sim, 0 para não. Aceita S/s, N/n. Se entrada for inválida, pede novamente */
int lerOpcao(const char *opcao) {
    char linha[32];
    
    while (1) {
        printf("%s (s/n): ", opcao);
        if (fgets(linha, sizeof(linha), stdin) == NULL) {
            clearerr(stdin); // Limpa indicadores de erro/EOF
            printf("\nErro na leitura da entrada. Tente novamente.\n");
            continue;
        }

        // Tenta encontrar e remover o caractere de nova linha
        char *newline_pos = strchr(linha, '\n');
        if (newline_pos != NULL) {
            *newline_pos = '\0';
        } else {
            /* Se a newline não foi encontrado, a linha lida era muito longa
               e há caracteres restantes no buffer de entrada. */
            printf("Entrada muito longa. Por favor, digite apenas 's' ou 'n'.\n");
            continue;
        }

        // Caso o usuário deixe a resposta vazia
        size_t i = 0;
        while (linha[i] && isspace((unsigned char)linha[i])) i++;

        if (!linha[i]) {
            printf("Resposta vazia. Digite novamente.\n");
            continue;
        }

        char c = tolower((unsigned char)linha[i]);
        if (c == 's') return 1;
        if (c == 'n') return 0;

        printf("Resposta inválida. Digite novamente. Use 's' para sim ou 'n' para não.\n");
    }
}

//----------------------------------------------------------------------------------------------------//

/* Essa função exibe recomendações gerais de acordo com o nível de urgência e o possível diagnóstico */
void diagnosticoRecomendacao(const char *diagnostico, int urgente) {
    printf("\n===== RESULTADO DA TRIAGEM =====\n");
    printf("Diagnóstico sugerido: %s\n", diagnostico);
    printf("\nRecomendações básicas:\n");
    if (urgente) {
        printf("- SINAL DE ALERTA: procure atendimento médico imediatamente (febre alta persistente, dificuldade para respirar, sangramento, confusão mental, vômitos persistentes, dor intensa).\n");
    }
    printf("- Repouso e evitar esforços.\n");
    printf("- Hidratação adequada (água ou soluções de reidratação oral se houver vômitos/diarreia).\n");
    printf("- Tomar antitérmico ou analgésico conforme orientação local (ou somente após uma orientação médica).\n");
    printf("- Se os sintomas piorarem ou sinais de gravidade aparecerem, buscar serviço de saúde.\n");
    printf("- Evitar automedicação inadequada e procurar orientação quando possível.\n");

    if (strcmp(diagnostico, "Possível infecção viral respiratória (gripe/viral)") == 0) {
        printf("- Isolar-se quando possível e usar máscara ao conviver com outras pessoas, se disponível.\n");
    }
    if (strcmp(diagnostico, "Possível dengue (procure serviço de saúde)") == 0) {
        printf("- Evitar anti-inflamatórios até avaliação médica, pois podem aumentar risco de sangramento.\n");
        printf("- Monitorar sinais de alarme: dor abdominal intensa, vômitos persistentes, sangramentos, tontura.\n");
    }
    printf("\nAviso: este sistema fornece apenas uma triagem inicial e não substitui avaliação médica presencial.\n");
}

//----------------------------------------------------------------------------------------------------//

// Programa principal que irá exibir todos os procedimentos/funções
int main(void) {
	setlocale(LC_ALL, "Portuguese");
	
    printf("        ========== Bem-vindo(a) ao Sistema de Triagem de Sintomas ==========\n");
    printf("Este sistema oferece apenas sugestões iniciais! Em caso de dúvida, procure uma unidade de saúde.\n\n");

    int febre = lerOpcao("Você está com febre ou teve febre recentemente?");
    int manchasVermelhas = lerOpcao("Você tem manchas vermelhas na pele?");
    int dorCabeca = lerOpcao("Você está com dor de cabeça muito intensa ou sensibilidade à luz?");
    int dorMuscular = lerOpcao("Você tem dor nas articulações ou dores musculares fortes?");
    int tosse = lerOpcao("Você está com tosse?");
    int faltaAr = lerOpcao("Você está com falta de ar ou respiração mais difícil do que o normal?");
    int dorGarganta = lerOpcao("Você está com dor de garganta?");
    int coriza = lerOpcao("Você está com coriza ou espirros frequentes?");
    int vomito = lerOpcao("Você está com vômito?");
    int diarreia = lerOpcao("Você está com diarreia?");
    int sangramento = lerOpcao("Você teve sangramentos nas gengivas ou nariz ou vômito com sangue?");

    const char *diagnostico = "Sintomas leves ou não específicos";
    int urgente = 0;

    if (febre) {
        if (manchasVermelhas) {
            diagnostico = "Possível dengue, procure serviço de saúde!";
            if (sangramento || dorCabeca || vomito) urgente = 1;
        } else if (tosse && dorGarganta) {
            diagnostico = "Possível infecção viral respiratória (gripe/viral)";
            if (faltaAr) urgente = 1;
        } else if (dorCabeca && dorMuscular) {
            diagnostico = "Sintomas que sugerem infecção com cefaleia intensa, procure serviço de saúde!";
            urgente = 1;
        } else if (tosse && !coriza) {
            diagnostico = "Possível infecção respiratória sem coriza (monitore sinais!)";
        } else {
            diagnostico = "Sintomas com febre (causa não determinada)";
            if (faltaAr || sangramento) urgente = 1;
        }
    } else {
        if (tosse && coriza) {
            diagnostico = "Possível resfriado (infecção respiratória leve)";
        } else if (vomito || diarreia) {
            diagnostico = "Possível gastroenterite (possível desidratação)";
            if (vomito && diarreia) urgente = 1;
        } else if (faltaAr) {
            diagnostico = "Falta de ar sem febre — pode necessitar avaliação (urgente)";
            urgente = 1;
        } else {
            diagnostico = "Sintomas leves ou não específicos";
        }
    }

    diagnosticoRecomendacao(diagnostico, urgente);

    printf("\nObrigado por usar o sistema de triagem.\n");

	system("pause");
    return 0;
}
