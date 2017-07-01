#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define  MAX 200

struct produto {
  int id;
  char nome[255];
  float preco;
  int categoria; // 1 para comida, 2 para bebida
  int quantidade;
};

// Caso o parâmetro passado seja verdadeiro (true ou 1), solicita ao usuário que pressione ENTER.
// Depois pausa a execução do programa até que a tecla seja pressionada.
void confirmacao(bool mostrarMensagem) {
  setbuf(stdin, NULL);
  if (mostrarMensagem) printf("Pressione Enter para continuar...");
  getchar();
  setbuf(stdin, NULL);
}

// Função para limpar a tela
void limpar() {
  system("clear || cls");
}

// Função para ler números inteiros fazendo a verificação se a entrada é válida.
// Imprime a string passada no parâmetro e retorna o valor inserido pelo usuário.
// Em caso de erro, é exibido um aviso e a função é executada novamente.
int inputInt (char mensagem[]) {
  char entrada[255];
  int saida;

  printf("%s", mensagem);
  setbuf(stdin, NULL);
  scanf("%[^\n]s", &entrada);

  if (strcmp(entrada, "0") == 0) {
    return 0;
  } else {
    saida = atoi(entrada);
    if (saida != 0) {
      return saida;
    }
    else {
      printf("Erro! Você deve inserir um número inteiro. Tente novamente.\n");
      return inputInt(mensagem);
    }
  }
}

// Função para ler números float fazendo a verificação se a entrada é válida.
// Exeto pelo tipo do retorno, que é um float, a função funciona de forma similar à inputInt
float inputFloat (char mensagem[]) {
  char entrada[255];
  float saida;

  printf("%s", mensagem);
  setbuf(stdin, NULL);
  scanf("%[^\n]s", &entrada);

  for (int i = 0; i < strlen(entrada); i++) {
    if (entrada[i] == ',') // Caso seja inserido valor decimal separado por vírgula, este é trocado para ponto.
      entrada[i] = '.';
  }

  if ((strcmp(entrada, "0") == 0) || (strcmp(entrada, "0.0\n") == 0)) {
    return 0;
  } else {
    saida = atof(entrada);
    if (saida != 0) {
      return saida;
    }
    else {
      printf("Erro! Você deve inserir um número inteiro ou decimal! Tente novamente.\n");
      return inputInt(mensagem);
    }
  }
}

// Exibe uma lista com todos os produtos cadastrados no sistema.
void listarProdutos(struct produto produtos[], int lenth) {
  limpar();
  if (lenth == 0) {
    printf("Nenhum produto cadastrado no sistema.\n");
    return;
  }

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

// Função para cadastrar novos produtos no sistema.
void cadastrar(struct produto produtos[], int lenth) {
  static int contadorID = 0;
  bool erro = false;

  limpar();
  printf("== Novo Produto ==\n");

  produtos[lenth].id = ++contadorID;
  printf("Nome do produto: ");
  setbuf(stdin, NULL);
  scanf("%[^\n]s", &produtos[lenth].nome);
  produtos[lenth].preco = inputFloat("Preço: ");

  do {
    produtos[lenth].categoria = inputInt("Informe uma categoria para o produto:\n1-Comestíveis\n2-Bebidas\n");
    erro = produtos[lenth].categoria < 1 || produtos[lenth].categoria > 2;
    if (erro)
      printf("Erro! Categoria Inválida\n");
  } while (erro); // Caso seja digitado um valor que não pertence à nenhuma categoria, é solicitada uma nova entrada.

  produtos[lenth].quantidade = inputInt("Quantidade em estoque: ");

  printf("Produto \"%s\" cadastrado com sucesso!\n", produtos[lenth].nome);
  confirmacao(true);
}

// Busca a posição de um produto no vetor de produtos usando o seu id para a busca.
// A função retorna -1 caso a busca não encontre o produto com o id informado no parâmetro.
int buscarIndice (struct produto produtos[], int lenth, int id) {
  int posicao = -1;

  for (int i = 0; i < lenth; i++) {
    if (produtos[i].id == id) {
      posicao = i;
    }
  }

  if (posicao == -1) {
    printf("ID inválido! Este ID não está cadastrado no sistema.\n");
    confirmacao(true);
  }

  return posicao;
}

// Faz a busca de um produto e o exibe na tela.
void buscarProduto (struct produto produtos[], int lenth) {
  limpar();
  printf("== Buscar um Produto ==\n");
  int id = inputInt("Informe o ID do produto que deseja buscar: ");
  int posicao = buscarIndice(produtos, lenth, id);// Função buscarIndice utilizada para descobrir a posicao do produto no vetor.

  if (posicao == -1) {//Caso a busca seja mal sucedida, a função é encerrada.
    return;
  } else {// Caso a busca encontre o produto
    struct produto produtoEncontrado[1];// É criada um vetor de produtos com o produto.
    produtoEncontrado[0] = produtos[posicao];// O produto é copiado para o vetor de uma posição.
    listarProdutos(produtoEncontrado, 1);// A função listarProdutos é utilizada para mostrar as informações do produto encontrado.
    confirmacao(true);
  }
}

void alterarProduto() {
  
}

// A função deletarProduto apaga um produto do vetor.
// Retorna 1 se a deleção for bem sucedida, ou 0 se a deleção for cancelada.
int deletarProduto(struct produto produtos[], int lenth) {
  limpar();

  if (lenth == 0) {
    printf("Nenhum produto cadastrado no sistema.\n");
    confirmacao(true);
    return false;
  }

  printf("== Deletar Produto ==\n");
  printf("Digite o ID de um dos produtos da lista para deletar:\n");
  confirmacao(true);
  listarProdutos(produtos, lenth);

  int id, posicao = -1;
  do {
    id = inputInt("ID do item a ser deletado (-1 para cancelar): ");
    if (id == -1) return false;

    posicao = buscarIndice(produtos, lenth, id);
  } while (posicao == -1);

  for (int i = 0; i < lenth; i++) {
    if (i == posicao) {
      produtos[i] = produtos[i+1];
      posicao++;
    }
  }

  return true;
}

/* A função Menu exibe o menu de opções do programa, em seguida lê a entrada do usuário, que é o retorno */
int menu () {
  limpar();
  return inputInt("1 - Cadastrar Produtos\n2 - Listar Produtos\n3 - Buscar Produto\n4 - Alterar Informações de Produto\n5 - Remover Produto\n6 - Realizar Venda\n7 - Sair\n");;
}

int main() {
  struct produto produtos[MAX];
  int lenth = 0;

  /* MENU */
  int opcao;

  do {
    opcao = menu();
    switch (opcao) {
      case 1:
        cadastrar(produtos, lenth);
        lenth++;
        break;
      case 2:
        listarProdutos(produtos, lenth);
        confirmacao(true);
        break;
      case 3:
        buscarProduto(produtos, lenth);
        break;
      case 5:
        if (deletarProduto(produtos, lenth)) lenth--;
        break;
      //case 5:
      case 7:
        break;
      default:
        printf("Opção Inválida. Tente Novamente\n");
        confirmacao(false);
    }
  } while(opcao != 7);

  return 0;
}
