# iCortinaSmart2k


esse projeto tem o objetivo de desenvolver uma plataforma para automatização de cortina, foi feito com base na nossa cortina mas é facilmente adaptavel para varios outros tipos.

## 1° Etapa software
serão necessarios os seguintes sotwares:
- node red
- mqtt broker (mosquitto ou similar)
- arduino idle (ou similar)


### 1.5 configurando o software
- mqtt broker

começo recomendando o uso de alguma plataforma para manter o acesso constante dos dispositivos ao broker, recomendação pessoal seria um raspberry pi com o home assistant e instale o mosquitto broker, mas é possivel instalar em outras plataformas ou usar um online fica a seu criterio.

- node red
- 
primeiro instale o dashboard para o node red

segundo, podemos configurar o node red de duas maneiras, importando nosso documento que esta na pasta node red, é um json, somente ncessario clicar no menu ddireito do lado de deploy > import e selecionar o json baixado.


ou manualmente seguindo os diagramas:

no node red foi feito o seguinte flow:
![node red](https://user-images.githubusercontent.com/61274560/119423046-c476a600-bcd8-11eb-8867-ca245ae8ed00.PNG)

onde cada node especifico foi feito uma configuração seguindo o fluxograma:
![diagrama](https://user-images.githubusercontent.com/61274560/119423327-6ac2ab80-bcd9-11eb-863d-262b8f074775.PNG)

a segunda parte do fluxograma foi feita somente para fazer um dashboard no nopde red, existem muitas outras maneiras melhores de controlar o node red, somente foi usado pois era um requerimento nosso.

na segunda parte os botões enviam comandos seguin do o seguinte modelo:

0 - desativa o motor

1 - abrir um poouco

2 - fechar um pouco

3 - abrir tudo

4 - fechar tudo

e o outro somente pega do mqtt o estado da cortina.

- arduino idle

no arduino idle será nec essario instalar as bibliotecas para a placa e para o mqtt.
primeiro para instalar a blbioteca do esp32.
primeiro precisamos colocar a url não oficial da biblioteca.
va em arquivo > preferencias > URLs Adicionais...  e cole o seguinte link (sem aspas) "https://dl.espressif.com/dl/package_esp32_index.json"
agora va em ferramentas > placa > gerenciador de placas e pesquise por esp32 e instale.

agora para instalar a biblioteca de comunicação mqtt.
va em ferramentas > gerenciar biblotecas e pesquise por PubSubClient e instale.

Pronto seu softare foi configurado.

# 2° Etapa Hardware
sera necessario:
- esp32
- fotoresistor
- resisto de 4.7k ohms
- driver ULN2003
- motor de passo 28BYJ-48 5v
- magnetic switch
- placa de solda
- soldador (e solda)
- impressora 3d

primeiro sera necessario realizar a conexão dos componentes seguindo o diagrama:



aops acabar com a montagem dos componentes terá algo parecido com isso:
![IMG_20210524_213438](https://user-images.githubusercontent.com/61274560/119425642-2980ca80-bcde-11eb-89c7-70bbdd4f5483.jpg)

![IMG_20210524_213142](https://user-images.githubusercontent.com/61274560/119425733-474e2f80-bcde-11eb-8b05-ea9527b09df8.jpg)

e com as seguintes dimensões:
![IMG_20210524_212932](https://user-images.githubusercontent.com/61274560/119425757-53d28800-bcde-11eb-93f3-828417276b06.jpg)
![IMG_20210524_212945](https://user-images.githubusercontent.com/61274560/119425766-59c86900-bcde-11eb-9a46-979e519c946a.jpg)
![IMG_20210524_213039](https://user-images.githubusercontent.com/61274560/119425774-5fbe4a00-bcde-11eb-88b8-2ebb14a1ab95.jpg)

para o adaptador para a polia da cortina usamos um feito pelo ususario JohnA: https://www.thingiverse.com/thing:12403

mas provavelmente sera necessario um para sua cortina
no final temos algo como:
![IMG_20210524_213400](https://user-images.githubusercontent.com/61274560/119426105-07d41300-bcdf-11eb-9a8e-78523cae3d4f.jpg)

# 3° etapa comunicação

agora iremos explicar como é feita a domuniação entre o esp e as interfacers de usuario:
## protocolo mqtt
![images](https://user-images.githubusercontent.com/61274560/119426381-7f09a700-bcdf-11eb-94d3-af86a9c6a076.png)

imagem retirada de <https://www.robotyka.net.pl/wp-content/uploads/mqtt_en.png>

é a base de todas comunicações ele usa metodos de publicar e se inscrever em topicos para enviar e receber dados, temos um broker (servidor) central que controla o acesso e regula as mensagens, foram usados os topicos cortina e luz para o projeto
