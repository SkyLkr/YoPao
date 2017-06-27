#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define  MAX 200

struct produto {
  int id;
  char nome[255];
  float preco;
  int categoria; // 1 para comida, 2 para bebida
  int quantidade;
};

void confirmacao() {
  setbuf(stdin, NULL);

  printf("Pressione Enter para continuar...");
  getchar();

  setbuf(stdin, NULL);
}

int inputInt (char mensagem[]) {
  char entrada[255];
  int saida;

  printf("%s", mensagem);
  scanf("%s", &entrada);

  if (strcmp(entrada, "0") == 0) {
    return 0;
  } else {
    saida = atoi(entrada);
    if (saida != 0) {
      return saida;
    }
    else {
      printf("Entrada Inválida! Tente novamente.\n");
      return inputInt(mensagem);
    }
  }
}

float inputFloat (char mensagem[]) {
  char entrada[255];
  float saida;

  printf("%s", mensagem);
  scanf("%s", &entrada);

  for (int i = 0; i < strlen(entrada); i++) {
    if (entrada[i] == ',')
      entrada[i] = '.';
  }

  if ((strcmp(entrada, "0") == 0) || (strcmp(entrada, "0.0") == 0)) {
    return 0;
  } else {
    saida = atof(entrada);
    if (saida != 0) {
      return saida;
    }
    else {
      printf("Entrada Inválida! Tente novamente.\n");
      return inputInt(mensagem);
    }
  }
}

void listarProdutos(struct produto produtos[], int lenth) {
  printf("ID | NOME            | PREÇO     | TIPO\n");
  for (int i = 0; i < lenth; i++) {
    char tipo[10];

    if (produtos[i].categoria == 1) strcpy(tipo, "Comida");
    else if (produtos[i].categoria == 2) strcpy(tipo, "Bebida");

    printf("%*d| ", -3, produtos[i].id);
    printf("%*s| ", -17, produtos[i].nome);
    printf("R$ %4.2f| ", produtos[i].preco);
    printf("%*s\n", -8, tipo);
  }
}

/* Função cadastrar retorna o próximo ID disponível para cadastro no sistema */
int cadastrar(struct produto produtos[], int lenth, int id) {
  int erro = 0;

  printf("== Novo Produto ==\n");

  produtos[lenth].id = ++id;
  printf("Nome do produto: ");
  scanf("%s", &produtos[lenth].nome);
  produtos[lenth].preco = inputFloat("Preço: ");

  do {
    produtos[lenth].categoria = inputInt("Informe uma categoria para o produto:\n1-Comestíveis\n2-Bebidas\n");
    erro = produtos[lenth].categoria < 1 || produtos[lenth].categoria > 2;
    if (erro)
      printf("Erro! Categoria Inválida\n");
  } while (erro);

  produtos[lenth].quantidade = inputInt("Quantidade em estoque: ");

  printf("Produto \"%s\" cadastrado com sucesso!\n", produtos[lenth].nome);
  confirmacao();

  return id;
}

int buscar (struct produto produtos[], int lenth, int id) {
  int posicao = -1;

  for (int i = 0; i < lenth; i++) {
    if (produtos[i].id == id) {
      posicao = i;
    }
  }

  if (posicao == -1) {
    printf("ID inválido! Este ID não está cadastrado no sistema.\n");
    return buscar(produtos, lenth, inputInt("Digite um novo id: "));
  } else {
    return posicao;
  }
}

/* A função deletar retorna 1 se a deleção for bem sucedida, ou 0 se a deleção for cancelada */
int deletar(struct produto produtos[], int lenth) {
  printf("== Deletar Produto ==\n");
  printf("Digite o ID de um dos produtos da lista para deletar:\n");
  confirmacao();
  listarProdutos(produtos, lenth);

  int id = inputInt("ID do item a ser deletado (-1 para cancelar): ");
  if (id == -1) return 0;

  int posicao = buscar(produtos, lenth, id);
  
  for (int i = 0; i < lenth; i++) {
    if (i == posicao) {
      produtos[i] = produtos[i+1];
      posicao++;
    }
  }

  listarProdutos(produtos, --lenth);

  return 1;
}

/* A função Menu exibe o menu de opções do programa, em seguida lê a entrada do usuário, que é o retorno */
int menu () {
  int opcao;

  do {
    system("clear || cls");
    opcao = inputInt("1 - Cadastrar Produtos\n2 - Listar Produtos\n3 - Buscar Produto\n4 - Alterar Informações de Produto\n5 - Remover Produto\n6 - Realizar Venda\n7 - Sair\n");
    if (opcao < 1 || opcao > 7) {
      printf("Opção Inválida. Tente Novamente\n");
      setbuf(stdin, NULL);
      getchar();
    }
  } while (opcao < 1 || opcao > 7);

  return opcao;
}

int main() {
  struct produto produtos[MAX];
  int lenth = 4;
  int contadorID = 4;

  /*contadorID = cadastrar(produtos, lenth, contadorID);
  lenth++;
  contadorID = cadastrar(produtos, lenth, contadorID);
  lenth++;*/

  produtos[0].id = 0;
  strcpy(produtos[0].nome,"Pão");
  produtos[0].preco = 0.5;
  produtos[0].categoria = 1;
  produtos[0].quantidade = 12;

  produtos[1].id = 1;
  strcpy(produtos[1].nome,"Vinho");
  produtos[1].preco = 50;
  produtos[1].categoria = 2;
  produtos[1].quantidade = 5;

  produtos[2].id = 2;
  strcpy(produtos[2].nome,"Mais Vinho");
  produtos[2].preco = 50;
  produtos[2].categoria = 2;
  produtos[2].quantidade = 5;

  produtos[3].id = 3;
  strcpy(produtos[3].nome,"Outro Vinho");
  produtos[3].preco = 50;
  produtos[3].categoria = 2;
  produtos[3].quantidade = 5;

  /*printf("LISTA\n");
  listarProdutos(produtos, lenth);*/
  if (deletar(produtos, lenth)) lenth--;


  return 0;
}