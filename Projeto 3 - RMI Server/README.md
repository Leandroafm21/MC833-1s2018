# RMI Server

## Arquitetura

### Servidor

**Classe SubjectsDatabase**: Interface remota para RMI.  
**Classe Server**: Implementa SubjectsDatabase. Possui os métodos HandleAuthentication e HandleCommand.

```
HandleAuthentication: recebe um datagrama contendo um caractere indicando se o usuário é Estudante ou Professor e uma senha, no caso de Professor; retorna se a autenticação foi bem sucedida, verificando se a senha é a correta no caso do Professor.  

HandleCommand: recebe um datagrama contendo um caractere indicando uma operação e, dependendo da operação, um código de 5 caracteres indicando o código de uma disciplina.
```

### Cliente

**Classe UserTypePrompt**: Pequena interface que pergunta se o usuário é Estudante ou Professor.  
**Classe PasswordPrompt**: Pequena interface para obter a senha do Professor.  
**Classe MainInterface**: Interface contendo as operações a serem realizadas pelo Usuário, bem como seus argumentos.  
**Classe ResponseInterface**: Interface que exibirá a resposta do servidor.  
**Classe Client**: Implementa a interação entre o cliente e servidor utilizando as interfaces gráficas.  

## Compilação - Windows 10

Depois de setar corretamente a variável de ambiente CLASSPATH para o caminho até a pasta src (inclusive), execute:

```
>javac SubjectsDatabase.java Server.java Disciplina.java
>javac Client.java UserTypePrompt.java PasswordPrompt.java MainInterface.java ResponseInterface.java
```

## Execução - Windows 10

Abra duas janelas separadas. Na primeira, execute:

```
>start rmiregistry
>java -Djava.rmi.server.hostname=127.0.0.1 com.unicamp.redes.server.Server
```

E na segunda:

```
>java com.unicamp.redes.client.Client
```