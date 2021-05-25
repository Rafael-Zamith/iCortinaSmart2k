# iCortinaSmart2k


Esse projeto tem o objetivo de desenvolver uma plataforma para automatização de cortina, foi feito com base na nossa cortina mas é facilmente adaptável para vários outros tipos.

## 1° Etapa software
Serão necessários os seguintes softwares:
- node red
- mqtt broker (mosquitto ou similar)
- arduino idle (ou similar)


### 1.5 Configurando o software
- mqtt broker

Começo recomendando o uso de alguma plataforma para manter o acesso constante dos dispositivos ao broker, recomendação pessoal seria um raspberry pi com o Home Assistant e instale o mosquitto broker, mas é possível instalar em outras plataformas ou usar um online fica a seu critério.

- node red

Primeiro instale o dashboard para o node red

Segundo, podemos configurar o node red de duas maneiras, importando nosso documento que esta na pasta node red, é um JSON, somente necessário clicar no menu direito do lado de deploy > import e selecionar o JSON baixado.


Ou manualmente seguindo os diagramas:

No node red foi feito o seguinte flow:
![node red](https://user-images.githubusercontent.com/61274560/119423046-c476a600-bcd8-11eb-8867-ca245ae8ed00.PNG)

onde cada node especifico foi feito uma configuração seguindo o fluxograma:
![diagrama](https://user-images.githubusercontent.com/61274560/119423327-6ac2ab80-bcd9-11eb-863d-262b8f074775.PNG)

A segunda parte do fluxograma foi feita somente para fazer um dashboard no nopde red, existem muitas outras maneiras melhores de controlar o node red, somente foi usado pois era um requerimento nosso.

A segunda parte os botões enviam comandos seguindo o seguinte modelo:

0 - Desativa o motor

1 - Abrir um pouco

2 - Fechar um pouco

3 - Abrir tudo

4 - Fechar tudo

E o outro somente busca do mqtt o estado da cortina.

- Arduino idle

No arduino idle será necessário instalar as bibliotecas para a placa e para o mqtt.
Primeiro para instalar a biblioteca do esp32.
Primeiro precisamos colocar a url não oficial da biblioteca.
Vá em arquivo > preferencias > URLs Adicionais...  e cole o seguinte link (sem aspas) "https://dl.espressif.com/dl/package_esp32_index.json"
Agora vá em ferramentas > placa > gerenciador de placas e pesquise por esp32 e instale.

Agora para instalar a biblioteca de comunicação mqtt.
vá em ferramentas > gerenciar bibliotecas e pesquise por PubSubClient e instale.

Pronto seu software foi configurado.

# 2° Etapa Hardware
Será necessário:
- esp32
- fotoresistor
- resisto de 4.7k ohms
- driver ULN2003
- motor de passo 28BYJ-48 5v
- magnetic switch
- placa de solda
- soldador (e solda)
- impressora 3d

Primeiro será necessário realizar a conexão dos componentes seguindo o diagrama:



Após acabar com a montagem dos componentes terá algo parecido com isso:
![IMG_20210524_213438](https://user-images.githubusercontent.com/61274560/119425642-2980ca80-bcde-11eb-89c7-70bbdd4f5483.jpg)

![IMG_20210524_213142](https://user-images.githubusercontent.com/61274560/119425733-474e2f80-bcde-11eb-8b05-ea9527b09df8.jpg)

E com as seguintes dimensões:
![IMG_20210524_212932](https://user-images.githubusercontent.com/61274560/119425757-53d28800-bcde-11eb-93f3-828417276b06.jpg)
![IMG_20210524_212945](https://user-images.githubusercontent.com/61274560/119425766-59c86900-bcde-11eb-9a46-979e519c946a.jpg)
![IMG_20210524_213039](https://user-images.githubusercontent.com/61274560/119425774-5fbe4a00-bcde-11eb-88b8-2ebb14a1ab95.jpg)

Para o adaptador para a polia da cortina usamos um feito pelo usuário JohnA: https://www.thingiverse.com/thing:12403

Mas provavelmente será necessário um para sua cortina

No final temos algo como:
![IMG_20210524_213400](https://user-images.githubusercontent.com/61274560/119426105-07d41300-bcdf-11eb-9a8e-78523cae3d4f.jpg)

# 3° Etapa comunicação

Agora iremos explicar como é feita a comunicação entre o esp e as interfaces de usuário:
## Protocolo mqtt
![images](https://user-images.githubusercontent.com/61274560/119426381-7f09a700-bcdf-11eb-94d3-af86a9c6a076.png)

Imagem retirada de <https://www.robotyka.net.pl/wp-content/uploads/mqtt_en.png>

É a base de todas comunicações ele usa métodos de publicar e se inscrever em tópicos para enviar e receber dados, temos um broker (servidor) central que controla o acesso e regula as mensagens, foram usados os tópicos cortina e luz para o projeto.

Para a essencial comunicação com o broker o ESP conta com WIFI embutido e foi usado para conectar a rede.

O node red se comunica usando mqtt ao broker que o mesmo replica as mensagens ao esp.
