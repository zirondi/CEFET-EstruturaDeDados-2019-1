#include<iostream>

using namespace std;

//Structs:

//Struct dos Pedidos: contém o ID do produto (vindo da matriz de referência), a quantidade do produto e o ponteiro pro próximo pedido do cliente.
struct pedido{
	int pedidoID;
	int qntPedido;
	float pedidoValor;
	struct pedido *proxPedido;
};

typedef struct pedido *ptrPedido;

//Struct do Cliente: contém o ID do cliente, o ponteiro pros seus pedidos e o ponteiro pro proximo cliente.
struct cliente{
	int clienteID;
	ptrPedido pedidoCliente;
	struct cliente *proxCliente; 
};

typedef struct cliente *ptrCliente;

//Escopo:

int menu(); //Pronto

//Cliente
void insereCliente(); //Pronto
void removeCliente(ptrCliente endCliente); //Pronto
void listaCliente(); //Pronto
bool clienteVazia(); //Pronto
ptrCliente procuraClienteID(int IDCliente); //Pronto


//Pedido
void inserePedido(); //Pronto
void listaPedido(); //Pronto
void removePedido(ptrCliente endCliente); //Pronto
bool pedidoVazia(ptrCliente EndCliente); //Pronto
ptrPedido procuraPedidoID(int IDPedido, ptrCliente endCliente); //Pronto

//Caixa
void fechaCliente(); //Pronto - falta comentar;

/*
Váriaveis globais:

inicioCliente é o ponteiro pra minha lista de clientes;
indiceMenu dita se eu mostro o logo do programa ao retornar ao menu ou não;
movimento é o total de dinheiro que passou pelo caixa.
*/

ptrCliente inicioCliente = NULL;
int indiceMenu = 0;
float movimento = 0;

//Funções:

//A main é apenas uma função menu que chama as outras funções do programa;
int main(){
 	int op;
 	do {
 		op = menu();
 		switch(op){
 			case 1: insereCliente(); break;
 			case 2: listaCliente();  break;
 			case 3: inserePedido();  break;
 			case 4: listaPedido();   break;
 			case 5: fechaCliente();  break;
 			case 6: op = 0;          break;
 		}
 	}while(op != 0);

 	//A linha "cout << "\033c";" apaga qualquer texto que foi exibido antes na tela do terminal e reseta a posição do cursor. 
 	//Li que é um comando multiplataforma, mas só tive como testar isso no terminal do ubunto, o programa funciona normal sem ela, porém deixa TODO texto na tela, o que fica gigante rapidamente;
 	//Usarei essa linha sempre que for desenhar novas caixas de texto no programa;
	//O comando cin.get(); é para o usuário ter que apertar enter para prosseguir (ou seja segurar a mensagem na tela). Ele é chamado 2 vezes pois o primeiro limpa o buffer e o segundo espera pelo enter.
 	cout << "\033c";
	cout << "##############################################################################" << endl;
	cout << "#                  Opção 6: Fechar o caixa                                   #" << endl;
	cout << "#                                                                            #" << endl;
	cout << "#                  O rendimento do dia foi de " << movimento << " reais" << endl;
	cout << "#                                                                            #" << endl;
	cout << "##############################################################################" << endl;
	cin.get();
 	cin.get();

 	cout << "\033c";
	cout << "##############################################################################" << endl;
	cout << "#                  Obrigado por usar o software Caixa 2.0                    #" << endl;
	cout << "#                               Até mais!                                    #" << endl;
	cout << "##############################################################################" << endl;
}

//A função menu desenha meu menu. Ela verifica a var global indiceMenu para desenhar o logo apenas na primeira vez que o usuário acessar o menu;
int menu(){
	int opcao;
	
	if (indiceMenu == 0){
		cout << "\033c";
		cout << "##############################################################################" << endl;
	 	cout << "#                                                                            #" << endl;
	 	cout << "#  _|_|_|    _|_|    _|_|_|  _|      _|    _|_|          _|_|          _|    #" << endl;
	 	cout << "#_|        _|    _|    _|      _|  _|    _|    _|      _|    _|      _|  _|  #" << endl;
	 	cout << "#_|        _|_|_|_|    _|        _|      _|_|_|_|          _|        _|  _|  #" << endl;
	 	cout << "#_|        _|    _|    _|      _|  _|    _|    _|        _|          _|  _|  #" << endl;
	 	cout << "#  _|_|_|  _|    _|  _|_|_|  _|      _|  _|    _|      _|_|_|_|  _|    _|    #" << endl;
	 	cout << "#                                                                            #" << endl;
	 	cout << "#                                                  Made by Zirondi Inc. 1986 #" << endl;
	 	cout << "##############################################################################" << endl;
		cout << "##############################################################################" << endl;
		cout << "#   Bem vindo ao Caixa 2.0 - A nova maneira de administrar seu restaurante!  #" << endl;
		cout << "#                                                                            #" << endl;
		cout << "#                  Digite 1 para adicionar um cliente.                       #" << endl;
		cout << "#                  Digite 2 para listar os clientes.                         #" << endl;
		cout << "#                  Digite 3 para adicionar um pedido.                        #" << endl;
		cout << "#                  Digite 4 para listar os pedidos de um cliente.            #" << endl;
		cout << "#                  Digite 5 para fechar a conta de um cliente.               #" << endl;
		cout << "#                  Digite 6 para fechar o caixa.                             #" << endl;
		cout << "#                                                                            #" << endl;
		cout << "##############################################################################" << endl;
		cin >> opcao;
		indiceMenu++;
		return opcao;
	}
	
	else{
		cout << "\033c";
		cout << "##############################################################################" << endl;
		cout << "#                  Bem vindo de volta ao Caixa 2.0!                          #" << endl;
		cout << "#                                                                            #" << endl;
		cout << "#                  Digite 1 para adicionar um cliente.                       #" << endl;
		cout << "#                  Digite 2 para listar os clientes.                         #" << endl;
		cout << "#                  Digite 3 para adicionar um pedido.                        #" << endl;
		cout << "#                  Digite 4 para listar os pedidos de um cliente.            #" << endl;
		cout << "#                  Digite 5 para fechar a conta de um cliente.               #" << endl;
		cout << "#                  Digite 6 para fechar o caixa.                             #" << endl;
		cout << "#                                                                            #" << endl;
		cout << "##############################################################################" << endl;
		cin >> opcao;
		return opcao;
	}
}

//Funções CLIENTE

//A função insereCliente primeiro verifica se o ID já existe, existindo ele retorna um erro. Caso o contrário, é criado um novo cliente.
void insereCliente(){
	int IDCliente;
	ptrCliente auxCliente;

	cout << "\033c";
	cout << "##############################################################################" << endl;
	cout << "#                  Opção 1: Adicionar um cliente                             #" << endl;
	cout << "#                                                                            #" << endl;
	cout << "#                  Por favor, digite o código do Cliente.                    #" << endl;
	cout << "#                                                                            #" << endl;
	cout << "##############################################################################" << endl;
	cin >> IDCliente;

	auxCliente = procuraClienteID(IDCliente);
	
	if (auxCliente != NULL){
		cout << "\033c";
		cout << "##############################################################################" << endl;
		cout << "#                  Opção 1: Adicionar um cliente                             #" << endl;
		cout << "#                                                                            #" << endl;
		cout << "#                  O código já existe, por favor tente novamente.            #" << endl;
		cout << "#                                                                            #" << endl;
		cout << "##############################################################################" << endl;
		
		cin.get();
		cin.get();
	}


	else{
		ptrCliente auxCliente;
		auxCliente = new cliente;
		auxCliente -> proxCliente = inicioCliente;
		auxCliente -> pedidoCliente = NULL;
		auxCliente -> clienteID = IDCliente;
		inicioCliente = auxCliente;

		cout << "\033c";
		cout << "##############################################################################" << endl;
		cout << "#                  Opção 1: Adicionar um cliente                             #" << endl;
		cout << "#                                                                            #" << endl;
		cout << "#                  Cliente adicionado com sucesso.                           #" << endl;
		cout << "#                                                                            #" << endl;
		cout << "##############################################################################" << endl;
		cin.get();
		cin.get();
	}
}

//A função listaCliente chama primeiro a função clienteVazia para saber se há algum cliente ja cadastrado na lista, caso verdade a função simplesmente desenha uma mensagem avisando que não há nenhum cliente cadastrado;
void listaCliente(){
	if (clienteVazia()){
		cout << "\033c";
		cout << "##############################################################################" << endl;
		cout << "#                  Opção 2: Listar os clientes                               #" << endl;
		cout << "#                                                                            #" << endl;
		cout << "#                  No momento não há nenhum cliente cadastrado.              #" << endl;
		cout << "#                                                                            #" << endl;
		cout << "##############################################################################" << endl;
		
		cin.get();
		cin.get();
	}
	
	//Caso haja pelo menos 1 cliente na minha lista de clientes, a função percorre todos os clientes, printa o código do cliente e acrescenta um contador;
	//Esse contador é usado na última mensagem onde diz o total de clientes na casa no momento;
	//Os couts da caixa de texto não tem a parede da esquerda pois qualquer cliente com um ID maior que 1 digito quebraria a formatação, então preferi deixar sem;
	else{
		ptrCliente auxCliente = inicioCliente;
		int contador = 0;
		
		cout << "\033c";
		cout << "##############################################################################" << endl;
		cout << "#                  Opção 2: Listar os clientes                                " << endl;
		cout << "#                                                                             " << endl;
		
		while(auxCliente != NULL){
			cout << "#                  Cliente Código: " << auxCliente->clienteID  << endl;
			auxCliente = auxCliente -> proxCliente;
			contador++;
		}
		cout << "#                  Temos na casa hoje um total de " << contador << " clientes!   " << endl;
		cout << "##############################################################################" << endl;
		cin.get();
		cin.get();	
	}
}

//A função primeiro verifica se o cliente é o primeiro da lista, se afirmativo, a variável global que é o inicio da lista dos clientes vira o próximo cliente e o cliente é deetado;
//Se o cliente não for o primeiro, 3 variáveis de apoio são criadas e um while percorre pela lista sabendo sembre quem veio antes e quem vem depois.
//Achando o cliente desejado, o anterior agora irá apontar pro posterior e o cliente será deletado.
void removeCliente(ptrCliente endCliente){
	if(inicioCliente == endCliente){
		inicioCliente = endCliente -> proxCliente;
		delete endCliente;
	}

	else{
		ptrCliente clienteAtras, clienteMeio, clienteFrente;
		clienteMeio = inicioCliente;

		while(clienteMeio -> proxCliente != NULL){
			clienteAtras = clienteMeio;
			clienteMeio = clienteMeio -> proxCliente;
			clienteFrente = clienteMeio -> proxCliente;

			if (clienteMeio == endCliente){
				clienteAtras -> proxCliente = clienteFrente;
				delete endCliente;
				break;
			}
		}

	}
}

//Função retorna true se o inicio da minha lista de clientes é NULL e falsa se for diferente de NULL;
bool clienteVazia(){
	if (inicioCliente == NULL){
		return true;
	}
	else{
		return false;
	}
}

//A primeira função de procura. Ela recebe um ID de cliente que usa enquanto percorre a lista de clientes para achar o cliente que quer;
//Caso o cliente exista a função retorna o endereço do cliente;
//Caso o cliente não exista, a função retorna NULL;
ptrCliente procuraClienteID(int IDCliente){
	ptrCliente auxCliente = inicioCliente;

	while(auxCliente != NULL){
		if(auxCliente -> clienteID == IDCliente){
			return auxCliente;
		}
		auxCliente = auxCliente -> proxCliente;
	}
	
	return NULL;
}

//Funções PEDIDO

//A função inserePedido tem vários ifs pois tenta prever os erros que o usuário pode cometer: caso não haja nenhum cliente na lista ou caso não exista um cliente com o ID especificado;
//Ela também usa o campo quantidade na struct de pedidos, criando mais um if na função;
//Cada peculiaridade é explicada dentro da função;
void inserePedido(){
	//Se não há nenhum cliente na minha lista, eu retorno um erro para meu usuário;
	if (clienteVazia()){
		cout << "\033c";
		cout << "##############################################################################" << endl;
		cout << "#                  Opção 3: Adicionar um pedido                              #" << endl;
		cout << "#                                                                            #" << endl;
		cout << "#                  No momento não há nenhum cliente cadastrado.              #" << endl;
		cout << "#                  Cadastre pelo menos um cliente para adicionar um pedido.  #" << endl;
		cout << "#                                                                            #" << endl;
		cout << "##############################################################################" << endl;

		cin.get();
		cin.get();
	}

	//Caso exista pelo menos um cliente, eu peço o ID do Cliente para fazer a procura por ele;
	else{
		int IDCliente;
		ptrCliente auxCliente;

		cout << "\033c";
		cout << "##############################################################################" << endl;
		cout << "#                  Opção 3: Adicionar um pedido                              #" << endl;
		cout << "#                                                                            #" << endl;
		cout << "#                  Por favor, digite o código do Cliente.                    #" << endl;
		cout << "#                                                                            #" << endl;
		cout << "##############################################################################" << endl;
		cin >> IDCliente;

		//Crio uma variável com a função procuraClienteID, caso minha função retorne um endereço, eu sigo pedindo o código do pruduto, caso retorne NULL, notifico o erro ao usuário.
		auxCliente = procuraClienteID(IDCliente);

		if (auxCliente != NULL){				
			int IDPedido;
			ptrPedido auxPedido;
			
			cout << "\033c";
			cout << "##############################################################################" << endl;
			cout << "#                  Opção 3: Adicionar um pedido                              #" << endl;
			cout << "#                                                                            #" << endl;
			cout << "#                  Por favor, digite o código do Pedido.                     #" << endl;
			cout << "#                                                                            #" << endl;
			cout << "##############################################################################" << endl;
			cin >> IDPedido;


			//Usando a mesma ideia do procuraClienteID, crio uma variável para o pedido, caso o pedido já exista, só é adicionado um inteiro ao campo qntPedido.
			auxPedido = procuraPedidoID(IDPedido, auxCliente);

			if(auxPedido != NULL){
				int quantidadePedido;
				cout << "\033c";
				cout << "##############################################################################" << endl;
				cout << "#                  Opção 3: Adicionar um pedido                              #" << endl;
				cout << "#                                                                            #" << endl;
				cout << "#                  Por favor, digite a quantidade do pedido.                 #" << endl;
				cout << "#                                                                            #" << endl;
				cout << "##############################################################################" << endl;
				cin >> quantidadePedido;

				auxPedido -> qntPedido = auxPedido -> qntPedido + quantidadePedido;
			}

			//Não existindo um pedido com esse código, eu primeiro verifico se minha lista de pedidos está vazia.
			else
			{
				//Estando vazia, eu crio um novo pedido e aponto o auxCliente -> pedidoCliente para ele.
				if(pedidoVazia(auxCliente)){
					ptrPedido novoPedido = new pedido;
					novoPedido -> pedidoID = IDPedido;
					novoPedido -> proxPedido = NULL;
				
					cout << "\033c";
					cout << "##############################################################################" << endl;
					cout << "#                  Opção 3: Adicionar um pedido                              #" << endl;
					cout << "#                                                                            #" << endl;
					cout << "#                  Por favor, digite a quantidade do pedido.                 #" << endl;
					cout << "#                                                                            #" << endl;
					cout << "##############################################################################" << endl;
					cin >> novoPedido -> qntPedido;
					
					cout << "\033c";
					cout << "##############################################################################" << endl;
					cout << "#                  Opção 3: Adicionar um pedido                              #" << endl;
					cout << "#                                                                            #" << endl;
					cout << "#                  Por favor, digite o valor do produto.                     #" << endl;
					cout << "#                                                                            #" << endl;
					cout << "##############################################################################" << endl;
					cin >> novoPedido -> pedidoValor;

					auxCliente -> pedidoCliente = novoPedido;
				}

				//Não estando vazia, eu vou atribuir ao meu auxPedido o auxCliente -> pedidoCliente, percorrer até achar o último cliente e sigo pedindo as informações necessárias para o cadastro.
				else{	
					auxPedido = auxCliente -> pedidoCliente;

					while(auxPedido -> proxPedido != NULL){
						auxPedido = auxPedido -> proxPedido;
					}

					ptrPedido novoPedido = new pedido;
					novoPedido -> proxPedido = NULL;
					novoPedido -> pedidoID = IDPedido;
					auxPedido -> proxPedido = novoPedido;
					
					cout << "\033c";
					cout << "##############################################################################" << endl;
					cout << "#                  Opção 3: Adicionar um pedido                              #" << endl;
					cout << "#                                                                            #" << endl;
					cout << "#                  Por favor, digite a quantidade do pedido.                 #" << endl;
					cout << "#                                                                            #" << endl;
					cout << "##############################################################################" << endl;
					cin >> novoPedido -> qntPedido;
					
					cout << "\033c";
					cout << "##############################################################################" << endl;
					cout << "#                  Opção 3: Adicionar um pedido                              #" << endl;
					cout << "#                                                                            #" << endl;
					cout << "#                  Por favor, digite o valor do produto.                     #" << endl;
					cout << "#                                                                            #" << endl;
					cout << "##############################################################################" << endl;
					cin >> novoPedido -> pedidoValor;

				}
			}

			cout << "\033c";
			cout << "##############################################################################" << endl;
			cout << "#                  Opção 3: Adicionar um pedido                              #" << endl;
			cout << "#                                                                            #" << endl;
			cout << "#                  Pedido adicionado com sucesso.                            #" << endl;
			cout << "#                                                                            #" << endl;
			cout << "##############################################################################" << endl;
			cin.get();
			cin.get();
		}
		
		//Se procuraClienteID retornar NULL, apresento a mensagem de erro ao usuário.
		else{
			cout << "\033c";
			cout << "##############################################################################" << endl;
			cout << "#                  Opção 3: Adicionar um pedido                              #" << endl;
			cout << "#                                                                            #" << endl;
			cout << "#                  Não existe um cliente com o ID digitado.                  #" << endl;
			cout << "#                                                                            #" << endl;
			cout << "##############################################################################" << endl;
			cin.get();
			cin.get();
		}
	}
}

//A função lista pedido verifica se a lista de clientes esta vazia e se o cliente não fez nenhum pedido, caso falso para ambas, o cout percorrerá os ponteiros exbindo o conteúdo. 
void listaPedido(){
	//Se não há nenhum cliente na minha lista, eu retorno um erro para meu usuário;
	if (clienteVazia()){
		cout << "\033c";
		cout << "##############################################################################" << endl;
		cout << "#                  Opção 4: Listar os pedidos                                #" << endl;
		cout << "#                                                                            #" << endl;
		cout << "#                  No momento não há nenhum cliente cadastrado.              #" << endl;
		cout << "#                  Cadastre pelo menos um cliente e um pedido.               #" << endl;
		cout << "#                                                                            #" << endl;
		cout << "##############################################################################" << endl;

		cin.get();
		cin.get();
	}

	//Caso exista pelo menos um cliente, eu peço o ID do Cliente para fazer a procura por ele;
	else{
		int IDCliente;

		cout << "\033c";
		cout << "##############################################################################" << endl;
		cout << "#                  Opção 4: Listar os pedidos                                #" << endl;
		cout << "#                                                                            #" << endl;
		cout << "#                  Por favor, digite o código do Cliente.                    #" << endl;
		cout << "#                                                                            #" << endl;
		cout << "##############################################################################" << endl;
		cin >> IDCliente;

		
		//Se pedidoVazia(); me retorna TRUE, o cliente ainda não fez nenhum pedido.
		//Caso FALSE, eu irei percorrer pelos pedidos do auxCliente, exibindo o código do pedido, a quantidade e o preço unitário.
		ptrCliente auxCliente = procuraClienteID(IDCliente);

		if (pedidoVazia(auxCliente)){
			cout << "\033c";
			cout << "##############################################################################" << endl;
			cout << "#                  Opção 4: Listar os pedidos                                #" << endl;
			cout << "#                                                                            #" << endl;
			cout << "#                  O cliente ainda não fez nenhum pedido.                    #" << endl;
			cout << "#                                                                            #" << endl;
			cout << "##############################################################################" << endl;
			cin.get();
			cin.get();
		}
		
		else{	
			ptrPedido auxPedido = auxCliente -> pedidoCliente;

			cout << "\033c";
			cout << "##############################################################################" << endl;
			cout << "#                  Opção 4: Listar os pedidos                                 " << endl;
			cout << "#                                                                             " << endl;
			cout << "#                  O cliente " << IDCliente <<" fez os seguintes pedidos:     " << endl;
			cout << "#                                                                             " << endl;

			while(auxPedido != NULL){
				cout << "#                  Código do Pedido: " << auxPedido -> pedidoID  << endl;
				cout << "#                  Quantidade: " << auxPedido -> qntPedido << endl;
				cout << "#                  Preço Unidade: " <<  auxPedido -> pedidoValor << endl;
				cout << "#                                                                         " << endl;
				auxPedido = auxPedido -> proxPedido;
			}
			
			cout << "#                                                                             " << endl;
			cout << "##############################################################################" << endl;
			cin.get();
			cin.get();	 
		}
	}
}

//A função passa por todos os pedidos de um cliente, deletando o anterior e movendo o loop para o próximo pedido.
void removePedido(ptrCliente endCliente){
	ptrPedido auxPedido = endCliente -> pedidoCliente, auxDelete;

	while(auxPedido != NULL){
		auxDelete = auxPedido;
		auxPedido = auxPedido -> proxPedido;
		delete auxDelete;		
	}
}

//Função simples, recebe um ponteiro, se o endereço de pedido é NULL retorna TRUE, caso o contrário, FALSE;
bool pedidoVazia(ptrCliente auxCliente){
	if (auxCliente -> pedidoCliente == NULL){
		return true;
	}
	else{
		return false;
	}
}

//A função procura no cliente um ID específico, retornando o endereço do pedido com esse ID caso ele exista.
ptrPedido procuraPedidoID(int IDPedido, ptrCliente endCliente){
	ptrPedido auxPedido = endCliente -> pedidoCliente;

	while(auxPedido != NULL){
		if (auxPedido -> pedidoID == IDPedido){
			return auxPedido;
		}

		auxPedido = auxPedido -> proxPedido;
	}

	return NULL;
}

//Funções CAIXA

//fechaCliente é uam função muito parecida com listaPedido, porém logo depois de listar o pedido a função chama a removePedido e a removeCliente.
void fechaCliente(){
	if (clienteVazia()){
	cout << "\033c";
	cout << "##############################################################################" << endl;
	cout << "#                  Opção 5: Fechar conta                                     #" << endl;
	cout << "#                                                                            #" << endl;
	cout << "#                  No momento não há nenhum cliente cadastrado.              #" << endl;
	cout << "#                                                                            #" << endl;
	cout << "##############################################################################" << endl;
	
	cin.get();
	cin.get();
	}

	else{
		int IDCliente;

		cout << "\033c";
		cout << "##############################################################################" << endl;
		cout << "#                  Opção 5: Fechar conta                                     #" << endl;
		cout << "#                                                                            #" << endl;
		cout << "#                  Por favor, digite o código do Cliente.                    #" << endl;
		cout << "#                                                                            #" << endl;
		cout << "##############################################################################" << endl;
		cin >> IDCliente;

		ptrCliente auxCliente = procuraClienteID(IDCliente);

		if(pedidoVazia(auxCliente)){
			cout << "\033c";
			cout << "##############################################################################" << endl;
			cout << "#                  Opção 5: Fechar conta                                     #" << endl;
			cout << "#                                                                            #" << endl;
			cout << "#                  O cliente não fez nenhum pedido.                          #" << endl;
			cout << "#                                                                            #" << endl;
			cout << "##############################################################################" << endl;

			removeCliente(auxCliente);

			cin.get();
			cin.get();
		}

		else{
			ptrPedido auxPedido = auxCliente -> pedidoCliente;
			float total = 0;

			cout << "\033c";
			cout << "##############################################################################" << endl;
			cout << "#                  Opção 5: Fechar conta                                      " << endl;
			cout << "#                                                                             " << endl;
			cout << "#                  O cliente " << IDCliente <<" fez os seguintes pedidos:     " << endl;
			cout << "#                                                                             " << endl;

			while(auxPedido != NULL){
				cout << "#                  Código do Pedido: " << auxPedido -> pedidoID  << endl;
				cout << "#                  Quantidade: " << auxPedido -> qntPedido << endl;
				cout << "#                  Preço Unidade: " <<  auxPedido -> pedidoValor << endl;
				cout << "#                                                                         " << endl;
				total = total + ((auxPedido -> pedidoValor) * (auxPedido -> qntPedido));
				auxPedido = auxPedido -> proxPedido;

			}


			cout << "#                  Que totalizam " << total <<" reais.                         " << endl;
			cout << "#                                                                             " << endl;
			cout << "##############################################################################" << endl;
			cin.get();
			cin.get();

			movimento = movimento + total;
			removePedido(auxCliente);
			removeCliente(auxCliente); 
		}

		cout << "\033c";
		cout << "##############################################################################" << endl;
		cout << "#                  Opção 5: Fechar conta                                     #" << endl;
		cout << "#                                                                            #" << endl;
		cout << "#                  Cliente removido com sucesso.                             #" << endl;
		cout << "#                                                                            #" << endl;
		cout << "##############################################################################" << endl;
		cin.get();
	}
}
